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
	sf::RectangleShape hpBar2;
	sf::RectangleShape unitBar;

	std::string goldTexId = "graphics/coin.png";
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
	void UpdateExpMessage(int count);
	void UpdatehpBarMessage(int h);
	void UpdateHpBar(int maxHp, int hp);
	void UpdateHpBar2(int maxHp2, int hp2);
	
};
