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
	CommonResources* m_commonResources;                    // ���ʃ��\�[�X

	std::unique_ptr<Collision> m_collision;                // �����蔻��
private:
	std::unique_ptr<Body> m_body;               // �v���C���[�̓���
private:


public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
