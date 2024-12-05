//*=======================================================*
// Collision.h
// �����F�����蔻����s��
//*=======================================================*
#pragma once

class Player;
class Tunomaru;
class RockBoss;
class ICollisionObject;

class Collision
{
public:
	// �R���W�����̃C���X�^���X�擾
	static Collision* const GetInstance();
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

public:
	//�f�X�g���N�^
	~Collision() = default;
	// �X�V����
	void Update();
	// �I������
	void Finalize();

public:
	// �v���C���[��ݒ肷��
	void SetPlayer(Player* player) { m_player = player; };


	//----------------------------------------------------------------------------
	// �U���̔��� 
	//----------------------------------------------------------------------------
public:
	// �v���C���[����G�ւ̍U������
	void CheckHitPlayerToEnemy(ICollisionObject* enemy);
	// �{�X�Ƃ̓����蔻��
	void CheckHitRockBoss(RockBoss* rockboss);

	//----------------------------------------------------------------------------
	// �Փ˂̔���
	//----------------------------------------------------------------------------
public:
	// �v���C���[�Ƌ��I�u�W�F�N�g�̉����߂�����
	void CheckPushBack(ICollisionObject* object);

private:
	// �R���W�����N���X
	static std::unique_ptr<Collision> m_collision;
	// �v���C���[
	Player* m_player;
};