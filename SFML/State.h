#pragma once

#include "Button.h"
#include "GraphicSettings.h"
class Player;
class GraphicstSettings;
class State;

class StateData
{
public:
	StateData() {}

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Ressources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();
	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();
	//Functions

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updatekeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};





