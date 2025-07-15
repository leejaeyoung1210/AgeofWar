#include "stdafx.h"
#include "Player2.h"
#include "Unit.h"


Player2::Player2(const std::string& name)
	: Unit("player2")
{
	direction = { -1.f,0.f };
}

void Player2::Init()
{
	Unit::Init();

}

void Player2::Release()
{
}

void Player2::Reset()
{
	Unit::Reset();

}

void Player2::Update(float dt)
{
	Unit::Update(dt);
	std::cout << "Player HP: " << this->GetHp() << std::endl;
}

void Player2::Draw(sf::RenderWindow& window)
{
	Unit::Draw(window);
}

