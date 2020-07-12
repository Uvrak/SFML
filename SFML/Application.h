#ifndef APPLICATION_H
#define APPLICATION_H

#include "GraphicSettings.h"

class Application
{
private:
	GraphicSettings graphicSettings;
	sf::RenderWindow* pWindow;

	//Initializer Functions
	void initVariables();
	void initGraphicsSettings();
	void initStateData();
	void initWindow();

public:
	//Constructors /Destructors
	Application();
	virtual ~Application();

	//Functions
	void run();
};

#endif

