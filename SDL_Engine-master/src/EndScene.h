#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "PlayerScene2.h"
class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	void SpawnBullet();
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void GUI_Function() const;
	float bulletSpawnTimerStart;
	float bulletSpawnTimerDuration;
private:
	PlayerScene2* m_pPlayer;
	Label* m_label{};
	BulletPool* m_pPool;
	Button* m_pRestartButton;
};

#endif /* defined (__END_SCENE__) */