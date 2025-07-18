#include "stdafx.h"
#include "Button.h"
#include "GameScene.h"
#include "InputMgr.h"


//버튼 입렵시 텍스트가 엑티브 활성비활성으로 돼야하고 
	// 버튼 입력값을 받아 타입이 정해져서 소환되어야한다.
	//되팔기 입력받아 활성화 된상태에서 터렛에서 클릭을 더하면 삭제되는걸로
	// 업그레이드..
//his->spwan = flase;  이렇게 draw 는 if(swan)windowl.draw 로 하고

Button::Button(const std::string& name)
	: GameObject(name)
{
}
void Button::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Button::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}
void Button::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Button::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Button::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Button::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;	
	

	basicbutton = { ButtonType::unit,ButtonType::turret,ButtonType::sell,ButtonType::addspace,ButtonType::upgrade };
	unitbutton ={ButtonType::u1,ButtonType::u2,ButtonType::u3,ButtonType::back };
	turretbutton = { ButtonType::t1,ButtonType::t2,ButtonType::t3,ButtonType::back };
	for (int i = 0; i < unitbutton.size(); ++i)
	{
		Button* basebtn = new Button();
		basebtn->ButtonTypeSettype(unitbutton[i]);		
		basebtn->body.setTexture(TEXTURE_MGR.Get(texId), true);
		basebtn->GetGlobalBounds();
		basebtn->SetPosition({ 640.f + (basebtn->GetGlobalBounds().width+50.f)*i,100.f });
		basebtn->SetActive(true);

		unitbuttons.push_back(basebtn);
		scene->AddGameObject(basebtn);
	}
	for (int i = 0; i < unitbutton.size(); ++i)
	{
		Button* unitbtn = new Button();
		unitbtn->ButtonTypeSettype(unitbutton[i]);
		unitbtn->body.setTexture(TEXTURE_MGR.Get(texId), true);
		unitbtn->GetGlobalBounds();
		unitbtn->SetPosition({ 640.f + (200.f * (i + 1)),100.f });
		unitbtn->SetActive(false);

		unitbuttons.push_back(unitbtn);
		scene->AddGameObject(unitbtn);
	}
	for (int i = 0; i < turretbutton.size(); ++i)
	{
		Button* turtbtn = new Button();
		turtbtn->ButtonTypeSettype(unitbutton[i]);
		turtbtn->body.setTexture(TEXTURE_MGR.Get(texId), true);
		turtbtn->GetGlobalBounds();
		turtbtn->SetPosition({ 640.f + (200.f * (i + 1)),100.f });
		turtbtn->SetActive(false);

		turretbuttons.push_back(turtbtn);
		scene->AddGameObject(turtbtn);
	}
}
void Button::Release()
{
}

void Button::Reset()
{
}
void Button::Update(float dt)
{
	cursor = GetMousePositionUI();

	



}

void Button::Draw(sf::RenderWindow& window)
{
}

void Button::ButtonTypeSettype(ButtonType type)
{
	this->type = type;
	switch (this->type)
	{
	case ButtonType::unit:
		texId = "UnitButton.png";		
		break;
	case ButtonType::turret:
		texId = "TurretButton.png";
		break;
	case ButtonType::sell:
		texId = "SellButton.png";
		break;
	case ButtonType::addspace:
		texId = "UnitButton.png";
		break;
	case ButtonType::upgrade:
		texId = "addButton.png";
		break;
	case ButtonType::skill:
		texId = "skill.png";
		break;
	case ButtonType::u1:
		texId = "u1Button.png";
		break;
	case ButtonType::u2:
		texId = "u2Button.png";
		break;
	case ButtonType::u3:
		texId = "u3Button.png";
		break;
	case ButtonType::t1:
		texId = "t1Button.png";
		break;
	case ButtonType::t2:
		texId = "t2Button.png";
		break;
	case ButtonType::t3:
		texId = "t3Button.png";
		break;
	case ButtonType::back:
		texId = "backButton.png";
		break;
	case ButtonType::cancel:
		texId = "UnitButton.png";
		break;
	default:
		break;
	}




}
