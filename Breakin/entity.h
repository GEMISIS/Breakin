#pragma once

#include <SFML/Graphics.hpp>
#include <string>

typedef enum
{
	COL_TOP = 0,
	COL_BOTTOM = 1,
	COL_LEFT = 2,
	COL_RIGHT = 3
}COLLISION_DIRECTION;

class Entity : public sf::Sprite
{
public:
	sf::Vector2f velocity;
	static sf::Vector2f scroll;

	Entity();

	void Load(std::string filename);

	virtual bool Update(sf::RenderWindow* window);

	bool CheckCollision(Entity* entity);
	bool CollisionSide(Entity* entity, COLLISION_DIRECTION side);

	virtual void Collision(Entity* entity);

	int GroupID();

	int Active();

	void Destroy();

	~Entity();
protected:
	int active;
	int groupId;
private:
	sf::Texture* texture;
};

