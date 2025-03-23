#pragma once
#ifndef BULLET_FACTORY_DEFINED
#define BULLET_FACTORY_DEFINED
#include <vector>
#include "Interface/IBulletFactory.h"

class Bullet;

class BulletFactory : public IBulletFactory
{
public:
	// éwíËÇ≥ÇÍÇΩñCíeîzóÒÇê∂ê¨Ç∑ÇÈ
	static std::vector<std::unique_ptr<IBullet>> CreateBullets(const int& number, const int& nodeNumber, IBullet::BulletState bulletState);
};

#endif	// BULLET_FACTORY_DEFINED
