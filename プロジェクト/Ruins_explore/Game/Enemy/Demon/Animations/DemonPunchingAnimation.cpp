/*
	ファイル名：DemonPunchingAnimation.h
	　　　概要：ウォーロックのパンチアニメーションを管理するクラス
*/
#include "pch.h"
#include "DemonPunchingAnimation.h"
#include "Game/Enemy/Demon/Demon.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// // アニメーションが終了しているかどうか取得する
//---------------------------------------------------------
bool DemonPunchingAnimation::IsEndAnimation()
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
// ダメージを与えることができるか取得する
//---------------------------------------------------------
bool DemonPunchingAnimation::IsAbleToDealDamage()
{
	// アニメーションの時間が【1.4f～1.7】の場合
	if (m_time > HIT_START_TIME && m_time < HIT_END_TIME)
	{
		// ダメージ処理は可能
		return true;
	}
	else
	{
		// ダメージ処理は不可能
		return false;
	}
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
DemonPunchingAnimation::DemonPunchingAnimation(Demon* demon)
	:
	m_demon{demon},
	m_model{},
	m_time{},
	m_animTime{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
DemonPunchingAnimation::~DemonPunchingAnimation()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void DemonPunchingAnimation::Initialize()
{
	// プレイヤーのモデルを取得する
	m_model = Resources::GetInstance()->GetModel(L"Demon");
	// AnimationSDKMeshクラスを作成する
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// リソースディレクトリの設定
	Graphics::GetInstance()->GetFX()->SetDirectory(L"Resources/SDKMesh");
	// アニメーションをロードする
	m_animation->Load(L"Resources/SDKMesh/Demon_Punching.sdkmesh_anim");
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
void DemonPunchingAnimation::Update()
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
void DemonPunchingAnimation::Render()
{
	using namespace DirectX::SimpleMath;

	Matrix worldMatrix = 
		// スケール行列を作成
		Matrix::CreateScale(MODEL_SCALE) *
		// 180度回転させる(モデルの向き調整)
		Matrix::CreateRotationY(DirectX::XM_PI) *
		// 回転行列を作成
		Matrix::CreateFromQuaternion(m_demon->GetAngle()) *
		// 移動行列を作成
	    Matrix::CreateTranslation(m_demon->GetPosition() + Vector3(0.0f,-1.0f,0.0f)); 

	// アニメーションモデルの描画する
	DrawAnimation(m_model, &m_animBone, worldMatrix);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void DemonPunchingAnimation::Finalize()
{

}

//---------------------------------------------------------
// アニメーションモデルを描画する
//---------------------------------------------------------
void DemonPunchingAnimation::DrawAnimation(
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