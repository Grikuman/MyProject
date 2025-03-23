#pragma once
#ifndef PLAYER_IDLING_DEFINED
#define PLAYER_IDLING_DEFINED
#include "Interface/IState.h"

class SoccerPlayer;

// PlayerIdling�N���X���`����
class PlayerIdling : public IState
{
public:
	// �R���X�g���N�^
	PlayerIdling(SoccerPlayer* player);
	// �f�X�g���N�^
	~PlayerIdling();
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
	DirectX::BoundingSphere m_boundingSphereLeftLeg;
	// ���r�{�[���C���f�b�N�X
	uint32_t m_leftLeg;
	// �{�[���}�g���b�N�X
	DirectX::SimpleMath::Matrix m_boneMatrix;
};

#endif		// PLAYER_IDLING_DEFINED
