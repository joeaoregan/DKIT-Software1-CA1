/*
    Audio.cpp
    Joe O'Regan
    02/11/2022
*/
#include "Audio.hpp"
#include <iostream>

Audio *Audio::s_pInstance = 0;

void Audio::init()
{
    // InitAudioDevice(); // initialise the audio device

    Music m_song1 = LoadMusicStream("resources/music/song_1.mp3");
    Music m_song2 = LoadMusicStream("resources/music/song_2.mp3");
    Music m_song3 = LoadMusicStream("resources/music/song_3.mp3");
    Music m_song4 = LoadMusicStream("resources/music/song_4.mp3");
    Music m_song5 = LoadMusicStream("resources/music/song_5.mp3");

    listOfMusic.push_back(m_song1);
    listOfMusic.push_back(m_song2);
    listOfMusic.push_back(m_song3);
    listOfMusic.push_back(m_song4);
    listOfMusic.push_back(m_song5);

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
    if (IsKeyPressed(KEY_PERIOD))
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
    if (m_currentSong + 1 < listOfMusic.size())
    {
        m_currentSong++; // go to next song index
    }
    else
    {
        m_currentSong = 0; // go to start of song list
    }

    PlayMusicStream(listOfMusic[m_currentSong]);
    SeekMusicStream(listOfMusic[m_currentSong], 0.0f);

    return m_currentSong;
}

int Audio::skipTrackBackward()
{
    m_currentSong--;
    if (m_currentSong < 0 || m_currentSong >= listOfMusic.size())
    {
        m_currentSong = listOfMusic.size() - 1; // go to end of song list
    }

    PlayMusicStream(listOfMusic[m_currentSong]);
    SeekMusicStream(listOfMusic[m_currentSong], 0.0f);

    return m_currentSong;
}
