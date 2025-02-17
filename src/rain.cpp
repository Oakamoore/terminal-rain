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
				event == ftxui::Event::Character('Q') ||
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

	void resizeScreen(ftxui::Screen& screen)
	{
		// Update the screen to match the terminal's current dimensions
		screen = ftxui::Screen::Create(ftxui::Dimension::Full());
	}
}

void Rain::resize(int screenWidth)
{
	constexpr float dropCoefficient {0.75f};
	
	int numDrops {static_cast<int>(screenWidth * dropCoefficient)};

	// Prevent unnecessary reallocations
	m_drops.reserve(numDrops);

	if (m_drops.size() < numDrops)
	{
		for (auto i {m_drops.size()}; i != numDrops; ++i)
			m_drops.emplace_back(std::make_unique<Drop>()); 
	}
	else if (m_drops.size() > numDrops) 
	{
		// Destroy out of bounds drops
		std::erase_if(m_drops, [screenWidth] (const auto& drop)
		{
			return drop->getX() > screenWidth;
		});
	}
}

void Rain::fall()
{
	// Ensures non-zero initial screen size, and responsive terminal resizes by using the primary screen buffer
	ftxui::ScreenInteractive screen {ftxui::ScreenInteractive::FixedSize(ftxui::Terminal::Size().dimx, ftxui::Terminal::Size().dimy)};
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

		screen.RequestAnimationFrame();

		std::this_thread::sleep_for(frameDuration);

		// Process any input events 
		input.RunOnce();
	}
}