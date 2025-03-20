/*
	�t�@�C�����FStageEnd.h
	�@�@�@�T�v�F�X�e�[�W�I���̉��o���Ǘ�����N���X
*/
#pragma once

class StageEnd
{
public:
	// ���o���I�����Ă��邩�擾����(true:�I��)
	bool GetEnd() { return m_end; }

public:
	// �R���X�g���N�^
	StageEnd();
	// �f�X�g���N�^
	~StageEnd();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �I������
	void Finalize();

private:
	// ���o���Ԃ̏���
	void Time();
	// �摜�̓����̏���
	void TexturesAnimate();
	// ��x����������ʂ�����(���y)
	void ProcessOnce();

private:
	// ���o�̎���
	const float MAX_TIME = 420.0f;
	// ���̂ڂ����̈ʒu
	const DirectX::SimpleMath::Vector2 BLACK_POS = { 0.0f, 0.0f };
	// �A�C�R���̈ʒu
	const DirectX::SimpleMath::Vector2 ICON_POS = { 300.0f, 200.0f };
	// �摜�̒��S�ʒu
	DirectX::SimpleMath::Vector2 ORIGIN_POS = { 300.0f, 300.0f };
	// ��ʒ����ʒu
	DirectX::SimpleMath::Vector2 SCREEN_CENTER = { 640.0f, 360.0f };

private:
	//�X�v���C�g�o�b�`
	DirectX::SpriteBatch* m_spriteBatch;
	// ���̂ڂ���
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_black_Tex;
	// �����̃A�C�R��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stageClearIcon_Tex;
	// ���s�̃A�C�R��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stageFailedIcon_Tex;
	// �A�C�R���̂̊g�嗦
	float m_scale; 
	// ���̓����x
	float m_blackAlpha;
	// �A�C�R���̓����x
	float m_IconAlpha;

	// ���o���Ԃ̃J�E���g
	float m_time;
	// ���o�̏I���t���O
	bool m_end;
};
