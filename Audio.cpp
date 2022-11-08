/*
    Audio.cpp
    Joe O'Regan
    02/11/2022
*/
#include "Audio.hpp"
#include <iostream>
#include <string>

std::string songs[5] = {"song_1", "song_2", "song_3", "song_4", "song_5"};

Audio *Audio::s_pInstance = 0;

void Audio::init()
{
    m_musicVolume = 1.0f;
    m_fxVolume = 1.0f;
    m_masterVolume = 1.0f;

    for (int i = 0; i < 5; i++)
    {
        std::string src = "resources/music/" + songs[i] + ".mp3";
        Music song = LoadMusicStream(src.c_str());
        listOfMusic.push_back(song);
    }

    m_pauseMusic = false; // music starts unpaused

    m_currentSong = rand() % NUMBER_OF_SONGS;
    // std::cout << "current song index: " << currentSong << std::endl;

    PlayMusicStream(listOfMusic[m_currentSong]);
}

void Audio::update()
{
    UpdateMusicStream(listOfMusic[m_currentSong]);
}

void Audio::handleEvents()
{
    // Restart music playing (stop and play)
    if (IsKeyPressed(KEY_M))
    {
        StopMusicStream(listOfMusic[m_currentSong]);
        PlayMusicStream(listOfMusic[m_currentSong]);
    }
    if (IsKeyPressed(KEY_P))
    {
        m_pauseMusic = !m_pauseMusic;

        if (m_pauseMusic)
            PauseMusicStream(listOfMusic[m_currentSong]);
        else
            ResumeMusicStream(listOfMusic[m_currentSong]);
    }

    if (IsKeyPressed(KEY_COMMA))
    {
        skipTrackBackward();
    }
    else if (IsKeyPressed(KEY_PERIOD))
    {
        skipTrackForward();
    }
}

void Audio::close()
{
    for (unsigned int i = 0; i < listOfMusic.size(); i++)
    {
        UnloadMusicStream(listOfMusic[i]); // unload each music stream buffers from RAM
    }

    // CloseAudioDevice(); // close the audio device
}

int Audio::skipTrackForward()
{
    m_currentSong++;                         // select next song index
    if (m_currentSong >= listOfMusic.size()) // if the song index is greater than the amount of songs
    {
        m_currentSong = 0; // go to start of song list
    }

    PlayMusicStream(listOfMusic[m_currentSong]);       // play the song
    SeekMusicStream(listOfMusic[m_currentSong], 0.0f); // start at the beginning

    return m_currentSong;
}

int Audio::skipTrackBackward()
{
    m_currentSong--; // select the previous song in the list
    if (m_currentSong < 0 || m_currentSong >= listOfMusic.size())
    {
        m_currentSong = listOfMusic.size() - 1; // go to end of song list
    }

    PlayMusicStream(listOfMusic[m_currentSong]);       // play the song
    SeekMusicStream(listOfMusic[m_currentSong], 0.0f); // start at the beginning

    return m_currentSong;
}

float Audio::timePlayed()
{
    m_timePlayed = GetMusicTimePlayed(listOfMusic[m_currentSong]) / GetMusicTimeLength(listOfMusic[m_currentSong]);
    if (m_timePlayed > 1.0f)
        m_timePlayed = 1.0f; // Time shouldn't be longer than music length

    // std::cout << "time played: " << m_timePlayed << std::endl;
    return m_timePlayed;
}

const char *Audio::currentTrackName()
{
    return songs[m_currentSong].c_str();
}

void Audio::setMusicVolume(float amount)
{
    if (isVolumeChanging(m_musicVolume, amount))
    {
        float newVolume = adjustedVolume(m_musicVolume, amount);
        for (Music song : listOfMusic)
        {
            SetMusicVolume(song, newVolume);
        }
    }
}

void Audio::setFXVolume(float amount)
{
    if (isVolumeChanging(m_fxVolume, amount))
    {
        float newVolume = adjustedVolume(m_fxVolume, amount);
        for (Sound fx : listOfFX)
        {
            SetSoundVolume(fx, newVolume);
        }
    }
}

void Audio::setMasterVolume(float amount)
{
    if (isVolumeChanging(m_masterVolume, amount))
    {
        SetMasterVolume(adjustedVolume(m_masterVolume, amount));
    }
}

bool Audio::isVolumeChanging(float &volume, float amount)
{
    std::cout << "checking volume change" << std::endl;

    if (amount > 0.0f && volume == 1.0f)      // no need to increase volume if it's already 1
        return false;                         // volume stays max or 1.0
    else if (amount < 0.0f && volume == 0.0f) // no need to lower volume if it's already 0
        return false;                         // volume stays min value or 0.0

    std::cout << "volume: " << volume << " amount: " << amount << std::endl;

    return true; // otherwise change the value
}

float Audio::adjustedVolume(float &volume, float amount)
{
    volume += amount; // change volume

    if (volume > 1.0f)
    {
        volume = 1.0f; // volume can't be more than 1
    }
    if (volume < 0.0f)
    {
        volume = 0.0f; // volume can't be less than 0
    }

    return volume;
}
