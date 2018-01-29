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

	void run(std::function<void(double)> onTick)
	{
		//resetMouseState();

		while (mainWindow->isOpen())
		{

			sf::Event event;

			while (mainWindow->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					mainWindow->close();

				else if (event.type == sf::Event::Resized)
				{
					mainWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));

					terminal->resizePix(event.size.width, event.size.height);
				}

				else if (event.type == sf::Event::LostFocus)
					setWindowFocus(false);

				else if (event.type == sf::Event::GainedFocus)
					setWindowFocus(true);

				else if (event.type == sf::Event::MouseButtonPressed)
					setMouseState(event.mouseButton.button, true);

				else if (event.type == sf::Event::MouseButtonReleased)
					setMouseState(event.mouseButton.button, false);

				else if (event.type == sf::Event::MouseMoved)
					setMousePosition(event.mouseButton.x, event.mouseButton.y);

				else if (event.type == sf::Event::KeyPressed)
					keyPressed(event);

				else if (event.type == sf::Event::MouseWheelMoved)
				{
					if (event.mouseWheel.delta < 0)
						setMouseState(Button::WHEEL_UP, true);

					else if(event.mouseWheel.delta > 0)
						setMouseState(Button::WHEEL_DOWN, true);
				}
			}


			mainWindow->clear();

			onTick(double{});

			terminal->render(*mainWindow);

			mainWindow->display();
		}
	}
}


