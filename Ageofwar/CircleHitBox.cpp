#include "stdafx.h"
#include "CircleHitBox.h"

CircleHitBox::CircleHitBox()
{
	//ä��
	circle.setFillColor(sf::Color::Transparent);
	//����
	circle.setOutlineColor(sf::Color::Green);
	//����
	circle.setOutlineThickness(3.f);
}

void CircleHitBox::UpdateTransform(const sf::Transformable& tr, float radius)
{
	circle.setRadius(radius + radiusplus);
	circle.setOrigin(radius + radiusplus, radius + radiusplus);
	circle.setOutlineColor(sf::Color::Green);	
	circle.setPosition(tr.getPosition());
	circle.setRotation(tr.getRotation());
	circle.setScale(tr.getScale());

}

void CircleHitBox::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox)
	{
		window.draw(circle);
	}
}