#pragma once
#include "GameObject.h"
class Player;

class GameUI : public GameObject
{
protected:	
	sf::Text skillMessage;
	sf::Text menuMessage;
	sf::Text expMessage;
	sf::Text hpBarMessage;
	sf::Text goldMessage;

	sf::Sprite goldIcon;
	sf::RectangleShape hpBar;

	
	std::string fontId = "fonts/DS-DIGIT.ttf";

	const float BAR_SIZE = 10.f;

	Player* player = nullptr;

public:
	GameUI(const std::string& name = "");
	virtual ~GameUI() = default;

	void SetPlayer(Player* p) { player = p; }
	

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateGoldMessage(int count);
	void UpdatehpBarMessage(int h);
	void UpdateExpMessage(int count);
	void UpdateHpBar(int maxHp, int hp);
	//void UpdateSkillMessage(int );
};
