#pragma once
#include "Scene.h"
#include "Unit.h"
#include "Base.h"
#include "Player2.h"


class TextGo;
class Unit;

class GameScene : public Scene
{
protected:
	sf::Sprite background;
	
	sf::Sprite cursor;
		
	Player2* player = nullptr;
	Player2* player2 = nullptr;
	
	Unit* base = nullptr;
	Unit* base2 = nullptr;

	std::list<Unit*> unitList;
	std::list<Unit*> unitPool;

	std::list<Player2*> player2List;
	std::list<Player2*> player2Pool;

	
public:
	static int Gold;
	static int Exp;
	GameScene();	
	~GameScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnPlayer2(int count);

	
};

