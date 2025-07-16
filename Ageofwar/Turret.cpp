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
	look = (team == Team::Team1) ? sf::Vector2f{ 1.f, 0.f } : sf::Vector2f{ -1.f, 0.f };
}

void Turret::Update(float dt)
{
	if (!isSpawn)
	{
		return;
	}

	float radius = std::max(body.getLocalBounds().width, body.getLocalBounds().height) / 2.f;
	turrethitBox.UpdateTransform(body, radius);

	attackTimer += dt;

	const auto& allUnits = gameScene->GetAllUnits();

	for (Unit* unit : allUnits)
	{
		if (!unit || !unit->IsAlive() || unit == this)
			continue;

		if (unit->GetTeam() == this->GetTeam())
			continue;


		if (Utils::CheckCircleRectCollision(turrethitBox.circle, unit->GetHitBox().rect))
		{
			look = Utils::GetNormal(unit->GetPosition() - GetPosition());
			if (scale.x < 0) // 오른쪽을 바라보는 터렛이라면
			{
				look = -look; // 방향 반전
			}
			
			SetRotation(Utils::Angle(look));

			if (attackTimer >= attackInterval)
			{
				attackTimer = 0.f;				
				Shoot();
				std::cout << "발사" << std::endl;
				break;
			}
		}
	}
}
void Turret::Draw(sf::RenderWindow& window)
{
	{
		window.draw(body);
		turrethitBox.Draw(window);
		for (auto projectile : projectileList)
		{
			if (projectile->GetActive()) // 활성 상태라면
				projectile->Draw(window);
		}
	}
}

void Turret::SetType(Turretypes type)
{
	this->type = type;
	switch (this->type)
	{
	case Turretypes::turret1:
		texId = "graphics/cave_turret_1_attack0001.png";
		std::cout << "터렛 타입: turret1" << std::endl;
		attackInterval = 2;
		turrethitBox.radiusplus = { 700.f };
		break;

	case Turretypes::turret2:
		texId = "graphics/cave_turret_2_attack0001.png";
		std::cout << "터렛 타입: turret2" << std::endl;
		attackInterval = 1;
		turrethitBox.radiusplus = { 50.f };
		break;

	case Turretypes::turret3:
		texId = "graphics/cave_turret_3_attack0001.png";
		std::cout << "터렛 타입: turret3" << std::endl;
		attackInterval = 3;
		turrethitBox.radiusplus = { 50.f };
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
	projectile->SetType(ConvertTurretTypeToProjectileType(type));
	projectile->Reset();
	projectile->SetTeam(this->GetTeam());	
	float a = (team == Team::Team1) ? 25.f : -25.f;
	projectile->Fire(position + look * a, look);

	projectileList.push_back(projectile);
	gameScene->AddGameObject(projectile);
}

