#pragma once
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};
namespace gui
{
	class Button
	{
	private:
		// Variables
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		// Constructors /Destructors
		Button(
			float x, float y, float width, float height,
			sf::Font *font, std::string text = "Text", int fontSize = 30,
			sf::Color idle_color = sf::Color(70, 70, 70, 0), sf::Color hover_color = sf::Color(150, 150, 150, 0), sf::Color active_color = sf::Color(20, 20, 20, 0),
			sf::Color text_idle_color = sf::Color(70, 70, 70, 200), sf::Color text_hover_color = sf::Color(250, 250, 250, 200), sf::Color text_active_color = sf::Color(20, 20, 20, 50),
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent
		);

		~Button();
		// Accessors
		const bool isPressed() const;

		// Functions
		void update(const sf::Vector2f &mousePos);
		void render(sf::RenderTarget& target);
	};

}


