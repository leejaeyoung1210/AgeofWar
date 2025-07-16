#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "CircleHitBox.h"



class GameScene;

class Unit :    public GameObject
{

public:
	enum class Types
	{		
		melee,
		range,
		tank,
	};

	

	static const int TotalTypes = 3;

protected:
	Types type = Types::melee;
	Team team = Team::None;
	

	sf::Sprite body;
	std::string texId;
	sf::Vector2f direction={ 0.f,0.f };
		

	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 0.f;
	float originalSpeed = 50.f;

	int hp;
	float attackTimer = 0.f;

	GameScene* gameScene = nullptr;
	
	HitBox hitBox;
	CircleHitBox rangeCirclehitBox;
	

public:
	bool IsAlive() const { return hp > 0; }

	Unit(const std::string& name = "");
	virtual ~Unit() = default;

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SetTeam(Team t) { team = t; }
	Team GetTeam() const { return team; }

	sf::Vector2f GetDirection() const { return direction; }
	float GetSpeed() const { return speed; }
	
	

	void SetType(Types type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	const CircleHitBox& GetRangeCirclehitBox() const
	{
		return rangeCirclehitBox;
	}

	void OnDamage(int damage);
	int GetHp() const { return hp; }
	void SetHp(int hp) { this->hp = hp; }

	
	
};

