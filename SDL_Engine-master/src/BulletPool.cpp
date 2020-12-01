#include <iostream>
#include <vector>
#include "BulletPool.h"
#include "Bullet.h"

using namespace std;

BulletPool::BulletPool(int size)
{
    for (int i = 0; i < size; i++) {
        inactive.push_back(new Bullet());
    }
}

BulletPool::~BulletPool()
= default;

Bullet* BulletPool::Spawn() {
    Bullet* bullet = NULL;
    if (inactive.size() > 0) {
        bullet = inactive.back();
        bullet->Reset();
        bullet->active = true;
        inactive.pop_back();
        active.push_back(bullet);
    }
    return bullet;
}

void BulletPool ::Despawn(Bullet* bullet) {
    bullet->Reset();
    inactive.push_back(bullet);
    for (std::vector<Bullet*>::iterator myiter = active.begin(); myiter != active.end(); myiter++)
    {
        if (*myiter == bullet) {
            active.erase(myiter);
            return;
        }
    }
}