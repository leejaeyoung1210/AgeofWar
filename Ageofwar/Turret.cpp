#include "stdafx.h"
#include "Turret.h"
#include "Unit.h"
#include "Projectile.h"
#include "CircleHitBox.h"

Turret::Turret(const std::string& name)
	: Unit(name)
{
}

void Turret::Init()
{
	Unit::Init();
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;	
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
	look = { 1.0f,0.f };	
}

void Turret::Update(float dt)
{
	if (!isSpawn)
	{
		return;
	}

	turrethitBox.UpdateTransform(body, GetRadius());
	float size = turrethitBox.Getradius();	

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
			look = Utils::GetNormal(unit->GetPosition() - GetPosition());
			SetRotation(Utils::Angle(look));

			if (attackTimer >= attackInterval)
			{
				attackTimer = 0.f;
				Shoot();
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
		std::cout << "ем╥© е╦ют: turret1" << std::endl;		
		attackInterval = 2;
		turrethitBox.sizeplus = { 400.f,400.f };
		break;

	case Turretypes::turret2:
		texId = "graphics/cave_turret_2_attack0001.png";		
		std::cout << "ем╥© е╦ют: turret2" << std::endl;
		attackInterval = 1;
		turrethitBox.sizeplus = { 400.f,300.f };
		break;

	case Turretypes::turret3:
		texId = "graphics/cave_turret_3_attack0001.png";		
		std::cout << "ем╥© е╦ют: turret3" << std::endl;
		attackInterval = 3;
		turrethitBox.sizeplus = { 500.f,300.f };
		break;
	}
}

void Turret::Spawn(const sf::Vector2f& pos)
{
	SetPosition(pos);
	isSpawn = true;
}

Projectile::ProjectileTypes ConvertTurretTypeToProjectileType(Turret::Turretypes turretType)
{
	switch (turretType)
	{
	case Turret::Turretypes::turret1:
		return Projectile::ProjectileTypes::typ1;
	case Turret::Turretypes::turret2:
		return Projectile::ProjectileTypes::typ2;
	case Turret::Turretypes::turret3:
		return Projectile::ProjectileTypes::typ3;
	default:
		return Projectile::ProjectileTypes::None;
	}
}

void Turret::Shoot()
{
	Projectile* projectile = nullptr;
	if (projectilePool.empty())
	{
		projectile = new Projectile();
		projectile->Init();
	}
	else
	{
		projectile = projectilePool.front();
		projectilePool.pop_front();
		projectile->SetActive(true);	
	}
	projectile->Reset();

	projectile->SetType(ConvertTurretTypeToProjectileType(type));
	projectile->Fire(position + look * 20.f, look);

	projectileList.push_back(projectile);
	gameScene->AddGameObject(projectile);










}

