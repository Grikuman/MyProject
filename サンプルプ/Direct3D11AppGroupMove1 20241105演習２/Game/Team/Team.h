#pragma once
#include <unordered_map>
#include <vector>
#include <mutex>
#include "Interface/IComponent.h"
#include "Turret/Header/Turret.h"

#ifndef TEAM_DEFINED
#define TEAM_DEFINED

class Team
{
	// エンプティ
	static const std::vector<int> EMPTY_LIST;

public:
	// プレイヤーチーム番号を取得する
	static int GetPlayerTeamNumber() { return s_playerTeamNumber; }
	// プレイヤーチーム番号を設定する
	static void SetPlayerTeamNumber(int teamNumber) { s_playerTeamNumber = teamNumber; }
	// エネミーチーム番号を取得する
	static int GetEnemyTeamNumber() { return s_enemyTeamNumber; }
	// エネミーチーム番号を設定する
	static void SetEnemyTeamNumber(int teamNumber) { s_enemyTeamNumber = teamNumber; }
	// 指定されたチーム番号と敵対するチーム番号を取得する
	static int GetOpposingTeamNumber(int teamNumber) { return (teamNumber == s_playerTeamNumber) ? s_enemyTeamNumber : s_playerTeamNumber; }
	// チーム番号からノードリストを取得する
	static const std::vector<int>& GetNodeListForTeam(int teamNumber);
	// ノード番号からチーム番号を取得する
	static int GetTeamNumberForNodeNumber(int nodeNumber);
	// ノード番号から砲塔参照リストのノードを取得する
	static IComponent* GetNodeFromTurretReferenceList(int nodeNumber);
	// プレイヤーチーム中心位置を取得する
	static DirectX::SimpleMath::Vector3& GetPlayerTeamCenterPosition();
	// 敵チーム中心位置を取得する
	static DirectX::SimpleMath::Vector3& GetEnemyTeamCenterPosition();
	// プレイヤーと敵をスイッチしたかどうかを取得する
	static bool GetOpponentSwitch() { return s_opponentSwitch; }

public:
	// 参照リストにノードを追加する
	static void AddNodeToReferenceList(int nodeNumber, IComponent* node);
	// プレイヤーチームを変更する
	static void ChangePlayerTeam();
	// 砲塔参照リストからノードを削除する
	static void DeleteNodeFromTurretReferenceList(int nodeNumber);

private:
	// プレイヤーチーム番号
	static int s_playerTeamNumber;
	// エネミーチーム番号
	static int s_enemyTeamNumber;
	// チームリスト(チーム番号とノード番号配列)
	static std::unordered_map<int, std::vector<int>> s_teamList;
	// 砲塔参照リスト
	static std::unordered_map<int, IComponent* > s_nodeReferenceList;
	// プレイヤーチーム中央位置
	static DirectX::SimpleMath::Vector3 s_playerTeamCenterPosition;
	// 敵チーム中央位置
	static DirectX::SimpleMath::Vector3 s_enemyTeamCenterPosition;
	// ミューテックス
	static std::mutex m_mutex;
	// プレイヤーと敵をスイッチしたかどうか
	static bool s_opponentSwitch;
};

#endif		// TEAM_DEFINED
