#include "stdafx.h"
#include "Turret.h"

Turret::Turret(const std::string& name)
	: Unit(name)
{
}

void Turret::Init()
{
	Unit::Init();
}

void Turret::Reset()
{
	texId = "graphics/base.png";
	
	Unit::Reset();

}

void Turret::Update(float dt)
{
	Unit::Update(dt);
}

void Turret::Draw(sf::RenderWindow& window)
{
	Unit::Draw(window);

}