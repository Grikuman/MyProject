/*
	ファイル名：IScene.h
	　　　概要：シーンのインターフェース
*/
#pragma once

class IScene
{
public:
	//シーンID
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		MAPSELECT,
		PLAY,
		RESULT
	};

public:
	// 次のシーンIDを取得する
	virtual SceneID GetNextSceneID() const = 0;

public:
	// デストラクタ
	virtual ~IScene() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(float elapsedTime) = 0;
	// 描画する
	virtual void Render() = 0;
	// 終了処理
	virtual void Finalize() = 0;
};
