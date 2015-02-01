#pragma once

#include "entity.h"
#include "map.h"

extern int bricksDestroyed;

class enemy : public Entity
{
public:
	enemy(float x, float y);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
	int health;
private:
	int maxHealth;
	sf::Vector2f position;
};

