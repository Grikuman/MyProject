#pragma once
#ifndef DOWNING_DEFINED
#define DOWNING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Downクラスを定義する 
class Downing : public IState
{
public:
	// コンストラクタ
	Downing(Mario* mario);
	// デストラクタ
	~Downing();
	// 初期化する 
	void Initialize() override;
	// 更新する 
	void Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// 描画する 
	void Render() override;
	// 後処理をおこなう 
	void Finalize() override;

private:
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// マリオ
	Mario* m_mario;
	// 「立ち」テクスチャ
	ID3D11ShaderResourceView* m_downingTexture;
};

#endif // DOWNING_DEFINED