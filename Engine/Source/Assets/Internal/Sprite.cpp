#include "Sprite.h"

#include "Core/Services/Backends/RenderBackend.h"

using namespace TGL;

void Sprite::Unbind(const u8 slot)
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.UnbindTexture(slot);
}
