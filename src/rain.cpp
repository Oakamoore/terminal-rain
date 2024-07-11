#include "rain.h"

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
		// Adds as many drops as are needed
		for (auto i {m_drops.size()}; i != numDrops; ++i)
			m_drops.emplace_back(std::make_unique<Drop>()); 
	}
	else if (m_drops.size() > numDrops) // Screen width has decreased
	{
		// Destroys any drops that are out of bounds
		std::erase_if(m_drops, [screenWidth] (const auto& drop)
		{
			return drop->getX() > screenWidth;
		});
	}
}

void Rain::fall(ftxui::Screen& screen)
{
	for (auto& drop : m_drops)
	{
		drop->draw(screen);
		drop->fall();
	}
}