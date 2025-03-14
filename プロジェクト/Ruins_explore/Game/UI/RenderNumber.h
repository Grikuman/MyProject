/*
	�t�@�C�����FRenderNumber.h
	�T�v�F�����̑������l���e�N�X�`���\�����邽�߂̃N���X
*/

#pragma once
#include "Particle.h"

class RenderNumber
{
public:
	// �����̕\���������`
	enum class RenderDirection
	{
		LeftAlignment,  // ����
		RightAlignment  // �E��
	};

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	RenderNumber();
	~RenderNumber();

	// ����������
	void Initialize(DX::DeviceResources* pDR);
	// �X�V����
	void Update(float elapseTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	// �\�����鐔�l��ݒ�
	void SetRenderValue(uint64_t val, bool notAnimation = true);
	// �\��������ݒ�
	void SetRenderColumn(int column);
	// �`�������ݒ�
	void SetDirection(RenderDirection dir);
	// �ʒu��ݒ�i���W�w��j
	void SetPosition(float x, float y);
	void SetPosition(DirectX::SimpleMath::Vector2 pos);
	// UV���W��ݒ�
	void SetPositionUV(float x, float y);
	// �T�C�Y��ݒ�i���W�w��j
	void SetSize(float x, float y);
	void SetSize(DirectX::SimpleMath::Vector2 size);
	// UV�T�C�Y��ݒ�
	void SetUVSize(float x, float y);
	void SetUVSize(DirectX::SimpleMath::Vector2 size);
	// �����̐F��ݒ�i���C���J���[�A�A�E�g���C�����J���[�j
	void SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB);
	// �w�i�F��ݒ�
	void SetBackColor(DirectX::SimpleMath::Vector4 color);
	// �����I�[�o�[���̕`�拖�t���O��ݒ�
	void SetRenderOverColumn(bool flag);

private:
	// �f�o�C�X���\�[�X�Ǘ��p�|�C���^
	DX::DeviceResources* m_pDR;

	// �����I�u�W�F�N�g�i�p�[�e�B�N���V�X�e���𗘗p�j
	tito::Particle* m_pNumberObject;
	// �\�����鐔�l
	uint64_t m_renderValue;
	// �O��̐��l�i�A�j���[�V�����p�j
	uint64_t m_oldValue;
	// �`�悷�錅��
	int m_renderColumn;
	// ���l�̌���
	int m_valueColumn;
	int m_valueColumn2;
	// �����̕`�����
	RenderDirection m_direction;
	// UV���W
	DirectX::SimpleMath::Vector2 m_uvPos;
	// UV�T�C�Y
	DirectX::SimpleMath::Vector2 m_uvSize;
	// �����̐F�i���C���J���[�A�A�E�g���C�����J���[�A�w�i�J���[�j
	DirectX::SimpleMath::Vector4 m_colorA;
	DirectX::SimpleMath::Vector4 m_colorB;
	DirectX::SimpleMath::Vector4 m_colorC;
	// �����I�[�o�[���̕`��t���O
	bool m_isOverColumn;

	// �萔�z��i���l�̍X�V�Ɏg�p�j
	static const int UPDATE_VALUE_LENGE[10];
	// �f�t�H���g�̃����_�[�T�C�Y
	static const float DEFAULT_RENDER_WIDTH;
	static const float DEFAULT_RENDER_HEIGHT;
};
