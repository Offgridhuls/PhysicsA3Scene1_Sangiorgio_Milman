#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "PlayerScene2.h"
EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Renderer::Instance()->getRenderer());
	TextureManager::Instance()->draw("backround", 400, 300, 0, 255, true);
	drawDisplayList();
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}
void EndScene::SpawnBullet() {
	Bullet* bullet = m_pPool->Spawn();
	if (bullet) {
		addChild(bullet);
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}
void EndScene::update()
{
	updateDisplayList();
	if (SDL_GetTicks() - bulletSpawnTimerStart >= m_pPlayer->bulletSpawnTimer) {
		SpawnBullet();
	}

	std::vector<Bullet*>& activeBullets = m_pPool->active;
	for (std::vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); ++myiter) {
		Bullet* bullet = *myiter;
		if (bullet->getTransform()->position.y >= 650) {
			m_pPool->Despawn(bullet);
			removeChild(bullet);
			break;
		}
		if (CollisionManager::AABBCheck(bullet, m_pPlayer)) {
			m_pPool->Despawn(bullet);
			removeChild(bullet);
			break;
		}
	}
}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
	TheGame::Instance()->quit();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
	m_pPlayer->moveLeft();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
	m_pPlayer->moveRight();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/BackgroundWW.jpg", "backround");
	
	m_pPlayer = new PlayerScene2();
	addChild(m_pPlayer);
	m_pPool = new BulletPool(10);
	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pRestartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pRestartButton->setAlpha(128);
	});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pRestartButton->setAlpha(255);
	});

	addChild(m_pRestartButton);
}
void EndScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Physics Assigment 3 Scene 1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	////Testing the Img::Button function

	float playerSpeed = 0;
	float spawnTimer = 0;
	/*if (ImGui::Button("Throw")) {
		m_pBall->doThrow();
		m_pBall->throwPosition = glm::vec2(200, 200);
	}*/
	if (ImGui::SliderFloat("Player Speed", &playerSpeed, 0.0f, 500.0f)) {
		m_pPlayer->PlayerSpeed = playerSpeed;
	}
	if (ImGui::SliderFloat("Bullet spawn timer, (1000.0 = 1 sec)", &spawnTimer, 0.0f, 6000.0f)) {
	m_pPlayer->bulletSpawnTimer = spawnTimer;
	}

		/*auto size = TextureManager::Instance()->getTextureSize("circle");
		m_pPlayer->RotAmount += 90;
		m_pPlayer->setWidth(size.y);
		m_pPlayer->setHeight(size.x);

	}*/

	//if (buttonPressed) {
	//	std::cout << "ThrowPressed" << std::endl;
	//}


	/*if(ImGui::Button("Throw"))
	{
		std::cout << "Throw Pressed" << std::endl;
	}*/

	ImGui::Separator();

	//static bool GravityBool = false;
	/*if ((ImGui::Checkbox("Gravity", &GravityBool)))
	{
		m_pBall->hasGravity = GravityBool;

	}*/
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
	//std::string grav = GravityBool ? "Gravity is turned ON" : "Gravity is turned OFF";
	//std::cout << grav << std::endl;
	/*static int xPlayerPos = 100;
	if (ImGui::SliderInt("PlayerPosition x", &xPlayerPos, 0, 800)) {
		m_pPlayer->getTransform()->position.x = xPlayerPos;
		m_pBall->throwPosition = glm::vec2(xPlayerPos, 200);
		m_pBall->getTransform()->position = m_pPlayer->getTransform()->position;
		m_pBall->getTransform()->position.x += m_pBall->getWidth();

	}*/