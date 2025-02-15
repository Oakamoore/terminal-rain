#include "rain.h"
#include "terminal.h"
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/loop.hpp>
#include <thread>
#include <chrono>

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
	// Uses the primary screen buffer, ensuring that terminal resizes are responsive
	auto screen {ftxui::ScreenInteractive::FixedSize(ftxui::Terminal::Size().dimx, ftxui::Terminal::Size().dimy)};

	// A blank component used to catch input events
	ftxui::Component component {};

	Terminal::setupInput(screen, component);

	// Set the initial number of drops
	resize(screen.dimx());

	using namespace std::chrono_literals;
	const auto frameDuration {30ms};

	ftxui::Loop input {&screen, component};

	while (!input.HasQuitted())
	{
		if (Terminal::hasResized(screen))
		{
			Terminal::updateScreen(screen);

			// Re-adjust the number of drops 
			resize(screen.dimx());
		}

		for (auto& drop : m_drops)
		{
			drop->draw(screen);
			drop->fall();
		}

		Terminal::printScreen(screen);

		std::this_thread::sleep_for(frameDuration);

		// Process any input events 
		input.RunOnce();
	}
}