/*
	ファイル名：PlayScene.h
	　　　概要：プレイシーンを管理するクラス
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Interface/IStage.h"
#include "Game/Factory/StageFactory.h"
#include <PostProcess.h>

namespace DX
{
	class RenderTexture;
}

class PlayScene final : public IScene
{
public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

public:
	// コンストラクタ
	PlayScene();
	// コンストラクタ
	~PlayScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime)override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// ステージの初期化
	void StageInitialize();
	// 次のステージへの移行を処理する
	void TransitionToNextStage();
	// レンダーテクスチャを作成する
	void CreateRenderTexture(ID3D11Device* device);

private:
	// 現在のステージ
	std::unique_ptr<IStage> m_currentStage;
	// シーンチェンジフラグ
	bool m_isChangeScene;

	// ポストプロセス
	std::unique_ptr<DirectX::BasicPostProcess> m_basicPostProcess;
	std::unique_ptr<DirectX::DualPostProcess> m_dualPostProcess;
	// レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_offScreenRT;
	std::unique_ptr<DX::RenderTexture> m_blur1RT;
	std::unique_ptr<DX::RenderTexture> m_blur2RT;
	// スクリーンサイズ
	RECT m_screenSize;
};
