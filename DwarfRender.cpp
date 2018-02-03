#include "DwarfRender.h"
#include "Terminal.h"

#include <imgui.h>
#include <imgui-sfml.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <chrono>

typedef std::chrono::milliseconds::rep TimePoint;
inline TimePoint now() {
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now().time_since_epoch()).count();
}

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

	void run(std::function<void(double)>& onTick)
	{
		resetMouseState();

		ImGui::SFML::Init(*mainWindow);

		sf::Clock deltaClock;
		while (mainWindow->isOpen())
		{
			sf::Event event;

			while (mainWindow->pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(event);

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
					setMousePosition(event.mouseMove.x, event.mouseMove.y);

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

			static double deltaT = 0.0;
			static const double MS_PER_UPDATE = 17.0;

			while (deltaT < MS_PER_UPDATE)
			{
				deltaT += static_cast<double>(now());
			}

			ImGui::SFML::Update(*mainWindow, deltaClock.restart());

			mainWindow->clear();

			onTick(MS_PER_UPDATE);

			terminal->render(*mainWindow);
			ImGui::SFML::Render(*mainWindow);

			mainWindow->display();
		}
	}
}


