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
	// �v���C���[�ƒʏ�G�̔�����܂Ƃ߂�����
	void NormalEnemy(IEnemy* enemy);
	// �v���C���[�ƃ{�X�̓����蔻����܂Ƃ߂�����
	void BossEnemy(IEnemy* enemy);
	// �v���C���[�ƃX�e�[�W�̏Փ˔���
	void CheckPlayerStageCollision(DirectX::BoundingBox object);
	// �G�ƃX�e�[�W�̏Փ˔���
	void CheckEnemyStageCollision(IEnemy& enemy, const DirectX::BoundingBox stageObject);
public:
	// �v���C���[��ݒ肷��
	void SetPlayer(Player* player) { m_player = player; };
	// �R���W�����̃C���X�^���X�擾
	static Collision* const GetInstance();

private:
	// �v���C���[����G�ւ̍U������
	void CheckHitPlayerToEnemy(IEnemy* enemy); 
	// �v���C���[�Ƌ��I�u�W�F�N�g�̉����߂�����
	void CheckPushBack(ICollisionObject* object); 
	// ���莞�̌��ʉ�
	void PlayerCollisionSound(IEnemy* enemy);

public:
	//�f�X�g���N�^
	~Collision() = default;

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