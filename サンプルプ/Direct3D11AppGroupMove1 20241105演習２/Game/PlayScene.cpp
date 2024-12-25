#include "Framework/pch.h"
#include "PlayScene.h"
#include "Resources.h"
#include "Framework/Geometry.h"
#include "Framework/Cursor.h"
#include "Framework/SpriteString2D.h"
#include "Interface/IComponent.h"
#include "Node/Root.h"
#include "Turret/Header/Turret.h"
#include "Factory/TurretFactory.h"
#include "Team/Team.h"
#include "Observer/Messenger.h"
#include "Game/Game.h"
#include "Node/NodeFactory.h"
#include "Node/Obstacle.h"

// ���E(�ŏ�)
const float PlayScene::MIN_BOUNDARY = -250.0f;
// ���E(�ő�)
const float PlayScene::MAX_BOUNDARY = 250.0f;

// �u�v���C�V�[���v�R���X�g���N�^
PlayScene::PlayScene(Game* game)
	:
	m_game(game),												// �Q�[��
	m_graphics{},													// �O���t�B�b�N�X
	m_device{},														// �f�o�C�X
	m_context{},														// �f�o�C�X�R���e�L�X�g
	m_keyboardState{},										// �L�[�{�[�h�X�e�[�g
	m_keyboardStateTracker{},						// �L�[�{�[�h�X�e�[�g�g���b�J�[
	m_mouseState{},											// �}�E�X�X�e�[�g
	m_mouseStateTracker{}	,							// �}�E�X�X�e�[�g�g���b�J�[
	m_ballCamera{},												// �{�[���J����
	m_viewMatrix{},												// �r���[
	m_projectionMatrix{},									// �v���W�F�N�V����
	m_cameraRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::Up, 
			DirectX::XMConvertToRadians(-0.02f)
		)
	),																				// �J������]
	m_cameraPosition{},									// �J�����ʒu
	m_cameraFocus{},											// �J�����t�H�[�J�X
	m_distance{},													// �����_���王�_�܂ł̋���
	m_zoom{},															// �Y�[��
	m_root{},																// �V�[���O���t���[�g
	m_playerGroupNumber(0)						// �v���C���[�O���[�v�ԍ�
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
	// �V�[���O���t���[�g
	m_root.reset();
}

// �u�v���C�V�[���v����������
void PlayScene::Initialize()
{
	using namespace DirectX::SimpleMath;

	// ���\�[�X�����[�h����
	Resources::GetInstance()->LoadResource();
	// �J�[�\���𐶐�����
	m_cursor = std::make_unique<Cursor>();
	// �v���C���[�`�[�����S�ʒu�J�[�\��
	m_playerCenterCursor = std::make_unique<Cursor>();
	// �G�`�[�����S�ʒu�J�[�\��
	m_enemyCenterCursor = std::make_unique<Cursor>();

	// ���[�g�𐶐�����
	m_root = std::make_unique<Root>(nullptr, Vector3(0.0f, 0.0f, 0.0f), 0.0f);
	// ���[�g�ɏ�Q����ǉ�����
	m_root->Attach(NodeFactory::CreateObstacle(m_root.get(), Vector3(0.0f, 1.0f, 0.0f), DirectX::XMConvertToRadians(0.0)));
	// ���[�g�ɖC��1��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-40.0f, 0.0f, -200.0f), DirectX::XMConvertToRadians(0.0f)));
	// ���[�g�ɖC��2��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-20.0f, 0.0f, -180.0f), DirectX::XMConvertToRadians(0.0f)));
	// ���[�g�ɖC��3��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(   0.0f, 0.0f, -160.0f), DirectX::XMConvertToRadians(0.0f)));
	// ���[�g�ɖC��4��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(20.0f, 0.0f, -180.0f), DirectX::XMConvertToRadians(0.0f)));
	// ���[�g�ɖC��5��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(40.0f, 0.0f, -200.0f), DirectX::XMConvertToRadians(0.0f)));

	// ���[�g�ɖC��6��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(40.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));
	// ���[�g�ɖC��7��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(20.0f, 0.0f, 180.0f), DirectX::XMConvertToRadians(180.0)));
	// ���[�g�ɖC��8��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(00.0f, 0.0f, 160.0f), DirectX::XMConvertToRadians(180.0)));
	// ���[�g�ɖC��9��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-20.0f, 0.0f, 180.0f), DirectX::XMConvertToRadians(180.0)));
	// ���[�g�ɖC��10��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-40.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));
	// ���[�g�ɖC��11��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(10.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));
	// ���[�g�ɖC��12��ǉ�����
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-10.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));


	// ���b�Z�[�W�𑗐M����ώ@�҃��X�g���\�[�g����
	Messenger::SortObserverList();
	//  �L�[�{�[�h�̃L�[�͈̓��X�g�𐶐�����
	Messenger::CreateKeyRangeList();
	// �v���C���[�ߐږC���𐶐�����
	 CreatePlayerNeighbors();
	// �G�ߐږC���𐶐�����
	 CreateEnemyNeighbors();
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
void PlayScene::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

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

	// �J�������R���g���[������
	ControlCamera(timer);
	// �}�E�X�J�[�\���ʒu���v���C���[�C���ɐݒ肷��
	SetMousePositionToTurrets();
	// �v���C���[�`�[����ύX����
	Team::ChangePlayerTeam();
	// �v���C���[�m�[�h�ԍ��z����擾����
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(Team::GetPlayerTeamNumber());
	// �L�[�{�[�h�����������ꍇ�Ƀ��b�Z���W���[�ɃL�[�{�[�h�X�e�[�g�ƃv���C���[�m�[�h�ԍ��z���ʒm����
	if (IsKeyPress(m_keyboardState)) { Messenger::Notify(m_keyboardState, playerNodeNumbers); }
	// �V�[���O���t���X�V����
	m_root->Update(timer, DirectX::SimpleMath::Vector3::Zero, Quaternion::Identity);
}


// �v���C���[�ߐږC���𐶐�����
void PlayScene::CreatePlayerNeighbors()
{
	// �v���C���[�`�[���ԍ����擾����
	int playerTeamNumber = Team::GetPlayerTeamNumber();
	// �v���C���[�m�[�h�ԍ��z����擾����
	std::vector<int> playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);

	for (auto& nodeNumber : playerNodeNumbers)
	{
		// �v���C���[�C�����擾����
		Turret* turret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber));
		// �e�v���C���[�C���ɋߐږC���z��𐶐�����
		turret->CreateNeighbors(playerNodeNumbers);
	}
}


// �G�ߐږC���𐶐�����
void PlayScene::CreateEnemyNeighbors()
{
	// �G�`�[���ԍ����擾����
	int enemyTeamNumber = Team::GetEnemyTeamNumber();
	// �G�m�[�h�ԍ��z����擾����
	std::vector<int> enemyNodeNumbers = Team::GetNodeListForTeam(enemyTeamNumber);

	for (auto& nodeNumber : enemyNodeNumbers)
	{
		// �G�C�����擾����
		Turret* turret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber));
		// �e�G�C���ɋߐږC���z��𐶐�����
		turret->CreateNeighbors(enemyNodeNumbers);
	}
}

// �A�[�N�{�[�����g�p���ăJ�������R���g���[������
void PlayScene::ControlCamera(const DX::StepTimer& timer)
{
	// �o�ߎ��Ԃ��擾����
	float elapsedTime = float(timer.GetElapsedSeconds());
	// �X�P�[���Q�C��
	constexpr float SCALE_GAIN = 0.001f;
	// ���_�x�N�g�����擾����
	auto& eyePosition = m_game->GetCamera()->GetEyePosition();
	// ���_�ƒ����_�̋������v�Z����
	m_distance = eyePosition.Length();

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
		m_zoom = std::max(m_zoom, 0.01f);
		// �}�E�X�z�C�[�������Z�b�g����
		m_game->GetMouse()->ResetScrollWheelValue();
	}
	// �h���b�O���łȂ��ꍇ
	if (!m_ballCamera.IsDragging())
	{
		// �}�E�X�z�C�[�������������Ă���ꍇ �{�[���J�������J�n����
		if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			m_ballCamera.OnBegin(m_mouseState.x, m_mouseState.y);
		}
	}
	// �}�E�X�z�C�[����������Ă���ꍇ �{�[���J�������I������
	else if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::RELEASED)
	{
		m_ballCamera.OnEnd();
	}
	// �J�����̌������X�V����
	auto direction = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward, m_cameraRotation);
	// �J�����ʒu���v�Z����
	m_cameraPosition = m_cameraFocus + (m_distance * m_zoom) * direction;
	// �����x�N�g����ݒ肷��
	m_game->GetCamera()->SetEyePosition(m_cameraPosition);
}

// �}�E�X�J�[�\���ʒu���v���C���[�C���ɐݒ肷��
void PlayScene::SetMousePositionToTurrets()
{
	using namespace DirectX::SimpleMath;

	// �}�E�X�J�[�\�����[���h�ʒu������������
	DirectX::SimpleMath::Vector3 mouseWorldPosition(Vector3::Zero);
	// ���}�E�X�{�^�����N���b�N�����ꍇ
	if (m_mouseStateTracker.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		// �}�E�X�J�[�\���ʒu
		DirectX::SimpleMath::Vector2 mouseCursorPosition(Vector2::Zero);
		// ���ʂ�����������
		DirectX::SimpleMath::Plane plane(0.0f, 1.0f, 0.0f, 0.0f);
		// �}�E�X�J�[�\���̃X�N���[���ʒu���擾����
		mouseCursorPosition = DirectX::SimpleMath::Vector2(roundf((float)m_mouseState.x), roundf((float)m_mouseState.y));
		// �X�N���[���ʒu��������𐶐�����
		DirectX::SimpleMath::Ray ray = CreateRayFromScreenPoint(mouseCursorPosition);
		// �����ƕ��ʂƂ̌����_���擾����
		IntersectRayPlane(ray, plane, &mouseWorldPosition);
		// �}�E�X�J�[�\�������E���̏ꍇ�Ɋe�C���Ƀ��[���h���W��ݒ肷��
		if (mouseWorldPosition.x > MIN_BOUNDARY && mouseWorldPosition.x < MAX_BOUNDARY &&
			mouseWorldPosition.z > MIN_BOUNDARY && mouseWorldPosition.z < MAX_BOUNDARY)	
		{
			// �}�E�X�J�[�\���Ƀ��[���h�ʒu��ݒ肷��
			m_cursor->SetPosition(mouseWorldPosition);
			// �v���C���[�ώ@�҂ɖC���Ɉړ���̈ʒu��ʒm����
			Messenger::NotifyToPlayer(mouseWorldPosition);
		}
	}
}

// �u�v���C�V�[���v�`�悷��
void PlayScene::Render()
{
	// �O���b�h��`�悷��
	DrawGrid(DirectX::g_XMZero, 10, 10, DirectX::Colors::DarkGray);
	// �J�[�\����`�悷��
	DrawCursor();
	// �v���C���[�`�[�����S�ʒu��`�悷��
	DrawPlayerTeamCenterPosition();
	// �G�`�[�����S�ʒu��`�悷��
	DrawEnemyTeamCenterPosition();
	// �V�[���O���t��`�悷��
	m_root->Render();
	// ����\������
	DrawInfo();
}

// �O���b�h��`�悷��
void PlayScene::DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, const size_t& ydivs, const DirectX::GXMVECTOR& m_color)
{
	using namespace DirectX::SimpleMath;
	const DirectX::XMVECTORF32 xaxis = { 200.f, 0.0f, 0.0f };
	const DirectX::XMVECTORF32 zaxis = { 0.0f, 0.0f, 200.f };

	// �p�t�H�[�}���X�J�n�C�x���g
	m_graphics->GetDeviceResources()->PIXBeginEvent(L"Draw Grid");
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());

	for (size_t index = 0; index <= xdivs; ++index)
	{
		float percent = (float(index) / float(xdivs) * 2.0f) - 1.0f;
		// �X�P�[�����v�Z����
		DirectX::XMVECTOR scale = DirectX::XMVectorScale(xaxis, percent);
		// ���_�ɃX�P�[�������Z����
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
		// ���_�ɃX�P�[�������Z����
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

// �J�[�\����`�悷��
void PlayScene::DrawCursor()
{
	m_cursor->SetColor(DirectX::Colors::White);
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �J�[�\����`�悷��
	m_cursor->Render();
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �v���C���[�`�[�������ʒu��`�悷��
void PlayScene::DrawPlayerTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// �v���C���[�`�[���̒����ʒu���擾����
	Vector3 playerTeamCenterPosition = Team::GetPlayerTeamCenterPosition();
	// �J�[�\���ʒu��ݒ肷��
	m_playerCenterCursor->SetPosition(playerTeamCenterPosition);
	// �J�[�\�������F�ɐݒ肷��
	m_playerCenterCursor->SetColor(DirectX::Colors::Blue);
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �v���C���[�`�[�����S�ʒu�J�[�\����`�悷��
	m_playerCenterCursor->Render();
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �G�`�[�������ʒu��`�悷��
void PlayScene::DrawEnemyTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// �G�`�[���̒����ʒu���擾����
	Vector3 enemyTeamCenterPosition = Team::GetEnemyTeamCenterPosition();
	// �J�[�\���ʒu��ݒ肷��
	m_enemyCenterCursor->SetPosition(enemyTeamCenterPosition);
	// �J�[�\����F�ɐݒ肷��
	m_enemyCenterCursor->SetColor(DirectX::Colors::Blue);
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �G�`�[�����S�ʒu�J�[�\����`�悷��
	m_enemyCenterCursor->Render();
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
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

	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Mouse cursor position : %6.2f, %6.2f, %6.2f ",
		m_cursor->GetPosition().x, m_cursor->GetPosition().y, m_cursor->GetPosition().z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 56.0f));

	Vector3 playeyTeamCenterPosition = Team::GetPlayerTeamCenterPosition();
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Player team position : %6.2f, %6.2f, %6.2f ",
		playeyTeamCenterPosition.x, playeyTeamCenterPosition.y, playeyTeamCenterPosition.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 84.0f));

	Vector3 enemyTeamCenterPosition = Team::GetEnemyTeamCenterPosition();
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Enemy team position : %6.2f, %6.2f, %6.2f ",
		enemyTeamCenterPosition.x, enemyTeamCenterPosition.y, enemyTeamCenterPosition.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 112.0f));

	// ���ׂĂ̏���`�悷��
	spriteString2D.Render();
}

// �}�E�X�J�[�\���ʒu����X�N���[���ւ̌����𐶐�����
DirectX::SimpleMath::Ray PlayScene::CreateRayFromScreenPoint(const DirectX::SimpleMath::Vector2& mousePosition)
{
	// �r���[�|�[�g���擾����
	DirectX::SimpleMath::Viewport viewport(m_graphics->GetDeviceResources()->GetScreenViewport());
	// �X�N���[���̃}�E�X�J�[�\���ʒu��Vector3�ɐݒ肷��
	DirectX::SimpleMath::Vector3 screenPosition(mousePosition.x, mousePosition.y, 0.0f);
	// �X�N���[�����W��3�������W�ɕϊ�����
	DirectX::SimpleMath::Vector3 worldPoint = viewport.Unproject(
		screenPosition,
		m_graphics->GetProjectionMatrix(),
		m_graphics->GetViewMatrix(),
		DirectX::SimpleMath::Matrix::Identity
	);

	// �r���[�s�񂩂�t�s����擾����
	DirectX::SimpleMath::Matrix matrix = m_graphics->GetViewMatrix().Invert();
	// �J�����ʒu���擾����
	DirectX::SimpleMath::Vector3 cameraPosition(matrix._41, matrix._42, matrix._43);
	// �J�����̈ʒu���烏�[���h��Ԃ̃}�E�X�J�[�\���ʒu�ւ̕������擾����
	DirectX::SimpleMath::Vector3 direction = worldPoint - cameraPosition;
	// ���K������
	direction.Normalize();
	// �����𐶐�����
	DirectX::SimpleMath::Ray ray(cameraPosition, direction);
	// ������Ԃ�
	return ray;
}
