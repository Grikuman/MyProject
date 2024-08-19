#include "pch.h"
#include "Mario.h"
#include "PlayScene.h"
#include "DeviceResources.h"

class Standing;
class Downing;
class Jumping;
class Running;

// �R���X�g���N�^
Mario::Mario(PlayScene* playScene)
:
m_playScene(playScene),																				// �v���C�V�[��
m_standing{},																									// �X�^���f�B���O
m_downing{},																									// �_�E�j�C���O
m_jumping{},																									// �W�����s���O
m_position(DirectX::SimpleMath::Vector2(100.0f, PlayScene::GROUND)),	// �����ʒu
m_velocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),									// ���x	
m_acceleration(DirectX::SimpleMath::Vector2(0.0f, 0.4f)),							// �����x
m_currentState{},																							// ���݂̏��
m_direction(Direction::RIGHT)																		// ����
{
}

// �f�X�g���N�^
Mario::~Mario()
{
}

// ����������
void Mario::Initialize()
{
	// �f�o�C�X���擾����
	auto device = m_graphics->GetInstance()->GetDeviceResources()->GetD3DDevice();
	
	// �u�����v�e�N�X�`��
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\standing.png", nullptr, m_standingTexture.GetAddressOf());
	// �u���ށv�e�N�X�`��
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\downing.png", nullptr, m_downingTexture.GetAddressOf());
	// �u�W�����v�v�e�N�X�`��
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\jumping.png", nullptr, m_jumpingTexture.GetAddressOf());

	// �u�����v��Ԃ𐶐�����
	m_standing = std::make_unique<Standing>(this);
	// �u���ށv��Ԃ𐶐�����
	m_downing = std::make_unique<Downing>(this);
	// �u�W�����v�v��Ԃ𐶐�����
	m_jumping = std::make_unique<Jumping>(this);

	// ������Ԃ��u�����v�ɐݒ肷��
	m_currentState = m_standing.get();
}

// �X�V����
void Mario::Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// ���݂̏�Ԃ��X�V����
	m_currentState->Update(timer, keyboardStateTracker);
}

// �`�悷��
void Mario::Render()
{
	// ���݂̏�Ԃ�`�悷��
	m_currentState->Render();
}

// �㏈�����s��
void Mario::Finalize()
{
}