#pragma once
#ifndef __PLAYERSCENE2__
#define __PLAYERSCENE2__

#include "Sprite.h"

class PlayerScene2 final : public Sprite
{
public:
	PlayerScene2();
	~PlayerScene2();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void stopMoving();
	
	float PlayerSpeed;
	float bulletSpawnTimer;
private:
	/*const float SPEED = 100.0f;
	const float ACCELERATION = 10.0f;*/
	glm::vec2 m_direction;
};

#endif 