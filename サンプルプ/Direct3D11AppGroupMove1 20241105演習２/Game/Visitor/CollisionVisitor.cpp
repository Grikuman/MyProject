#include "Framework/pch.h"
#include "Utilities/DebugDraw.h"
#include "Visitor/CollisionVisitor.h"
#include "Interface/IBullet.h"
#include "Team/Team.h"

// �R���W�����r�W�^�[
std::unique_ptr<CollisionVisitor> CollisionVisitor::s_collisionVisitor = nullptr;

// CollisionVisitor�N���X�̃C���X�^���X���擾����
CollisionVisitor* CollisionVisitor::GetInstance()
{
	if (s_collisionVisitor == nullptr)
	{
		// CollisionVisitor�N���X�̃C���X�^���X�𐶐�����
		s_collisionVisitor.reset(new CollisionVisitor());
	}
	// CollisionVisitor�N���X�̃C���X�^���X��Ԃ�
	return s_collisionVisitor.get();
}

// �R���X�g���N�^
CollisionVisitor::CollisionVisitor()
	:
	m_boundingBoxes{},
	m_worldMatrixes{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}

// �f�X�g���N�^
CollisionVisitor::~CollisionVisitor()
{
}

// �Փ˔�����J�n����
void CollisionVisitor::StartPrepareCollision(IComponent* component)
{
	// �Փˏ������r�W�^�[���J�n����
	component->PrepareCollision(this);
}

// �Փ˔���̏������s��
void CollisionVisitor::PrepareCollision(IComponent* component)
{
	DirectX::BoundingBox boundingBox;
	if (component->GetPartID() == -1) return;
	// ���f�����擾����
	DirectX::Model* model = component->GetModel();
	//	���f�����狫�E�{�b�N�X���擾����
	for (auto it = model->meshes.cbegin(); it != model->meshes.cend(); it++)
	{
		// �ŏ��̃��f���̋��E�{�b�N�X��ݒ肷��
		if (it == model->meshes.cbegin())
		{
			// ���f�����狫�E�{�b�N�X��ݒ肷��
			boundingBox = (*it)->boundingBox;
		}
		else
		{
			// ���f�����狫�E�{�b�N�X���}�[�W����
			DirectX::BoundingBox::CreateMerged(boundingBox, boundingBox, (*it)->boundingBox);
		}
	}
	// ���i�ԍ��Ƌ��E�{�b�N�X�����E�}�b�v�Ɋi�[����
	m_boundingBoxes.insert({ component->GetPartNumber(),boundingBox });
}

// �C�e�ƖC�����i�̏Փ˔�����s��
void CollisionVisitor::DetectCollision(IComponent* component, IBullet* bullet)
{
	DirectX::BoundingBox worldBoundingBox;
	if (component->GetPartID() == -1) return;
	// ���i�ԍ����狫�E�{�b�N�X����������
	auto it = m_boundingBoxes.find(component->GetPartNumber());
	// ���E�{�b�N�X���g�����X�t�H�[������
	it->second.Transform(worldBoundingBox, component->GetWorldMatrix());
	// �C�e����e���ŖC�����i�ƖC�e���Փ˂����ꍇ�̏������L�q����
	if (bullet->GetBulletState() == IBullet::FLYING && worldBoundingBox.Intersects(*bullet->GetWorldBoundingBox()))
	{
		// �C�����i�ƖC�e���Փ˂����ꍇ�̏������L�q����
		component->SetCollision(true);
	}
}

// ���E�{�b�N�X��`�悷��
void CollisionVisitor::DrawBoundingBox(int index, const DirectX::SimpleMath::Matrix& matrix)
{
	DirectX::BoundingBox worldBoundingBox;
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// ���E�{�b�N�X���g�����X�t�H�[������
	m_boundingBoxes[index].Transform(worldBoundingBox, matrix);
	// ���E�{�b�N�X��`�悷��
	DX::Draw(m_graphics->GetPrimitiveBatch(), worldBoundingBox, DirectX::Colors::White);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �m�[�h�ԍ�����C�����i�ɃJ���[��ݒ肷��
void CollisionVisitor::SetTurretPartColor(int nodeNumber, DirectX::Model* model, bool collision)
{
	// �m�[�h�ԍ����ǂ̃`�[���ԍ��ɏ������邩���擾����
	int teamNumber = Team::GetTeamNumberForNodeNumber(nodeNumber);
	if (teamNumber == Team::GetPlayerTeamNumber())
	{ 	// �v���C���[�Ƀ_�[�N�O���[��ݒ肷��
		SetColorToModel(model, DirectX::Colors::Gray);
	}
	else
	{ 	// �G�Ƀ��C�g�X���[�g�O���[��ݒ肷��
		SetColorToModel(model, DirectX::Colors::LightSlateGray);
	}
	if (collision == true)
	{ 	// �Փ˂����ꍇ�Ƀ_�[�N���b�h��ݒ肷��
		SetColorToModel(model, DirectX::Colors::DarkRed);
	}
}

// ���f���ɃJ���[��ݒ肷��
void CollisionVisitor::SetColorToModel(DirectX::Model* model, const DirectX::XMVECTORF32& color)
{
	model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// �x�C�V�b�N�G�t�F�N�g���擾����
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			// �f�B�t���[�Y�J���[��ݒ肷��
			basicEffect->SetDiffuseColor(color);
			// �X�y�L�����J���[��ݒ肷��
			basicEffect->SetSpecularColor(color);
			// �X�y�L�����p���[��ݒ肷��
			basicEffect->SetSpecularPower(10.0f);
		});
}
