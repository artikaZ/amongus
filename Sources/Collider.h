#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx,dy); }

	bool CheckCollider(Collider other, sf::Vector2f & direction, float push); // push kintamasis reikalingas objekto stumimo greiciui
	sf::Vector2f GetPosition() const {return body.getPosition(); }
	sf::Vector2f GetHalfSize() const {return body.getSize() / 2.0f; }
private:
	sf::RectangleShape& body;
};

