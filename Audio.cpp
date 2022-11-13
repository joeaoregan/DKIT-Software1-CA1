/*
    Audio.cpp
    Joe O'Regan
    02/11/2022
*/
#include "Audio.hpp" // audio header file
#include <iostream>  // using cout for debugging
#include <string>    // easier for me to work with strings

std::string songs[5] = {"song_1", "song_2", "song_3", "song_4", "song_5"}; // array of song names

Audio *Audio::s_pInstance = 0; // singleton audio instance

void Audio::init()
{
    m_musicVolume = 1.0f;  // volume - music
    m_fxVolume = 1.0f;     // volume - fx
    m_masterVolume = 1.0f; // volume - master

    for (int i = 0; i < 5; i++) // add 5 songs
    {
        std::string src = "resources/music/" + songs[i] + ".mp3"; // string to load each song -- todo - load from file
        Music song = LoadMusicStream(src.c_str());                // load each song
        listOfMusic.push_back(song);                              // add to music list
    }

    m_pauseMusic = false;                        // music starts unpaused
    m_currentSong = rand() % NUMBER_OF_SONGS;    // select random song each time
    PlayMusicStream(listOfMusic[m_currentSong]); // play the music

    // std::cout << "current song index: " << currentSong << std::endl; // debug message
}

void Audio::update()
{
    UpdateMusicStream(listOfMusic[m_currentSong]); // update the music stream
}

void Audio::handleEvents()
{
    // Restart music playing (stop and play)
    if (IsKeyPressed(KEY_M)) // M key pressed
    {
        StopMusicStream(listOfMusic[m_currentSong]); // stop music stream if playing
        PlayMusicStream(listOfMusic[m_currentSong]); // play music stream if stopped
    }
    if (IsKeyPressed(KEY_P)) // P key pressed
    {
        m_pauseMusic = !m_pauseMusic; // toggle the music paused or playing

        if (m_pauseMusic)                                 // if the pause flag is true
            PauseMusicStream(listOfMusic[m_currentSong]); // pause the music
        else
            ResumeMusicStream(listOfMusic[m_currentSong]); // otherwise play the music
    }

    if (IsKeyPressed(KEY_COMMA)) // Use comma to skip track back
    {
        skipTrackBackward(); // skip the current song backwards
    }
    else if (IsKeyPressed(KEY_PERIOD)) // use full stop to skip the song forwards
    {
        skipTrackForward(); // skip the current song forwards
    }
}

void Audio::close()
{
    for (unsigned int i = 0; i < listOfMusic.size(); i++) // for each song
    {
        UnloadMusicStream(listOfMusic[i]); // unload each music stream buffers from RAM
    }

    // CloseAudioDevice(); // close the audio device
}

/*
    skip the song forwards, or back to start of list if already at end of song list
*/
int Audio::skipTrackForward()
{
    m_currentSong++;                         // select next song index
    if (m_currentSong >= listOfMusic.size()) // if the song index is greater than the amount of songs
    {
        m_currentSong = 0; // go to start of song list
    }

    PlayMusicStream(listOfMusic[m_currentSong]);       // play the song
    SeekMusicStream(listOfMusic[m_currentSong], 0.0f); // start at the beginning
    return m_currentSong;                              // return the current song index
}

/*
    skip the song backwards, or to the end of song list if at start of song list
*/
int Audio::skipTrackBackward()
{
    m_currentSong--; // select the previous song in the list
    if (m_currentSong < 0 || m_currentSong >= listOfMusic.size())
    {
        m_currentSong = listOfMusic.size() - 1; // go to end of song list
    }

    PlayMusicStream(listOfMusic[m_currentSong]);       // play the song
    SeekMusicStream(listOfMusic[m_currentSong], 0.0f); // start at the beginning
    return m_currentSong;                              // return the current song index
}

/*
    get the percentage of the song that has been played
*/
float Audio::timePlayed()
{
    m_timePlayed = GetMusicTimePlayed(listOfMusic[m_currentSong]) / GetMusicTimeLength(listOfMusic[m_currentSong]);
    if (m_timePlayed > 1.0f) // if time played exceed 100%
        m_timePlayed = 1.0f; // Time shouldn't be longer than music length

    // std::cout << "time played: " << m_timePlayed << std::endl;
    return m_timePlayed; // return time played %
}

/*
    get name of song that is currently playing
*/
const char *Audio::currentTrackName()
{
    return songs[m_currentSong].c_str(); // get the song name from the list of song names using the current song as index
}

/*
    set music volume
    seems to be individual for each song
*/
void Audio::setMusicVolume(float amount) // set the music up or down the amount specified
{
    if (isVolumeChanging(m_musicVolume, amount)) // if the volume change flag is set
    {
        float newVolume = adjustedVolume(m_musicVolume, amount); // calculate the new volume
        for (Music song : listOfMusic)                           // for each song
        {
            SetMusicVolume(song, newVolume); // set the new volume
        }
    }
}

/*
    set fx volume
*/
void Audio::setFXVolume(float amount) // amount = % up or down
{
    if (isVolumeChanging(m_fxVolume, amount)) // if the volume is changing
    {
        float newVolume = adjustedVolume(m_fxVolume, amount); // calculate the new volume
        for (Sound fx : listOfFX)                             // for each fx
        {
            SetSoundVolume(fx, newVolume); // set the new volume
        }
    }
}

/*
    set master volume
*/
void Audio::setMasterVolume(float amount) // amount = % up or down
{
    if (isVolumeChanging(m_masterVolume, amount)) // if the volume is changing
    {
        SetMasterVolume(adjustedVolume(m_masterVolume, amount)); // set the volume
    }
}

/*
    check is the volume changes
    if it's already 100% no need to increase
    if it's already 0% no need to decrease
*/
bool Audio::isVolumeChanging(float &volume, float amount) // check will volume change -- amount can be +/- value
{
    std::cout << "checking volume change" << std::endl;

    if (amount > 0.0f && volume == 1.0f)      // no need to increase volume if it's already 1
        return false;                         // volume stays max or 1.0
    else if (amount < 0.0f && volume == 0.0f) // no need to lower volume if it's already 0
        return false;                         // volume stays min value or 0.0

    std::cout << "volume: " << volume << " amount: " << amount << std::endl;

    return true; // otherwise change the value
}

/*
    adjust the volume
    keep volume within normal limits
*/
float Audio::adjustedVolume(float &volume, float amount) // adjust volume by amount, amount can be +/- value
{
    volume += amount; // change volume

    if (volume > 1.0f) // check volume percentage isn't too high
    {
        return 1.0f; // volume can't be more than 1
    }
    if (volume < 0.0f) // check volume percentage isn't too low
    {
        return 0.0f; // volume can't be less than 0
    }

    return volume; // return the new volume
}
