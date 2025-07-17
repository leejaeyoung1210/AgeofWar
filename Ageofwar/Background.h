#pragma once
#include "GameObject.h"
class Background :    public GameObject
{
protected:
	sf::Sprite background;
	std::string texId = "graphics/background.png";
		

public:
	Background(const std::string& name = "");
	virtual ~Background() = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return background.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return background.getGlobalBounds();
	}
};

