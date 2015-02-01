#include "main_game.h"
#include "main_guy.h"
#include "ball.h"

main_guy::main_guy(sf::RenderWindow* window, EntityManager* entityManager)
{
	this->Load("paddle.png");
	this->setColor(sf::Color::Green);
	this->setPosition(window->getSize().x / 2 - this->getGlobalBounds().width / 2, window->getSize().y - this->getGlobalBounds().height);
	this->speed = 4.0f;
	this->groupId = 1;
	this->entityManager = entityManager;
	Entity::scroll = sf::Vector2f(0, 0);
}

bool main_guy::Update(sf::RenderWindow* window)
{
	this->velocity.x = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) * this->speed;

	if (this->velocity.x > 0)
	{
		this->direction = 0.0f;
	}
	else if (this->velocity.x < 0)
	{
		this->direction = 180.0f;
	}
	while (this->getPosition().x <= 0)
	{
		this->move(1, 0);
		this->velocity.x = 0;
	}
	while (this->getPosition().x + this->getGlobalBounds().width >= window->getSize().x)
	{
		this->move(-1, 0);
		this->velocity.x = 0;
	}

	Entity::Update(window);
	return true;
}

void main_guy::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 3:
		if (entity->getPosition().y >= this->getPosition().y && 
			entity->getPosition().x + entity->getGlobalBounds().width >= this->getPosition().x)
		{
			reinterpret_cast<Ball*>(entity)->Bounce(1, 1);
			this->move(-this->velocity);
		}
		else if (entity->getPosition().y >= this->getPosition().y &&
			entity->getPosition().x <= this->getPosition().x + this->getGlobalBounds().width)
		{
			reinterpret_cast<Ball*>(entity)->Bounce(1, 1);
			this->move(-this->velocity);
		}
		else
		{
			reinterpret_cast<Ball*>(entity)->Bounce(0, 1);
		}
		break;
	}
}

