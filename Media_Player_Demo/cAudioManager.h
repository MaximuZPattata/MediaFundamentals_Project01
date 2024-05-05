#pragma once
#include "pch.h"
#include "cAudioUtil.h"

#include<map>
#include<vector>

// This struct is created to integrate with FMOD::Sound and handle audio related actions
struct Audio
{
	FMOD::Sound* sound; // Instance of FMOD Sound class
};

// This struct is created to integrate with FMOD::Channel and handle channel related actions
struct Channel
{
	FMOD::Channel* fmodChannel; // Instance of FMOD Channel class
	
	float volume; // Float value to hold the volume of the channel
	float pitch; // Float value to hold the pitch of the channel
	float pan; // Float value to hold the pan of the channel
	
	bool playing; // Bool value to check if the channel is playing
	bool looping = false; // Bool value to check if the channel is looping
	bool paused = false; // Bool value to check if the channel is paused
};

// This class is created to integrate with the FMOD system and manage sounds along with it's functionalities
class cAudioManager
{
private:
	int m_NextChannelId = 0; // Integer variable to hold channel id
	bool mInitialized = false; //Bool value to check if the system is initialized

	std::map<const char*, Audio*> mAudioMap; // Map to hold audio(Sound system)
	std::vector<Channel*> mChannelList; // Vector to hold Channel list

	FMOD::System* mSystem = nullptr; // Instance of FMOD System class

public:
	cAudioManager();

	~cAudioManager();

	void Initialize();
	void Update();
	void Destroy();

	void SetChannelVolume(int id, float value);
	void SetChannelPitch(int id, float value);
	void SetChannelPan(int id, float value);
	void PauseSound(int id);
	void StopAudio(int id);
	void LoopAudio(int id);

	bool GetPauseStatus(int id);
	bool GetLoopStatus(int id);
	float GetChannelVolume(int id);
	float GetChannelPitch(int id);
	float GetChannelPan(int id);

	void LoadSoundStream(const char* source);
	void LoadSound(const char* file);
	int PlaySound(const char* SoundName);

	void InitializeChannelAttributes(int id);
	bool IsChannelPlaying(int id);
	void GetPlaybackPosition(int id, unsigned int& value);
	void GetAudioLength(const char* file, unsigned int& value);
};
