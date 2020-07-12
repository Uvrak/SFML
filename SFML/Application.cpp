#include "pch.h"
#include "Application.h"

//Initializer Functions
void Application::initVariables()
{
}

void Application::initGraphicsSettings()
{
	this->graphicSettings.loadFromFile("Config/graphics.ini");
}

void Application::initStateData()
{
}

void Application::initWindow()
{
	if (this->graphicSettings.fullscreen) 
	{

	}
	else
	{
		this->pWindow = new sf::RenderWindow(
			this->graphicSettings.resolution,
			this->graphicSettings.title,
			sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize,
			this->graphicSettings.contextSettings
		);
	}
}

Application::Application()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
}

Application::~Application()
{
	delete this->pWindow;
}

void Application::run()
{
	while (this->pWindow->isOpen())
	{
		sf::Event event;
		while (pWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				pWindow->close();
		}
	}
}
