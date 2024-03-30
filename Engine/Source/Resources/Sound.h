#pragma once
#include <memory>
#include <string>

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
    };
}
