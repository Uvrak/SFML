#pragma once
#include "State.h"

class U7TilesState :
    public State
{
private:
	//Variables
	std::vector<sf::RectangleShape> shape;

	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	std::map<std::string, std::vector <std::string>> textures;

	std::vector<sf::Texture> text;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initBackground();
	void initTiles();
	void updateTiles();
	void initButtons();

public:
	U7TilesState(StateData* state_data);
	virtual ~U7TilesState();
	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);

};
