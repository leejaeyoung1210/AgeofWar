#include "stdafx.h"
#include "Player2.h"
#include "Unit.h"
#include "GameScene.h"

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
	SetScale({ -0.4f, 0.4f });
	gameScene = (GameScene*)SCENE_MGR.GetCurrentScene();

}

void Player2::Update(float dt)
{
    Unit::Update(dt);    
	
}

void Player2::Draw(sf::RenderWindow& window)
{
	Unit::Draw(window);
}

