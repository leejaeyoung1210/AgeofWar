#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "Turret.h"

class GameScene;
class Turret;

class Projectile : public GameObject
{
public:
	enum class ProjectileTypes
	{
		None,
		typ1,
		typ2,
		typ3,
	};


protected:
	ProjectileTypes type = ProjectileTypes::None;
	Team team = Team::None;

	//Turret::Turretypes type = Turret::Turretypes::None;

	sf::Sprite body;
	std::string texId;
	sf::Vector2f direction;
	float speed = 0.f;
	int damage = 0;

	HitBox hitBox;
	Turret* turret;

	GameScene* gameScene = nullptr;

public:
	Projectile(const std::string& name = "");
	virtual ~Projectile() = default;

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

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}


	ProjectileTypes GetType()const { return type; };
	void SetType(ProjectileTypes type);


	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir);

	void SetTeam(Team t) { team = t; }
	Team GetTeam() const { return team; }
	
	float GetSpeed() const { return speed; }
};

