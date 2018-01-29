

#include <SFML\Window.hpp>
#include "../DwarfRender.h"
#include "../FontManager.h"

using namespace dfr;

int main()
{
	config_r cf("SFML WINDOW", "font20x.png", 40, 40, "font");
	registerFont("font", "font20x.png", 20, 20);

	init(cf);

	terminal->setChar(0, 0, { 'b', {55, 55, 0}, {0, 0, 233} });
	terminal->setChar(2, 0, { 196,{ 55, 55, 0 },{ 0, 0, 233 } });
	terminal->setChar(3, 0, { 205,{ 55, 55, 0 },{ 0, 0, 233 } });
	terminal->setChar(255, 0, { 15,{ 55, 55, 0 },{ 0, 55, 233 } });


	run([](double d) {});

	/*
	while (true) {
		

		getWindow()->clear();

		terminal->render(*getWindow());

		getWindow()->display();
	}
	*/
	return 0;
}