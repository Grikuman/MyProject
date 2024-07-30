#include "Framework/pch.h"
#include "Game/SoccerPlayer/State/PlayerIdling.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"
#include "Framework/Resources.h"

// コンストラクタ
PlayerIdling::PlayerIdling(SoccerPlayer* player)
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
	m_boundingSphereLeftLeg{},
	m_leftLeg(66),
	m_boneMatrix{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// コンテキストを取得する
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
}

// デストラクタ
PlayerIdling::~PlayerIdling()
{
}

// 初期化する
void PlayerIdling::Initialize()
{
	// サッカープレイヤーモデルを取得する
	m_soccerPlayerModel = Resources::GetInstance()->GetSoccerPlayerModel();
	// AnimationSDKMESHクラスのインスタンスを生成する
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// リソースディレクトリを設定する
	m_graphics->GetFX()->SetDirectory(L"resources\\sdkmesh");
	// サッカープレイヤー アイドリングアニメーションをロードする
	m_animation->Load(L"resources\\sdkmesh\\OffensiveIdle.sdkmesh_anim");
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
	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;
	// 事前更新を呼び出す
	PreUpdate();
}

// 事前更新する
void PlayerIdling::PreUpdate()
{
	// ボーンインデックスを設定する
	m_leftLeg = 66;
	// アイドリングアニメーションの開始時間を設定する
	m_animation->SetStartTime(0.0f);
	// アイドリングアニメーションの終了時間を設定する
	m_animation->SetEndTime(9.2f);
}

// 更新する
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();
	if (keyboardState.Space)
	{
		// ストライクフォワーディング状態に遷移する
		m_player->ChangeState(m_player->GetPlayerStrikeForwarding());
	}

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
	}
	// サッカープレーヤーのワールド行列を計算する
	m_worldMatrix = Matrix::CreateScale(m_player->GetScale()) *
		Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_player->GetAngle())) *
		Matrix::CreateTranslation(m_player->GetPosition());

	// ボーンからトラックを取得する
	auto track = m_animation->GetBoneToTrack(m_leftLeg);
	// 左脚のボーンマトリックスを取得する
	Matrix animBoneMatrix = m_soccerPlayerModel->invBindPoseMatrices[track] * m_animBones[track];
	// ワールドボーンマトリックスを計算する
	m_boneMatrix = animBoneMatrix * m_worldMatrix;
	// バウンディングスフィアの中心点を設定する
	m_boundingSphereLeftLeg.Center = Vector3(m_boneMatrix._41, m_boneMatrix._42, m_boneMatrix._43);
	// サッカープレイヤーオブジェクトへのポインタを取得する
	auto soccerPlayer = dynamic_cast<SoccerPlayer*>(m_player);
	// サッカーボールのバウンディングスフィアを取得する
	DirectX::BoundingSphere* boundingSphereSoccerBall = soccerPlayer->GetPlayScene()->GetSoccerBall()->GetBoundingSphere();
	// プレーヤーの左脚がサッカーボールと接触したかどうかを検出する
	if (m_boundingSphereLeftLeg.Intersects(*boundingSphereSoccerBall))
	{
		// サッカーボールをリセットする
		soccerPlayer->GetPlayScene()->GetSoccerBall()->Reset();
	}
}

// 事後更新する
void PlayerIdling::PostUpdate()
{
}

// 描画する
void PlayerIdling::Render()
{
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// プレーヤーモデルを描画する
	m_graphics->DrawModel(m_soccerPlayerModel, m_animation.get(), &m_animBones, m_worldMatrix);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 後処理を行う
void PlayerIdling::Finalize()
{
	// アニメーションをリセットする
	m_animation.reset();
}
