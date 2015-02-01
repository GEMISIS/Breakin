#pragma once

#include "entity_manager.h"
#include "game_state.h"
#include "score.h"
#include "lives.h"
#include "speech.h"

#include "map.h"

#include "SaveSystem.h"

extern int bricksDestroyed;
extern bool gameOver;
extern SaveSystem saveSystem;

class main_game : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	Score* score;
	Lives* lives;
	Speech* speech;
	sf::Text* pausedText;

	sf::Font* font;

	bool paused, enterKey;

	EntityManager* manager;

	int brickCount;
};