#pragma once

#include <SFML/Audio.hpp>
#include "entity.h"
#include "score.h"
#include "lives.h"

class Ball : public Entity
{
public:
	Ball(Lives* lives, Score* score, float x, float y, float direction);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
	void Bounce(float x, float y);

	~Ball();
private:
	Score* score;
	Lives* lives;
	sf::SoundBuffer* soundBuffer;
	sf::Sound* sound;
};