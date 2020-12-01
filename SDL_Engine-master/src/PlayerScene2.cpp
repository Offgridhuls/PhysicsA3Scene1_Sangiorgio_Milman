#include "PlayerScene2.h"
#include "TextureManager.h"
#include "EndScene.h"
PlayerScene2::PlayerScene2()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");

	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 550.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

PlayerScene2::~PlayerScene2()
= default;

void PlayerScene2::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void PlayerScene2::update()
{
	const float deltaTime = 1.0f / 60.f;

	glm::vec2 pos = getTransform()->position;
	/*pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;*/

	//getTransform()->position = pos;
}

void PlayerScene2::clean()
{

}

void PlayerScene2::moveLeft() {
	const float deltaTime = 1.0f / 60.0f;
	getRigidBody()->velocity = glm::vec2(-PlayerSpeed, 0.0f);
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
}

void PlayerScene2::moveRight() {
	const float deltaTime = 1.0f / 60.0f;
	getRigidBody()->velocity = glm::vec2(PlayerSpeed, 0.0f);
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
}

void PlayerScene2::stopMoving() {
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}
