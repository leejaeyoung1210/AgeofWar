#include "stdafx.h"
#include "Turret.h"
#include "Unit.h"

Turret::Turret(const std::string& name)
	: Unit(name)
{
}

void Turret::Init()
{
	Unit::Init();
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetType(type);
}

void Turret::Release()
{
}

void Turret::Reset()
{
	Unit::Reset();
	
	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetScale({ 0.4f, 0.4f });
	//turrethitBox.sizeplus = { 0.f,0.f };
	attackTimer = 0.f;

}

void Turret::Update(float dt)
{
	if (!isSpawn)
	{
		return;
	}

	turrethitBox.UpdateTransform(body, GetLocalBounds());
	
	attackTimer += dt;
	
	const auto& allUnits = gameScene->GetAllUnits();

	for (Unit* unit : allUnits)
	{
		if (!unit || !unit->IsAlive() || unit == this)
			continue;

		if (unit->GetTeam() == this->GetTeam())
			continue;

		if (Utils::CheckCollision(turrethitBox.rect, unit->GetHitBox().rect))
		{
			if (attackTimer >= attackInterval)
			{
				attackTimer = 0.f;
				unit->OnDamage(damage);
				break; 			
			}
		}
	}
}
void Turret::Draw(sf::RenderWindow& window)
{
	if (isSpawn)
	{
		window.draw(body);
		turrethitBox.Draw(window);
	}
}

void Turret::SetType(Turretypes type)
{
	this->type = type;
	switch (this->type)
	{
	case Turretypes::turret1:
		texId = "graphics/cave_turret_1_attack0001.png";
		damage = 15;
		attackInterval = 3.f;
		turrethitBox.sizeplus = { 50.f,50.f };
		break;
	case Turretypes::turret2:
		texId = "graphics/cave_turret_2_attack0001.png";
		damage = 5;
		attackInterval = 2.f;
		turrethitBox.sizeplus = { 400.f,300.f };
		break;
	case Turretypes::turret3:
		texId = "graphics/cave_turret_3_attack0001.png";
		damage = 30;
		attackInterval = 4.f;
		turrethitBox.sizeplus = { 500.f,300.f };
		break;
	}
}

void Turret::Spawn(const sf::Vector2f& pos)
{
	SetPosition(pos);
	isSpawn = true;
}

