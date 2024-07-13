#ifndef RAIN_H
#define RAIN_H

#include "drop.h"
#include <ftxui/screen/screen.hpp>
#include <vector>
#include <memory>

class Rain
{
private:
	using Drops = std::vector<std::unique_ptr<Drop>>;

public:
	Rain() = default;

	void resize(int screenWidth);
	void fall(ftxui::Screen& screen);

	const Drops& getDrops() { return m_drops; }

private:
	Drops m_drops {};

};

#endif