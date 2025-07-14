#pragma once

#include "Unit.h"
#include "HitBox.h"

class GameScene;

class Player :    public Unit
{
protected:  	 

public:
    Player(const std::string& name ="");
    virtual ~Player() = default;
		
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
		
};

