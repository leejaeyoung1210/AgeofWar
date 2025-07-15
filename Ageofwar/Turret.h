#pragma once
#include "Unit.h"
class Turret :    public Unit
{
protected:


public:
	Turret(const std::string& name = "base");
	virtual ~Turret() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};
