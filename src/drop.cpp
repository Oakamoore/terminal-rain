#include "drop.h"
#include "random.h"
#include <ftxui/screen/terminal.hpp>
#include <array>

namespace Constants
{
	using enum Drop::Distance;
	using ftxui::Color;

	constexpr std::array distances {close, near, far};
	const std::array colors {Color::White, Color::GrayLight, Color::GrayDark};
	constexpr std::array characters {'|', ':', '.'};
	constexpr int minSpeed {1};
	constexpr int maxSpeed {3};
}

Drop::Drop()
{
	reset();
}

void Drop::draw() const
{

}

void Drop::fall()
{

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

}

