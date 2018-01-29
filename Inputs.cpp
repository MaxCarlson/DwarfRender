#include "Inputs.h"
#include <array>

namespace dfr
{
	std::vector<sf::Event> events;

	namespace mstate
	{
		bool isWindowFocused = true;
		std::array<bool, 7> mouseButtonsPressed;
		int mouseX = 0;
		int mousey = 0;
	}

	bool isWindowFocused()
	{
		return mstate::isWindowFocused;
	}

	void setWindowFocus(const bool f)
	{
		mstate::isWindowFocused = f;
	}

	void resetMouseState()
	{
		std::fill(mstate::mouseButtonsPressed.begin(), mstate::mouseButtonsPressed.end(), false);
		mstate::mouseX = 0;
		mstate::mousey = 0;
	}

	void setMousePosition(const int x, const int y)
	{
		mstate::mouseX = x;
		mstate::mousey = y;
	}

	std::pair<int, int> getMousePosition()
	{
		return std::make_pair(mstate::mouseX, mstate::mousey);
	}

	void setMouseState(const int button, const bool state)
	{
		mstate::mouseButtonsPressed[button] = state;
	}

	bool getMouseState(const int button)
	{
		return mstate::mouseButtonsPressed[button];
	}

	void keyPressed(sf::Event & event)
	{
		events.emplace_back(event);
	}
}