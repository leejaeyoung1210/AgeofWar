#pragma once
#include "Scene.h"


class TextGo;
class Unit;

class GameScene : public Scene
{
protected:
	sf::Sprite background;
	
	sf::Sprite cursor;
	sf::Sprite base;
	sf::Sprite base2;
	
	Unit* player = nullptr;  
	Unit* player2 = nullptr;

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

