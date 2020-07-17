#include "pch.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	//this->tile.setFillColor(sf::Color::White);
	//this->tile.setOutlineThickness(1.f);
	//this->tile.setOutlineColor(sf::Color::Red);
	this->tile.setPosition(x, y);
	this->tile.setTexture(&texture);
	this->tile.setTextureRect(texture_rect);

}

Tile::~Tile()
{
}

//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tile);
}

void Tile::addTile()
{
}

void Tile::removeTile()
{
}