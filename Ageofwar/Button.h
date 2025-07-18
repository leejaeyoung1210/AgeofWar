#pragma once
#include "GameObject.h"
#include "InputMgr.h"
#include "Scene.h"
class Scene;

class Button : public GameObject
{
public:
	enum class ButtonType
	{	
		unit,
		turret,
		sell,
		addspace,
		upgrade,
		skill,
		u1,
		u2,
		u3,
		t1,
		t2,
		t3,
		back,
		cancel,
	};


protected:
	Scene* scene;
	ButtonType type = ButtonType::unit;

	sf::Sprite body;
	std::string texId;
	
	sf::Vector2f cursor;
	sf::FloatRect buttonBounds;

	std::vector<ButtonType> basicbutton;
	std::vector<Button*> basicbuttons;

	std::vector<ButtonType> unitbutton;
	std::vector<Button*> unitbuttons; 

	std::vector<ButtonType> turretbutton;
	std::vector<Button*> turretbuttons;


public:
	Button(const std::string& name = "");
	virtual ~Button() = default;

	sf::Vector2f Getposition() const { return position; };
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	// GameObject을(를) 통해 상속됨
	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	ButtonType ButtonTypeGetType() const { return type; };
	void ButtonTypeSettype(ButtonType type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	sf::Vector2f GetMousePositionUI() const
	{		
		sf::Vector2i mousePosScreen = InputMgr::GetMousePosition();		
		return scene->ScreenToUi(mousePosScreen);
	}
	
	bool IsMouseOver() const
	{
		sf::Vector2f mousePosUI = GetMousePositionUI();
		return GetGlobalBounds().contains(mousePosUI);
	}



};

