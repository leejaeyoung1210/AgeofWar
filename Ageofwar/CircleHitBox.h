#pragma once
class CircleHitBox
{
public:
	CircleHitBox();

	sf::CircleShape circle;
	float radiusplus = 0.f;

	void SetSizeplus(float plus) { radiusplus = plus; };
	void UpdateTransform(const sf::Transformable& tr, float radius);
	void Draw(sf::RenderWindow& window);


};

