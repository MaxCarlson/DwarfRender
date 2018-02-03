
/*
#include <SFML\Window.hpp>
#include "../DwarfRender.h"
#include "../FontManager.h"
#include <imgui.h>
#include <imgui-SFML.h>

using namespace dfr;

int main()
{
	config_r cf("SFML WINDOW", "DwarfTex.png", 40, 40, "font");
	registerFont("font", "DwarfTex.png", 16, 16);
	initInputs(16, 16);

	init(cf);

	ImGui::SFML::Init(*getWindow());
	//getWindow()->resetGLStates();

	terminal->setChar(0, 0, { 'b', {55, 55, 0}, {0, 0, 233} });
	terminal->setChar(2, 0, { 196,{ 55, 55, 0 },{ 0, 0, 233 } });
	terminal->setChar(3, 0, { 205,{ 55, 55, 0 },{ 0, 0, 233 } });
	terminal->setChar(25, 0, { 570,{ 255, 55, 0 },{ 233, 55, 233 } });


	run([](double d) {});

	return 0;
}
*/