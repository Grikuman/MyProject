/*
	@file	Player.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class GeometricPrimitive;
class Collision;

class Body;

namespace NRLib
{
	class FixedCamera;
	class TPS_Camera;
};

namespace mylib
{
	class GridFloor;
};

class Player
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �v���C���[�̓���
	std::unique_ptr<Body> m_body;
private:


public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();

public:
	NRLib::TPS_Camera* GetCamera();
	DirectX::BoundingSphere GetBoundingSphere();
	bool GetIsAttack();
};
