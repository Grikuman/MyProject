#pragma once
#ifndef TURRET_PLATE_DEFINED
#define TURRET_PLATE_DEFINED
#include "Interface/ILeaf.h"

// �u�C���v���[�g�v�N���X���`����
class TurretPlate : public ILeaf
{
public:
	// �v���[�g���
	enum State : int{ OPEN, CLOSE, MOVE};

	// �v���[�g�I�[�v���ʒu
	const DirectX::SimpleMath::Vector3 OPEN_POSITION = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.5f);
	// �v���[�g�N���[�Y�ʒu
	const DirectX::SimpleMath::Vector3 CLOSE_POSITION = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.35f);

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
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	// ���݂̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// ���ʂ��擾����
	float GetMass() const { return m_mass; }
	// ���ʂ�ݒ肷��
	void SetMass(const float& mass) { m_mass = mass; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return m_model; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	// ��Ԃ�ݒ肷��
	void SetState(const State& state) { m_currentState = state; }
	// �Փ˂��擾����
	bool GetCollision() const { return m_collision; }
	// �Փ˂�ݒ肷��
	void SetCollision(bool collision) { m_collision = collision; }

public:
	// �R���X�g���N�^
	TurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	// �f�X�g���N�^
	~TurretPlate();
	// ����������
	void Initialize();
	// �ʒm����
	inline void OnKeyPressed(const DirectX::Keyboard::Keys& keys);
	// �X�V����
	inline void Update(DX::StepTimer const& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle);
	// �Փ˔������������
	void PrepareCollision(ICollisionVisitor* visitor);
	// �Փ˔��肷��
	void DetectCollision(ICollisionVisitor* visitor, IBullet* bullets);
	// �v���[�g���J����
	inline void MovePlate();
	// �`�悷��
	inline void Render();
	// �㏈�����s��
	void Finalize();

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �Փ˃r�W�^�[
	ICollisionVisitor* m_collisionVisitor;
	// ���f��
	DirectX::Model* m_model;
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
	// �v���[�g���`��Ԉʒu
	DirectX::SimpleMath::Vector3 m_lerpPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// ����
	float m_mass;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���
	State m_currentState;
	// ��ԌW���𑝕�����
	float m_lerpT;
	// �J�n�ʒu
	DirectX::SimpleMath::Vector3 m_startPosition;
	// �I���ʒu
	DirectX::SimpleMath::Vector3 m_endPosition;
	// �Փ�
	bool m_collision;
};

#endif		// TURRET_PLATE_DEFINED
