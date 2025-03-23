#include "Framework/pch.h"
#include "Bullet/BulletFactory.h"
#include "Bullet/Bullet.h"

// –C’e‚ğ¶¬‚·‚é
std::vector<std::unique_ptr<IBullet>> BulletFactory::CreateBullets(const int& number, const int& nodeNumber, IBullet::BulletState bulletState)
{
	using namespace DirectX::SimpleMath;
	// ”z—ñ‚ğéŒ¾‚·‚é
	std::vector<std::unique_ptr<IBullet>> bullets;
	// ”z—ñ‚ÌƒTƒCƒY‚ğİ’è‚·‚é
	bullets.resize(number);
	// ”z—ñ‚É–C’e‚ğŠi”[‚·‚é
	for (int index = 0; index < number; index++)
	{
		// –C’e‚ğ¶¬‚·‚é
		bullets[index] = std::make_unique<Bullet>(nodeNumber, bulletState);
		// –C’e‚ğ‰Šú‰»‚·‚é
		bullets[index]->Initialize();
	}
	// –C’e”z—ñ‚ğ•Ô‚·
	return bullets;
}

