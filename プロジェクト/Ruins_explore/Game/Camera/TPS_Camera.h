/*
	�t�@�C�����FTPS_Camera.h
	�@�@�@�T�v�F�O�l�̃J�����𐧌䂷��N���X
*/
#pragma once

namespace NRLib
{
	class TPS_Camera
	{
	public:
		// �r���[���擾����
		const DirectX::SimpleMath::Matrix& GetViewMatrix() const       { return m_view; }
		// �v���W�F�N�V�������擾����
		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
		// �A�C�|�W�V�������擾����
		const DirectX::SimpleMath::Vector3& GetEyePosition() const     { return m_eye; }
		// �^�[�Q�b�g���擾����
		const DirectX::SimpleMath::Vector3& GetTargetPosition() const  { return m_target; }
		// �A�b�v���擾����
		const DirectX::SimpleMath::Vector3& GetUpVector() const        { return m_up; }

	public:
		// �R���X�g���N�^
		TPS_Camera(const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero);
		// �f�X�g���N�^
		~TPS_Camera() = default;
		// �X�V����
		void Update(const DirectX::SimpleMath::Vector3& newTarget,const DirectX::SimpleMath::Matrix& rotate);

	private:
		// �r���[�s����v�Z����
		void CalculateViewMatrix();
		// �v���W�F�N�V�����s����v�Z����
		void CalculateProjectionMatrix();
		// �J�������W���v�Z����
		void CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate);

	private:
		// �^�[�Q�b�g����̃f�t�H���g����
		const float CAMERA_DISTANCE = 15.0f;
		const float CAMERA_HIGHT = 3.5f;
		// ��p
		const float FOV = DirectX::XMConvertToRadians(45.0f);
		// �߂����e��
		const float NEAR_PLANE = 1.0f;
		// �������e��
		const float FAR_PLANE = 1000.0f;

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
}
