#pragma once
#include "GameObject.h"
#include "InputMgr.h"
#include "Scene.h"
class Scene;

class Button : public GameObject
{
protected:
	Scene* scene;

	sf::Text but;
	sf::Text but2;
	sf::Text but3;
	sf::Text but4;
	sf::Text but5;
	sf::Text but6;


	sf::Vector2f cursor;
	sf::FloatRect buttonBounds;

	bool spawn = false;


public:
	Button(const std::string& name = "");
	virtual ~Button() = default;

	// GameObject을(를) 통해 상속됨
	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetMousePositionUI() const
	{		
		sf::Vector2i mousePosScreen = InputMgr::GetMousePosition();		
		return scene->ScreenToUi(mousePosScreen);
	}
	
	bool IsMouseOver(const sf::FloatRect& buttonBounds) const
	{
		sf::Vector2f mousePosUI = GetMousePositionUI();
		return buttonBounds.contains(mousePosUI);
	}

};

