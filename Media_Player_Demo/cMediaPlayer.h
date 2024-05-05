#pragma once
#include "pch.h"
#include "cAudioManager.h"
#include "cAudioLoader.h"
#include "UserInterface.h"

// This class was created to initialize and run the media player, audio loading, gathering audio data, etc. 
class cMediaPlayer
{
public:
	cMediaPlayer() = default;
	~cMediaPlayer() {}

	void InitiateMediaPlayer();
	void PrepareMediaPlayer();
	void InitializeAudioData();
	void RunMediaPlayer();
	void DestroySoundManagerObj();

private:
	void StopMediaPlayer();

	int mAudioChannel = 0; // Integer to hold the current audio channel number
	bool mMediaPlayerRunning; // To check if media player is running

	cAudioManager* mAudioManager; // Instance of cAudioManager class
	cAudioLoader* mAudioLoader; // Instance of cAudioLoader class
	sUserInterface mUserInterface; // Instance of sUserInterface struct
	sPlaybackPosition mPlaybackPosition; // Instance of sPlaybackPosition struct
};


