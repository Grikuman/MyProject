#include "Framework/pch.h"
#include "Bullet/BulletFactory.h"
#include "Bullet/Bullet.h"

// �C�e�𐶐�����
std::vector<std::unique_ptr<IBullet>> BulletFactory::CreateBullets(const int& number, const int& nodeNumber, IBullet::BulletState bulletState)
{
	using namespace DirectX::SimpleMath;
	// �z���錾����
	std::vector<std::unique_ptr<IBullet>> bullets;
	// �z��̃T�C�Y��ݒ肷��
	bullets.resize(number);
	// �z��ɖC�e���i�[����
	for (int index = 0; index < number; index++)
	{
		// �C�e�𐶐�����
		bullets[index] = std::make_unique<Bullet>(nodeNumber, bulletState);
		// �C�e������������
		bullets[index]->Initialize();
	}
	// �C�e�z���Ԃ�
	return bullets;
}

