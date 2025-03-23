#pragma once
#ifndef IBULLET_DEFINED
#define IBULLET_DEFINED
#include "Framework/pch.h"

// IBullet�C���^�[�t�F�[�X���`����
class IBullet
{
public:
	// �C�e�̏��
	enum BulletState : short { UNUSED, FLYING, USED };

public:
	// �m�[�h�ԍ����擾����
	virtual int GetNodeNumber() const = 0;
	// ���݂̈ʒu���擾����
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// ���݂̈ʒu��ݒ肷��
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// �C�e��]�p���擾���� 
	virtual DirectX::SimpleMath::Quaternion GetBulletAngle() const = 0;
	// �C�e�㉺��]�p��ݒ肷�� 
	virtual void SetBulletAngle(const DirectX::SimpleMath::Quaternion& bulletAngle) = 0;
	// �C�e�����˂���Ă��邩�ǂ������擾����
	virtual BulletState GetBulletState() const = 0;
	// �C�e�̏�Ԃ�ݒ肷��
	virtual void SetBulletState(BulletState bulletState) = 0;
	// ���ʂ��擾����
	virtual float GetMass() const = 0;
	// ���f�����擾����
	virtual DirectX::Model* GetModel() = 0;
	// ���[���h���E�{�b�N�X���擾����
	virtual DirectX::BoundingBox* GetWorldBoundingBox() = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~IBullet() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const DX::StepTimer& timer) = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};

#endif		// IBULLET_DEFINED
