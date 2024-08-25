/*
	@file	EnemySpawner.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class Player;
class Tunomaru;
class Tatemaru;
class Collision;

namespace NRLib
{
	class TPS_Camera;
}

// ��ʓI�ȃV�[���N���X
class EnemySpawner
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �v���C���[
	// 
	// �J�����I�u�W�F�N�g�ւ̃|�C���^
	NRLib::TPS_Camera* m_camera;
	// �������Ă���G�̐�
	int m_aliveEnemy;
	// �G�̍ő吔
	const int MAX_ENEMY = 2;
	// ���ꂼ��̓G�̐�
	static const int MAX_TUNOMARU = 2;
	static const int MAX_TATEMARU = 2;
	// �̂܂�
	std::unique_ptr<Tunomaru> m_tunomaru[MAX_TUNOMARU];
	// �����蔻��
	std::unique_ptr<Collision> m_collision;

	// �V�[���J�ڃt���O
	bool m_isChangeScene;

public:
	EnemySpawner();
	~EnemySpawner();

	void Initialize(CommonResources* resources, NRLib::TPS_Camera* camera);
	void Update(DirectX::BoundingSphere boundingSphere,bool isAttack);
	void Render();
	void Finalize();

	bool IsChangeScene();
public:
};
