#include "terminal.h"
#include <ftxui/screen/terminal.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>
#include <iostream>

namespace Terminal
{
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
	}
	
	void printScreen(ftxui::Screen& screen)
	{
		static std::string resetPosition {};

		// Resets the cursor position, preventing the terminal from scrolling
		std::cout << resetPosition << screen.ToString() << std::flush;
		resetPosition = screen.ResetPosition();

		screen.Clear();
	}
}