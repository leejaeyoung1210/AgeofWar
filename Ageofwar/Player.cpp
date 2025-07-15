#include "stdafx.h"
#include "Player.h"
#include "Unit.h"

Player::Player(const std::string& name)
	: Unit("player")
{
	direction = { 1.f,0.f };
}

void Player::Init()
{
	Unit::Init();

}

void Player::Release()
{
}

void Player::Reset()
{
	Unit::Reset();

}

void Player::Update(float dt)
{
	Unit::Update(dt);
    
}

void Player::Draw(sf::RenderWindow& window)
{	
	Unit::Draw(window);
}


