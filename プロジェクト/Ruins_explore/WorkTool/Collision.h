/*
	�t�@�C�����FCollision.h
	�@�@�@�T�v�F�����蔻�菈�����s���N���X
*/
#pragma once

class Player;
class Tunomaru;
class ICollisionObject;
class IEnemy;

class Collision
{
public:
	// �v���C���[�ƒʏ�G�̓����蔻����܂Ƃ߂�����
	void PlayerToNormalEnemy(IEnemy* enemy);
	// �v���C���[����G�ւ̍U������
	void CheckHitPlayerToEnemy(IEnemy* enemy);
	// �v���C���[�Ƌ��I�u�W�F�N�g�̉����߂�����
	void CheckPushBack(ICollisionObject* object);
	// �v���C���[�ƃX�e�[�W�̃I�u�W�F�N�g�ŉ����߂�����
	void CheckPushBack(DirectX::BoundingBox object);
public:
	// �R���W�����̃C���X�^���X�擾
	static Collision* const GetInstance();

public:
	// �v���C���[��ݒ肷��
	void SetPlayer(Player* player) { m_player = player; };

public:
	//�f�X�g���N�^
	~Collision() = default;
	// �X�V����
	void Update();
	// �I������
	void Finalize();

private:
	// �R���X�g���N�^
	Collision();
	// �C���X�^���X���R�s�[���邱�Ƃ��֎~����
	void operator=(const Collision&) = delete;
	// �C���X�^���X�����[�u���邱�Ƃ��֎~����
	Collision& operator= (Collision&&) = delete;
	// �R�s�[�R���X�g���N�^�͋֎~����
	Collision(const Collision&) = delete;
	// ���[�u�R���X�g���N�^�͋֎~����
	Collision(Collision&&) = delete;

private:
	// �R���W�����N���X
	static std::unique_ptr<Collision> m_collision;
	// �v���C���[
	Player* m_player;
};