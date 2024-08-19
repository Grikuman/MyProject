#pragma once
#ifndef STANDING_DEFINED
#define STANDING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Standingクラスを定義する 
class Standing : public IState
{
public:
	// コンストラクタ
	Standing(Mario* mario);
	// デストラクタ
	~Standing();
	// 初期化する 
	void Initialize() override;
	// 更新する 
	void Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// 描画する 
	void Render() override;
	// 後処理をする 
	void Finalize() override;

private:
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// マリオ
	Mario* m_mario;
	// 「立ち」テクスチャ
	ID3D11ShaderResourceView* m_standingTexture;
};

#endif // STANDING_DEFINED
