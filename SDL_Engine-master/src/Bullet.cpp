#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet() {
	TextureManager::Instance()->load("../Assets/textures/Bullet1.png", "bullet");

	auto size = TextureManager::Instance()->getTextureSize("bullet");

	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(700.0f, 300.0f);
	setType(TARGET);

	Reset();
}

Bullet::~Bullet()
= default;

void Bullet::draw() {
	if (active)
	{
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
	}
}

void Bullet::update() {
	if (active) {
		float deltaTime = 1.0f / 60.0f;
		getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration * deltaTime;
		getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
	}
}

void Bullet::clean()
{
}

void Bullet::Reset()
{
	active = false;
	getRigidBody()->velocity = glm::vec2(0.0f, 20.0f);
	getRigidBody()->acceleration = glm::vec2(0, 9.8);
	getRigidBody()->isColliding = false;
}
