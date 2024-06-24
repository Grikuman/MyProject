/*
	@file		Billboard.h
	@brief		�r���{�[�h�s����擾����֐�
	@details	DirectXTK�̃r���{�[�h���A�|���S���̕\�����t�ɂȂ邽�߁A�C�������o�[�W�����B�g�p�͎��ȐӔC�Łc�B
*/
#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>

namespace mylib
{
	//---------------------------------------------------------
	// �r���{�[�h�s����擾����P
	//---------------------------------------------------------
	inline DirectX::SimpleMath::Matrix CreateBillboard(
		const DirectX::SimpleMath::Vector3& objectPosition,
		const DirectX::SimpleMath::Vector3& cameraPosition,
		const DirectX::SimpleMath::Vector3& cameraUp
	) noexcept
	{
		using namespace DirectX;
		using namespace DirectX::SimpleMath;

		const XMVECTOR O = XMLoadFloat3(&objectPosition);
		const XMVECTOR C = XMLoadFloat3(&cameraPosition);
		XMVECTOR Z = XMVectorSubtract(O, C);

		const XMVECTOR N = XMVector3LengthSq(Z);

		// �������߂��Ƃ�
		if (XMVector3Less(N, g_XMEpsilon))
		{
			Z = g_XMIdentityR2;
		}
		else
		{
			Z = XMVector3Normalize(-Z);
		}

		const XMVECTOR up = XMLoadFloat3(&cameraUp);
		XMVECTOR X = XMVector3Cross(up, Z);
		X = XMVector3Normalize(X);

		const XMVECTOR Y = XMVector3Cross(Z, X);

		XMMATRIX M;
		M.r[0] = X;
		M.r[1] = Y;
		M.r[2] = Z;
		M.r[3] = XMVectorSetW(O, 1.f);

		Matrix R;
		XMStoreFloat4x4(&R, M);
		return R;
	}

	//---------------------------------------------------------
	// �r���{�[�h�s����擾����Q
	//---------------------------------------------------------
	inline DirectX::SimpleMath::Matrix CreateConstrainedBillboard(
		const DirectX::SimpleMath::Vector3& objectPosition,
		const DirectX::SimpleMath::Vector3& cameraPosition,
		const DirectX::SimpleMath::Vector3& rotateAxis
	) noexcept
	{
		using namespace DirectX;
		using namespace DirectX::SimpleMath;

		static const XMVECTORF32 s_minAngle = { { { 0.99825467075f, 0.99825467075f, 0.99825467075f, 0.99825467075f } } }; // 1.0 - XMConvertToRadians( 0.1f );

		const XMVECTOR O = XMLoadFloat3(&objectPosition);
		const XMVECTOR C = XMLoadFloat3(&cameraPosition);
		XMVECTOR faceDir = XMVectorSubtract(O, C);

		const XMVECTOR N = XMVector3LengthSq(faceDir);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			faceDir = g_XMIdentityR2;
		}
		else
		{
			faceDir = XMVector3Normalize(-faceDir);
		}

		const XMVECTOR Y = XMLoadFloat3(&rotateAxis);
		XMVECTOR X, Z;

		XMVECTOR dot = XMVectorAbs(XMVector3Dot(Y, faceDir));
		if (XMVector3Greater(dot, s_minAngle))
		{
			{
				dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
				Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
			}

			X = XMVector3Cross(Y, Z);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}
		else
		{
			X = XMVector3Cross(Y, faceDir);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}

		XMMATRIX M;
		M.r[0] = X;
		M.r[1] = Y;
		M.r[2] = Z;
		M.r[3] = XMVectorSetW(O, 1.f);

		Matrix R;
		XMStoreFloat4x4(&R, M);
		return R;
	}
}