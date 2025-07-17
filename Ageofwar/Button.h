#pragma once
#include "GameObject.h"
class Button :    public GameObject
{
protected:
	sf::Texture buttonTexture; 
	

public:
	Button(const std::string& name = "");
	virtual ~Button() = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	//텍스쳐 구분화 
	//게임씬에서의 인풋 받아다가 그걸로 유닛에 명령 전달
	//버튼이동 draw 온오프식으로
	
};

