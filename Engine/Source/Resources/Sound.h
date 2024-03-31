#pragma once

#include <memory>
#include <string>
#include <vector>

// Forward declarations
namespace SoLoud
{
    class Wav;
}

namespace TGL
{
    class Sound
    {
    private:
        friend class ResourceManager;
        friend class AudioPlayer;

    private:
        std::string m_FilePath;
        SoLoud::Wav* m_SoloudSound = nullptr;

    private:
        std::pmr::vector<AudioPlayer*> m_CurrentPlayers;

    public:
        Sound(std::string filePath);
        ~Sound();

    public:
        static std::shared_ptr<Sound> Load(const std::string& filePath);

    public:
        float GetVolume() const;
        void SetVolume(float volume);

    private:
        void Init();
        void Free();

    private:
        void AddPlayer(AudioPlayer* player);
        void RemovePlayer(AudioPlayer* player);
    };
}
