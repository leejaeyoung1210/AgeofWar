#pragma once
#include "GameObject.h"
#include "hitBox.h"
#include "Unit.h"
class Base : public Unit
{
protected:
	

public:
	Base(const std::string& name = "base");
	virtual ~Base() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

