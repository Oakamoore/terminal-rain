#ifndef TERMINAL_H
#define TERMINAL_H

#include <ftxui/screen/screen.hpp>

namespace Terminal
{
	bool hasResized(const ftxui::Screen& screen);
	void updateScreen(ftxui::Screen& screen);
	void printScreen(ftxui::Screen& screen);
}

#endif