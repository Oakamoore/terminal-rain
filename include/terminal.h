#ifndef TERMINAL_H
#define TERMINAL_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>

namespace Terminal
{
	void setupInput(ftxui::ScreenInteractive& screen, ftxui::Component& component);
	bool hasResized(const ftxui::Screen& screen);
	void updateScreen(ftxui::Screen& screen);
	void printScreen(ftxui::Screen& screen);
}

#endif