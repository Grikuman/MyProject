#pragma once
#ifndef NODEBASE_DEFINED
#define NODEBASE_DEFINED
#include "Interface/IComponent.h"

// �V�[���O���t���[�g�N���X���`����
class NodeBase : public IComponent
{
	// �e���擾����
	IComponent* GetParent() const { return m_parent; }
	// ���ʂ��擾����
	float GetMass() const { return m_mass; }
	// ���ʂ�ݒ肷��
	void SetMass(const float& mass) { m_mass = mass; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }

public:
	// �R���X�g���N�^
	NodeBase(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngleRL, const float& mass);
	// �f�X�g���N�^
	virtual ~NodeBase();
	// ����������
	virtual void Initialize();
	// �X�V����
	inline virtual void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle);
	// �`�悷��
	inline virtual void Render();
	// �C�����i��ǉ�����
	void Attach(std::unique_ptr<IComponent> node);
	// �C�����i���폜����
	void Detach(std::unique_ptr<IComponent> node);

	// �㏈�����s��
	virtual void Finalize();

public:
	// �m�[�h�J�E���g�̃J�E���g�A�b�v��m�[�h�J�E���g���擾����(1����J�n����)
	static int GetNodeCountAfterCountUp() { return ++s_nodeCount; }
	// �m�[�h�J�E���g���擾����
	static int GetNodeCount() { return s_nodeCount; }

private:
	// �m�[�h�J�E���g
	static int s_nodeCount;

private:
	// �e
	IComponent* m_parent;
	// �����ʒu
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// ������]�p
	float m_initialAngle;
	// ����
	float m_mass;
	// �m�[�h�z��
	std::vector<std::unique_ptr<IComponent>> m_nodes;
};

#endif		// NODEBASE_DEFINED
