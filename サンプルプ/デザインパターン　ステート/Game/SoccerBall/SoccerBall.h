#pragma once
#ifndef SOCCER_BALL_DEFINED
#define SOCCER_BALL_DEFINED

class PlayScene;

class SoccerBall
{
public:
	// �z�[���ʒu
	static const DirectX::SimpleMath::Vector3 HOME_POSITION;
	// �d�͉����x
	static const float GRAVITATION_ACCELERATION;
	// ��C��R
	static const float AIR_RESISTANCE;
	// ����
	static const float MASS;
	// ���a
	static const float RADIUS;
	// ���a
	static const float DIAMETER;
	// ��C��R�W��
	static const float DRAG_COEFFICIENT;
	// �f�ʐ�
	static const float CROSS_SECTION;
	// ��C���x
	static const float AIR_DENSITY;
	// ���C�W��
	static const float FRICTION;
	// �ő�ړ����x
	static const float MAX_SPEED;
	// �������苗��
	static const  float INTERSECT_JUDGEMENT_DISTANCE;

public:
	// �ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// ���x���擾����
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// ���E�����擾����
	DirectX::BoundingSphere* GetBoundingSphere() { return &m_boundingSphere; }

public:
	// �R���X�g���N�^
	SoccerBall(PlayScene* playScene, const float& mass, const float& rotationAngle, const float& scale, const DirectX::SimpleMath::Vector3& position);
	// �f�X�g���N�^
	~SoccerBall();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// ���E����`�悷��
	void DrawBoundingSphere();
	// �㏈�����s��
	void Finalize();
	// �T�b�J�[�{�[�����R��
	void  Shoot(const DirectX::SimpleMath::Vector3& direction, const float& impulsiveForce);
	// ���Z�b�g����
	void Reset();

private:
	// �v���C�V�[��
	PlayScene* m_playScene;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �f�o�C�X
	ID3D11Device* m_device;
	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_deviceResources;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
	// �T�b�J�[�{�[���̉�]�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_quaternion;
	// �T�b�J�[�{�[���̔��a
	float m_radius;
	// ���v�b��
	float m_totalSeconds;
	// ����
	float m_mass;
	// �p�x
	float m_angle;
	// �X�P�[��
	float m_scale;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �����x
	DirectX::SimpleMath::Vector3 m_acceralation;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphere;
	// �v���[���[���f��
	DirectX::Model* m_soccerBallModel;
};

#endif		// SOCCER_BALL_DEFINED
