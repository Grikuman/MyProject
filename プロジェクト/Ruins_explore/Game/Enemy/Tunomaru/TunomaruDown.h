/*
	�t�@�C�����FTunomaruDown.h
	�@�@�@�T�v�F�̂܂�̃_�E����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Effect/DownEffect.h"

// �O���錾
class Tunomaru;

namespace NRLib
{
	class TPS_Camera;
};

class TunomaruDown : public IEnemyState
{
public:
	// �R���X�g���N�^
	TunomaruDown(Tunomaru* tunomaru);
	// �f�X�g���N�^
	~TunomaruDown();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �_�E������
	void Down();

private:
	// �_�E�����Ă��鎞��
	const float MAX_DOWNTIME = 180.f;

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// �G�t�F�N�g
	std::unique_ptr<DownEffect> m_effect;
	// �_�E�����Ă��鎞��
	float m_downTime;
};
