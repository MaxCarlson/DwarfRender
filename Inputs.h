#pragma once
#include <SFML\Graphics.hpp>

namespace dfr
{
	enum Button
	{
		LEFT,
		RIGHT,
		MIDDLE,
		SIDE1,
		SIDE2,
		WHEEL_UP,
		WHEEL_DOWN
	};

	extern bool isWindowFocused();

	extern void setWindowFocus(const bool f);

	extern void resetMouseState();

	extern void setMousePosition(const int x, const int y);

	extern std::pair<int, int> getMousePosition();

	extern void setMouseState(const int button, const bool state);
	extern bool getMouseState(const int button);

	extern void keyPressed(sf::Event &event);

	struct KeyPressed
	{
		KeyPressed() = default;
		KeyPressed(sf::Event e) : event(e) {}

		sf::Event event;
	};
}

