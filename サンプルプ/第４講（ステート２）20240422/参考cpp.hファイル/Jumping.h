#pragma once
#ifndef JUMPING_DEFINED
#define JUMPING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Jumpingクラスを定義する 
class Jumping : public IState
{
public:
	// コンストラクタ
	Jumping(Mario* mario);
	// デストラクタ
	~Jumping();
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
	// 立ちテクスチャ
	ID3D11ShaderResourceView* m_jumpingTexture;
};

#endif	// JUMPING_DEFINED
