#pragma once
#ifndef COLLISION_VISITOR_DEFINED
#define COLLISION_VISITOR_DEFINED
#include "Interface/IComponent.h"

class CollisionVisitor : public ICollisionVisitor
{
public:
	// CollisionVisitor�N���X�̃C���X�^���X���擾����
	static CollisionVisitor* GetInstance();
	// �R���X�g���N�^
	CollisionVisitor();
	// �f�X�g���N�^
	~CollisionVisitor();
	// �Փ˔�����J�n����
	void StartPrepareCollision(IComponent* component);
	// �Փ˔���̏������s��
	void PrepareCollision(IComponent* component);
	// �Փ˔�����s��
	void DetectCollision(IComponent* component, IBullet* bullet);
	// ���E�{�b�N�X��`�悷��
	void DrawBoundingBox(int index, const DirectX::SimpleMath::Matrix& matrix);
	// �m�[�h�ԍ�����C�����i�ɃJ���[��ݒ肷��
	void SetTurretPartColor(int nodeNumber, DirectX::Model* model, bool collision);
	// ���f���ɃJ���[��ݒ肷��
	void SetColorToModel(DirectX::Model* model, const DirectX::XMVECTORF32& color);


private:
	// �R���W�����r�W�^�[
	static std::unique_ptr<CollisionVisitor> s_collisionVisitor;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �u�C���v�z��o�E���f�B���O�{�b�N�X
	std::unordered_map<int, DirectX::BoundingBox> m_boundingBoxes;
	// ���[���h�s��z��
	std::vector<DirectX::SimpleMath::Matrix*> m_worldMatrixes;

};

#endif		// COLLISION_VISITOR_DEFINED
