#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_LENGHT = 1200.0f;
static const float VIEW_HEIGHT = 800.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) // keiciant lango dydi, objektas nepraranda proporciju
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_LENGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Epic game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_LENGHT, VIEW_HEIGHT));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("standing2.png");

	Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f, 100.0f);

	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 100.0f), sf::Vector2f(300.0f, 0.0f));

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
				ResizeView(window, view);
				break;
			}
		}

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)&&player.getGlobalBounds().left>0)
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
		}*/


		player.Update(deltaTime);

		platform1.GetCollider().CheckCollider(player.GetCollider(), 0.0f);
		platform2.GetCollider().CheckCollider(player.GetCollider(), -1.0f);

		view.setCenter(player.GetPosition()); // kamera sekioja zaideja

		window.clear(sf::Color(100,150,200));
		window.setView(view);
		player.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);
		window.display();
	} 

	return 0;
}