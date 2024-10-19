#include "FantasylandGameMode.h"

#include "Implementations/Entities/Camera.h"

using namespace TGL;

FantasylandGameMode::FantasylandGameMode()
{
    m_Camera = SpawnEntity<Camera>(true);
	m_Camera->SetHorizontalSize(15.0f);
	
	m_Player = SpawnEntity<Player>(m_AssetCollection);
}
