#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "Player2.h"
#include "GameScene.h"
#include "CircleHitBox.h"

Unit::Unit(const std::string& name)
	: GameObject(name)
{
}

void Unit::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Unit::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
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
	animator.SetTarget(&body);
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;	

	//animator.AddEvent("meleeidle", 0, []() {});
	//animator.AddEvent("meleedie", 10, []() {});
	//animator.AddEvent("meleewalk", 10, []() {});
	//animator.AddEvent("meleeattack", 10, []() {});

	//animator.AddEvent("rangeidle", 0, []() {});
	//animator.AddEvent("rangedie", 10, []() {});
	//animator.AddEvent("rangewalk", 10, []() {});
	//animator.AddEvent("rangemeleeattack", 10, []() {});
	//animator.AddEvent("rangeidleattack", 10, []() {});
	//animator.AddEvent("rangewalkattack", 10, []() {});

	//animator.AddEvent("tankidle", 0, []() {});
	//animator.AddEvent("tankdie", 10, []() {});
	//animator.AddEvent("tankwalk", 10, []() {});
	//animator.AddEvent("tankattack", 10, []() {});

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

	if (type == Types::range)
	{
		rangeCirclehitBox.radiusplus = { 400.f };
	}
}

void Unit::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());	

	if (type == Types::range)
	{
		float radius = std::max(body.getLocalBounds().width, body.getLocalBounds().height) / 2.f;
		rangeCirclehitBox.UpdateTransform(body, radius);
	}

	SetPosition(GetPosition() + direction * speed * dt);

	attackTimer += dt;
	//충돌여부확인용
	bool isMoving = speed > 0.f;


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
					/*PlayMoveAnimation("idle");*/
					break;
				}
				else
				{
					// 내 뒤에 있으면 움직임 유지
					speed = originalSpeed;
					/*PlayMoveAnimation("walk");*/
					continue;
				}
			}
			else
			{				
				speed = 0.f;
				PlayMoveAnimation("idle");
				if (attackTimer > attackInterval)
				{
					attackTimer = 0.f;
					/*if (type == Types::range)
					{
						PlayMoveAnimation("rangemeleeattack");
					}
					else
					{
						PlayMoveAnimation("attack");
					}*/
					target->OnDamage(damage);
				}
				break;
			}
		}
		else if (type == Types::range &&
			Utils::CheckCircleRectCollision(rangeCirclehitBox.circle, target->GetHitBox().rect))
		{
			if (target->GetTeam() != this->GetTeam())
			{
				if (attackTimer > attackInterval)
				{
					attackTimer = 0.f;
					/*if (speed > 0)
					{
						PlayMoveAnimation("walkattack");
					}
					else
					{
						PlayMoveAnimation("idleattack");
					}*/
					target->OnDamage(damage);
				}
			}
		}
	}

	if (!isColliding)
	{
		
		speed = originalSpeed;
	}

}
void Unit::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
	rangeCirclehitBox.Draw(window);
}

void Unit::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::melee:
		texId = "graphics/cave_melee_walk0001.png";
		maxHp = 2000;
		speed = originalSpeed;
		damage = 15;
		attackInterval = 3.f;		
		break;
	case Types::range:
		texId = "graphics/cave_range_walk0001.png";
		maxHp = 1000;
		speed = originalSpeed;
		damage = 5;
		attackInterval = 2.f;		
		break;
	case Types::tank:
		texId = "graphics/cave_tank_walk0001.png";
		maxHp = 3000;
		speed = originalSpeed;
		damage = 30;
		attackInterval = 4.f;		
		break;
	}
}

void Unit::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	std::cout << GetName() << " 데미지: " << damage << ", 현재 체력: " << hp << std::endl;
	if (hp == 0)	
	{
		PlayMoveAnimation("death");
		SetActive(false);
		std::cout << GetName() << "가 죽었습니다." << std::endl;
		
	}

}

//void Unit::PlayMoveAnimation(const std::string& action)
//{
//	std::string prefix;
//
//	switch (type)
//	{
//	case Types::melee: prefix = "melee"; break;
//	case Types::range: prefix = "range"; break;
//	case Types::tank:  prefix = "tank";  break;
//	}
//
//	animator.Play(prefix + action);
//}
