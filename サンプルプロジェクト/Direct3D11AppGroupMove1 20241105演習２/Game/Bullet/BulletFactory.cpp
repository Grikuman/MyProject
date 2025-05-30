#include "Framework/pch.h"
#include "Bullet/BulletFactory.h"
#include "Bullet/Bullet.h"

// 砲弾を生成する
std::vector<std::unique_ptr<IBullet>> BulletFactory::CreateBullets(const int& number, const int& nodeNumber, IBullet::BulletState bulletState)
{
	using namespace DirectX::SimpleMath;
	// 配列を宣言する
	std::vector<std::unique_ptr<IBullet>> bullets;
	// 配列のサイズを設定する
	bullets.resize(number);
	// 配列に砲弾を格納する
	for (int index = 0; index < number; index++)
	{
		// 砲弾を生成する
		bullets[index] = std::make_unique<Bullet>(nodeNumber, bulletState);
		// 砲弾を初期化する
		bullets[index]->Initialize();
	}
	// 砲弾配列を返す
	return bullets;
}

