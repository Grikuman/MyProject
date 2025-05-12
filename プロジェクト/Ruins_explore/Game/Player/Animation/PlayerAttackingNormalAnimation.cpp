/*
	ファイル名：PlayerAttackingNormalAnimation.h
	　　　概要：プレイヤーのアニメーションを管理するクラス
*/
#include "pch.h"
#include "PlayerAttackingNormalAnimation.h"
#include "Game/Player/Player.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// // アニメーションが終了しているかどうか取得する
//---------------------------------------------------------
bool PlayerAttackingNormalAnimation::IsEndAnimation()
{
	// アニメーションが終了した場合
	if (m_time >= ANIMATION_TIME)
	{
		// アニメーション時間をリセットする
		m_animation->SetAnimTime(0.0f);
		m_time = 0.0f;
		// アニメーションを終了する
		return true;
	}
	return false;
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttackingNormalAnimation::PlayerAttackingNormalAnimation()
	:
	m_player{},
	m_model{},
	m_time{},
	m_animTime{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttackingNormalAnimation::~PlayerAttackingNormalAnimation()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttackingNormalAnimation::Initialize()
{
	// プレイヤーのポインタを取得する
	m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
	// プレイヤーのモデルを取得する
	m_model = Resources::GetInstance()->GetModel(L"Player");
	// AnimationSDKMeshクラスを作成する
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// リソースディレクトリの設定
	Graphics::GetInstance()->GetFX()->SetDirectory(L"Resources/SDKMesh");
	// アニメーションをロードする
	m_animation->Load(L"Resources/SDKMesh/Player_AttackingNormal.sdkmesh_anim");
	// アニメーションとモデルをバインドする
	m_animation->Bind(*m_model);
	// ボーン用のトランスフォーム配列を生成する
	m_animBone = DirectX::ModelBone::MakeArray(m_model->bones.size());
	// 相対ボーン配列を変換配列に複製する
	m_model->CopyAbsoluteBoneTransformsTo(m_model->bones.size(), m_animBone.get());
	// エフェクトを更新する
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// SkinnedEffectクラスにキャストする
			auto skin = dynamic_cast<DirectX::SkinnedEffect*>(effect);
			if (skin)
			{
				// パーピクセルライティングを有効にする
				skin->SetPerPixelLighting(true);
			}
		}
	);
	// アニメーションの開始時間を設定する
	m_animation->SetStartTime(0.0f);
	// アニメーションの終了時間を設定する
	m_animation->SetEndTime(ANIMATION_TIME);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttackingNormalAnimation::Update()
{
	m_time += ANIMATION_SPEED;
	// アニメーションが終了するまで更新
	if (m_animation->GetAnimTime() < m_animation->GetEndTime()) 
	{
		// アニメーションを更新する
		m_animation->Update(ANIMATION_SPEED);
	}
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttackingNormalAnimation::Render()
{
	using namespace DirectX::SimpleMath;

	Matrix worldMatrix = 
		// スケール行列を作成
		Matrix::CreateScale(MODEL_SCALE) * 
		// 回転行列を作成
		Matrix::CreateFromQuaternion(m_player->GetAngle()) *
		// 移動行列を作成
	    Matrix::CreateTranslation(m_player->GetPosition() + Vector3(0.0f,-1.0f,0.0f)); 

	// アニメーションモデルの描画する
	DrawAnimation(m_model, &m_animBone, worldMatrix);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerAttackingNormalAnimation::Finalize()
{

}

//---------------------------------------------------------
// アニメーションモデルを描画する
//---------------------------------------------------------
void PlayerAttackingNormalAnimation::DrawAnimation(
	const DirectX::Model* model, 
	const DirectX::ModelBone::TransformArray* transformArray, 
	const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// ボーン配列のサイズを取得する
	size_t bones = m_model->bones.size();
	// アニメーションにモデル、ボーン数、ボーンを適用する
	m_animation->Apply(*model, bones, transformArray->get());
	// コモンステートを取得する
	DirectX::CommonStates* commonState = Graphics::GetInstance()->GetCommonStates();
	// スキンメッシュアニメーションを描画する
	model->DrawSkinned(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*commonState,
		bones,
		transformArray->get(),
		worldMatrix,
		Graphics::GetInstance()->GetViewMatrix(),
		Graphics::GetInstance()->GetProjectionMatrix()
	);
}