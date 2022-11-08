#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "raylib.h" // for raylib stuff
#include <vector>   // for vector lists
#include <iostream> // for null

#define NUMBER_OF_SONGS 5; // total number of songs

const float VOLUME_DOWN = -0.1f;
const float VOLUME_UP = 0.1f;

class Audio
{
public:
    ~Audio() {}

    static Audio *Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new Audio();
            return s_pInstance;
        }
        return s_pInstance;
    }

    void init();
    void update();
    void handleEvents();
    void close();

    int skipTrackForward();  // skip song forwards - returns current song index
    int skipTrackBackward(); // skip song backwards - returns current song index

    float timePlayed();

    std::vector<Music> listOfMusic;
    std::vector<Sound> listOfFX;

    const char *currentTrackName();

    float getMusicVolume() { return m_musicVolume; }
    float getFXVolume() { return m_fxVolume; }
    float getMasterVolume() { return m_masterVolume; }

    void setMusicVolume(float amount);
    void setFXVolume(float amount);
    void setMasterVolume(float amount);

private:
    Audio() {}
    static Audio *s_pInstance;

    Music m_song1;
    Music m_song2;
    Music m_song3;
    Music m_song4;
    Music m_song5;

    unsigned int m_currentSong;
    bool m_pauseMusic;

    float m_musicVolume;
    float m_fxVolume;
    float m_masterVolume;

    float m_timePlayed;

    bool isVolumeChanging(float &volume, float amount);
    float adjustedVolume(float &volume, float amount);
};

#endif