#include "stdafx.h"
#include "GameUI.h"
#include "GameScene.h"


GameUI::GameUI(const std::string& name)
	: GameObject(name)
{
}

void GameUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	

	goldMessage.setCharacterSize(10);
	goldMessage.setFont(FONT_MGR.Get(fontId));
	goldMessage.setPosition({ 30.f,10.f });

	expMessage.setCharacterSize(100);
	expMessage.setFont(FONT_MGR.Get(fontId));
	expMessage.setFillColor(sf::Color::Black);
	expMessage.setPosition({ 10.f,30.f });

	goldIcon.setTexture(TEXTURE_MGR.Get(goldTexId));
	goldIcon.setPosition({ 10.f,10.f });

	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize({ BAR_SIZE,100.f });
	hpBar.setPosition({ 10.f,windowSize.y - 40.f });
	Utils::SetOrigin(hpBar, Origins::ML);

	hpBar2.setFillColor(sf::Color::Red);
	hpBar2.setSize({ BAR_SIZE,100.f });
	hpBar2.setPosition({ 300.f,windowSize.y - 40.f });
	Utils::SetOrigin(hpBar2, Origins::ML);

	unitBar.setFillColor(sf::Color::Blue);
	unitBar.setSize({ BAR_SIZE+240.f,10.f });
	unitBar.setPosition({ 300.f,10.f});
	Utils::SetOrigin(unitBar, Origins::ML);


}

void GameUI::Release()
{
}

void GameUI::Reset()
{
	/*goldMessage.setString(std::to_string(GameScene::Gold));
	Utils::SetOrigin(goldMessage, Origins::TL);

	expMessage.setString("Exp: " + std::to_string(GameScene::Exp));
	Utils::SetOrigin(expMessage, Origins::TL);*/


	hpBar.setSize({ BAR_SIZE,50.f });
}

void GameUI::Update(float dt)
{
}

void GameUI::Draw(sf::RenderWindow& window)
{
	window.draw(goldMessage);
	window.draw(expMessage);
	window.draw(goldIcon);	
	window.draw(hpBar);
	window.draw(hpBar2);
}


void GameUI::UpdateHpBar(int maxHp, int hp)
{
	hpBar.setSize({ BAR_SIZE * ((float)hp / maxHp),50.f });
}

void GameUI::UpdateHpBar2(int maxHp2, int hp2)
{
	hpBar2.setSize({ BAR_SIZE * ((float)hp2 / maxHp2),50.f });
}
