#include "Framework/pch.h"
#include "Observer/Messenger.h"
#include "Team/Team.h"
#include "Interface/IObserver.h"
#include "Turret/Header/Turret.h"

// コマンド実行中
bool Messenger::m_commandExecution = false;
// キーボード観察者リストを初期化する
std::vector<std::pair<DirectX::Keyboard::Keys, IComponent*>> Messenger::s_observerList;
// キー範囲リスト(キーとキーの範囲(開始インデックスと終了インデックス))
std::unordered_map<DirectX::Keyboard::Keys, std::pair<size_t, size_t>> Messenger::s_keysRangeList;

// コマンド実行を取得する
bool Messenger::GetCommandExecution() { return m_commandExecution; }
// コマンド実行を設定する
void Messenger::SetCommandExecution(bool commandExecution) { m_commandExecution = commandExecution; }


// 観察者をアタッチする
void Messenger::Attach(const DirectX::Keyboard::Keys& keys, IComponent* observer)
{
	// 観察者リストに観察者を追加する
	s_observerList.emplace_back(std::make_pair(keys, observer));
}

// 観察者をデタッチする
void Messenger::Detach(const DirectX::Keyboard::Keys& keys, IComponent* observer)
{
	// 観察者リストから観察者を検索する
	s_observerList.erase
	(
		std::remove_if(s_observerList.begin(), s_observerList.end(),
			[&keys, observer](const std::pair<DirectX::Keyboard::Keys, IComponent*>& entry) 
			{
				return entry.first == keys && entry.second == observer;
			}),
		s_observerList.end()
	);
}

// 観察者に通知する
void Messenger::Notify(const DirectX::Keyboard::State& keyboardState, const std::vector<int>& playerNodeNumbers)
{
	// 「観察者リスト」からキーとキーの範囲(開始インデックスと終了インデックス)を取り出す
	for (const auto& keyRange : s_keysRangeList)
	{
		// 観察者が処理すべきキーかどうかを調べる
		if (keyboardState.IsKeyDown(keyRange.first))
		{
			// キーの開始インデックスから終了インデックスまでのインデックス取り出す
			for (auto range = keyRange.second.first; range <= keyRange.second.second; range++)
			{
				// プレイヤーノード番号配列からプレイヤーノード番号を取り出す
				for (const auto& playerNodeNumber : playerNodeNumbers)
				{
					// プレイヤーノード番号と観察者のノード番号が等しい場合 観察者にキーを通知する
					if (playerNodeNumber == s_observerList[range].second->GetNodeNumber())
					{
						// 観察者の通知関数に押下げられたキーを通知する
						s_observerList[range].second->OnKeyPressed(s_observerList[range].first);
					}
				}
			}
		}
	}
}

// キー入力により観察者に通知する
void Messenger::Notify(const DirectX::Keyboard::Keys& keys, const std::vector<int>& playerNodeNumbers)
{
	// 「観察者リスト」からキーとキーの範囲(開始インデックスと終了インデックス)を取り出す
	auto it = s_keysRangeList.find(keys);

	// キーの開始インデックスから終了インデックスまでのインデックス取り出す
	for (auto range = it->second.first; range <= it->second.second; range++)
	{
		// プレイヤーノード番号配列からプレイヤーノード番号を取り出す
		for (const auto& playerNodeNumber : playerNodeNumbers)
		{
			// プレイヤーノード番号と観察者のノード番号が等しい場合 観察者にキーを通知する
			if (playerNodeNumber == s_observerList[range].second->GetNodeNumber())
			{
				// 観察者の通知関数に押下げられたキーを通知する
				s_observerList[range].second->OnKeyPressed(s_observerList[range].first);
			}
		}
	}
}

// キー入力により観察者に通知する
void Messenger::Notify(const DirectX::Keyboard::Keys& keys)
{
	// 「観察者リスト」からキーとキーの範囲(開始インデックスと終了インデックス)を取り出す
	auto it = s_keysRangeList.find(keys);

	// キーの開始インデックスから終了インデックスまでのインデックス取り出す
	for (auto range = it->second.first; range <= it->second.second; range++)
	{
		// 観察者の通知関数に押下げられたキーを通知する
		s_observerList[range].second->OnKeyPressed(keys);
	}
}

// 左ボタンがクリックされた時にプレイヤーの観察者に通知する
void Messenger::NotifyToPlayer(const DirectX::SimpleMath::Vector3& mousePosition)
{
	// プレイヤーチーム番号を取得する
	int playerTeamNumber = Team::GetPlayerTeamNumber();
	// プレイヤーノード番号配列を取得する
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);
	for (auto& nodeNumber : playerNodeNumbers)
	{
		// プレイヤー砲塔を取得する
		Turret* turret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber));
		// 左ボタンがクリックされた時にプレイヤー観察者に通知する
		turret->OnLeftButtonClicked(mousePosition);
	}
}

// 「観察者リスト」をソートする
void Messenger::SortObserverList()
{
	// 「観察者リスト」をキーでソートする
	std::sort(
		s_observerList.begin(), 
		s_observerList.end(),
		[](const std::pair<DirectX::Keyboard::Keys, IComponent*>& a, const std::pair<DirectX::Keyboard::Keys, IComponent*>& b)
		{
			return a.first < b.first;
		});
}

//  キー範囲リストを生成する
void Messenger::CreateKeyRangeList()
{
	// 開始インデックスを設定する
	size_t  startIndex = 0;
	// 「キー範囲リスト」でデータが存在する場合は「キー範囲リスト」をクリアする
	if (s_keysRangeList.size()) 
		s_keysRangeList.clear();
	// 「観察者リスト」の開始キーを現在のキーにする
	DirectX::Keyboard::Keys currentKey = s_observerList[startIndex].first;
	// 「観察者リスト」の開始から終了まで繰り返す
	for (size_t  index = 1; index < s_observerList.size(); index++) 
	{
		// 「観察者リスト」のキーと現在のキーが等しくなくなった場合
		if (s_observerList[index].first != currentKey) 
		{
			// キーとキーの範囲(開始インデックスと終了インデックス)を「キー範囲リスト」に追加する
			s_keysRangeList.emplace(currentKey, std::make_pair(startIndex, index - 1));
			// インデックスを開始インデックスに設定する
			startIndex = index;
			// 「観察者リスト」のキーを現在のキーに設定する
			currentKey = s_observerList[index].first;
		}
	}
	// キーとキーの範囲(開始インデックスと終了インデックス)を「キー範囲リスト」に追加する
	s_keysRangeList.emplace(currentKey, std::make_pair(startIndex, s_observerList.size() - 1));
}
