#pragma once
#include "GameObject.h"
#include "hitBox.h"
#include "Unit.h"
class Base :    public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/base.png";



	int maxHp = 500;
	int hp;

	

	GameScene* gameScene = nullptr;
	HitBox hitBox;

public:
	Base(const std::string& name = "");
	virtual ~Base() = default;

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f& pos) override;
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

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void OnDamage(int damage);
	int GetHp() const { return hp; }
	void SetHp(int hp) { this->hp = hp; }

};

