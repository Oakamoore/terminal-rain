#include "rain.h"
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/event.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>

namespace
{
	void setupQuitEvent(ftxui::ScreenInteractive& screen, ftxui::Component& component)
	{
		component = ftxui::Renderer([] { return ftxui::text(""); });

		// Decorates the component to catch a 'quit' event
		component |= ftxui::CatchEvent([&] (ftxui::Event event)
		{
			if (event == ftxui::Event::Character('q') ||
				event == ftxui::Event::Escape)
			{
				screen.ExitLoopClosure()();
				return true;
			}

			return false;
		});
	}

	bool hasTerminalResized(const ftxui::Screen& screen)
	{
		if (screen.dimx() != ftxui::Terminal::Size().dimx ||
			screen.dimy() != ftxui::Terminal::Size().dimy)
		{
			return true;
		}

		return false;
	}

	void printScreen(ftxui::Screen& screen)
	{
		static std::string resetPosition {};

		// Hides the cursor, and resets its position, preventing the terminal from scrolling
		std::cout << "\033[?25l" << resetPosition << screen.ToString() << std::flush;
		resetPosition = screen.ResetPosition();

		screen.Clear();
	}

	void resizeScreen(ftxui::Screen& screen)
	{
		// Update the screen to match the terminal's current dimensions
		screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Full());

		printScreen(screen);
	}
}

void Rain::resize(int screenWidth)
{
	constexpr float dropCoefficient {0.75f};
	
	int numDrops {static_cast<int>(screenWidth * dropCoefficient)};

	// Prevents unnecessary reallocations
	m_drops.reserve(numDrops);

	// The width of the screen has increased, or 'm_drops' is currently empty 
	if (m_drops.size() < numDrops)
	{
		// Adds as many drops as are needed
		for (auto i {m_drops.size()}; i != numDrops; ++i)
			m_drops.emplace_back(std::make_unique<Drop>()); 
	}
	else if (m_drops.size() > numDrops) 
	{
		// Destroys any drops that are out of bounds
		std::erase_if(m_drops, [screenWidth] (const auto& drop)
		{
			return drop->getX() > screenWidth;
		});
	}
}

void Rain::fall()
{
	// Use the primary screen buffer, ensuring that terminal resizes are responsive
	// Ensures the initial screen size is equal to the terminal
	auto screen {ftxui::ScreenInteractive::FixedSize(ftxui::Terminal::Size().dimx, ftxui::Terminal::Size().dimy)};

	// A blank component used to catch input events
	ftxui::Component component {};

	setupQuitEvent(screen, component);

	// Set the initial number of drops
	resize(screen.dimx());

	using namespace std::chrono_literals;
	const auto frameDuration {30ms};

	ftxui::Loop input {&screen, component};

	while (!input.HasQuitted())
	{
		if (hasTerminalResized(screen))
		{
			resizeScreen(screen);

			// Re-adjust the number of drops 
			resize(screen.dimx());
		}

		for (auto& drop : m_drops)
		{
			drop->draw(screen);
			drop->fall();
		}

		printScreen(screen);

		std::this_thread::sleep_for(frameDuration);

		// Process any input events 
		input.RunOnce();
	}
}