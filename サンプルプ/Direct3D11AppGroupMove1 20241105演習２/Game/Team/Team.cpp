#include "Framework/pch.h"
#include "Game/Team/Team.h"

// ミューテックスを初期化する 
std::mutex Team::m_mutex{};
// プレイヤーチーム番号の初期化
int Team::s_playerTeamNumber = 0;
// エネミーチーム番号の初期化
int Team::s_enemyTeamNumber = 1;
// プレイヤーチーム中心位置
DirectX::SimpleMath::Vector3 Team::s_playerTeamCenterPosition = DirectX::SimpleMath::Vector3::Zero;
// エネミーチーム中心位置
DirectX::SimpleMath::Vector3 Team::s_enemyTeamCenterPosition = DirectX::SimpleMath::Vector3::Zero;
// プレイヤーと敵をスイッチしたかどうか
bool Team::s_opponentSwitch = false;

// チームリスト(チーム番号とノード番号配列)の初期化
std::unordered_map<int, std::vector<int>> Team::s_teamList =
{
	{0,	{ 1,  2,   3,   4,  5}},							// グループ 0 : {  1,   2,   3,   4,   5}
	{1,	{ 6,  7,   8,   9,  10,  11,  12}},		// グループ 1 : {  6,   7,   8,   9,   10,  11,  12} 
};

// 参照リストの初期化
std::unordered_map<int, IComponent* > Team::s_nodeReferenceList = {};
// 空リスト
const std::vector<int> Team::EMPTY_LIST = {};

// チーム番号からノードリストを取得する
const std::vector<int>& Team::GetNodeListForTeam(int teamNumber)
{
	// チーム番号からノードリストを探す
	auto it = s_teamList.find(teamNumber);
	// ノードリストを検出した場合ノードリスト配列を返す
	if (it != s_teamList.end())
	{
		// ノードリストの配列を返す
		return it->second;
	}
	// ノードリストが見つからない場合は空の配列を返す
	return EMPTY_LIST;
}

// ノード番号からチーム番号を取得する
int Team::GetTeamNumberForNodeNumber(int nodeNumber)
{
	for (auto& team : s_teamList)
	{
		// ノードリスト配列を取得する
		std::vector<int>& nodeArray = team.second;
		// ノードリスト配列のノードを選択する
		for (int node : nodeArray)
		{
			// ノードリスト配列の番号とノード番号が等しい場合にチーム番号を返す
			if (node == nodeNumber)
			{
				// チーム番号を返す
				return team.first;
			}
		}
	}
	// どのチームにも属していない場合は -1 を返す
	return -1;
}

// 参照リストにノードを追加する
void Team::AddNodeToReferenceList(int nodeNumber, IComponent* node)
{
	// ノード番号とノードを挿入する
	s_nodeReferenceList.insert({ nodeNumber, node });
}

// ノード番号から砲塔参照リストのノードを取得する
IComponent* Team::GetNodeFromTurretReferenceList(int nodeNumber)
{
	// ノード番号からノードを検索する
	auto it = s_nodeReferenceList.find(nodeNumber);
	// ノードが見つかった場合にノードを返す
	if (it != s_nodeReferenceList.end())
		return it->second;
	else
		return nullptr;
}

// プレイヤーチームを変更する
void Team::ChangePlayerTeam()
{
	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();
	// 数字配列を作成する
	std::vector<bool> digital = { keyboardState.D0, keyboardState.D1 };
	// どの数字を押下げたかを調べる
	for (int index = 0; index < digital.size(); index++)
	{
		// 押下げられた数字がプレイヤーチーム番号になる
		if (digital[index])
		{
			if (index == s_enemyTeamNumber) 
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				// エネミーチーム番号を取得する
				int enemyTeamNumber = s_playerTeamNumber;
				// プレイヤーチーム番号を取得する
				int playerTeamNumber = index;
				// プレイヤーチーム番号を設定する
				s_playerTeamNumber = playerTeamNumber;
				// エネミーチーム番号を設定する
				s_enemyTeamNumber = enemyTeamNumber;
				// プレイヤーと敵が切り替わった
				s_opponentSwitch = (s_opponentSwitch == false) ? true : false;
			}
		}
	}
}

// 砲塔参照リストからノードを削除する
void Team::DeleteNodeFromTurretReferenceList(int nodeNumber)
{
	// ノード番号をリファレンスリストから探す
	auto it = s_nodeReferenceList.find(nodeNumber);
	// ノード番号がリファレンスリストに存在する場合ノードを削除する
	if (it != s_nodeReferenceList.end())
	{
		// ノードを削除する
		s_nodeReferenceList.erase(it);
	}
}

// プレイヤーチーム中心位置を取得する
DirectX::SimpleMath::Vector3& Team::GetPlayerTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// プレイヤーチーム番号を取得する
	int playerTeamNumber = GetPlayerTeamNumber();
	// プレイヤーノード番号配列を取得する
	std::vector<int> playerNodeNumbers = GetNodeListForTeam(playerTeamNumber);
	// 位置集計をクリアする
	Vector3 sumPosition(Vector3::Zero);
	for (auto& nodeNumber : playerNodeNumbers)
	{
		// プレイヤー砲塔を取得する
		Turret* turret = dynamic_cast<Turret*>(GetNodeFromTurretReferenceList(nodeNumber));
		// 位置総計を計算する
		sumPosition = sumPosition + turret->GetPosition();
	}
	// プレイヤーチームの中央位置を計算する
	s_playerTeamCenterPosition = sumPosition / (float)playerNodeNumbers.size();
	// プレイヤーチーム中心位置を返す
	return s_playerTeamCenterPosition;
}

// エネミーチーム中心位置を取得する
DirectX::SimpleMath::Vector3& Team::GetEnemyTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// エネミーチーム番号を取得する
	int enemyTeamNumber = GetEnemyTeamNumber();
	// エネミーノード番号配列を取得する
	std::vector<int> enemyNodeNumbers = GetNodeListForTeam(enemyTeamNumber);
	// 位置集計をクリアする
	Vector3 sumPosition(Vector3::Zero);
	for (auto& nodeNumber : enemyNodeNumbers)
	{
		// エネミー砲塔を取得する
		Turret* turret = dynamic_cast<Turret*>(GetNodeFromTurretReferenceList(nodeNumber));
		// 位置総計を計算する
		sumPosition = sumPosition + turret->GetPosition();
	}
	// エネミーチームの中央位置を計算する
	s_enemyTeamCenterPosition = sumPosition / (float)enemyNodeNumbers.size();
	// エネミーチーム中心位置を返す
	return s_enemyTeamCenterPosition;
}