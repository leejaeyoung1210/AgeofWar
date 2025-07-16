#include "stdafx.h"
#include "HitBox.h"

HitBox::HitBox()
{
	//채움
	rect.setFillColor(sf::Color::Transparent);
	//선색
	rect.setOutlineColor(sf::Color::Green);
	//굵기
	rect.setOutlineThickness(3.f);
}

void HitBox::UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds)
{
	rect.setSize({ localBounds.width + sizeplus.x, localBounds.height+ sizeplus.y });
	rect.setOutlineColor(sf::Color::Green);
	rect.setOrigin(tr.getOrigin());
	rect.setPosition(tr.getPosition());
	rect.setScale(tr.getScale());
	rect.setRotation(tr.getRotation());
}

void HitBox::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox)
	{
		window.draw(rect);
	}
}
