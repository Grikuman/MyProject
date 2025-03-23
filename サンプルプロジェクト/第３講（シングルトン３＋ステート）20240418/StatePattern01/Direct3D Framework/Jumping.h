#pragma once
#ifndef Jumping_DEFINED
#define Jumping_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Downクラスを宣言する 
class Jumping : public IState
{
public:
	// コンストラクタ
	Jumping(Mario* mario);
	// デストラクタ
	~Jumping();
	// Jumpingオブジェクトを初期化する 
	void Initialize() override;
	// ジャンプを更新する 
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// ジャンプを描画する 
	void Render() override;
	// 後始末をする 
	void Finalize() override;

private:
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// マリオ
	Mario* m_mario;
	// ジャンプテクスチャ
	ID3D11ShaderResourceView* m_jumpingTexture;
};

#endif // Jumping_DEFINED