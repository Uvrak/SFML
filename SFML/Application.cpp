#include "pch.h"
#include "Application.h"

//Initializer Functions
void Application::initVariables()
{
	this->initFont();
	if (!texture.loadFromFile("d:/Tiles/tiles0000_00.png"))
		std::cout << "Fehler\n";
	std::cout << texture.getSize().x << " " << texture.getSize().y << "\n";
	//sf::IntRect intRect(0, 0, 8, 8);
	//tile = new Tile(10, 10, 8, texture, intRect);
	shape.setSize(sf::Vector2f(this->texture.getSize()));
	//shape.setPosition(sf::Vector2f(100.f, 100.f));
	//shape.setFillColor(sf::Color::Red);
	//shape()
	shape.setTexture(&texture);
	//shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
	buttons["UP"] = new gui::Button(100.f, 100.f, 250.f, 50.f, &font, "vergrößern");
	buttons["DOWN"] = new gui::Button(100.f, 200.f, 250.f, 50.f, &font, "verkeinern");
	gridSize = 8;
}

void Application::initGraphicsSettings()
{
	this->graphicSettings.loadFromFile("Config/graphics.ini");
}

void Application::initStateData()
{
}

void Application::initFont()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void Application::initWindow()
{
	//graphicSettings.fullscreen = true;
	if (this->graphicSettings.fullscreen) 
	{
		this->pWindow = new sf::RenderWindow(
			this->graphicSettings.resolution,
			this->graphicSettings.title,
			sf::Style::Fullscreen,
			this->graphicSettings.contextSettings
		);
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
	pWindow->setFramerateLimit(120);

}

// Consturctors / Destructors
Application::Application()
{
	
	this->initGraphicsSettings();
	this->initWindow();

	this->initVariables();
	
}

Application::~Application()
{
	delete this->tile;
	
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	delete this->pWindow;
}

void Application::updateSFMLEvents()
{
	sf::Event event;
	while (pWindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			pWindow->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->pWindow->close();

}

void Application::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
	//system("cls");
	//std::cout << this->dt << "\n";
}

void Application::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->pWindow);
	this->mousePosView = this->pWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->pWindow));
	this->mousePosGrid =
		sf::Vector2u(
			static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
			static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
		);
}



void Application::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions();
	//this->updatekeytime(dt);
	
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
	{
		i->second->update(mousePosView);	
		if (i->second->isPressed())
		{
			if (i->first._Equal("UP"))
			{
				this->shape.setSize(this->shape.getSize() * 2.f);
			}
			else if (i->first._Equal("DOWN"))
			{
				this->shape.setSize(this->shape.getSize() / 2.f);
			}
			std::cout << i->first;
			std::this_thread::sleep_for(std::chrono::microseconds(300000));

		}
		
	}
		
}

void Application::render()
{
	this->pWindow->clear();
	;
	pWindow->draw(shape);
	//this->tile->render(*this->pWindow);
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		i->second->render(*pWindow);

	//REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 10, this->mousePosView.y - 10);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << "x:= " << this->mousePosView.x << " " << "y= " << this->mousePosView.y;
	mouseText.setString(ss.str());

	this->pWindow->draw(mouseText);


	this->pWindow->display();

	
	
}

void Application::run(){
	while (this->pWindow->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
