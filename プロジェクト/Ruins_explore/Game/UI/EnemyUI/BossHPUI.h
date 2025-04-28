/*
	�t�@�C�����FBossHPUI.h
	�@�@�@�T�v�F�{�X�̗̑�UI���Ǘ�����N���X
*/

#pragma once
#include "StepTimer.h"
#include "UserInterface.h"
#include "Framework/DeviceResources.h"
#include <vector>
#include "Keyboard.h"

class BossHPUI
{
public:
	// �R���X�g���N�^
	BossHPUI();
	// �f�X�g���N�^
	~BossHPUI();
	// ����������
	void Initialize(DX::DeviceResources* pDR, int width, int height);
	// �X�V����
	void Update(float bossHP, float MAX_BossHP);
	//�`�悷��
	void Render();
	// �ǉ�����
	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);
private:
	unsigned int m_menuIndex;
	DX::DeviceResources* m_pDR;
	std::unique_ptr<UserInterface> m_BossHPUI;
	std::unique_ptr<UserInterface> m_frame;
	std::unique_ptr<UserInterface> m_base;
	const wchar_t* m_baseTexturePath;
	std::unique_ptr<UserInterface> m_baseWindow;
	int m_windowWidth, m_windowHeight;
	DirectX::Keyboard::KeyboardStateTracker m_tracker;

	// �X�v���C�g�o�b�`
	DirectX::SpriteBatch* m_spriteBatch;
	// �X�v���C�g�t�H���g
	DirectX::SpriteFont* m_spriteFont;
	// �{�X�̌��݂̗̑�
	float m_currentHP;
	// �{�X�̍ő�̗�
	float m_maxHP;
};