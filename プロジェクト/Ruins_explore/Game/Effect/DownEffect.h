/*
	�t�@�C�����F.h
	�@�@�@�T�v�F���Ǘ�����N���X
*/
#pragma once

class DownEffect
{
public:
	// �R���X�g���N�^
	DownEffect();
	// �f�X�g���N�^
	~DownEffect();
	// ����������
	void Initialize(const DirectX::SimpleMath::Vector3& position);
	// �X�V����
	void Update();
	// �`�悷��
	void Render(const DirectX::SimpleMath::Vector3& position);
	// �㏈������
	void Finalize();

private:
	// �G�t�F�N�g���f���̉�]���a
	const float RADIUS = 1.0f;
	// �e�G�t�F�N�g���f�������炷�傫��
	const float ANGLE_OFFSET = DirectX::XM_PI / 2.0f;

private:
	// ���̃��f��
	std::unique_ptr<DirectX::Model> m_starModel;
	// �G�t�F�N�g�̒��S�ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ��]
	float m_rotate;
};
