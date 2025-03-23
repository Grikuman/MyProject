#pragma once
#ifndef TURRET_TOP_DEFINED
#define TURRET_TOP_DEFINED
#include "Interface/IComposite.h"

// �u�C���㕔�v�N���X���`����
class TurretTop : public IComposite
{
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
	// �Փ˂��擾����
	bool GetCollision() const { return m_collision; }
	// �Փ˂�ݒ肷��
	void SetCollision(bool collision) { m_collision = collision; }

public:
	// �R���X�g���N�^
	TurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	// �f�X�g���N�^
	~TurretTop();
	// ����������
	void Initialize();
	// �ʒm����
	inline void OnKeyPressed(const DirectX::Keyboard::Keys& keys);
	// �X�V����
	inline void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle);
	// �Փ˔������������
	void PrepareCollision(ICollisionVisitor* visitor);
	// �Փ˔��肷��
	void DetectCollision(ICollisionVisitor* visitor, IBullet* bullet);
	// �C�����i��ǉ�����
	void Attach(std::unique_ptr<IComponent> turretPart);
	// �C�����i���폜����
	void Detach(std::unique_ptr<IComponent> turretPart);
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
	DirectX::SimpleMath::Quaternion  m_initialAngle;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �C���㕔��]�p
	DirectX::SimpleMath::Quaternion m_rotationTopAngle;
	// ����
	float m_mass;
	// �C�����i
	std::unique_ptr<IComponent> m_turretPart;
	// �C�����i�z��
	std::vector<std::unique_ptr<IComponent>> m_turretParts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �Փ�
	bool m_collision;
	// �����ǔ�
	bool m_automaticTracking;
};

#endif		// TURRET_TOP_DEFINED
