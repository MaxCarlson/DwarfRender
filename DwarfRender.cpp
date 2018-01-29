#include "DwarfRender.h"
#include "Terminal.h"
#include <memory>

namespace dfr
{
	std::unique_ptr<sf::RenderWindow> mainWindow;
	std::unique_ptr<Terminal> terminal;

	sf::RenderWindow * getWindow()
	{
		return dfr::mainWindow.get();
	}

	void init(config_r config)
	{
		
		Font * font = getFont(config.fontTag);

		mainWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(config.width * font->characterSize.first, config.height * font->characterSize.second), 
			config.title, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

		mainWindow->setVerticalSyncEnabled(true);

		sf::Vector2u sizePixel = mainWindow->getSize();
		
		terminal = std::make_unique<Terminal>(config.fontTag, 0, 0);
		terminal->resizePix(sizePixel.x, sizePixel.y);
	}
}


