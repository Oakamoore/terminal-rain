#ifndef RAIN_H
#define RAIN_H

#include "drop.h"
#include <ftxui/screen/screen.hpp>
#include <vector>
#include <memory>

class Rain
{
public:
	Rain();

	void resize();
	void fall(ftxui::Screen& screen);

private:
	std::vector<std::unique_ptr<Drop>> m_drops {};

};

#endif