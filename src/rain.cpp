#include "rain.h"
#include <ftxui/screen/terminal.hpp>

Rain::Rain(int screenWidth)
{
	resize(screenWidth);
}

void Rain::resize(int screenWidth)
{
	// Used to determine the number of drops needed 
	// based on the current width of the screen 
	static constexpr float dropCoefficient {0.75f};
	
	int numDrops {static_cast<int>(screenWidth * dropCoefficient)};

	// Prevents unnecessary reallocations
	m_drops.reserve(numDrops);

	// The width of the screen has increased,
	// or 'm_drops' is currently empty 
	if (m_drops.size() < numDrops)
	{
		for (auto i {m_drops.size()}; i != numDrops; ++i)
			m_drops.emplace_back(std::make_unique<Drop>()); 
	}
	else if (m_drops.size() > numDrops)
	{
		m_drops.resize(numDrops);
	}
}

void Rain::fall([[maybe_unused]] ftxui::Screen& screen)
{
	
}