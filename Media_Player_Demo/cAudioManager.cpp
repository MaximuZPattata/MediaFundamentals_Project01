#include "pch.h"
#include "cAudioManager.h"
#include "cAudioUtil.h"

//Constructor
cAudioManager::cAudioManager()
{
}

//Destructor
cAudioManager::~cAudioManager()
{
}

// Function to initialize the FMOD system
void cAudioManager::Initialize()
{
	if (mInitialized)
		return;

	FMOD_RESULT result;

	result = FMOD::System_Create(&mSystem);

	if (result != FMOD_OK)
	{
		printf("Failed to create FMOD System !\n");
		return;
	}

	result = mSystem->init(1, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		printf("Failed to initialize system !");

		result = mSystem->close();

		if (result != FMOD_OK)
		{
			printf("Failed to close FMOD System !\n");
		}

		return;
	}

	printf("Audio Manager Initialized Successful !\n");

	for (int i = 0; i < 10; i++)
	{
		mChannelList.push_back(new Channel);
	}

	mInitialized = true;
}

// Function to cleanup the system(release FMOD::SOUND instance/close and release FMOD::System instance)
void cAudioManager::Destroy()
{
	if (!mInitialized)
		return;

	FMOD_RESULT result;

	for (std::pair<const char*, Audio*>pair : mAudioMap)
	{
		result = pair.second->sound->release();
		FMODCheckError(result);
	}

	mAudioMap.clear();

	result = mSystem->close();
	FMODCheckError(result);

	result = mSystem->release();
	FMODCheckError(result);

	mInitialized = false;
}

// Function to load sound stream (loads audio resource data when needed)
void cAudioManager::LoadSoundStream(const char* file)
{
	if (!mInitialized)
		return;

	if (mAudioMap.find(file) != mAudioMap.end())
	{
		printf("AudioManager::LoadAudio() Audio already loaded!\n");
		return;
	}

	mAudioMap.insert(std::pair<const char*, Audio*>(file, new Audio()));

	FMOD_RESULT result;
	result = mSystem->createStream(file, FMOD_DEFAULT, 0, &mAudioMap[file]->sound);
	if (result != FMOD_OK)
	{
		printf("Failed to load the sound file !");
	}

	printf("Audio : [%s] : Loaded successfully as stream !\n", file);
}

// Function to load sound stream (loads audio directly into memory)
void cAudioManager::LoadSound(const char* file)
{
	if (!mInitialized)
		return;

	if (mAudioMap.find(file) != mAudioMap.end())
	{
		printf("AudioManager::LoadAudio() Audio already loaded!\n");
		return;
	}

	mAudioMap.insert(std::pair<const char*, Audio*>(file, new Audio()));

	FMOD_RESULT result;
	result = mSystem->createSound(file, FMOD_DEFAULT, 0, &mAudioMap[file]->sound);
	if (result != FMOD_OK)
	{
		printf("Failed to load the sound file !");
	}

	printf("Audio : [%s] : Loaded successfully into memory !\n", file);
}

// Function to initialize channel attributes
// [param_1]: Integer value is passed as parameter(channel id)
void cAudioManager::InitializeChannelAttributes(int id)
{
	mChannelList[id]->looping = false;
	mChannelList[id]->paused = false;
	mChannelList[id]->pitch = 1.f;
	mChannelList[id]->volume = 1.f;
	mChannelList[id]->pan = 0;
}

// Function to play the sound from path
// [param_1]: String value is passed as parameter(name/path of the audio to be played)
// [return_value]: The function returns an integer value(creates the channel id and returns it) 
int cAudioManager::PlaySound(const char* SoundName)
{
	if (!mInitialized)
	{
		printf("Not Initialized !\n");
		return m_NextChannelId;
	}

	std::map<const char*, Audio*>::iterator it = mAudioMap.find(SoundName);
	if (it == mAudioMap.end())
	{
		printf("Audio not found !\n");
		return m_NextChannelId;
	}

	FMOD_RESULT result;

	int channelId = m_NextChannelId;
	m_NextChannelId = (m_NextChannelId + 1) % 1;
	Channel* channel = mChannelList[channelId];

	InitializeChannelAttributes(channelId);

	result = mSystem->playSound(it->second->sound, 0, false, &channel->fmodChannel);
	FMODCheckError(result);

	return channelId;
}

// Function to check if the channel is still playing
// [param_1]: Integer value is passed as parameter(channel id)
// [return_value]: The function returns a bool value(true/false) 
bool cAudioManager::IsChannelPlaying(int id)
{
	bool isPLaying;

	mChannelList[id]->fmodChannel->isPlaying(&isPLaying);

	return isPLaying;
}

// Function to update the system. If any error indicated then the FMOD::System instance is released
void cAudioManager::Update()
{
	if (!mInitialized)
		return;

	FMOD_RESULT result;
	result = mSystem->update();

	if (result != FMOD_OK)
	{
		FMODCheckError(result);
		Destroy();
	}
}

// Function to pause and resume the channel audio
// [param_1]: Integer value is passed as parameter(channel id)
void cAudioManager::PauseSound(int id)
{
	FMOD_RESULT result;

	if (!mChannelList[id]->paused)
		mChannelList[id]->paused = true;
	else
		mChannelList[id]->paused = false;

	result = mChannelList[id]->fmodChannel->setPaused(mChannelList[id]->paused);
	FMODCheckError(result);
}

// Function to stop the channel audio
// [param_1]: Integer value is passed as parameter(channel id)
void cAudioManager::StopAudio(int id)
{
	FMOD_RESULT result;

	result = mChannelList[id]->fmodChannel->stop();
	FMODCheckError(result);
}

// Function to loop and unloop the channel audio
// [param_1]: Integer value is passed as parameter(channel id)
void cAudioManager::LoopAudio(int id)
{
	FMOD_RESULT result;

	if (mChannelList[id]->looping == false)
	{
		result = mChannelList[id]->fmodChannel->setMode(FMOD_LOOP_NORMAL);
		result = mChannelList[id]->fmodChannel->setLoopCount(-1);
		mChannelList[id]->looping = true;
	}
	else
	{
		result = mChannelList[id]->fmodChannel->setMode(FMOD_DEFAULT);
		result = mChannelList[id]->fmodChannel->setLoopCount(0);
		mChannelList[id]->looping = false;
	}
	FMODCheckError(result);
}

// Function to set the channel volume
// [param_1]: Integer value is passed as parameter(channel id)
// [param_2]: Float value is passed as parameter(value of volume to be changed in float)
void cAudioManager::SetChannelVolume(int id, float value)
{
	FMOD_RESULT result;
	mChannelList[id]->volume += value;

	if (mChannelList[id]->volume < 0)
	{
		mChannelList[id]->volume = 0;
	}
	result = mChannelList[id]->fmodChannel->setVolume(mChannelList[id]->volume);
	FMODCheckError(result);
}

// Function to set the channel pitch
// [param_1]: Integer value is passed as parameter(channel id)
// [param_2]: Float value is passed as parameter(value of pitch to be changed in float)
void cAudioManager::SetChannelPitch(int id, float value)
{
	FMOD_RESULT result;
	mChannelList[id]->pitch += value;

	if (mChannelList[id]->pitch < 0.2f)
	{
		mChannelList[id]->pitch = 0.2f;
	}

	result = mChannelList[id]->fmodChannel->setPitch(mChannelList[id]->pitch);
	FMODCheckError(result);
}

// Function to set the channel pan
// [param_1]: Integer value is passed as parameter(channel id)
// [param_2]: Float value is passed as parameter(value of pan to be changed in float)
void cAudioManager::SetChannelPan(int id, float value)
{
	FMOD_RESULT result;
	mChannelList[id]->pan += value;
	result = mChannelList[id]->fmodChannel->setPan(mChannelList[id]->pan);
	FMODCheckError(result);
}

// Function to get the channel volume
// [param_1]: Integer value is passed as parameter(channel id)
// [return_value]: The function returns a float value(channel volume is returned in float)
float cAudioManager::GetChannelVolume(int id)
{
	return mChannelList[id]->volume;
}

// Function to get the channel pitch
// [param_1]: Integer value is passed as parameter(channel id)
// [return_value]: The function returns a float value(channel pitch is returned in float)
float cAudioManager::GetChannelPitch(int id)
{
	return mChannelList[id]->pitch;
}

// Function to get the channel pan
// [param_1]: Integer value is passed as parameter(channel id)
// [return_value]: The function returns a float value(channel pan is returned in float)
float cAudioManager::GetChannelPan(int id)
{
	return mChannelList[id]->pan;
}

// Function to get the channel pause status
// [param_1]: Integer value is passed as parameter(channel id)
// [return_value]: The function returns a bool value(if channel is paused or not)
bool cAudioManager::GetPauseStatus(int id)
{
	return mChannelList[id]->paused;
}

// Function to get the channel loop status
// [param_1]: Integer value is passed as parameter(channel id)
// [return_value]: The function returns a bool value(if channel is looped or not)
bool  cAudioManager::GetLoopStatus(int id)
{
	return mChannelList[id]->looping;
}

// Function to get the channel audio's playback position
// [param_1]: Integer value is passed as parameter(channel id)
// [param_2]: Pointer of unsigned integer value is passed 
void cAudioManager::GetPlaybackPosition(int id, unsigned int& value)
{
	FMOD_RESULT result = mChannelList[id]->fmodChannel->getPosition(&value, FMOD_TIMEUNIT_MS);
	FMODCheckError(result);
}

// Function to get the audio length
// [param_1]: String value is passed as parameter(audio path)
// [param_2]: Pointer of unsigned integer value is passed 
void cAudioManager::GetAudioLength(const char* file, unsigned int& value)
{
	FMOD_RESULT result = mAudioMap[file]->sound->getLength(&value, FMOD_TIMEUNIT_MS);
	FMODCheckError(result);
}


