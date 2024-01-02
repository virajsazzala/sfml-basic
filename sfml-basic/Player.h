#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void update(float deltatime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return body.getPosition(); }
	Collider getCollider() { return Collider(body); }
	void onCollision(sf::Vector2f direction);

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	float fold;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

