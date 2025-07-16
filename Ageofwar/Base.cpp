#include "stdafx.h"
#include "Base.h"

Base::Base(const std::string& name)
	: Unit(name)
{
}

void Base::Init()
{
	Unit::Init();	
	sortingOrder = -1;
}

void Base::Reset()
{
	texId = "graphics/base.png";
	maxHp = 500;
	Unit::Reset();

}

void Base::Update(float dt)
{	
	Unit::Update(dt);
}

void Base::Draw(sf::RenderWindow& window)
{
	Unit::Draw(window);

}

