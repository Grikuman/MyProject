#include "Framework/pch.h"
#include "Game/SoccerPlayer/State/PlayerStrikeFowarding.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"
#include "Framework/Resources.h"

// コンストラクタ
PlayerStrikeForwarding::PlayerStrikeForwarding(SoccerPlayer* player)
	:
	m_player(player),
	m_graphics{},
	m_context{},
	m_animBones{},
	m_totalSeconds(0.0f),
	m_animTime(0.0),
	m_worldMatrix{},
	m_soccerPlayerModel{},
	m_animation{},
	m_boundingSphereRightLeg{},
	m_rightLeg(63),
	m_boneMatrix{},
	m_inCollision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// コンテキストを取得する
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
}

// デストラクタ
PlayerStrikeForwarding::~PlayerStrikeForwarding()
{
}

// 初期化する
void PlayerStrikeForwarding::Initialize()
{
	// サッカープレイヤーモデルを取得する
	m_soccerPlayerModel = Resources::GetInstance()->GetSoccerPlayerModel();
	// AnimationSDKMESHクラスのインスタンスを生成する
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// リソースディレクトリを設定する
	m_graphics->GetFX()->SetDirectory(L"resources\\sdkmesh");
	// サッカープレイヤー ストライクフォワーディングアニメーションをロードする
	m_animation->Load(L"resources\\sdkmesh\\strikefowardJog.sdkmesh_anim");
	// アニメーションとモデルをバインドする
	m_animation->Bind(*m_soccerPlayerModel);
	// ボーン用のトランスフォーム配列を生成する
	m_animBones = DirectX::ModelBone::MakeArray(m_soccerPlayerModel->bones.size());
	// 相対ボーン配列を変換配列に複製する
	m_soccerPlayerModel->CopyAbsoluteBoneTransformsTo(m_soccerPlayerModel->bones.size(), m_animBones.get());
	// エフェクトを更新する
	m_soccerPlayerModel->UpdateEffects([&](DirectX::IEffect* effect)
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
	// 右脚境界球を生成する
	m_boundingSphereRightLeg = std::make_unique<DirectX::BoundingSphere>(m_player->GetPosition(), 0.006f);
	// 事前更新を呼び出す
	PreUpdate();
}

// 事前更新する
void PlayerStrikeForwarding::PreUpdate()
{
	// アイドリングアニメーションの開始時間を設定する
	m_animation->SetStartTime(0.0f);
	// アイドリングアニメーションの終了時間を設定する
	m_animation->SetEndTime(1.0);
}

// 更新する
void PlayerStrikeForwarding::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	// 総秒数を計算する
	m_totalSeconds += elapsedTime;
	// アニメーション時間がアニメーション終了時間より小さい場合はアニメーションを繰り返す
	if (m_animation->GetAnimTime() < m_animation->GetEndTime())
	{
		// アニメーションを更新する
		m_animation->Update(elapsedTime);
	}
	else
	{
		// アニメーションの開始時間を設定する
		m_animation->SetStartTime(0.0);
		// アイドリング状態に遷移する
		m_player->ChangeState(m_player->GetPlayerIdling());
	}
	// サッカープレーヤーのワールド行列を計算する
	m_worldMatrix = Matrix::CreateScale(m_player->GetScale()) *
		Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_player->GetAngle())) *
		Matrix::CreateTranslation(m_player->GetPosition());

	// ボーンからトラックを取得する
	auto track = m_animation->GetBoneToTrack(m_rightLeg);
	// ボーンマトリックスを取得する
	Matrix animBoneMatrix = m_soccerPlayerModel->invBindPoseMatrices[track] * m_animBones[track];
	// ワールドボーンマトリックスを計算する
	m_boneMatrix = animBoneMatrix * m_worldMatrix;
	// バウンディングスフィアの中心点を設定する
	m_boundingSphereRightLeg->Center = Vector3(m_boneMatrix._41, m_boneMatrix._42, m_boneMatrix._43);

	// サッカーボールのインスタンスを取得する
	auto soccerBall = dynamic_cast<SoccerBall*>(m_player->GetPlayScene()->GetSoccerBall());
	// サッカーボールのバウンディングスフィアを取得する
	DirectX::BoundingSphere soccerBallBoundingSphere = *soccerBall->GetBoundingSphere();
	// プレーヤーの右脚がサッカーボールと接触したかどうかを検出する
	if (m_boundingSphereRightLeg->Intersects(soccerBallBoundingSphere) && m_inCollision == false)
	{
		// 衝突開始
		m_inCollision = true;
		// サッカーボールを初期化する
		soccerBall->Reset();
		// サッカーボールを蹴る
		soccerBall->Shoot(m_player->GetPlayScene()->CalculateDirection(), m_player->GetPlayScene()->GetShootForce());
		// 衝突終了
		m_inCollision = false;
	}
}

// 事後更新する
void PlayerStrikeForwarding::PostUpdate()
{
}

// 描画する
void PlayerStrikeForwarding::Render()
{
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// プレーヤーモデルを描画する
	m_graphics->DrawModel(m_soccerPlayerModel, m_animation.get(), &m_animBones, m_worldMatrix);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 後処理を行う
void PlayerStrikeForwarding::Finalize()
{
	// アニメーションをリセットする
	m_animation.reset();
}
