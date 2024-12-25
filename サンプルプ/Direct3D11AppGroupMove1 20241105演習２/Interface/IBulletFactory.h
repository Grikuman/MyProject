#pragma once
#ifndef IBULLET_FACTORY_DEFINED
#define IBULLET_FACTORY_DEFINED
#include <vector>
#include "Interface/IBullet.h"

class Bullet;

class IBulletFactory
{
	// �w�肳�ꂽ�C�e�z��𐶐�����
	virtual std::vector<std::unique_ptr<IBullet>> CreateBullets(const int& number, const int& nodeNumber, IBullet::BulletState bulletState) = 0;
};

#endif			// IBULLET_FACTORY_DEFINED
