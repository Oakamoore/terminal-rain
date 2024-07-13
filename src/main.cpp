#include "rain.h"
#include "terminal.h"
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/loop.hpp>
#include <thread>
#include <chrono>

int main()
{
	using namespace std::chrono_literals;
	
	// Uses the primary screen buffer, ensuring that terminal resizes are responsive
	auto screen {ftxui::ScreenInteractive::FixedSize(ftxui::Terminal::Size().dimx, ftxui::Terminal::Size().dimy)};

	const auto frameDuration {10ms};

	Rain rain {};

	// Sets the initial number of drops
	rain.resize(screen.dimx()); 

	// A blank component used to catch input events
	ftxui::Component component {};

	Terminal::setupInput(screen, component);
	
	// Registers and responds to relevant events
	ftxui::Loop input {&screen, component};

	while (!input.HasQuitted())
	{
		if (Terminal::hasResized(screen))
		{
			Terminal::updateScreen(screen);

			// Re-adjust the number of drops 
			rain.resize(screen.dimx());
		}

		rain.fall(screen);

		Terminal::printScreen(screen);

		std::this_thread::sleep_for(frameDuration);

		// Process any input events 
		input.RunOnce();
	}

	return 0;
}