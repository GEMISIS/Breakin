#pragma once

#include "entity.h"
#include "lives.h"

extern SaveSystem saveSystem;

class main_guy : public Entity
{
public:
	main_guy(sf::RenderWindow* window, EntityManager* entityManager);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
	float speed;
	EntityManager* entityManager;
	float direction;
};

