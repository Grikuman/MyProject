#pragma once
#ifndef BULLET_DEFINED
#define BULLET_DEFINED
#include "Interface/IBullet.h"
#include "StepTimer.h"

// �C�e(Bullet)�N���X���`����
class Bullet : public IBullet
{
public:
	// �C�e���f���X�P�[��
	static const DirectX::SimpleMath::Vector3 BULLET_MODEL_SCALE;
	// �C�e���E�{�b�N�X�X�P�[��
	static const DirectX::SimpleMath::Vector3 BULLET_BOUNDINGBOX_SCALE;
	// ���E(�ŏ�)
	static const float MIN_BOUNDARY;
	// ���E(�ő�)
	static const float MAX_BOUNDARY;
	// �C�e�X�s�[�h���`����
	static const DirectX::SimpleMath::Vector3 SPEED;
	// ���˂����
	static const float IMPULSIVE_FORCE;
	// ����
	static const float MASS;
	// ���a (m)
	static const float DIAMETER;
	// ��C��R�W��(Cd)
	static const float DRAG_COEFFICIENT;
	// ��C���x(��) kg/m^3
	static const float AIR_DENSITY;
	//�T�b�J�[�{�[�����a�f�ʐ�( m^2)
	static const float CROSS_SECTION;
	// ��C��R�W��(k)
	// �{�[���ɓ�����C��R�̓{�[���̑��x�̓��ɔ�Ⴗ��
	static const float AIR_RESISTANCE;

public:
	// �m�[�h�ԍ����擾����
	virtual int GetNodeNumber() const { return m_nodeNumber; }
	// �ʒu���擾���� 
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// �ʒu��ݒ肷��
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; };
	// ���ʂ��擾����
	float GetMass() const { return MASS; }
	// ���˗͂��擾����
	float GetImpulsiveForce() const { return IMPULSIVE_FORCE; }
	// �C�e��]�p���擾���� 
	DirectX::SimpleMath::Quaternion GetBulletAngle() const { return m_bulletAngle; }
	// �C�e��]�p��ݒ肷�� 
	void SetBulletAngle(const DirectX::SimpleMath::Quaternion& angle) { m_bulletAngle = angle; }
	// �C�e�����˂���Ă��邩�ǂ������擾����
	IBullet::BulletState GetBulletState() const { return m_bulletState; }
	// �C�e�̏�Ԃ�ݒ肷��
	void SetBulletState(IBullet::BulletState bulletState) { m_bulletState = bulletState; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return m_model; }
	// ���[���h���E�{�b�N�X���擾����
	DirectX::BoundingBox* GetWorldBoundingBox() { return &m_worldBoundingBox; }
	// ���[���h�}�g���b�N�X���擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	Bullet(const int& nodeNumber, IBullet::BulletState bulletState);
	// �f�X�g���N�^
	~Bullet();
	// ����������
	void Initialize();
	// Bullet�I�u�W�F�N�g���X�V���� 
	inline void Update(const DX::StepTimer& timer);
	// Bullet�I�u�W�F�N�g��`�悷�� 
	inline void Render();
	// �C�e��`�悷��
	inline void DrawBullet(const DirectX::SimpleMath::Matrix& matrix);
	// ���E�{�b�N�X��`�悷��
	inline void DrawBoundingBox();
	// Bullet�I�u�W�F�N�g�̌㏈���������Ȃ� 
	void Finalize();

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �m�[�h�ԍ�
	int m_nodeNumber;
	// �u�C�e�v���f��
	DirectX::Model* m_model;
	// �����x
	DirectX::SimpleMath::Vector3 m_acceralation;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �p�x
	DirectX::SimpleMath::Quaternion m_bulletAngle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �u�e�v���E�{�b�N�X
	DirectX::BoundingBox m_boundingBox;
	DirectX::BoundingBox m_worldBoundingBox;
	// �C�e�����˂���Ă��邩�ǂ���������
	BulletState m_bulletState;
};

#endif	// BULLET_DEFINED
