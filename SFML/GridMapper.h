#pragma once
#include "State.h"
#include <SFML\Graphics\Rect.hpp>

class GridMapper :
    public State
{
private:
	//Variables
	std::vector<std::vector<std::vector<sf::RectangleShape>>> grid;
	std::vector<std::vector<std::vector<sf::RectangleShape*>>> horizontalLines;

	unsigned gridSizeX = 10;
	unsigned gridSizeY = 10;

	sf::Vector2u mousePosHorizontal;

	sf::RectangleShape horizontalHit;

	sf::Event ev;

	bool isRendered;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	GridMapper(StateData* state_data);
	virtual ~GridMapper();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};


