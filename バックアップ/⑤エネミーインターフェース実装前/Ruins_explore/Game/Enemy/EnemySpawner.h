/*
	@file	EnemySpawner.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class SmallEnemy;
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

	NRLib::TPS_Camera* m_camera; // �J�����I�u�W�F�N�g�ւ̃|�C���^

	// ���^�G�l�~�[
	static const int MAX_SMALL_ENEMY = 2;                        // ���^�G�l�~�[������
	std::unique_ptr<SmallEnemy> m_smallEnemy[MAX_SMALL_ENEMY];   // ���^�G�l�~�[
	// �����蔻��
	std::unique_ptr<Collision> m_collision;

public:
	EnemySpawner();
	~EnemySpawner();

	void Initialize(CommonResources* resources, NRLib::TPS_Camera* camera);
	void Update(DirectX::BoundingSphere boundingSphere,bool isAttack);
	void Render();
	void Finalize();
public:
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }
};
