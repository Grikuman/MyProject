//*=======================================================*
// Collision.h
// �����F�����蔻����s��
//*=======================================================*
#pragma once

class Collision
{
public:
	// �n�ʂƂ̓����蔻����s���Abool�l�Ō��ʂ�Ԃ��i�v���C���[���W,�n�ʂ̐ݒ�j
	bool CheckGround(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 ground
	);

	bool CheckCollision(DirectX::BoundingSphere box1, DirectX::BoundingSphere box2);

private:
};