#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "raylib.h" // for raylib stuff
#include <vector>   // for vector lists
#include <iostream> // for null

#define NUMBER_OF_SONGS 5; // total number of songs

const float VOLUME_DOWN = -0.1f; // % to decrease volume
const float VOLUME_UP = 0.1f;    // % to increase volume

class Audio
{
public:
    ~Audio() {} // constructor

    static Audio *Instance() // singleton audio instance, only one instance of audio will be created and used
    {
        if (s_pInstance == 0) // if there is no instance of Audio
        {
            s_pInstance = new Audio(); // create a new instance
            return s_pInstance;        // return that instance
        }
        return s_pInstance; // otherwise return the already created instance
    }

    void init();         // initialise audio, load files etc.
    void update();       // update audio streams
    void handleEvents(); // handle user input
    void close();        // unload files when done

    int skipTrackForward();  // skip song forwards - returns current song index
    int skipTrackBackward(); // skip song backwards - returns current song index

    float timePlayed(); // percentage of song that has been played

    std::vector<Music> listOfMusic; // list of songs
    std::vector<Sound> listOfFX;    // list of fx

    const char *currentTrackName(); // song currently playing

    float getMusicVolume() { return m_musicVolume; }   // the current music volume %
    float getFXVolume() { return m_fxVolume; }         // current fx volume %
    float getMasterVolume() { return m_masterVolume; } // master volume %

    void setMusicVolume(float amount);  // set music volume
    void setFXVolume(float amount);     // set fx volume
    void setMasterVolume(float amount); // set master volume

private:
    Audio() {}                 // private constructor for singleton
    static Audio *s_pInstance; // audio instance, single Audio instance used in game

    Music m_song1, m_song2, m_song3, m_song4, m_song5; // songs

    unsigned int m_currentSong; // current song index
    bool m_pauseMusic;          // pause music flag

    float m_musicVolume;  // % volume for music
    float m_fxVolume;     // % volume for fx
    float m_masterVolume; // % volume for master audio

    float m_timePlayed; // % time played

    bool isVolumeChanging(float &volume, float amount); // check will the volume change
    float adjustedVolume(float &volume, float amount);  // adjust the volume, return it's value
};

#endif