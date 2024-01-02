#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) : body(body)
{
}

Collider::~Collider()
{

}

sf::FloatRect Collider::getGlobalBounds()
{
	sf::FloatRect bounds = body.getGlobalBounds();
	bounds.left += 30.0f;
	bounds.width -= 30.0f;

	bounds.top += 30.0f;
	bounds.height -= 33.0f;

	return bounds;
}


bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float displace)
{
	//sf::Vector2f otherPosition = other.getPosition();
	//sf::Vector2f otherHalfSize = other.getHalfSize();
	//sf::Vector2f thisPosition = getPosition();
	//sf::Vector2f thisHalfSize = getHalfSize();

	//float dx = otherPosition.x - thisPosition.x;
	//float dy = otherPosition.y - thisPosition.y;
	//float intersectx = abs(dx) - (otherHalfSize.x + thisHalfSize.x);
	//float intersecty = abs(dy) - (otherHalfSize.y + thisHalfSize.y);

	sf::FloatRect thisBounds = getGlobalBounds();
	sf::FloatRect otherBounds = other.getGlobalBounds();

	float dx = otherBounds.left + otherBounds.width / 2.0f - (thisBounds.left + thisBounds.width / 2.0f);
	float dy = otherBounds.top + otherBounds.height / 2.0f - (thisBounds.top + thisBounds.height / 2.0f);

	float intersectx = abs(dx) - (otherBounds.width / 2.0f + thisBounds.width / 2.0f);
	float intersecty = abs(dy) - (otherBounds.height / 2.0f + thisBounds.height / 2.0f);


	if (intersectx < 0.0f && intersecty < 0.0f)
	{
		// clamping b/w 0 and 1
		displace = std::min(std::max(displace, 0.0f), 1.0f);

		if (abs(intersectx) < abs(intersecty))
		{
			// colliding on right
			if (dx > 0.0f)
			{
				move(intersectx * (1.0f - displace), 0.0f);
				other.move(-intersectx * displace, 0.0f);

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			// colliding on left
			else
			{
				move(-intersectx * (1.0f - displace), 0.0f);
				other.move(intersectx * displace, 0.0f);

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else
		{
			// colliding below
			if (dy > 0.0f)
			{
				move(0.0f, intersecty * (1.0f - displace));
				other.move(0.0f, -intersecty * displace);

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			//colliding above
			else
			{
				move(0.0f, -intersecty * (1.0f - displace));
				other.move(0.0f, intersecty * displace);

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}

		return true;
	}

	return false;
}

