//*=======================================================*
// Collision.cpp
//*=======================================================*
#include "pch.h"
#include "WorkTool/Collision.h"

#include "Game/Player/Player.h"
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "Game/Interface/ICollisionObject.h"

std::unique_ptr<Collision> Collision::m_collision = nullptr;

Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		m_collision.reset(new Collision());
	}
	return m_collision.get();
}

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Collision::Collision()
{

}

// XV‚·‚é
void Collision::Update()
{

}

// I—¹ˆ—
void Collision::Finalize()
{

}

// ƒvƒŒƒCƒ„[‚©‚ç“G‚Ö‚ÌUŒ‚”»’è
void Collision::CheckHitPlayerToEnemy(ICollisionObject* enemy)
{
    // ƒvƒŒƒCƒ„[‚ªUŒ‚
    if (m_player->IsAttack())
    {
        // UŒ‚”ÍˆÍ“à‚É‚¢‚é‚È‚çƒ_ƒ[ƒW‚ðŽó‚¯‚é
        if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
        {
			enemy->Damage(0.5f);
        }
    }
}

// Šâƒ{ƒX‚Æ‚Ì“–‚½‚è”»’è
//void Collision::CheckHitRockBoss(RockBoss* rockboss)
//{
//    // ƒvƒŒƒCƒ„[‚ªUŒ‚
//    if (m_player->GetIsAttack())
//    {
//        // UŒ‚”ÍˆÍ“à‚É‚¢‚é‚È‚çƒ_ƒ[ƒW‚ðŽó‚¯‚é
//        if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(rockboss->GetBoundingSphere()))
//        {
//            rockboss->SetHP(rockboss->GetHP() - 0.5f);
//        }
//    }
//}

//---------------------------------------------------------
// ƒvƒŒƒCƒ„[‚Æ“G‚Ì‰Ÿ‚µ–ß‚µ”»’è
//---------------------------------------------------------
void Collision::CheckPushBack(ICollisionObject* object)
{
	DirectX::BoundingSphere m_boundingSphereA = m_player->GetBoundingSphere();
	DirectX::BoundingSphere m_boundingSphereB = object->GetBoundingSphere();

	// ‹…“¯Žm‚ÌÕ“Ë”»’è‚ð‚Æ‚é
	bool m_isHit = m_boundingSphereA.Intersects(m_boundingSphereB);

	// ƒqƒbƒg‚µ‚Ä‚¢‚È‚¯‚ê‚ÎI‚í‚è
	if (!m_isHit) 
	{ 
		return;
	}


	// Õ“ËŽžA‚a‚ª‚`‚ð‰Ÿ‚µ–ß‚·ˆ—========================

	// A‚Ì’†S‚ÆB‚Ì’†S‚ðSimpleMath::Vector3Œ^‚É•ÏŠ·
	DirectX::SimpleMath::Vector3 centerA = DirectX::SimpleMath::Vector3(
		m_boundingSphereA.Center.x,
		m_boundingSphereA.Center.y,
		m_boundingSphereA.Center.z
	);

	DirectX::SimpleMath::Vector3 centerB = DirectX::SimpleMath::Vector3(
		m_boundingSphereB.Center.x,
		m_boundingSphereB.Center.y,
		m_boundingSphereB.Center.z
	);

	// // ‚`‚Ì’†S‚Æ‚a‚Ì’†S‚Æ‚Ì·•ªƒxƒNƒgƒ‹i‚a‚©‚ç‚`‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹jc‡@
	DirectX::SimpleMath::Vector3 diffVec = centerA - centerB;

	// ‚`‚Ì’†S‚Æ‚a‚Ì’†S‚Æ‚Ì‹——£i‡@‚Ì’·‚³jc‡A
	float diffLength = diffVec.Length();
	// ‚`‚Ì”¼Œa‚Æ‚a‚Ì”¼Œa‚Ì‡Œvc‡B
	float sumRadius = m_boundingSphereA.Radius + m_boundingSphereB.Radius;
	// i‚`‚ª‚a‚Éj‚ß‚èž‚ñ‚¾‹——£i‡B|‡Ajc‡C
	diffLength = sumRadius - diffLength;

	// ‡@‚ð³‹K‰»‚·‚éc‡D
	diffVec.Normalize();
	// ‰Ÿ‚µ–ß‚·ƒxƒNƒgƒ‹‚ðŒvŽZ‚·‚éi‡D‚Æ‡C‚Å•\Œ»‚·‚éjc‡E
	diffVec *= diffLength;

	// ‡E‚ðŽg—p‚µ‚ÄA‚`‚ÌÀ•W‚Æ‚`‚ÌƒRƒ‰ƒCƒ_[À•W‚ðXV‚·‚éiŽÀÛ‚É‰Ÿ‚µ–ß‚·j
	m_player->SetPosition(m_player->GetPosition() += diffVec);
	m_boundingSphereA.Center = m_boundingSphereA.Center + diffVec;
}



