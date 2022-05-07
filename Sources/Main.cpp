#include <SFML\Graphics.hpp>
#include <iostream>
//#include "Animation.h"

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

};


int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Epic game", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(200.0f, 240.0f));
	player.setPosition(206.0f, 206.0f);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("standing1.png");
	player.setTexture(&playerTexture);
	
	Animation animation(&playerTexture, sf::Vector2u(4, 1), 0.3f);
	
	/*sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 6;
	textureSize.y /= 6;

	player.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0  , textureSize.x, textureSize.y));*/

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;

		while (window.pollEvent(evnt)) // duoda judint langa per ekrana
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:// leidzia isjungti langa paspaudzius ant "X"
				window.close();
				break;
			case sf::Event::Resized:
				//std::cout << "New window width: "<< evnt.size.width << " New window height: "<< evnt.size.height << std::endl;
				//printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)&&player.getGlobalBounds().left>0)
		{
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)&&player.getGlobalBounds().left < window.getSize().x-player.getGlobalBounds().width)
		{
			player.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.move(0.0f, 0.1f);
		}

		animation.Update(0, deltaTime);
		player.setTextureRect(animation.uvRect);

		window.clear(sf::Color(150,150,150));
		window.draw(player);
		window.display();
	}

	return 0;
}