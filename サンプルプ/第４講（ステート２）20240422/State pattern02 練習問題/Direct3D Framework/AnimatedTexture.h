//--------------------------------------------------------------------------------------
// File: AnimatedTexture.h
//
// C++ version of the C# example on how to animate a 2D sprite using SpriteBatch
// http://msdn.microsoft.com/en-us/library/bb203866.aspx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
// 2019/05/20 Modified by Shozo Tanaka

#pragma once

#include <stdexcept>
#include <SpriteBatch.h>
// Modified by Shozo Tanaka
#include "Direction.h"

class AnimatedTexture
{
public:
	AnimatedTexture() :
		m_paused(false),
		m_frame(0),
		m_frameCount(0),
		m_textureWidth(0),
		m_textureHeight(0),
		m_timePerFrame(0.0f),
		m_totalElapsed(0.0f),
		m_rotation(0.0f),
		m_scale(1.0f, 1.0f),
		m_depth(0.0f),
		m_origin(0.0f, 0.0f)
	{
	}

	AnimatedTexture(const DirectX::XMFLOAT2& origin, float rotation, float scale, float depth) 
		:
		m_paused(false),
		m_frame(0),
		m_frameCount(0),
		m_textureWidth(0),
		m_textureHeight(0),
		m_timePerFrame(0.0f),
		m_totalElapsed(0.0f),
		m_rotation(rotation),
		m_scale(scale, scale),
		m_depth(depth),
		m_origin(origin)
	{
	}

	void Load(ID3D11ShaderResourceView* texture, int frameCount, int framesPerSecond)
	{
		if (frameCount < 0 || framesPerSecond <= 0)
			throw std::invalid_argument("AnimatedTexture");

		m_paused = false;
		m_frame = 0;
		m_frameCount = frameCount;
		m_timePerFrame = 1.0f / float(framesPerSecond);
		m_totalElapsed = 0.0f;
		m_texture = texture;

		if (texture)
		{
			Microsoft::WRL::ComPtr<ID3D11Resource> resource;
			texture->GetResource(resource.GetAddressOf());

			D3D11_RESOURCE_DIMENSION dim;
			resource->GetType(&dim);

			if (dim != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
				throw std::exception("AnimatedTexture expects a Texture2D");

			Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
			resource.As(&texture2D);

			D3D11_TEXTURE2D_DESC desc;
			texture2D->GetDesc(&desc);

			m_textureWidth = int(desc.Width);
			m_textureHeight = int(desc.Height);
		}
	}

	void Update(float elapsed)
	{
		if (m_paused)
			return;

		m_totalElapsed += elapsed;

		if (m_totalElapsed > m_timePerFrame)
		{
			++m_frame;
			m_frame = m_frame % m_frameCount;
			m_totalElapsed -= m_timePerFrame;
		}
	}
	// Modified by Shozo Tanaka
	void Draw(DirectX::SpriteBatch* batch, const DirectX::XMFLOAT2& screenPos, Direction direction) 
	{
		// Modified by Shozo Tanaka
		Draw(batch, m_frame, screenPos, direction);
	}

	// Modified by Shozo Tanaka
	void Draw(DirectX::SpriteBatch* batch, int frame, const DirectX::XMFLOAT2& screenPos, Direction direction)
	{
		int frameWidth = m_textureWidth / m_frameCount;

		RECT sourceRect;
		sourceRect.left = frameWidth * frame;
		sourceRect.top = 0;
		sourceRect.right = sourceRect.left + frameWidth;
		sourceRect.bottom = m_textureHeight;
		DirectX::SpriteEffects effects = DirectX::SpriteEffects::SpriteEffects_None;
		if (direction == Direction::LEFT)
		{
			effects = DirectX::SpriteEffects_FlipHorizontally;
		}
		batch->Draw(
			m_texture.Get(), 
			screenPos, 
			&sourceRect, 
			DirectX::Colors::White,
			m_rotation, 
			m_origin, 
			m_scale, 
			effects,
			m_depth);
	}

	void Reset()
	{
		m_frame = 0;
		m_totalElapsed = 0.0f;
	}

	void Stop()
	{
		m_paused = true;
		m_frame = 0;
		m_totalElapsed = 0.0f;
	}

	void Play() 
	{ 
		m_paused = false; 
	}
	void Paused() 
	{ 
		m_paused = true; 
	}

	bool IsPaused() const 
	{ 
		return m_paused; 
	}

private:
	bool m_paused;
	int  m_frame;
	int  m_frameCount;
	int  m_textureWidth;
	int  m_textureHeight;
	float m_timePerFrame;
	float m_totalElapsed;
	float m_depth;
	float m_rotation;
	DirectX::XMFLOAT2 m_origin;
	DirectX::XMFLOAT2 m_scale;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};
