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
	speed = originalSpeed;
}

void Unit::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());	

	if (type == Types::range)
	{
		rangehitBox.UpdateTransform(body, GetLocalBounds());
	}

	SetPosition(GetPosition() + direction * speed * dt);

	attackTimer += dt;

	bool inAttackRange = false;
	bool isColliding = false;

	const auto& allUnits = gameScene->GetAllUnits();

	for (auto* target : allUnits)
	{
		if (!target || !target->IsAlive() || target == this)
			continue;
		
		if (Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect))
		{
			isColliding = true;

			// 같은 팀이면 공격은 하지 않음, 충돌만 감지
			if (target->GetTeam() == this->GetTeam())
			{
				sf::Vector2f toTarget = target->GetPosition() - position;
				float dot = direction.x * toTarget.x + direction.y * toTarget.y;

				if (dot > 0) // 내 앞에 있으면 멈춤
				{
					speed = 0.f;
					inAttackRange = true;
					break;
				}
				else
				{
					// 내 뒤에 있으면 움직임 유지
					speed = originalSpeed;
					continue;
				}
			}
			else
			{
				inAttackRange = true;
				speed = 0.f;
								
				if (attackTimer > attackInterval)
				{
					attackTimer = 0.f;
					
					target->OnDamage(damage);
				}
				break;
			}
		}
		else if (type == Types::range &&
			Utils::CheckCollision(rangehitBox.rect, target->GetHitBox().rect))
		{
			if (target->GetTeam() != this->GetTeam())
			{
				if (attackTimer > attackInterval)
				{
					attackTimer = 0.f;
					target->OnDamage(damage);
				}
			}
		}
	}

	if (!isColliding)
	{
		inAttackRange = false;
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
		std::cout << GetName() << " 데미지: " << damage << ", 현재 체력: " << hp << std::endl;
	{
		SetActive(false);
		std::cout << GetName() << "가 죽었습니다." << std::endl;
		
	}

}
