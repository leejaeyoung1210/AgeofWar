#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "Player2.h"
#include "GameScene.h"

Unit::Unit(const std::string& name)
	: GameObject(name)
{
}

void Unit::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Unit::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Unit::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Unit::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Unit::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	rangehitBox.sizeplus = { 250.f,0.f };

	SetType(type);
}

void Unit::Release()
{
}

void Unit::Reset()
{
	gameScene = (GameScene*)SCENE_MGR.GetCurrentScene();

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetScale({ 0.4f, 0.4f });

	hp = maxHp;
	attackTimer = 0.f;
}

void Unit::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());

	SetPosition(GetPosition() + direction * speed * dt);

	if (type == Types::range)
	{
		rangehitBox.UpdateTransform(body, GetLocalBounds());
	}	
	attackTimer += dt;
	bool inAttackRange = false;

	if (attackTimer > attackInterval)
	{
		const auto& allUnits = gameScene->GetAllUnits();

		for (auto* target : allUnits)
		{
			if (!target || !target->IsAlive())
				continue;
			if (target == this)
				continue;
			if (target->GetTeam() == this->GetTeam())
			{
				if (Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect))
				{
					speed = 0.f;
					attackTimer = 0.f;
					inAttackRange = true;
					break;
				}
			}

			if (Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect))
			{
				std::cout << "충돌 발생!\n";
				speed = 0.f;
				attackTimer = 0.f;
				target->OnDamage(damage);
				inAttackRange = true;
				break;
			}
			else if (type == Types::range &&
				Utils::CheckCollision(rangehitBox.rect, target->GetHitBox().rect))
			{
				attackTimer = 0.f;
				target->OnDamage(damage);				
				break;
			}
		}
	}

	if (!inAttackRange)
	{
		speed = originalSpeed;
	}
	
}
void Unit::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
	rangehitBox.Draw(window);
}

void Unit::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{	
	case Types::melee:
		texId = "graphics/cave_melee_walk0001.png";
		maxHp = 150;		
		speed = originalSpeed;
		damage = 20;
		attackInterval = 1.f;
		break;
	case Types::range:
		texId = "graphics/cave_range_walk0001.png";
		maxHp = 100;
		speed = originalSpeed;
		damage = 40;
		attackInterval = 1.f;
		break;
	case Types::tank:
		texId = "graphics/cave_tank_walk0001.png";
		maxHp = 200;
		speed = originalSpeed;
		damage = 60;
		attackInterval = 1.3f;
		break;
	}
}

void Unit::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		SetActive(false);
	}

}
