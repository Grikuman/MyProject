#include "Framework/pch.h"
#include "Utilities/DebugDraw.h"
#include "Visitor/CollisionVisitor.h"
#include "Interface/IBullet.h"
#include "Team/Team.h"

// コリジョンビジター
std::unique_ptr<CollisionVisitor> CollisionVisitor::s_collisionVisitor = nullptr;

// CollisionVisitorクラスのインスタンスを取得する
CollisionVisitor* CollisionVisitor::GetInstance()
{
	if (s_collisionVisitor == nullptr)
	{
		// CollisionVisitorクラスのインスタンスを生成する
		s_collisionVisitor.reset(new CollisionVisitor());
	}
	// CollisionVisitorクラスのインスタンスを返す
	return s_collisionVisitor.get();
}

// コンストラクタ
CollisionVisitor::CollisionVisitor()
	:
	m_boundingBoxes{},
	m_worldMatrixes{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}

// デストラクタ
CollisionVisitor::~CollisionVisitor()
{
}

// 衝突判定を開始する
void CollisionVisitor::StartPrepareCollision(IComponent* component)
{
	// 衝突初期化ビジターを開始する
	component->PrepareCollision(this);
}

// 衝突判定の準備を行う
void CollisionVisitor::PrepareCollision(IComponent* component)
{
	DirectX::BoundingBox boundingBox;
	if (component->GetPartID() == -1) return;
	// モデルを取得する
	DirectX::Model* model = component->GetModel();
	//	モデルから境界ボックスを取得する
	for (auto it = model->meshes.cbegin(); it != model->meshes.cend(); it++)
	{
		// 最初のモデルの境界ボックスを設定する
		if (it == model->meshes.cbegin())
		{
			// モデルから境界ボックスを設定する
			boundingBox = (*it)->boundingBox;
		}
		else
		{
			// モデルから境界ボックスをマージする
			DirectX::BoundingBox::CreateMerged(boundingBox, boundingBox, (*it)->boundingBox);
		}
	}
	// 部品番号と境界ボックスを境界マップに格納する
	m_boundingBoxes.insert({ component->GetPartNumber(),boundingBox });
}

// 砲弾と砲塔部品の衝突判定を行う
void CollisionVisitor::DetectCollision(IComponent* component, IBullet* bullet)
{
	DirectX::BoundingBox worldBoundingBox;
	if (component->GetPartID() == -1) return;
	// 部品番号から境界ボックスを検索する
	auto it = m_boundingBoxes.find(component->GetPartNumber());
	// 境界ボックスをトランスフォームする
	it->second.Transform(worldBoundingBox, component->GetWorldMatrix());
	// 砲弾が飛弾中で砲塔部品と砲弾が衝突した場合の処理を記述する
	if (bullet->GetBulletState() == IBullet::FLYING && worldBoundingBox.Intersects(*bullet->GetWorldBoundingBox()))
	{
		// 砲塔部品と砲弾が衝突した場合の処理を記述する
		component->SetCollision(true);
	}
}

// 境界ボックスを描画する
void CollisionVisitor::DrawBoundingBox(int index, const DirectX::SimpleMath::Matrix& matrix)
{
	DirectX::BoundingBox worldBoundingBox;
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 境界ボックスをトランスフォームする
	m_boundingBoxes[index].Transform(worldBoundingBox, matrix);
	// 境界ボックスを描画する
	DX::Draw(m_graphics->GetPrimitiveBatch(), worldBoundingBox, DirectX::Colors::White);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// ノード番号から砲塔部品にカラーを設定する
void CollisionVisitor::SetTurretPartColor(int nodeNumber, DirectX::Model* model, bool collision)
{
	// ノード番号がどのチーム番号に所属するかを取得する
	int teamNumber = Team::GetTeamNumberForNodeNumber(nodeNumber);
	if (teamNumber == Team::GetPlayerTeamNumber())
	{ 	// プレイヤーにダークグレーを設定する
		SetColorToModel(model, DirectX::Colors::Gray);
	}
	else
	{ 	// 敵にライトスレートグレーを設定する
		SetColorToModel(model, DirectX::Colors::LightSlateGray);
	}
	if (collision == true)
	{ 	// 衝突した場合にダークレッドを設定する
		SetColorToModel(model, DirectX::Colors::DarkRed);
	}
}

// モデルにカラーを設定する
void CollisionVisitor::SetColorToModel(DirectX::Model* model, const DirectX::XMVECTORF32& color)
{
	model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// ベイシックエフェクトを取得する
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			// ディフューズカラーを設定する
			basicEffect->SetDiffuseColor(color);
			// スペキュラカラーを設定する
			basicEffect->SetSpecularColor(color);
			// スペキュラパワーを設定する
			basicEffect->SetSpecularPower(10.0f);
		});
}
