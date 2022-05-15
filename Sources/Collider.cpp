#include "Collider.h"


Collider::Collider(sf::RectangleShape& body) :
	body(body)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollider(Collider other, sf::Vector2f & direction, float push)
{
	const sf::Vector2f otherPosition = other.GetPosition();
	const sf::Vector2f otherHalfSize = other.GetHalfSize();
	const sf::Vector2f thisPosition = GetPosition();
	const sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)// tikrinam ar objektai susiduria
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);

				direction.x = 1.0f; // susiduriam su kazkuo is desines
				direction.y = 0.0f; // 0, nes su nieko nesusiduriam y asyje
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1.0f;// susiduriam su kazkuo is kaires
				direction.y = 0.0f; // 0, nes su nieko nesusiduriam y asyje
			}
		}
		
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);

				direction.x = 0.0f;
				direction.y = 1.0f; // susiduriam su kazkuo po mumis
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f; 
			}
		}
		return true;
	}

	return false;
}