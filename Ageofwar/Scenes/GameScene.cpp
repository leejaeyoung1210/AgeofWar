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




}

void GameScene::Update(float dt)
{
	Scene::Update(dt);

	// 마우스 위치 가져오기
	sf::Vector2i screenPos = InputMgr::GetMousePosition();
	sf::Vector2f mousePos(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));

	base = (Base*)AddGameObject(new Base());
	base->Init();
	base->Reset();
	base->SetPosition({ 100.f, 570.f });
	base->SetActive(true);

	base2 = (Base*)AddGameObject(new Base());
	base2->Init();
	base2->Reset();
	base2->SetPosition({ -1000.f, 570.f });
	base2->SetActive(true);


	if (InputMgr::GetKeyDown(sf::Keyboard::Space) && unitList.empty())
	{
		player = (Player*)AddGameObject(new Player());
		player->SetType(Unit::Types::melee);
		player->Init();
		player->Reset();		
		player->SetPosition({ 300.f, 630.f }); 
		player->SetActive(true);

		player2 = (Player2*)AddGameObject(new Player2());
		player2->SetType(Unit::Types::tank);
		player2->Init();
		player2->Reset();
		player2->SetScale({ -0.4, 0.4f });
		player2->SetPosition({ 500.f, 630.f });
		player2->SetActive(true);

		player->SetTarget(player2);
		player2->SetTarget(player);

		unitList.push_back(player);
		unitList.push_back(player2);		
	}


	
	for (auto unit : unitList)
	{
		if (unit->GetActive())
			unit->Update(dt);
	}
	

}

void GameScene::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (auto unit : unitList)
	{
		if (unit->GetActive())
			unit->Draw(window);
	}

	for (auto go : gameObjects)
	{
		if (go->GetActive())
			go->Draw(window);
	}

	Scene::Draw(window);

}


