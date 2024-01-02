#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) : animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	fold = 0;
	canJump = true;

	body.setSize(sf::Vector2f(90.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;

		// sqrt(2.0f * gravity * jumpheight) -> 100sfml units == 1meter
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;


	if (velocity.x == 0.0f)
	{
		row = 0;
		fold = 1;
	}
	else
	{
		row = 6;
		fold = 6;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.update(row, deltaTime, faceRight, fold);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)            // collision on left
		velocity.x = 0.0f;            
	else if (direction.x > 0.0f)       // collision on right
		velocity.x = 0.0f;             
	
	if (direction.y < 0.0f)            // collision under
	{          
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)       // collision above
	{
		velocity.y = 0.0f;
	}
}
