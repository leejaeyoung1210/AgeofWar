#pragma once
#include "Scene.h"
#include "Unit.h"
#include "Base.h"
#include "Player2.h"
#include "Player.h"


class TextGo;
class Unit;

class GameScene : public Scene
{
protected:
	sf::Sprite background;
	
	sf::Sprite cursor;
		
	Player* player = nullptr;
	Player2* player2 = nullptr;
	
	Base* base = nullptr;
	Base* base2 = nullptr;

	std::vector<Unit*> allUnits;
	std::list<Player2*> player2List;
	std::list<Player2*> player2Pool;

	float spawncool = 10.f;	
	float spawntimer = 0.f;

	
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
	const std::vector<Unit*>& GetAllUnits() const { return allUnits; }
	
};

