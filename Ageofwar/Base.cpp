#include "stdafx.h"
#include "Base.h"

Base::Base(const std::string& name)
{
}

void Base::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Base::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Base::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Base::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Base::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder =-1;
	SetActive(true);
}

void Base::Release()
{
}

void Base::Reset()
{
	sf::FloatRect windowbound = FRAMEWORK.GetWindowBounds();
	gameScene = (GameScene*)SCENE_MGR.GetCurrentScene();

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetScale({ 0.4f, 0.4f });

	hp = maxHp;

}

void Base::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());

}

void Base::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);

}

void Base::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		SetActive(false);
	}

}
