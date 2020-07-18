#include "pch.h"
#include "U7TilesState.h"
#include "FileSystem.h"

//Initializer functions
void U7TilesState::initVariables()
{
	initTiles();
}


void U7TilesState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void U7TilesState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void U7TilesState::initBackground()
{
	background.setSize(sf::Vector2f(this->window->getSize()));
	background.setFillColor(sf::Color::Black);
}
void U7TilesState::initTiles()
{
	std::map<std::string, int> tileMap;
   FileSystem::TraverseFilesUsingDFS("D:\\Tiles", tileMap);
   int counter = -1;
   std::string preveousTile = "";
   for (auto i = tileMap.begin(); i != tileMap.end(); i++)
   {
	   std::vector<std::string> vec = FileSystem::split(i->first, '_');
	   std::stringstream ss;
	   ss << counter;

	   //if(vec[0] != preveousTile)
			//textures[ss.str()] =  std::vector<std::string>();

	   //std::cout << vec[0] << " == " << preveousTile << "\n";
	   if (vec[0] == preveousTile)
	   {
		   textures[ss.str()].push_back(i->first);
		   //std::cout << "        ";
	   }
	   else
	   {
		   //std::cout << ss.str() << ": ";
		   counter++;
	   }

	   preveousTile = vec[0];
	   //std::cout << i->first <<  "\n";
   }
	   //std::cout << i->first << " : " << i->second << std::endl;
}
void U7TilesState::initButtons()
{
	int bottom = 300;
	int left = 0;
	int counter = 0;
	while (left < background.getSize().x - 50.f && bottom < this->background.getSize().y - 100.f) 
	{
		std::stringstream ss;
		ss << counter;
		
		this->buttons[ss.str()] = new gui::Button
		(
			left, bottom, 50, 50,
			&font, ss.str()
		);
		
		counter++;
		bottom += 50;

		if (bottom > this->background.getSize().y - 100.f)
		{
			bottom = 300;
			left += 50;
		}
			
	}
	
}

//Constructors /Destructors
U7TilesState::U7TilesState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();

	this->initFonts();
	this->initKeybinds();
	this->initBackground();
	this->initButtons();
}

U7TilesState::~U7TilesState()
{

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
	//for (auto i : text)
		//delete i.second;
}

//Functions
void U7TilesState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {

	}
}

void U7TilesState::updateTiles()
{
	system("cls");

	float x = 0.f;
	float y = 0.f;
	std::cout << text.size() << "\n";
	for (auto i = 0; i < text.size(); i++) {
		sf::RectangleShape sh;
		std::cout << &text[i] << "\n";
		sh.setSize(sf::Vector2f(32.f, 32.f));
		sh.setPosition(x, y);
		sh.setOutlineThickness(1.f);
		sh.setOutlineColor(sf::Color::Green);
		x += 32.f;
		if (x == this->background.getSize().x - 32.f)
		{
			x = 0.f;
			y += 32.f;
		}
		sh.setTexture(&text[i]);
		shape.push_back(sh);
		
	}
		

}

void U7TilesState::updateButtons()
{
	//this->window->setKeyRepeatEnabled(false);
	/*Updates all the buttons in the state and handles their functionality.*/
	for (auto& it : this->buttons) 
	{
		it.second->update(this->mousePosView);
		if (it.second->isPressed())
		{
			//std::cout << it.first << "\n";
			std::this_thread::sleep_for(std::chrono::microseconds(300000));

			int counter = 0;
			
			std::cout << textures[it.first].size() << "\n";
			system("cls");
			for (auto i = 0; i < textures[it.first].size(); i++)
			{
				std::cout << textures[it.first][i] << "\n";
				std::stringstream ss;
				ss << counter;
				sf::Texture t;
				t.loadFromFile("d:/Tiles/" + textures[it.first][i]);
				this->text.push_back(t);

				std::cout << it.first << "\n";
				counter++;
			}
			//for (auto i : textures[it.first])
			//{
				//std::stringstream ss;
				//ss << counter;
				//this->text[ss.str()] = new sf::Texture();
				//std::cout << it.first << "\n";
				//counter++;
			//}
				

			this->updateTiles();
		}
	}

}


void U7TilesState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();


	//system("cls");
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void U7TilesState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void U7TilesState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	for (auto &i : shape)
	target->draw(i);

	this->renderButtons(*target);

	//REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);

}

