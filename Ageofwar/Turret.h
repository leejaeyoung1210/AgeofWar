#pragma once
#include "HitBox.h"
#include"GameScene.h"
#include "Unit.h"

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

	//std::list<Bullet*> bulletList;
	//std::list<Bullet*> bulletPool;

	
	bool isSpawn = false;
		
	HitBox turrethitBox;

public:
	Turret(const std::string& name = "");
	virtual ~Turret() = default;


		
	void Init() override;

	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
		
	void SetType(Turretypes type);

	void Spawn(const sf::Vector2f& pos);

};
