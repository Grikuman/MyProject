/*
	�t�@�C�����FFixedCamera.h
	�@�@�@�T�v�F�Œ�J�����𐧌䂷��N���X
*/
#pragma once

class FixedCamera
{
public:
	// �r���[�s����擾����
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }
	// �v���W�F�N�V�����s����擾����
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
	// �J�����̎��_�ʒu���擾����i�ύX�\�j
	DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eye; }
	// �J�����̒����_�i�^�[�Q�b�g�̈ʒu�j���擾����i�ύX�\�j
	DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	// �J�����̏�����x�N�g�����擾����
	const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }
	// �J�����̎��_�ʒu��ݒ肷��
	void SetEyePosition(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }
	// �J�����̒����_�i�^�[�Q�b�g�̈ʒu�j��ݒ肷��
	void SetTargetPosition(DirectX::SimpleMath::Vector3 target) { m_target = target; }

public:
	// �R���X�g���N�^
	FixedCamera(
		DirectX::SimpleMath::Vector3& eye,
		DirectX::SimpleMath::Vector3& target,
		const DirectX::SimpleMath::Vector3& up = DirectX::SimpleMath::Vector3::UnitY);
	// �f�X�g���N�^
	~FixedCamera() = default;

private:
	// �r���[�s����v�Z����
	void CalculateViewMatrix();
	// �v���W�F�N�V�����s����v�Z����
	void CalculateProjectionMatrix();

private:
	// ��p
	const float FOV = DirectX::XMConvertToRadians(45.0f);
	// �߂����e��
	const float NEAR_PLANE = 1.0f;
	// �������e��
	const float FAR_PLANE = 100.0f;

private:
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;
	// �J�������W
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// �J�����̓��̕���
	DirectX::SimpleMath::Vector3 m_up;

};
