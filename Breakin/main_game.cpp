#include "main_game.h"
#include "main_menu.h"
#include "game_over.h"
#include "win_screen.h"

#include "main_guy.h"
#include "enemy.h"
#include "ball.h"

bool gameOver = false;
SaveSystem saveSystem;
int bricksDestroyed = 0;

void main_game::Initialize(sf::RenderWindow* window)
{
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	this->score = new Score(*font, 64U);
	this->lives = new Lives(*font, 64U);
	this->lives->setPosition(window->getSize().x - this->lives->getGlobalBounds().width, 0);
	this->speech = new Speech(*font, 32U, window);

	this->pausedText = new sf::Text("Paused\nPress Escape to Quit", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->paused = false;
	this->enterKey = true;

	manager = new EntityManager();

	this->manager->Add("main_guy", new main_guy(window, manager));
	this->manager->Add("ball", new Ball(this->lives, this->score, window->getSize().x / 2, window->getSize().y - window->getSize().y / 8, 225.0f));

	this->brickCount = 16 * 10;
	for (int y = 0; y < 10; y += 1)
	{
		for (int x = 0; x < 16; x += 1)
		{
			this->manager->Add("block", new enemy(x * (64 + 10) + 64, y * (32 + 10) + 64));
		}
	}
}
void main_game::Update(sf::RenderWindow* window)
{
	this->brickCount -= bricksDestroyed;
	bricksDestroyed = 0;
	if (this->brickCount <= 0)
	{
		gameOver = false;
		coreState.SetState(new win_screen());
		return;
	}
	if (this->paused)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			saveSystem.x = this->manager->Get("main_guy")->getPosition().x + Entity::scroll.x;
			saveSystem.y = this->manager->Get("main_guy")->getPosition().y + Entity::scroll.y;
			saveSystem.Save();
			coreState.SetState(new main_menu());
			return;
		}
	}
	else if (this->speech->speaking)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->speech->speaking = false;
		}
	}
	else
	{
		if (!this->manager->Update(window))
		{
			return;
		}
		this->score->Update();
		this->lives->Update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = true;
		}
	}
	if (gameOver || this->lives->Value() <= 0)
	{
		gameOver = false;
		coreState.SetState(new game_over());
		return;
	}
	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void main_game::Render(sf::RenderWindow* window)
{
	this->manager->Render(window);
	window->draw(*this->score);
	window->draw(*this->lives);
	this->speech->Render();

	if (this->paused)
	{
		window->draw(*this->pausedText);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
	delete this->score;
	delete this->lives;
	delete this->pausedText;
	delete this->font;

	delete this->manager;
}
