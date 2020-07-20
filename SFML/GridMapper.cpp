#include "pch.h"
#include "GridMapper.h"

//Initializer functions
void GridMapper::initVariables()
{
	isRendered = false;
}

void GridMapper::initBackground()
{
	this->grid.resize(this->gridSizeX);
	for (auto x = 0; x < this->gridSizeX; x++)
	{
		for (auto y = 0; y < this->gridSizeY; y++)
		{
			this->grid.resize(this->gridSizeY);
			this->grid[x].push_back(std::vector<sf::RectangleShape>());

			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(this->gridSize, this->gridSize));
			rect.setPosition(sf::Vector2f(x * this->gridSize, y * this->gridSize));
			rect.setFillColor(sf::Color(255, 255, 255, 200));
			rect.setOutlineThickness(1.f);
			rect.setOutlineColor(sf::Color::Green);
			this->grid[x][y].push_back(rect);
			this->grid.push_back(std::vector<std::vector< sf::RectangleShape>>());
			
		}
	}
	for (auto x = 0; x <= this->gridSizeX; x++)
	{
		this->horizontalLines.resize(this->gridSizeX + 1);
		this->horizontalLines[x].push_back(std::vector<sf::RectangleShape*>());
		
		for (auto y = 0; y <= this->gridSizeY; y++)
		{
			this->horizontalLines.resize(this->gridSizeY + 1);
			this->horizontalLines[x].push_back(std::vector<sf::RectangleShape*>());

			this->horizontalLines[x][y].push_back(new sf::RectangleShape());
			this->horizontalLines[x][y].at(0)->setSize(sf::Vector2f(4, this->gridSize));
			this->horizontalLines[x][y].at(0)->setPosition(sf::Vector2f(x * this->gridSize - 2, y * gridSize));
			this->horizontalLines[x][y].at(0)->setFillColor(sf::Color::Transparent);

			
		}
	}

}

void GridMapper::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GridMapper::initKeybinds()
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

void GridMapper::initButtons()
{
	
}

//Constructors /Destructors
GridMapper::GridMapper(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

GridMapper::~GridMapper()
{
	//for (int i = 0; i < horizontalLines.size(); i++)
	//{
		//delete &this->horizontalLines[i];
	//}

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

//Functions
void GridMapper::updateInput(const float& dt)
{
	
	if (isRendered) {
		while (this->stateData->window->waitEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				this->stateData->window->close();
				break;
			case sf::Event::MouseButtonPressed:
				std::cout << "Button clicked";

				sf::RectangleShape line;
				//line.setSize(sf::Vector2f(3, this->gridSize));
				//line.setFillColor(sf::Color::Blue);
				//line.setPosition(this->mousePosGrid.x * this->gridSize - 2, this->mousePosGrid.y * this->gridSize);
				//horizontalLines.push_back(line);
				//std::cout << horizontalLines.size();
				//unsigned xMin = static_cast<unsigned>(this->horizontalLines[mousePosGrid.x][mousePosGrid.y].at(0).getLocalBounds().width) - 10;
				//unsigned xMax = static_cast<unsigned>(this->horizontalLines[mousePosGrid.x][mousePosGrid.y].at(0).getLocalBounds().width) + 10;;

				
				horizontalHit.setSize(sf::Vector2f(20, 20));
				horizontalHit.setPosition(mousePosView.x - 10.f, mousePosView.y - 10.f);
				horizontalHit.setFillColor(sf::Color::Magenta);
				int temp = (this->mousePosView.x + this->gridSize) / this->gridSize;
				if (
					(horizontalHit.getGlobalBounds().intersects(this->horizontalLines[mousePosGrid.x ][mousePosGrid.y].at(0)->getGlobalBounds()))
						|| (this->horizontalLines[mousePosGrid.x + 1][mousePosGrid.y].at(0)->getGlobalBounds().intersects(horizontalHit.getGlobalBounds()))
					)
					
					{
						float xPos = mousePosGrid.x;
						if(this->horizontalLines[mousePosGrid.x + 1][mousePosGrid.y].at(0)->getGlobalBounds().intersects(horizontalHit.getGlobalBounds()))
						{
							xPos = mousePosGrid.x + 1;
						}
					
						std::cout << temp;
						//std::cout << (this->horizontalLines[mousePosGrid.x][mousePosGrid.y].at(0).getGlobalBounds().left) << "\n";
						if (horizontalLines[xPos][this->mousePosGrid.y].at(0)->getFillColor() == sf::Color::Transparent)
							horizontalLines[xPos][this->mousePosGrid.y].at(0)->setFillColor(sf::Color::Blue);
						else
							horizontalLines[xPos][this->mousePosGrid.y].at(0)->setFillColor(sf::Color::Transparent);
					};

				
				std::cout << "\n";
				break;
			}


			break;
		}
	}
	
	
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
		this->stateData->window->setKeyRepeatEnabled(false);
		std::cout << this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n";

		
		
	}*/
	
}

void GridMapper::updateButtons()
{
	
}


void GridMapper::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();


	//system("cls");
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void GridMapper::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void GridMapper::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	//this->renderButtons(*target);
	for (int x = 0; x < this->gridSizeX; x++)
	{
		for (int y = 0; y < this->gridSizeY; y++)
		{
				target->draw(this->grid[x][y].at(0));

		}
	}

	for (auto x = 0; x <= this->gridSizeX; x++) 
	{
		for (auto y = 0; y <= this->gridSizeY; y++)
		{
			target->draw(*horizontalLines[x][y].at(0));
		}
	}

	target->draw(this->horizontalHit);

	isRendered = true;
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

