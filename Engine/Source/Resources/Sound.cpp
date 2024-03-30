#include "Sound.h"

#include "soloud_wav.h"
#include "Core/ResourceManager.h"
#include "Exceptions/Common/FileNotFoundException.h"
#include "Util/Macros/SpawnerMacros.h"

using namespace TGL;

Sound::Sound(std::string filePath)
    : m_FilePath(std::move(filePath))
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::ResourceManager, Sound);
}

Sound::~Sound()
{
    ResourceManager::UnloadSound(this);
}

std::shared_ptr<Sound> Sound::Load(const std::string& filePath)
{
    return ResourceManager::LoadSound(filePath);
}

float Sound::GetVolume() const
{
    return m_SoloudSound->mVolume;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Sound::SetVolume(const float volume)
{
    m_SoloudSound->mVolume = volume;
}

void Sound::Init()
{
    m_SoloudSound = new SoLoud::Wav();

    const SoLoud::result result = m_SoloudSound->load(m_FilePath.c_str());
    if (result != SoLoud::SO_NO_ERROR)
    {
        delete m_SoloudSound;
        m_SoloudSound = nullptr;

        throw FileNotFoundException(m_FilePath);
    }
}

void Sound::Free()
{
    delete m_SoloudSound;
    m_SoloudSound = nullptr;
}
