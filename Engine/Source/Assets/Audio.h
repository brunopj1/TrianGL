#pragma once

#include <memory>
#include <string>
#include <vector>

// Forward declarations
namespace SoLoud
{
    class AudioSource;
}

namespace TGL
{
    class Audio final
    {
    private:
        friend class AssetManager;
        friend class AudioPlayer;

    private:
        std::string m_FilePath;
        bool m_Streamed;
        SoLoud::AudioSource* m_SoloudAudio = nullptr;

    private:
        std::pmr::vector<AudioPlayer*> m_CurrentPlayers;

    public:
        Audio(std::string filePath, bool stream);
        ~Audio();

    public:
        static std::shared_ptr<Audio> Load(const std::string& filePath, bool stream = false);

    public:
        bool IsStreamed() const;

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
