#include "stdafx.h"
#include "Projectile.h"
#include "Turret.h"
#include "Unit.h"

Projectile::Projectile(const std::string& name)
	: GameObject(name)
{
}

void Projectile::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Projectile::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}
void Projectile::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Projectile::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Projectile::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Projectile::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetType(type);
}

void Projectile::Release()
{
}

void Projectile::Reset()
{
	gameScene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
	turret = (Turret*)gameScene->FindGameObject("Turret");

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);

	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

}

void Projectile::Update(float dt)
{

	SetPosition(GetPosition() + direction * speed * dt);

	hitBox.UpdateTransform(body, GetLocalBounds());

	const auto& allUnits = gameScene->GetAllUnits();
	for (const auto unit : allUnits)
	{
		if (unit->GetTeam() == turret->GetTeam())
			continue;

		if (Utils::CheckCollision(hitBox.rect, unit->GetHitBox().rect))
		{
			unit->OnDamage(damage);
			SetActive(false);
			break;
		}
	}
}

void Projectile::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Projectile::SetType(ProjectileTypes type)
{
	this->type = type;
	switch (this->type)
	{
	case ProjectileTypes::typ1:
		texId = "graphics/cave_turret_1_projectile.png";
		std::cout << "발사체 1" << std::endl;
		speed = 500;
		damage = 15;
		break;

	case ProjectileTypes::typ2:
		texId = "graphics/cave_turret_2_projectile.png";
		std::cout << "터렛 타입: turret2" << std::endl;
		speed = 300;
		damage = 10;
		break;

	case ProjectileTypes::typ3:
		texId = "graphics/cave_turret_3_projectile.png";
		std::cout << "터렛 타입: turret3" << std::endl;
		speed = 200;
		damage = 20;
		break;
	}
}

void Projectile::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir)
{
	SetPosition(pos);
	direction = (team == Team::Team2) ? -dir : dir;
	SetRotation(Utils::Angle(direction));

}

