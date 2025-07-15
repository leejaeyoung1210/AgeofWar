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

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	for (int i = 0; i < 100; ++i)
	{
		Player2* player2 = (Player2*)AddGameObject(new Player2());
		player2->SetActive(false);
		player2Pool.push_back(player2);
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
	base->SetTeam(Unit::Team::Team1);
	allUnits.push_back(base);

	base2 = (Base*)AddGameObject(new Base("base2"));
	base2->Init();
	base2->Reset();
	base2->SetPosition({ -1000.f, 570.f });
	base2->SetActive(true);
	base2->SetTeam(Unit::Team::Team2);
	allUnits.push_back(base2);



}
void GameScene::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (Player2* player2 : player2List)
	{
		player2->SetActive(false);
		player2Pool.push_back(player2);
	}
	player2List.clear();
	
	Scene::Exit();
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);

	// 마우스 위치 가져오기
	sf::Vector2i screenPos = InputMgr::GetMousePosition();
	sf::Vector2f mousePos(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
	//dt 조건식 가져오기
	//SpawnPlayer2(10);



	auto it =  player2List.begin();
	while (it != player2List.end())
	{
		if (!(*it)->GetActive())
		{
			player2Pool.push_back(*it);
			it = player2List.erase(it);			
			
		}
		else
		{
			++it;
		}
	}

	spawntimer += dt;
	if (spawntimer >= spawncool)
	{		
		for (int i = 0; i < 11; i++)
		{			
			SpawnPlayer2(1);
		}
		spawntimer = 0;
	}

	for (auto p2 : player2List)
	{
		if (p2->GetActive())
			p2->Update(dt);
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
		player2->SetPosition({ 500.f, 630.f });		
		player2->SetTeam(Unit::Team::Team2);
		player2List.push_back(player2);
		
	}
}


