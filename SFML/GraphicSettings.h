#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H
class GraphicSettings {
public:

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;
	
	//Constructors /Destructors
	GraphicSettings();

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

#endif