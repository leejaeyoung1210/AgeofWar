#pragma once
#include "Scene.h"
#include "Unit.h"
#include "Base.h"


class TextGo;
class Unit;

class GameScene : public Scene
{
protected:
	sf::Sprite background;
	
	sf::Sprite cursor;
		
	Unit* player = nullptr;  
	Unit* player2 = nullptr;
	
	Base* base = nullptr;
	Base* base2 = nullptr;

	std::list<Unit*> unitList;
	std::list<Unit*> unitPool;

public:
	static int Gold;
	static int Exp;
	GameScene();	
	~GameScene() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	
};

