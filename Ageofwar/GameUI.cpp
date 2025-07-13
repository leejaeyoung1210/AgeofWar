#include "stdafx.h"
#include "GameUI.h"

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
	goldMessage.setPosition({ 840.f,650.f });

	expMessage.setCharacterSize(50);
	expMessage.setFont(FONT_MGR.Get(fontId));
	expMessage.setFillColor(sf::Color::Blue);
	expMessage.setPosition({ 1100.f,600.f });

	//goldIcon.setTexture(TEXTURE_MGR.Get());
	goldIcon.setPosition({ 10.f,650.f });

	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize({ BAR_SIZE,100.f });
	hpBar.setPosition({ 300.f,windowSize.y - 40.f });
	Utils::SetOrigin(hpBar, Origins::ML);
}

void GameUI::Release()
{
}

void GameUI::Reset()
{
	scoreMessage.setString("SCORE:" + std::to_string(SceneGame::score));
	Utils::SetOrigin(scoreMessage, Origins::TL);

	ammoMessage.setString(std::to_string(player->GetCurrentAmmo()) + "/" + std::to_string(player->GetReserveAmmo()));
	Utils::SetOrigin(ammoMessage, Origins::TL);

	stageInfoMessage.setString("WAVE:" + std::to_string(stageLevel) + "     ZOMBIES:" + std::to_string(0));
	Utils::SetOrigin(stageInfoMessage, Origins::TL);

	manaMessage.setString("MANA:" + std::to_string(0));
	Utils::SetOrigin(manaMessage, Origins::TL);

	hpBar.setSize({ BAR_SIZE,50.f });
}

void GameUI::Update(float dt)
{
}

void GameUI::Draw(sf::RenderWindow& window)
{
	window.draw(scoreMessage);
	window.draw(ammoMessage);
	window.draw(stageInfoMessage);
	window.draw(ammoIcon);
	window.draw(hpBar);
	window.draw(manaMessage);
}

void GameUI::UpdateAmmoMessage()
{
	ammoMessage.setString(std::to_string(player->GetCurrentAmmo()) + "/" + std::to_string(player->GetReserveAmmo()));
	Utils::SetOrigin(ammoMessage, Origins::TL);
}

void GameUI::UpdateScoreMessage(int score)
{
	scoreMessage.setString("SCORE:" + std::to_string(score));
	Utils::SetOrigin(scoreMessage, Origins::TL);
}

void GameUI::UpdateZombieCountMessage(int zombieCount)
{
	stageInfoMessage.setString("WAVE:" + std::to_string(stageLevel) + "     ZOMBIES:" + std::to_string(zombieCount));
	Utils::SetOrigin(stageInfoMessage, Origins::TL);
}

void GameUI::UpdateHpBar(int maxHp, int hp)
{
	hpBar.setSize({ BAR_SIZE * ((float)hp / maxHp),50.f });
}

void GameUI::UpdateManaMessage(int mp)
{
	manaMessage.setString("MANA:" + std::to_string(mp));
	Utils::SetOrigin(manaMessage, Origins::TL);
}
