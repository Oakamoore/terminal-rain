#include "terminal.h"
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/event.hpp>
#include <string>
#include <iostream>

namespace Terminal
{
	void setupInput(ftxui::ScreenInteractive& screen, ftxui::Component& component)
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

	bool hasResized(const ftxui::Screen& screen)
	{
		if (screen.dimx() != ftxui::Terminal::Size().dimx || 
			screen.dimy() != ftxui::Terminal::Size().dimy)
		{
			return true;
		}

		return false;
	}

	void updateScreen(ftxui::Screen& screen)
	{
		// Updates the screen to match the terminal's current dimensions
		screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Full());

		screen.Clear();
	}
	
	void printScreen(ftxui::Screen& screen)
	{
		static std::string resetPosition {};

		// Hides the cursor, and resets its position, preventing the terminal from scrolling
		std::cout << "\033[?25l" << resetPosition << screen.ToString() << std::flush;
		resetPosition = screen.ResetPosition();

		screen.Clear();
	}
}