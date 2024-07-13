#include "rain.h"
#include <ftxui/screen/screen.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Change the number of rain drops upon screen resize")
{
	constexpr int defaultSize {100};
	constexpr int largerSize {150};
	constexpr int smallerSize {50};

	using namespace ftxui;
	
	auto screen {Screen::Create(Dimension::Fixed(defaultSize), Dimension::Fixed(defaultSize))};

	Rain rain {};

	// Sets the initial number of drops
	rain.resize(screen.dimx());

	const auto previousNumDrops {rain.getDrops().size()};
	const auto previousDropCapacity {rain.getDrops().capacity()};

	SECTION("Screen size increase")
	{
		// Assign a screen of a larger size
		screen = Screen::Create(Dimension::Fixed(largerSize), Dimension::Fixed(largerSize));

		rain.resize(screen.dimx());

		// The size and capacity of 'Rain::m_drops',
		// should be greater post resize, and equal to each other
		REQUIRE(rain.getDrops().size() > previousNumDrops);
		REQUIRE(rain.getDrops().capacity() > previousDropCapacity);
		REQUIRE(rain.getDrops().size() == rain.getDrops().capacity());
	}

	SECTION("Screen size decrease")
	{
		// Assign a screen of a smaller size
		screen = Screen::Create(Dimension::Fixed(smallerSize), Dimension::Fixed(smallerSize));

		rain.resize(screen.dimx()); 

		// The size of 'Rain::m_drops' can decrease or stay the same, 
		// though its capacity should stay the same
		REQUIRE(rain.getDrops().size() <= previousNumDrops);
		REQUIRE(rain.getDrops().capacity() == previousDropCapacity);
		REQUIRE(rain.getDrops().size() <= rain.getDrops().capacity());
	}

	SECTION("Screen size stays the same")
	{
		// Assign a screen of the same size
		screen = Screen::Create(Dimension::Fixed(defaultSize), Dimension::Fixed(defaultSize));

		rain.resize(screen.dimx());

		// Neither the size nor capacity of 'Rain::m_drops' should change
		REQUIRE(rain.getDrops().size() == previousNumDrops);
		REQUIRE(rain.getDrops().capacity() == previousDropCapacity);
		REQUIRE(rain.getDrops().size() == rain.getDrops().capacity());
	}
}

