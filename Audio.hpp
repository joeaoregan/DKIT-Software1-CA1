#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "raylib.h" // for raylib stuff
#include <vector>   // for vector lists
#include <iostream> // for null

#define NUMBER_OF_SONGS 5; // total number of songs

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

    std::vector<Music> listOfMusic;

private:
    Audio() {}
    static Audio *s_pInstance;

    // Music m_song1, m_song2, m_song3, m_song4, m_song5;

    Music m_song1;
    Music m_song2;
    Music m_song3;
    Music m_song4;
    Music m_song5;

    unsigned int m_currentSong;
    bool m_pauseMusic;
};

#endif