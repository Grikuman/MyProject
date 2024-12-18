/*
	@file	Stage1-1.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"

#include "Game/StageObject/Sky.h"
#include "Game/StageObject/Field.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/UI/TimeUI.h"


namespace NRLib
{
	class FixedCamera;
};

class Stage1_1 final : public IStage
{
public:
	// �R���X�g���N�^
	Stage1_1();
	// �R���X�g���N�^
	~Stage1_1() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �Q�[���̐�������
	static const int MAX_GAMETIME = 60;

private:
	// �v���C���[
	std::unique_ptr<Player> m_player;
	// �V��
	std::unique_ptr<Sky> m_sky;
	// �t�B�[���h
	std::unique_ptr<Field> m_field;
	// �G�l�~�[�X�|�i�[
	std::unique_ptr<EnemySpawner> m_enemySpawner;
	//TextUI
	std::unique_ptr<TimeUI> m_timeUI;
	// �v���C�V�[��UI

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	// �Q�[������
	float m_gameTime;
};
