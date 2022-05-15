#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime) 
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 120.0f)); // zaidejo dimensijos
	body.setOrigin(body.getSize() / 2.0f);// spawnina playeri centre
	body.setPosition(206.0f, 206.0f); // lango koordinate, kur bus atspawnintas zaidejas
	body.setTexture(texture); // ant zaidejo uzdedama textura
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//velocity.x *= 0.5f; //atleidus A arba D, zaidejas ne iskarto sustos

	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x -= speed  * 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x += speed  * 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump) // canJump tai pat turi buti true, kad leistu zaidejui pasokti
	{
		canJump = false;

		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); // sokimo impulso formule
		// square root ( 2.0f * gravity * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime; //gravitacija

	if (velocity.x == 0.0f)
	{
		row = 0; //stovejimo kadrai
	}

	else 
	{
		row = -1;  //judejimo kadrai

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{ 
	window.draw(body);
}

void Player::OnCollission(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f; // susidurimas kaireje
		canJump = true;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f; // susidurimas desineje
		canJump = true;
	}
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f; //susidurimas apacioje
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f; //susidurimas virsuje
	}
}
