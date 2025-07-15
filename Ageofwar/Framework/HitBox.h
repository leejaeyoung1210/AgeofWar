#pragma once
class HitBox
{
public:
	HitBox();

	sf::RectangleShape rect;
	sf::Vector2f sizeplus{ 0.f,0.f };

	void SetSizeplus(const sf::Vector2f& plus) { sizeplus = plus; };
	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void Draw(sf::RenderWindow& window);
};

