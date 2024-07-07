#include "drop.h"
#include "random.h"
#include <ftxui/screen/terminal.hpp>
#include <array>

namespace Constants
{
	using ftxui::Color;

	const std::array colors {Color::White, Color::GrayLight, Color::GrayDark};
	constexpr std::array characters {'|', ':', '.'};
	constexpr int minSpeed {1};
	constexpr int maxSpeed {3};
}

Drop::Drop()
{
	reset();
}

void Drop::draw(ftxui::Screen& screen) const
{
	// Modify the pixel at a given screen coordinate 
	screen.PixelAt(m_x, m_y).character = m_character;
	screen.PixelAt(m_x, m_y).foreground_color = m_color;
}

void Drop::fall()
{
	if (hasFallen())
		reset();
	else
		m_y += m_speed;
}

void Drop::reset()
{
	// Resets the attributes of a 'Drop' object
	m_x = Random::get(0, ftxui::Terminal::Size().dimx);
	m_y = 0;
	m_distance = static_cast<Distance>(Random::get(0, max_distance - 1));
	m_character = Constants::characters[m_distance];
	m_color = Constants::colors[m_distance];
	m_speed = Random::get(Constants::minSpeed, Constants::maxSpeed);
}

bool Drop::hasFallen() const
{
	// The terminal's current height threshold has been exceeded
	return (m_y > ftxui::Terminal::Size().dimy ? true : false);
}

