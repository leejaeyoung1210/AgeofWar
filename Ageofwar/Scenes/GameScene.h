#pragma once
#include "Scene.h"

class TextGo;

class GameScene : public Scene
{
protected:
	sf::Sprite background;
	

	
	TextGo* collisionText;
	TextGo* modeText;
	

	

public:
	GameScene();	
	~GameScene() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

