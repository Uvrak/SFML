#ifndef TILE_H
#define TILE_H

class Tile
{
private:

protected:
	sf::RectangleShape tile;
public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect);
	virtual ~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);

	void addTile();
	void removeTile();
};

#endif

