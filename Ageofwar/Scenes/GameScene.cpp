#include "stdafx.h"
#include "GameScene.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"

GameScene::GameScene()	
	: Scene(SceneIds::GameScene)
{
}


void GameScene::Init()
{	
	//uiView.setSize(1280.f, 720.f);

	texIds.push_back("graphics/background.png");
	//fontIds.push_back("fonts/DS-DIGIT.ttf");


	Scene::Init();
}

void GameScene::Enter()
{
	/*auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);*/

	
	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);
		
	//// 마우스 위치 가져오기
	//sf::Vector2i screenPos = InputMgr::GetMousePosition();
	//sf::Vector2f mousePos(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
	

		
}

void GameScene::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	Scene::Draw(window);
	
	
	
}
