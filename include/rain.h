#ifndef RAIN_H
#define RAIN_H

#include "drop.h"
#include <ftxui/screen/screen.hpp>
#include <vector>
#include <memory>

class Rain
{
public:
	explicit Rain(int screenWidth);

	void resize(int screenWidth);
	void fall(ftxui::Screen& screen);

	const std::vector<std::unique_ptr<Drop>>& getDrops() { return m_drops; }

private:
	std::vector<std::unique_ptr<Drop>> m_drops {};

};

#endif