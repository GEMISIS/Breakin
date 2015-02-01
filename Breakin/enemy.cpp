#include "main_game.h"
#include "enemy.h"

enemy::enemy(float x, float y)
{
	this->position = sf::Vector2f(x, y);
	this->Load("brick.png");
	this->setColor(sf::Color::Blue);
	this->setPosition(x, y);
	this->groupId = 2;
	this->health = 3;
	this->maxHealth = 3;
}

bool enemy::Update(sf::RenderWindow* window)
{
	this->setPosition(this->position.x - Entity::scroll.x, this->position.y - Entity::scroll.y);
	sf::Color color = this->getColor();
	switch (this->maxHealth - this->health)
	{
	case 0:
		color.r = 0;
		color.b = 255;
		this->setColor(color);
		break;
	case 1:
		color.r = 128;
		color.b = 128;
		this->setColor(color);
		break;
	case 2:
		color.r = 255;
		color.b = 0;
		this->setColor(color);
		break;
	}
	if (this->health <= 0)
	{
		bricksDestroyed += 1;
		this->Destroy();
	}
	Entity::Update(window);
	return true;
}

void enemy::Collision(Entity* entity)
{
}

