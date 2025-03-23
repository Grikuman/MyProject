#pragma once
#ifndef PLAYER_STRIKE_FORWADING_DEFINED
#define PLAYER_STRIKE_FORWADING_DEFINED
#include "Interface/IState.h"

class SoccerPlayer;

// PlayerStrikeForwarding�N���X���`����
class PlayerStrikeForwarding : public IState
{
public:
	// �R���X�g���N�^
	PlayerStrikeForwarding(SoccerPlayer* player);
	// �f�X�g���N�^
	~PlayerStrikeForwarding();
	// ����������
	void Initialize();
	// ���O�X�V����
	void PreUpdate();
	// �X�V����
	void Update(const float& elapsedTime);
	// ����X�V����
	void PostUpdate();
	// �`�悷��
	void Render();
	// �㏈�����s��
	void Finalize();

private:
	SoccerPlayer* m_player;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
	// �A�j���[�V�����{�[���z��
	DirectX::ModelBone::TransformArray m_animBones;
	// ������
	float m_totalSeconds;
	// �A�j���[�V��������
	double  m_animTime;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �v���[���[���f��
	DirectX::Model* m_soccerPlayerModel;
	// �A�j���[�V����
	std::unique_ptr<DX::AnimationSDKMESH> m_animation;

	// �o�E���f�B���O�X�t�B�A
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphereRightLeg;
	// �E���{�[���C���f�b�N�X
	uint32_t m_rightLeg;
	// �{�[���}�g���b�N�X
	DirectX::SimpleMath::Matrix m_boneMatrix;
	// �Փ˒�
	bool m_inCollision;
};

#endif		// PLAYER_STRIKE_FORWADING_DEFINED



