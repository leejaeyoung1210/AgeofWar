#pragma once
#include "GameObject.h"
#include "HitBox.h"

class GameScene;

class Unit :    public GameObject
{

public:
	enum class Types
	{
		base,
		melee,
		range,
		tank,
	};

	static const int TotalTypes = 3;

protected:
	Types type = Types::melee;

	sf::Sprite body;
	std::string texId;
	sf::Vector2f direction;

	

	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 0.3f;
	float originalSpeed = 50.f;

	int hp;
	float attackTimer = 0.f;

	GameScene* gameScene = nullptr;
	Unit* target = nullptr;
	std::vector<Unit*> targets;
	HitBox hitBox;
	HitBox rangehitBox;

public:
	bool IsAlive() const { return hp > 0; }

	Unit(const std::string& name = "");
	virtual ~Unit() = default;

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	void SetTarget(Unit* target) { this->target = target; };

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

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

	void OnDamage(int damage);
	int GetHp() const { return hp; }
	void SetHp(int hp) { this->hp = hp; }
	
};

