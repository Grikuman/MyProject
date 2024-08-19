#pragma once
#ifndef STANDING_DEFINED
#define STANDING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Standingクラスを宣言する 
class Standing : public IState
{
public:
	// コンストラクタ
	Standing(Mario* mario);
	// デストラクタ
	~Standing();
	// Standingオブジェクトを初期化する 
	void Initialize() override;
	// 立ちを実行する 
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// 立ちを描画する 
	void Render() override;
	// 後始末をする 
	void Finalize() override;

private:
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// マリオ
	Mario* m_mario;
	// 立ちテクスチャ
	ID3D11ShaderResourceView* m_standingTexture;
};

#endif // STANDING_DEFINED
