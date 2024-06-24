/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "Game/Player/Player.h"

// �O���錾
class CommonResources;

namespace NRLib
{
	class FixedCamera;
};

class PlayScene final :
    public IScene
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C���[
	std::unique_ptr<Player> m_player;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
