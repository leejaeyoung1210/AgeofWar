#pragma once
#include "GameObject.h"
class Button :    public GameObject
{
protected:
	sf::Texture buttonTexture; 
	

public:
	Button(const std::string& name = "");
	virtual ~Button() = default;

	// GameObject��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	//�ؽ��� ����ȭ 
	//���Ӿ������� ��ǲ �޾ƴٰ� �װɷ� ���ֿ� ��� ����
	//��ư�̵� draw �¿���������
	
};

