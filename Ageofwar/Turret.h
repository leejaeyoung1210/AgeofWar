#pragma once
#include "CircleHitBox.h"
#include"GameScene.h"
#include "Unit.h"

class Projectile;

class Turret : public Unit
{
public:
	enum class Turretypes
	{
		None,
		turret1,
		turret2,
		turret3,
	};

protected:
	Turretypes type = Turretypes::None;		
	
	
	sf::Vector2f look;

	std::list<Projectile*> projectileList;
	std::list<Projectile*> projectilePool;

	
	bool isSpawn = false;
		
	CircleHitBox turrethitBox;

public:
	Turret(const std::string& name = "");
	virtual ~Turret() = default;


		
	void Init() override;

	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
		
	Turretypes GetType()const { return type; };
	void SetType(Turretypes type);

	void Spawn(const sf::Vector2f& pos);

	void Shoot();

	sf::FloatRect GetLocalBounds() const override
	{
		return turrethitBox.circle.getLocalBounds(); 
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return turrethitBox.circle.getGlobalBounds();
	}

	const CircleHitBox& GetcirleHitBox() const
	{
		return turrethitBox;
	}



};
