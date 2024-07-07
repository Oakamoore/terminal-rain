#ifndef DROP_H
#define DROP_H

#include <ftxui/screen/color.hpp>

class Drop
{
public:
	Drop();

	void draw(/*ftxui::Screen& screen*/) const;		// Draw 'm_character' to the terminal
	void fall();									// Increment 'm_y' by a given 'm_speed'

private:
	enum Distance { close, near, far, max_distance };
	
	void reset();									// Reset the drop's attributes
	bool hasFallen() const;							// When 'm_y' is equal to 'Terminal::width'

private:
	int m_x {};
	int m_y {};
	int m_speed {};
	Distance m_distance {};
	ftxui::Color m_color {};
	char m_character {};

};

#endif