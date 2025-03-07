//--------------------------------------------------------------------------------------
//	File: SceneManager.h
//
//	シーンを管理するクラス
//
//	Date: 2023.3.25
//	Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

//	ESCキーで終了したい場合有効にしてください
#define ESC_QUIT_ENABLE

#ifdef ESC_QUIT_ENABLE
#include "Keyboard.h"
#endif

namespace Imase
{
	template <class T>
	class SceneManager;

	//	シーンの基底クラス
	template <class T>
	class Scene
	{
	private:

		//	シーンマネージャーへのポインタ
		SceneManager<T>* m_sceneManager;

	public:

		//	コンストラクタ
		Scene() : m_sceneManager(nullptr) {}

		//	デストラクタ
		virtual ~Scene() = default;

		//	初期化
		virtual void Initialize() = 0;

		//	更新
		virtual void Update(float elapsedTime) = 0;

		//	描画
		virtual void Render() = 0;

		//	終了処理
		virtual void Finalize() = 0;

		//	デバイスに依存するリソースを作成する関数
		virtual void CreateDeviceDependentResources() {}

		//	ウインドウサイズに依存するリソースを作成する関数
		virtual void CreateWindowSizeDependentResources() {}

		//	デバイスロストした時に呼び出される関数
		virtual void OnDeviceLost() {}

	public:

		//	シーンマネージャー設定関数
		void SetSceneManager(SceneManager<T>* sceneManager) { m_sceneManager = sceneManager; }

		//	シーンの切り替え関数
		template <class U>
		void ChangeScene();

		//	ユーザーが設定したリソース取得関数
		T* GetUserResources();

	};

	//	シーンマネージャークラス
	template <class T>
	class SceneManager
	{
	private:

		//	共通でアクセスしたいオブジェクトへのポインタ
		T* m_userResources;

		//	実行中のシーンへのポインタ
		Scene<T>* m_scene;

		//	シーン削除関数
		void DeleteScene();

	public:

		//	コンストラクタ
		SceneManager(T* userResources)
			: m_userResources(userResources)
			, m_scene(nullptr)
		{
		};

		//	デストラクタ
		virtual ~SceneManager() { DeleteScene(); };

		//	更新
		void Update(float elapsedTime);

		//	描画
		void Render();

		//	デバイスに依存するリソースを作成する関数
		void CreateDeviceDependentResources();
		
		//	ウインドウサイズに依存するリソースを作成する関数
		void CreateWindowSizeDependentResources();

		//	デバイスロストした時に呼び出される関数
		virtual void OnDeviceLost();

		//	シーンの設定関数
		template <class U>
		void SetScene();

		//	ユーザーリソース取得関数
		T* GetUseResources() { return m_userResources; }

	};

	//	シーンの切り替え関数
	template <class T>
	template <class U>
	void Scene<T>::ChangeScene()
	{
		m_sceneManager->SetScene<U>();
	}

	//	ユーザーが設定したリソース取得関数
	template <class T>
	T* Scene<T>::GetUserResources()
	{
		assert(m_sceneManager);

		return m_sceneManager->GetUseResources();
	}

	//	シーンの設定関数
	template <class T>
	template <class U>
	void SceneManager<T>::SetScene()
	{
		//	シーンを削除
		DeleteScene();

		assert(m_scene == nullptr);

		//	シーンを生成
		m_scene = new U;

		//	シーンにシーンマネージャーへのポインタを設定
		m_scene->SetSceneManager(this);

		//	シーンの初期化処理
		m_scene->Initialize();
	}

	//	更新関数
	template <class T>
	void SceneManager<T>::Update(float elapsedTime)
	{
#ifdef ESC_QUIT_ENABLE
		//	ESCキーで終了
		DirectX::Keyboard::State kb = DirectX::Keyboard::Get().GetState();
		if (kb.Escape) PostQuitMessage(0);
#endif

		if (m_scene) m_scene->Update(elapsedTime);
	}

	//	描画関数
	template <class T>
	void SceneManager<T>::Render()
	{
		if (m_scene) m_scene->Render();
	}

	//	デバイスに依存するリソースを作成する関数
	template <class T>
	void SceneManager<T>::CreateDeviceDependentResources()
	{
		if (m_scene) m_scene->CreateDeviceDependentResources();
	}

	//	ウインドウサイズに依存するリソースを作成する関数
	template <class T>
	void SceneManager<T>::CreateWindowSizeDependentResources()
	{
		if (m_scene) m_scene->CreateWindowSizeDependentResources();
	}

	//	デバイスロストした時に呼び出される関数
	template <class T>
	void SceneManager<T>::OnDeviceLost()
	{
		if (m_scene) m_scene->OnDeviceLost();
	}

	//	シーンの削除関数
	template <class T>
	void SceneManager<T>::DeleteScene()
	{
		if (m_scene)
		{
			m_scene->Finalize();

			delete m_scene;

			m_scene = nullptr;
		}
	}

}

