#include "drop.h"
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace ftxui;

static auto g_screen {Screen::Create(Dimension::Full(), Dimension::Full())};

TEST_CASE("Draw a drop to the screen")
{
	g_screen.Clear();

	Drop drop {};

	drop.draw(g_screen);

	// The above draw call should result in a pixel at a 
	// given coordinate being set to a non-blank character
	REQUIRE(g_screen.at(drop.getX(), drop.getY()) != " ");
}

TEST_CASE("Determine whether a drop is falling")
{
	g_screen.Clear();

	Drop drop {};
	
	// The drop has yet to exceed the height of the terminal
	while(drop.getY() <= Terminal::Size().dimy)
	{
		drop.fall();
		drop.draw(g_screen);
		
		// As the drop falls its new coordinates
		// are populated by a non-blank character
		REQUIRE(g_screen.at(drop.getX(), drop.getY()) != " ");
	}
}

TEST_CASE("Reset a drop's position in the Y-axis")
{
	Drop drop {};

	// The drop has yet to exceed the height of the terminal
	while (drop.getY() <= Terminal::Size().dimy)
	{
		drop.fall();
	}

	// This call should reset the drop's Y-axis position
	drop.fall();
	
	REQUIRE(drop.getY() == 0);
}