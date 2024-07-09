#include "drop.h"
#include "rain.h"
#include "terminal.h"
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	auto screen {ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Full())};

	Rain rain {};
	
	// Sets the initial number of drops
	rain.resize(screen.dimx()); 

	while (true)
	{
		if (Terminal::hasResized(screen))
		{
			Terminal::updateScreen(screen);

			// Re-adjust the number of drops 
			rain.resize(screen.dimx());
		}

		rain.fall(screen);

		Terminal::printScreen(screen);

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1ms);
	}

	return 0;
}