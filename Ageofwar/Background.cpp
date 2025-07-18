#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& name)
	: GameObject(name)
{
}

void Background::Init()
{	
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;	
	background.setTexture(TEXTURE_MGR.Get(texId), true);
}


void Background::Release()
{
}

void Background::Reset()
{
}	

void Background::Update(float dt)
{
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(background);
}
