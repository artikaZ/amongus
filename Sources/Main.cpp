#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_LENGTH = 1200.0f;
static const float VIEW_HEIGHT = 800.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) // keiciant lango dydi, objektas nepraranda proporciju
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_LENGTH * aspectRatio, VIEW_HEIGHT);
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Epic game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_LENGTH, VIEW_HEIGHT));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("standing2.png"); //ant zaidejo uzdeda textura is pasirinkto failo

	Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f, 100.0f, 200.0f); // 200 yra smfl unit'ai, 1 = 1pixel

	std::vector<Platform> platforms;

	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(200.0f, 200.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(300.0f, 0.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(200.0f, 500.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 50.0f), sf::Vector2f(-700.0f, 250.0f)));

	/*Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(150.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(300.0f, 0.0f));
	Platform platform3(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f));*/


	float deltaTime = 0.0f;
	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) // reikalingas, kad nebutu bugo kai langa perstumi ant ekrano 
		{
			deltaTime = 1.0f / 20.0f;
		} 

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

		sf::Vector2f direction;

		/*for (int i = 0; i < platforms.size(); i++)
		{
			Platform& platform = platforms[i];
		}*/

		for (Platform& platform : platforms)
		{
			if (platform.GetCollider().CheckCollider(player.GetCollider(),direction, 1.0f))
			{
				player.OnCollission(direction);
			}
		}

		view.setCenter(player.GetPosition()); // kamera sekioja zaideja

		window.clear(sf::Color(150,150,150));
		window.setView(view);
		player.Draw(window);

		for (Platform& platform : platforms)
			platform.Draw(window);

		window.display();
	} 

	return 0;
}