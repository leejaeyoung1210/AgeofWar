#include "stdafx.h"
#include "GameScene.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Unit.h"
#include "Player.h"
#include "Player2.h"
#include "Base.h"
#include "Turret.h"


int GameScene::Gold = 0;
int GameScene::Exp = 0;

GameScene::GameScene()
	: Scene(SceneIds::GameScene)
{
}


void GameScene::Init()
{
	uiView.setSize(1280.f, 720.f);
	//배경
	texIds.push_back("graphics/background.png");
	//집
	texIds.push_back("graphics/base.png");
	//유닛
	texIds.push_back("graphics/cave_melee_walk0001.png");
	texIds.push_back("graphics/cave_range_walk0001.png");
	texIds.push_back("graphics/cave_tank_walk0001.png");
	//터렛
	texIds.push_back("graphics/cave_turret_1_attack0001.png");
	texIds.push_back("graphics/cave_turret_2_attack0001.png");
	texIds.push_back("graphics/cave_turret_3_attack0001.png");
	//폰트
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	for (int i = 0; i < 100; ++i)
	{
		Player2* player2 = (Player2*)AddGameObject(new Player2());
		player2->SetActive(false);
		player2Pool.push_back(player2);

		Player* player = (Player*)AddGameObject(new Player());
		player->SetActive(false);
		playerPool.push_back(player);
	}


	Scene::Init();
}

void GameScene::Enter()
{
	Scene::Enter();


	sf::FloatRect windowbound = FRAMEWORK.GetWindowBounds();
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
	background.setPosition(0.f, 0.f);

	base = (Base*)AddGameObject(new Base("base"));
	base->Init();
	base->Reset();
	base->SetPosition({ 100.f, 570.f });
	base->SetActive(true);
	base->SetTeam(Team::Team1);
	allUnits.push_back(base);

	base2 = (Base*)AddGameObject(new Base("base2"));
	base2->Init();
	base2->Reset();
	base2->SetPosition({ -1000.f, 570.f });
	base2->SetActive(true);
	base2->SetTeam(Team::Team2);
	allUnits.push_back(base2);

	turret = (Turret*)AddGameObject(new Turret("Turret"));
	turret->Init();	
	turret->SetType(Turret::Turretypes::turret1);
	turret->Reset();
	turret->Spawn({ 250.f, 500.f });
	turret->SetActive(true);
	turret->SetTeam(Team::Team1);
	allUnits.push_back(turret);
		
	
	

}
void GameScene::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (Unit* unit : allUnits)
	{
		unit->SetActive(false);

		if (auto p2 = dynamic_cast<Player2*>(unit))
		{
			player2Pool.push_back(p2);
		}
		else if (auto p1 = dynamic_cast<Player*>(unit))
		{
			playerPool.push_back(p1);
		}
	}
	allUnits.clear();

	Scene::Exit();
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);

	// 마우스 위치 가져오기
	sf::Vector2i screenPos = InputMgr::GetMousePosition();
	sf::Vector2f mousePos(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
	
	auto it = allUnits.begin();
	while (it != allUnits.end())
	{
		if (!(*it)->GetActive())
		{
			if (auto p1 = dynamic_cast<Player*>(*it))
				playerPool.push_back(p1);
			else if (auto p2 = dynamic_cast<Player2*>(*it))
				player2Pool.push_back(p2);
			/*else if (auto turret = dynamic_cast<Turret*>(*it))
				turretPool.push_back(turret);*/
			
			it = allUnits.erase(it);		
		}
		else
		{
			++it;
		}
	}
		

	spawntimer += dt;
	wavetimer += dt;

	if (wavecool > wavetimer)
	{
		if (spawntimer >= spawncool)
		{
			SpawnPlayer2(1);	
			//SpawnPlayer(1);
			spawntimer = 0.f;
		}
	}
	else
	{
		waveDelayTimer += dt;
		if (waveDelayTimer > someDelayTime)
		{
			wavetimer = 0.f;
			spawntimer = 0.f;
			waveDelayTimer = 0.f;
		}
	}


	for (auto pl : allUnits)
	{
		if (pl->GetActive())
			pl->Update(dt);
	}

	
}

void GameScene::Draw(sf::RenderWindow& window)
{
	window.draw(background);	
	for (auto go : gameObjects)
	{
		if (go->GetActive())
			go->Draw(window);
	}

	Scene::Draw(window);

}

void GameScene::SpawnPlayer2(int count)
{
	for (int i = 0; i < count; ++i)
	{

		if (player2Pool.empty())
		{
			player2 = (Player2*)AddGameObject(new Player2());
			player2->Init();
		}
		else
		{
			player2 = player2Pool.front();
			player2Pool.pop_front();
			player2->SetActive(true);
		}
		player2->SetType((Player2::Types)Utils::RandomRange(0, Player2::TotalTypes));
		player2->Reset();
		player2->SetPosition({ 700.f, 630.f });
		player2->SetTeam(Team::Team2);
		allUnits.push_back(player2);

	}
}

void GameScene::SpawnPlayer(int count)
{
	for (int i = 0; i < count; ++i)
	{

		if (playerPool.empty())
		{
			player = (Player*)AddGameObject(new Player());
			player->Init();
		}
		else
		{
			player = playerPool.front();
			playerPool.pop_front();
			player->SetActive(true);
		}
		player->SetType((Player::Types)Utils::RandomRange(0, Player::TotalTypes));
		player->Reset();
		player->SetPosition({ 300.f, 630.f });
		player->SetTeam(Team::Team1);
		allUnits.push_back(player);

	}
}





