#ifndef APPLICATION_H
#define APPLICATION_H

#include "GraphicSettings.h"
#include "Tile.h"
#include "Button.h"

class Application
{
private:
	GraphicSettings graphicSettings;
	sf::RenderWindow* pWindow;
	sf::Clock dtClock;
	float dt;

	sf::Texture texture;
	Tile *tile;
	sf::RectangleShape shape;

	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	int gridSize;

	//Initializer Functions
	void initVariables();
	void initGraphicsSettings();
	void initStateData();
	void initFont();
	void initWindow();

public:
	//Constructors /Destructors
	Application();
	virtual ~Application();

	//Functions
	void updateSFMLEvents();
	void updateDt();
	void updateMousePositions();
	void update();
	void render();
	void run();
};

#endif

