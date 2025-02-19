/*
	@file	FollowCamera.cpp
	@brief	��ǂ��J�����N���X�A�΂˕t��
*/
#include "pch.h"
#include "FollowCamera.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
FollowCamera::FollowCamera()
	:
	m_eye{},
	m_target{},
	m_followUpTargetPosition{},
	m_followUpTargetQuaternion{}
{
}

//-------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------
void FollowCamera::Initialize(
	const DirectX::SimpleMath::Vector3* followUpTargetPosition,
	const DirectX::SimpleMath::Quaternion* followUpTargetQuaternion
)
{
	// �^�[�Q�b�g�Ɋւ���|�C���^��ێ�����
	m_followUpTargetPosition = followUpTargetPosition;
	m_followUpTargetQuaternion = followUpTargetQuaternion;
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void FollowCamera::Update()
{
	// ��ɂȂ�ueye�v���v�Z����
	DirectX::SimpleMath::Vector3 eye{ 0.0f, HEIGHT, DISTANCE };
	eye = DirectX::SimpleMath::Vector3::Transform(eye, *m_followUpTargetQuaternion);

	// ��ɂȂ�utarget�v���v�Z����
	DirectX::SimpleMath::Vector3 target = *m_followUpTargetPosition;

	// �i�r���[�s��Ŏg�p����j�um_eye�v�Ɓum_target�v���v�Z����
	m_eye += ((target + eye) - m_eye) * SPRING_RATE_EYE;
	m_target += (target - m_target) * SPRING_RATE_TARGET;
}
