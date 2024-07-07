#ifndef DROP_H
#define DROP_H

#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>

class Drop
{
public:
	enum Distance { close, near, far, max_distance };

	Drop();

	void draw(ftxui::Screen& screen) const;
	void fall();

	int getX() const { return m_x; }
	int getY() const { return m_y; }

private:
	void reset();
	bool hasFallen() const;

private:
	int m_x {};
	int m_y {};
	int m_speed {};
	Distance m_distance {};
	ftxui::Color m_color {};
	char m_character {};

};

#endif