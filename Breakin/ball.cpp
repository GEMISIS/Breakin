#include "ball.h"
#include "enemy.h"

Ball::Ball(Lives* lives, Score* score, float x, float y, float direction)
{
	this->active = 1;
	this->groupId = 3;
	this->Load("ship.png");
	this->setScale(0.25f, 0.25f);
	this->velocity.x = cos(direction / 180.0f * 3.14f) * 3;
	this->velocity.y = sin(direction / 180.0f * 3.14f) * 3;
	this->setPosition(x + this->getGlobalBounds().width, y + this->getGlobalBounds().height);
	this->score = score;
	this->lives = lives;

	this->soundBuffer = new sf::SoundBuffer();
	this->soundBuffer->loadFromFile("Sounds/bounce.wav");
	this->sound = new sf::Sound(*this->soundBuffer);
}

void Ball::Bounce(float x, float y)
{
	if (x > 0)
	{
		this->velocity.x *= -x;
	}
	if (y > 0)
	{
		this->velocity.y *= -y;
	}
	this->sound->play();
}

bool Ball::Update(sf::RenderWindow* window)
{
	if (this->getPosition().x <= 0 || this->getPosition().x + this->getGlobalBounds().width >= window->getSize().x)
	{
		this->Bounce(1, 0);
	}
	if (this->getPosition().y <= 0)
	{
		this->Bounce(0, 1);
	}
	if (this->getPosition().y + this->getGlobalBounds().height >= window->getSize().y)
	{
		this->lives->RemoveLife();
		this->setPosition(window->getSize().x / 2, window->getSize().y - window->getSize().y / 8);
		this->velocity.x = cos(225 / 180.0f * 3.14f) * 3;
		this->velocity.y = sin(225 / 180.0f * 3.14f) * 3;
	}
	Entity::Update(window);
	return true;
}

void Ball::Collision(Entity* entity)
{
	switch (entity->GroupID())
	{
	case 2:
		if (this->CollisionSide(entity, COL_LEFT) || this->CollisionSide(entity, COL_RIGHT))
		{
			if (this->CollisionSide(entity, COL_TOP) || this->CollisionSide(entity, COL_BOTTOM))
			{
				reinterpret_cast<enemy*>(entity)->health -= 1;
				this->Bounce(1, 1);
				this->score->IncrementScore();
			}
			else
			{
				reinterpret_cast<enemy*>(entity)->health -= 1;
				this->Bounce(1, 0);
				this->score->IncrementScore();
			}
		}
		else if (this->CollisionSide(entity, COL_TOP) || this->CollisionSide(entity, COL_BOTTOM))
		{
			reinterpret_cast<enemy*>(entity)->health -= 1;
			this->Bounce(0, 1);
			this->score->IncrementScore();
		}
		break;
	}
}

Ball::~Ball()
{
	delete this->sound;
	delete this->soundBuffer;
}