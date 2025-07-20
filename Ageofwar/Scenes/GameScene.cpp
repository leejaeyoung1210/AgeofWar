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
#include "Background.h"
#include "Button.h"


GameScene::GameScene()
	: Scene(SceneIds::GameScene)
{
}


void GameScene::Init()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

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
	//투사체
	texIds.push_back("graphics/cave_turret_1_projectile.png");
	texIds.push_back("graphics/cave_turret_2_projectile.png");
	texIds.push_back("graphics/cave_turret_3_projectile.png");
	//마우스
	texIds.push_back("graphics/pngegg.png");


	//폰트
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	//애니메이션 
	/*ANI_CLIP_MGR.Load("animations/meleeattack.csv");
	ANI_CLIP_MGR.Load("animations/meleedie.csv");
	ANI_CLIP_MGR.Load("animations/meleeidle.csv");
	ANI_CLIP_MGR.Load("animations/meleewalk.csv");\

	ANI_CLIP_MGR.Load("animations/rangedie.csv");
	ANI_CLIP_MGR.Load("animations/rangeidle.csv");
	ANI_CLIP_MGR.Load("animations/rangeidleattack.csv");
	ANI_CLIP_MGR.Load("animations/rangemeleeattack.csv");
	ANI_CLIP_MGR.Load("animations/rangewalk.csv");
	ANI_CLIP_MGR.Load("animations/rangewalkattack.csv");

	ANI_CLIP_MGR.Load("animations/tankattack.csv");
	ANI_CLIP_MGR.Load("animations/tankdie.csv");
	ANI_CLIP_MGR.Load("animations/tankidle.csv");
	ANI_CLIP_MGR.Load("animations/tankwalk.csv");*/





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

	background = (Background*)AddGameObject(new Background("background"));
	background->Init();

	sf::FloatRect bounds = background->GetLocalBounds();

	//배그라운드 가로사이즈//월드뷰 범위정하려고
	maxX = bounds.left + bounds.width - worldView.getSize().x * 0.6f;
	minX = bounds.left + worldView.getSize().x * 0.6f;

	//윈도우 사이즈
	auto winsize = FRAMEWORK.GetWindowSizeF();
	//윈도우 사이즈의 중심
	sf::Vector2f center{ winsize.x * 0.5f, winsize.y * 0.5f };
	//보여주는 화면 크기 

	worldView.setSize(winsize);
	worldView.setCenter(center);
	uiView.setSize(winsize);
	uiView.setCenter(center);


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
	base2->SetScale({ -0.4f,0.4f });
	base2->SetPosition({ 2154.f, 570.f });
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

	turret2 = (Turret*)AddGameObject(new Turret("Turret2"));
	turret2->Init();
	turret2->SetType(Turret::Turretypes::turret1);
	turret2->Reset();
	turret2->SetScale({ -0.4f,0.4f });
	turret2->Spawn({ 2004.f, 500.f });
	turret2->SetActive(true);
	turret2->SetTeam(Team::Team2);
	allUnits.push_back(turret2);

	cursor.setTexture(TEXTURE_MGR.Get("graphics/pngegg.png"));
	Utils::SetOrigin(cursor, Origins::MC);


}
void GameScene::Exit()
{
	//화면에 마우스 띄우기준비
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
	//마우스 좌표 월드에서 UI 좌표로 변경하기	
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

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
			SpawnPlayer(1);
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

	// 마우스 방향에 따라 뷰가 이동해야한다 
	sf::Vector2f woldmouse = ScreenToWorld(InputMgr::GetMousePosition());
	//오른쪽으로 가겠다는거 	
	space = worldView.getSize().x * 0.45f;
	leftBoundary = worldView.getCenter().x - space;
	rightBoundary = worldView.getCenter().x + space;
	offset = 0.f;
	if (woldmouse.x < leftBoundary)
		offset = woldmouse.x - leftBoundary;  
	else if (woldmouse.x > rightBoundary)
		offset = woldmouse.x - rightBoundary;

	//abs는 절대값 양수로 변한시켜주는 함수
	if (std::abs(offset) > speed)
	{
		offset = (offset > 0) ? speed : -speed;
	}
	sf::Vector2f pos = worldView.getCenter();
	
	pos.x += offset;

	pos.x = Utils::Clamp(pos.x, minX, maxX);
	
	worldView.setCenter(pos);


}

void GameScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	window.draw(cursor);

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
		player2->SetPosition({ 1954.f, 630.f });
		player2->SetTeam(Team::Team2);
		allUnits.push_back(player2);
		AddGameObject(player2);


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
		AddGameObject(player);

	}
}





