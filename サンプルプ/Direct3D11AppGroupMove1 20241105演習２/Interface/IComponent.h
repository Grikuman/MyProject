#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "StepTimer.h"
#include "Interface/IObserver.h"
#include "Interface/ICollision.h"

// IComponent�C���^�[�t�F�[�X���`����
class IComponent : public IObserver, public ICollision
{
public:
	// �m�[�h�ԍ����擾����
	virtual int GetNodeNumber() const = 0;
	// ���iID���擾����
	virtual int GetPartID() const = 0;
	// ���i�ԍ����擾����
	virtual int GetPartNumber() const = 0;
	// �e���擾����
	virtual IComponent* GetParent() const = 0;
	// ���݂̈ʒu���擾����
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// ���݂̈ʒu��ݒ肷��
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& curretPosition) = 0;
	// ���݂̉�]�p���擾����
	virtual DirectX::SimpleMath::Quaternion GetAngle() const = 0;
	// ���݂̉�]�p��ݒ肷��
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& angle) = 0;
	// ���ʂ��擾����
	virtual float GetMass() const = 0;
	// ���ʂ�ݒ肷��
	virtual void SetMass(const float& mass) = 0;
	// ���f�����擾����
	virtual DirectX::Model* GetModel() = 0;
	// ���[���h�s����擾����
	virtual DirectX::SimpleMath::Matrix& GetWorldMatrix() = 0;
	// �Փ˂��擾����
	virtual bool GetCollision() const = 0;
	// �Փ˂�ݒ肷��
	virtual void SetCollision(bool collision) = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~IComponent() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};

#endif		// ICOMPONENT_DEFINED
