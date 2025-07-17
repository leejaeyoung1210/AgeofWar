#pragma once
#include "Scene.h"
#include "Unit.h"
#include "Base.h"
#include "Player2.h"
#include "Player.h"




class TextGo;
class Unit;
class Turret;
class Background;

class GameScene : public Scene
{
protected:
	
	sf::Sprite cursor;
		
	Background* background = nullptr;

	Player* player = nullptr;
	Player2* player2 = nullptr;

	Turret* turret = nullptr;
	Turret* turret2 = nullptr;	

	Base* base = nullptr;
	Base* base2 = nullptr;

	std::list<Unit*> allUnits;
	
	std::list<Player*> playerPool;	
	std::list<Player2*> player2Pool;

	float spawncool = 1.f;	
	float spawntimer = 0.f;

	float wavecool = 6.f;
	float wavetimer = 0.f;	

	float someDelayTime = 7.f;
	float waveDelayTimer = 0.f;

	float speed = 0.5f;

	float minX;
	float maxX;
	float left;
	float right;
	
	sf::Vector2f pos = worldView.getCenter();;
	
	float space;
	float leftBoundary;
	float rightBoundary;
	float offset;

	
public:
	/*static int Gold;
	static int Exp;*/
	GameScene();	
	~GameScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnPlayer2(int count);
	void SpawnPlayer(int count);
	const std::list<Unit*>& GetAllUnits() const { return allUnits; }
	

};

