#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED
#include <unordered_map>
#include "IComponent.h"
#include "ISubject.h"
#include "Turret/Header/Turret.h"

// Subjectクラスを定義する
class Messenger : public ISubject
{
public:
	// コマンド実行を取得する
	static bool GetCommandExecution();
	// コマンド実行を設定する
	static void SetCommandExecution(bool commandExecution);

	// 観察者をアタッチする
	static void Attach(const DirectX::Keyboard::Keys& keys, IComponent* observer);
	// 観察者をデタッチする
	static void Detach(const DirectX::Keyboard::Keys& keys, IComponent* component);
	// キー入力により観察者に通知する
	static void Notify(const DirectX::Keyboard::State& keyboardState, const std::vector<int>& playerNodeNumbers);
	static void Notify(const DirectX::Keyboard::Keys& keys, const std::vector<int>& playerNodeNumbers);
	static void Notify(const DirectX::Keyboard::Keys& keys);
	// 左ボタンがクリックされた時にプレイヤー観察者に通知する
	static void NotifyToPlayer(const DirectX::SimpleMath::Vector3& mousePosition);
// 観察者リストをソートする
	static void SortObserverList();
	//  キー範囲リストを生成する
	static void CreateKeyRangeList();

private:
	// コマンド実行中
	static bool m_commandExecution;
	// キーボード観察者リスト
	static std::vector<std::pair<DirectX::Keyboard::Keys, IComponent*>> s_observerList;
	// キー範囲リスト(開始インデックスと終了インデックス)
	static std::unordered_map<DirectX::Keyboard::Keys, std::pair<size_t, size_t>> s_keysRangeList;
};

#endif	// MESSENGER_DEFINED