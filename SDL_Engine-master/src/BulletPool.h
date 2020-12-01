#pragma once
#ifndef __BULLETPOOL__
#define __BULLETPOOL__

#include "Bullet.h"

class BulletPool {
public:
   BulletPool(int);
    ~BulletPool();

    Bullet* Spawn();

    void Despawn(Bullet*);
    std::vector<Bullet*> active;
private:
    std::vector<Bullet*> inactive;
};
#endif 