#pragma once
#ifndef TURRET_DEFINED
#define TURRET_DEFINED
#include "Interface/IComposite.h"
#include "Interface/ICollision.h"
#include "Interface/IBullet.h"
#include "Steering/SteeringBehavior.h"

// �u�C���v�N���X���`����
class Turret : public IComposite
{
public:
	// ���iID
	enum PartID : int
	{
		TURRET = -1,								// PartID:-1
		TURRET_BOTTOM = 0,			// PartID:0
		TURRET_FOOT,							// PartID:1
		TURRET_MIDDLE,					// PartID:2
		TURRET_PLATE,						// PartID:3
		TURRET_TOP,								// PartID:4
		TURRET_FORT,							// PartID:5
		TURRET_GUN								// PartID:6
	};

public:
	// �ő�C�e��
	static const int MAX_BULLET_NUMBER;
	// �X�s�[�g
	static const DirectX::SimpleMath::Vector3 SPEED;
	// ������]�p
	static const float HORIZONTAL_ROTATION_ANGLE;
	// ������]�p
	static const float VERTICAL_ROTATION_ANGLE;
	// �C�����f���X�P�[��
	static const DirectX::SimpleMath::Vector3 TURRET_MODEL_SCALE;
	// �C�����E�{�b�N�X�X�P�[��
	static const DirectX::SimpleMath::Vector3 TURRET_BOUNDINGBOX_SCALE;

public:
	// �m�[�h�ԍ����擾����
	int GetNodeNumber() const { return m_nodeNumber; }
	// ���iID���擾����
	int GetPartID() const { return m_partID; }
	// ���i�ԍ����擾����
	int GetPartNumber() const { return m_partNumber; }
	// �e���擾����
	IComponent* GetParent() const { return m_parent; }
	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const {	return m_currentPosition; }
	// ���݂̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// ���x���擾����
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// �������擾����
	DirectX::SimpleMath::Vector3 GetHeading() const { return m_heading; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// ���ʂ��擾����
	float GetMass() const { return m_mass; }
	// ���ʂ�ݒ肷��
	void SetMass(const float& mass) { m_mass = mass; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	// �u�C�e�v���Q�Ƃ���
	std::vector<std::unique_ptr<IBullet>>& GetBullets() { return m_bullets; };
	// �Փ˂��擾����
	bool GetCollision() const { return m_collision; }
	// �Փ˂�ݒ肷��
	void SetCollision(bool collision) { m_collision = collision; }
	// �אږC���z����擾����
	 std::vector<Turret*> GetNeighbors() { return m_neighbors; }
	// �ő�ړ����x���擾����
	float GetMaxSpeed() const { return m_maxSpeed; }
	// �ő�̗͂��擾����
	float GetMaxForce() const { return m_maxForce; }

	// �����s�����s��(�^�[�Q�b�g�̈ʒu��ݒ肵�����s����L���ɂ���)
	void ArriveOn(const DirectX::SimpleMath::Vector3& position) { m_steeringBehavior->SetTargetPosition(position); m_steeringBehavior->ArriveOn(); }
	// ����s�����s��(����s����L���ɂ���)
	void AlignmentOn() { m_steeringBehavior->AllignmentOn(); }
	// �����s�����s��(�����s����L���ɂ���)
	void SeparationOn() { m_steeringBehavior->SeparationOn(); }
	// ��Q�������s�����s��(��Q�������s����L���ɂ���)
	void ObstacleAvoidanceOn(const DirectX::SimpleMath::Vector3& position) { m_steeringBehavior->SetTargetPosition(position); m_steeringBehavior->ObstacleAvoidanceOn(); }
	// �ړ����Ă��邩�ǂ������擾����
	bool IsMove() const { return m_move; }
	// �ړ��J�n/��~����
	void Move(bool start) { m_move = start; }

public:
	// �R���X�g���N�^
	Turret(IComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	// �f�X�g���N�^
	~Turret();
	// ����������
	void Initialize();
	// �ʒm����(�L�[�{�[�h)
	inline void OnKeyPressed(const DirectX::Keyboard::Keys& keys);
	// �ʒm����(�}�E�X)
	void OnLeftButtonClicked(const DirectX::SimpleMath::Vector3& position);
	// �X�V����
	inline void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle);
	// �C�����E�����쐬����
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);
	// �Փ˔������������
	void PrepareCollision(ICollisionVisitor* visitor);
	// �Փ˔��肷��
	inline void DetectCollision(ICollisionVisitor* visitor, IBullet* bullet);
	// �C���ƖC�e�̏Փ˔�����s��
	inline void DetectCollisionTurret();
	// �C�����i��ǉ�����
	void Attach(std::unique_ptr<IComponent> turretPart);
	// �C�����i���폜����
	void Detach(std::unique_ptr<IComponent> turretPart);
	// �`�悷��
	inline void Render();
	// �C�����E����`�悷��
	inline void DrawTurretBoundingSphere(bool collision);
	// �㏈�����s��
	void Finalize();
	// �C�e���`���[�W����
	void ChargeBullets();
	// �ߐږC���𐶐�����(�v���C�V�[������Ăяo�����)
	void CreateNeighbors(std::vector<int>& teamList);

public:
	// �C�����i�ԍ������Z�b�g����(-1����J�n����)
	static int ResetPartsNumber() { s_partsNumber = -1;  return s_partsNumber; }
	// �C�����i�ԍ����擾����
	static int GetPartsNumber() { return s_partsNumber; }
	// �C�����i�ԍ����₷
	static void IncrementPartsNumber() { s_partsNumber++; }
	// �C�����i�ԍ��̃C���N�������g��ɖC�����i�ԍ����擾����
	static int GetPartsNumberAfterIncrement() { return ++s_partsNumber; }

private:
	// �C�����i�J�E���g
	static int s_partsNumber;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �Փ˃r�W�^�[
	ICollisionVisitor* m_collisionVisitor;
	// �e
	IComponent* m_parent;
	// �m�[�h�ԍ�
	int m_nodeNumber;
	// ���i�ԍ�
	int m_partNumber;
	// ���iID
	int m_partID;
	// �����ʒu
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �C����]�p
	DirectX::SimpleMath::Quaternion m_rotationTurretAngle;
	// �C�����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �����x
	DirectX::SimpleMath::Vector3 m_acceleration;
	// �i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 m_heading;
	// �ő�ړ����x
	float m_maxSpeed;
	// �ő��]�䗦(���W�A��/�b)
	float m_maxTurnRate;
	// �K�p�����ő��
	float m_maxForce;
	// ����
	float m_mass;
	// �C�����i�z��
	std::vector<std::unique_ptr<IComponent>> m_turretParts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �C�e�z��
	std::vector<std::unique_ptr<IBullet>> m_bullets;
	// �C�����E��
	DirectX::BoundingSphere m_turretBoundingSphere;
	// �C�����S�_
	DirectX::SimpleMath::Vector3 m_turretCenter;
	// �Փ�
	bool m_collision;
	// �ړ��t���O
	bool m_move;
	// �אږC���z��
	 std::vector<Turret*> m_neighbors;
	 // ���Ǎs��
	std::unique_ptr<SteeringBehavior> m_steeringBehavior;

};

#endif		// TURRET_DEFINED
