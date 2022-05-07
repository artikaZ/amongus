#include <SFML\Graphics.hpp>
#include <iostream>

//using namespace std;

int main()
{
	///*std::*/cout << "New window width:  New window height: " ;

		sf::RenderWindow window(sf::VideoMode(512, 512), "Epic game", sf::Style::Close | sf::Style::Resize);

		while (window.isOpen())
		{
			sf::Event evnt;

			while (window.pollEvent(evnt)) // duoda judint langa per ekrana
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:// leidzia isjungti langa paspaudzius ant "X"
					window.close();
					break;
				case sf::Event::Resized:
					std::cout << "New window width: "<< evnt.size.width << " New window height: "<< evnt.size.height << std::endl;
					//printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
					break;
				}

			
			}
		}

	return 0;
}