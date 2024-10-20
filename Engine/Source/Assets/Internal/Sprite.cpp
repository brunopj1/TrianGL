#include "Sprite.h"

#include "Core/Services/Backends/RenderBackend.h"

using namespace TGL;

f32 Sprite::GetAspectRatio() const
{
	const glm::uvec2& resolution = GetResolution();

	if (resolution.y == 0)
	{
		return 0.0f;
	}

	return static_cast<f32>(resolution.x) / static_cast<f32>(resolution.y);
}

glm::vec2 Sprite::CalculateIdealScale() const
{
	const f32 aspectRatio = GetAspectRatio();

	if (aspectRatio == 0.0f)
	{
		return {1.0f, 1.0f};
	}

	if (aspectRatio > 1.0f)
	{
		return {aspectRatio, 1.0f};
	}
	else /* aspectRatio < 1.0f */
	{
		return {1.0f, 1.0f / aspectRatio};
	}
}

glm::vec2 Sprite::CalculateIdealScale(const bool keepWidth) const
{
	const f32 aspectRatio = GetAspectRatio();

	if (aspectRatio == 0.0f)
	{
		return {1.0f, 1.0f};
	}

	if (keepWidth)
	{
		return {1.0f, 1.0f / aspectRatio};
	}
	else
	{
		return {aspectRatio, 1.0f};
	}
}

void Sprite::Unbind(const u8 slot)
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.UnbindTexture(slot);
}
