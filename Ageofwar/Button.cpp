#include "stdafx.h"
#include "Button.h"
#include "GameScene.h"
#include "InputMgr.h"


//버튼 입렵시 텍스트가 온오프로 드로우 되야하고 
	// 버튼 입력값을 받아 타입이 정해져서 소환되어야한다.
	//되팔기 입력받아 활성화 된상태에서 터렛에서 클릭을 더하면 삭제되는걸로
	// 업그레이드..
//his->spwan = flase;  이렇게 draw 는 if(swan)windowl.draw 로 하고

Button::Button(const std::string& name)
	: GameObject(name)	
{
}

void Button::Init()
{
	but.setFont(FONT_MGR.Get("fonts/DS-DIGIT.ttf"));
	but2.setFont(FONT_MGR.Get("fonts/DS-DIGIT.ttf"));
	but3.setFont(FONT_MGR.Get("fonts/DS-DIGIT.ttf"));
	but4.setFont(FONT_MGR.Get("fonts/DS-DIGIT.ttf"));
	but5.setFont(FONT_MGR.Get("fonts/DS-DIGIT.ttf"));
	but6.setFont(FONT_MGR.Get("fonts/DS-DIGIT.ttf"));

	const int CHARSIZE = 10;
	but.setCharacterSize(CHARSIZE);
	but2.setCharacterSize(CHARSIZE);
	but3.setCharacterSize(CHARSIZE);
	but4.setCharacterSize(CHARSIZE);
	but5.setCharacterSize(CHARSIZE);
	but6.setCharacterSize(CHARSIZE);

	const int MESSAGEGAP = CHARSIZE + 20.f;
	but.setPosition({ 100.f,200.f });
	but2.setPosition({ 100.f + MESSAGEGAP,200.f  });
	but3.setPosition({ 100.f + MESSAGEGAP * 2,200.f});
	but4.setPosition({ 100.f + MESSAGEGAP * 3,200.f });
	but5.setPosition({ 100.f + MESSAGEGAP * 4,200.f });
	but6.setPosition({ 100.f + MESSAGEGAP * 5,200.f});


	but.setString("Unit");
	but2.setString("u1");
	but3.setString("turret");
	but4.setString("t1");
	but5.setString("sell");
	but6.setString("Up");

	
	
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

	buttonBounds = but.getGlobalBounds();
	if (IsMouseOver(buttonBounds))
	{
		but.setFillColor(sf::Color::Yellow);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			but = SetActive(false);          
			if (nextButton != nullptr)
				nextButton->SetActive(true);
		}
	}
	else
	{
		but.setFillColor(sf::Color::White);
	}



}

void Button::Draw(sf::RenderWindow& window)
{
}
