#include "Framework/pch.h"
#include "Game/PlayScene.h"
#include "Framework/Resources.h"
#include "Game/Game.h"
#include "Framework/SpriteString2D.h"

class SoccerPLayer;
class SoccerBall;

// �z�[���ʒu
const DirectX::SimpleMath::Vector3 PlayScene::HOME_POSITION = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

// �u�v���C�V�[���v�R���X�g���N�^
PlayScene::PlayScene(Game* game)
	:
	m_game(game),													// �Q�[��
	m_graphics{},														// �O���t�B�b�N�X
	m_device{},															// �f�o�C�X
	m_context{},															// �f�o�C�X�R���e�L�X�g
	m_keyboardState{},											// �L�[�{�[�h�X�e�[�g
	m_keyboardStateTracker{},							// �L�[�{�[�h�X�e�[�g�g���b�J�[
	m_mouseState{},												// �}�E�X�X�e�[�g
	m_mouseStateTracker{}	,								// �}�E�X�X�e�[�g�g���b�J�[
	m_ballCamera{},													// �{�[���J����
	m_viewMatrix{},													// �r���[
	m_projectionMatrix{},										// �v���W�F�N�V����
	m_cameraRotation{},										// �J������]
	m_cameraPosition{},										// �J�����ʒu
	m_cameraFocus{},												// �J�����t�H�[�J�X
	m_distance{},														// �����_���王�_�܂ł̋���
	m_zoom{},																// �Y�[��
	m_soccerBall{},													// �T�b�J�[�{�[��
	m_soccerPlayer{},												// �T�b�J�[�v���C���[
	m_inShift(false),													// �V�t�g�L�[(�ǉ�:20240513)
	m_shootAngleRL(0.0f),									// ���ˍ��E��]�p(�ǉ�:20240513)
	m_shootAngleUD(36.0f),								// ���ˏ㉺��]�p(�ǉ�:20240513)
	m_shootForce(240.0f)										// �R���(�ǉ�:20240513)
{
	// �O���t�B�b�N�X�C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �f�o�C�X���擾����
	m_device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// �f�o�C�X�R���e�L�X�g���擾����
	m_context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
}

// �u�v���C�V�[���v�f�X�g���N�^
PlayScene::~PlayScene()
{
}

// �u�v���C�V�[���v����������
void PlayScene::Initialize()
{
	using namespace DirectX::SimpleMath;

	// ���\�[�X�����[�h����
	Resources::GetInstance()->LoadResource();
	// �T�b�J�[�{�[���𐶐�����
	m_soccerBall = std::make_unique<SoccerBall>(this, SoccerBall::MASS, 0.0f, 0.0022f, SoccerBall::HOME_POSITION);
	// �T�b�J�[�{�[��������������
	m_soccerBall->Initialize();

	// �T�b�J�[�v���C���[�𐶐�����
	m_soccerPlayer = std::make_unique<SoccerPlayer>(this, 70.0f, -90.0f, 0.0024f, PlayScene::HOME_POSITION);
	// �T�b�J�[�v���C���[������������
	m_soccerPlayer->Initialize();
}

// �L�[�{�[�h����������ꂽ�ǂ����𔻒肷��
inline bool IsKeyPress(DirectX::Keyboard::State& state)
{
	// �L�[�{�[�h�X�e�[�g�ւ̃|�C���^���擾����
	auto ptr = reinterpret_cast<uint32_t*>(&state);
	for (int key = 0; key < 0xff; key++)
	{
		const unsigned int buffer = 1u << (key & 0x1f);
		// �L�[����������ꂽ���ǂ����𒲂ׂ�
		if (ptr[(key >> 5)] && buffer)	 return true;
	}
	// �L�[�͉��������Ă��Ȃ�
	return false;
}

// �u�v���C�V�[���v�X�V����
void PlayScene::Update(DX::StepTimer const& timer)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// �o�ߎ��Ԃ��擾����
	float elapsedTime = float(timer.GetElapsedSeconds());

	// �L�[�{�[�h�̏�Ԃ��擾����
	m_keyboardState = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�X�e�[�g�g���b�J�[���X�V����
	m_keyboardStateTracker.Update(m_keyboardState);
	// �}�E�X�̏�Ԃ��擾����
	m_mouseState = DirectX::Mouse::Get().GetState();
	// �}�E�X�X�e�[�g�g���b�J�[���X�V����
	m_mouseStateTracker.Update(m_mouseState);
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();
	// ���ˊp�x�Ɨ͂�ύX����(�ǉ�:20240513)
	ChangeShootAngleForce(m_keyboardState);
	// �T�b�J�[�{�[�����X�V����
	m_soccerBall->Update(elapsedTime);
	// �T�b�J�[�v���C���[���X�V����
	m_soccerPlayer->Update(elapsedTime);

	// ���_�x�N�g�����擾����
	auto eyePosition = m_game->GetCamera()->GetEyePosition();
	// ���_�ƒ����_�̋������v�Z����
	m_distance = eyePosition.Length();
	// �J�������R���g���[������
	ControlCamera(timer);
}

// �A�[�N�{�[�����g�p���ăJ�������R���g���[������
void PlayScene::ControlCamera(const DX::StepTimer& timer)
{
	// �o�ߎ��Ԃ��擾����
	float elapsedTime = float(timer.GetElapsedSeconds());
	// �X�P�[���Q�C��
	constexpr float SCALE_GAIN = 0.001f;

	// �J�����ړ��s��
	DirectX::SimpleMath::Matrix im;
	// �t�s����v�Z����
	m_viewMatrix.Invert(im);
	// �t�s��ƈړ��x�N�g�����|����
	DirectX::SimpleMath::Vector3 move = DirectX::SimpleMath::Vector3::Transform(move, im);

	// �}�E�X�̈ړ������΃}�E�X�ړ��ł���ꍇ
	if (m_mouseState.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		// �}�E�X�̈ړ��ʂ��v�Z����
		DirectX::SimpleMath::Vector3 delta = DirectX::SimpleMath::Vector3(-float(m_mouseState.x), float(m_mouseState.y), 0.0f) * m_distance;
		// �ړ��ʂƋt�s����|����
		delta = DirectX::SimpleMath::Vector3::TransformNormal(delta, im);
		// �J�����t�H�[�J�X�ʒu���v�Z����
		m_cameraFocus += delta * elapsedTime;
	}
	// �}�E�X�̉E�{�^�����h���b�O���Ă���ꍇ
	else if (m_ballCamera.IsDragging())
	{
		// �}�E�X�̈ړ�
		m_ballCamera.OnMove(m_mouseState.x, m_mouseState.y);
		// �{�[���J�����̌��݂̃N�H�[�^�j�I�����擾����
		auto quaternion = m_ballCamera.GetQuaternion();
		// �J������]�̋t�R�H�[�^�j�I�����v�Z����
		quaternion.Inverse(m_cameraRotation);
	}
	else
	{
		// �}�E�X�z�C�[������]�������ꍇ�̃J�����̃Y�[���l���v�Z����
		m_zoom = 1.0f + float(m_mouseState.scrollWheelValue) * SCALE_GAIN;
		// �Y�[���l�𒲐�����
		m_zoom = std::max(m_zoom, 0.1f);
		// �}�E�X�z�C�[�������Z�b�g����
		m_game->GetMouse()->ResetScrollWheelValue();
	}
	// �h���b�O���łȂ��ꍇ
	if (!m_ballCamera.IsDragging())
	{
		// �}�E�X�z�C�[�������������Ă���ꍇ
		if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
				// �{�[���J�������J�n����
				m_ballCamera.OnBegin(m_mouseState.x, m_mouseState.y);
		}
	}
	// �}�E�X�z�C�[����������Ă���ꍇ
	else if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::RELEASED)
	{
		// �{�[���J�������I������
		m_ballCamera.OnEnd();
	}
	// �J�����̌������X�V����
	auto direction = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward, m_cameraRotation);
	// �J�����ʒu���v�Z����
	m_cameraPosition = m_cameraFocus + (m_distance * m_zoom) * direction;
	// �����x�N�g����ݒ肷��
	m_game->GetCamera()->SetEyePosition(m_cameraPosition);
}

// �u�v���C�V�[���v�`�悷��
void PlayScene::Render()
{
	// �O���b�h��`�悷��
	DrawGrid(DirectX::g_XMZero, 10, 10, DirectX::Colors::DarkGray);
	// �T�b�J�[�{�[����`�悷��
	m_soccerBall->Render();
	// ���ˊp�Ɨ͂�`�悷��(�ǉ�:20240513)
	DrawShootAngleForce();
	// �T�b�J�[�v���C���[��`�悷��
	m_soccerPlayer->Render();

	// ����\������
	DrawInfo();
}

// �O���b�h��`�悷��
void PlayScene::DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, const size_t& ydivs, const DirectX::GXMVECTOR& m_color)
{
	using namespace DirectX::SimpleMath;
	const DirectX::XMVECTORF32 xaxis = { 5.0f, 0.0f, 0.0f };
	const DirectX::XMVECTORF32 zaxis = { 0.0f, 0.0f, 5.0f };
	// �p�t�H�[�}���X�J�n�C�x���g
	m_graphics->GetDeviceResources()->PIXBeginEvent(L"Draw Grid");
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());

	for (size_t index = 0; index <= xdivs; ++index)
	{
		float percent = (float(index) / float(xdivs) * 2.0f) - 1.0f;
		// �X�P�[�����v�Z����
		DirectX::XMVECTOR scale = DirectX::XMVectorScale(xaxis, percent);
		scale = DirectX::XMVectorAdd(scale, origin);
		// ���_1��ݒ肷��
		DirectX::VertexPositionColor v1(DirectX::XMVectorSubtract(scale, zaxis), m_color);
		// ���_2��ݒ肷��
		DirectX::VertexPositionColor v2(DirectX::XMVectorAdd(scale, zaxis), m_color);
		// ������`�悷��
		m_graphics->GetPrimitiveBatch()->DrawLine(v1, v2);
	}

	for (size_t index = 0; index <= ydivs; index++)
	{
		float percent = (float(index) / float(ydivs) * 2.0f) - 1.0f;
		// �X�P�[�����v�Z����
		DirectX::XMVECTOR scale = DirectX::XMVectorScale(zaxis, percent);
		scale = DirectX::XMVectorAdd(scale, origin);
		// ���_1��ݒ肷��
		DirectX::VertexPositionColor v1(DirectX::XMVectorSubtract(scale, xaxis), m_color);
		// ���_2��ݒ肷��
		DirectX::VertexPositionColor v2(DirectX::XMVectorAdd(scale, xaxis), m_color);
		// ������`�悷��
		m_graphics->GetPrimitiveBatch()->DrawLine(v1, v2);
	}
	// �v���~�e�B�u�o�b�`���I������
	m_graphics->DrawPrimitiveEnd();
	// �p�t�H�[�}���X�I���C�x���g
	m_graphics->GetDeviceResources()->PIXEndEvent();
}

// ����\������
void PlayScene::DrawInfo()
{
	using namespace DirectX::SimpleMath;
	wchar_t stringBuffer[128];

	// SpriteString2D��錾����
	SpriteString2D spriteString2D;
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Camera position : %6.2f, %6.2f, %6.2f ",
		m_cameraPosition.x, 0.0f, m_cameraPosition.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 0.0f));
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Camera rotation : %6.2f, %6.2f, %6.2f ",
		m_cameraRotation.x, 0.0f, m_cameraRotation.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 28.0f));

	// ���ׂĂ̏���`�悷��
	spriteString2D.Render();
}

// �R��p�x�Ɨ͂�ύX����(�ǉ�:20240513)
void PlayScene::ChangeShootAngleForce(const DirectX::Keyboard::State& keyboardState)
{
	//�u[Ctrl�v+�u���v�L�[�őŏo�������(���E)��ς���
	if (keyboardState.Left && keyboardState.LeftControl)
		m_shootAngleRL += 0.5f;
	// �uCtrl�v+�u���v�L�[�őŏo�������(���E)��ς���
	if (keyboardState.Right && keyboardState.LeftControl)
		m_shootAngleRL -= 0.5f;

	//�u[Ctrl�v+�u���v�L�[�őŏo����(�㉺)��ς���
	if (keyboardState.Up && keyboardState.LeftControl)
	{
		if (m_shootAngleUD < 180.0f)
			m_shootAngleUD += 0.5f;
	}
	// �uCtrl�v+�u���v�L�[�őŏo����(�㉺)��ς���
	if (keyboardState.Down && keyboardState.LeftControl)
	{
		if (m_shootAngleUD > 0.0f)
			m_shootAngleUD -= 0.5f;
	}
	// �uShift�v+�u���v�L�[�őŏo����͂�ς���
	if (keyboardState.Up && keyboardState.LeftShift)
		m_shootForce += 0.2f;
	//�uShift�v+�u���v�L�[�őŏo����͂�ς���
	if (keyboardState.Down && keyboardState.LeftShift)
		m_shootForce -= 0.2f;

	// �uShift�v�L�[�̉����������`�F�b�N����
	if (keyboardState.LeftShift)
		m_inShift = true;
	else
		m_inShift = false;
}

// �R��p�x�Ɨ͂�`�悷��(�ǉ�:20240513)
void PlayScene::DrawShootAngleForce()
{
	using namespace DirectX::SimpleMath;
	// �`��v���~�e�B�u���J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �R��������v�Z����
	DirectX::SimpleMath::Vector3 direction = CalculateDirection();
	if (m_inShift)
	{
		// �R�������\������`�悷��
		m_graphics->DrawVector(SoccerBall::HOME_POSITION, direction * m_shootForce * 0.0015f, DirectX::Colors::White);
	}
	// �`��v���~�e�B�u���I������
	m_graphics->DrawPrimitiveEnd();
}

// �T�b�J�[�{�[�����R��������v�Z����(�ǉ�:20240513)
DirectX::SimpleMath::Vector3 PlayScene::CalculateDirection()
{
	using namespace DirectX::SimpleMath;

	// �T�b�J�[�{�[�����R�������ݒ肷��
	Vector3 direction(1.0f, 0.0f, 0.0f);
	// Y������̉�]�s��𐶐�����
	Matrix rotationY = Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_shootAngleRL));
	// Z������̉�]�s��𐶐�����
	Matrix rotationZ = Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_shootAngleUD));
	// ���E�������v�Z����
	direction = Vector3::Transform(direction, rotationY);
	// �㉺�������v�Z����
	direction = Vector3::Transform(direction, rotationZ);
	// ������Ԃ�
	return direction;
}
