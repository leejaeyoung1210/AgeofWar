#pragma once

#include "Unit.h"
#include "HitBox.h"

class GameScene;

class Player2 : public Unit
{
protected:

public:
	Player2(const std::string& name = "");
	virtual ~Player2() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};
