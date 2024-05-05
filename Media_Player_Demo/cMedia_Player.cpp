#include "pch.h"
#include "cMediaPlayer.h"
#include "UserInterface.h"

// Function to initiate the media player(call other necessary functions for initiation)
void cMediaPlayer::InitiateMediaPlayer()
{
	PrepareMediaPlayer();
	RunMediaPlayer();
	DestroySoundManagerObj();
}

// Function to initialize user interface member variables and call other initialize() functions
void cMediaPlayer::InitializeAudioData()
{
	mUserInterface.CheckForPreviousLines(&mUserInterface);//Function call to check if current/previous lines on the console needs to be erased

	mUserInterface.play_status = "PLAYING";
	mUserInterface.loop_status = "OFF";
	mUserInterface.audio_name = mAudioLoader->GetAudioName(mUserInterface.audio_id);
	mUserInterface.audio_path = mAudioLoader->GetAudioPath(mUserInterface.audio_id);
	mUserInterface.audio_type = mAudioLoader->GetAudioType(mUserInterface.audio_id);

	mAudioChannel = mAudioManager->PlaySound(mUserInterface.audio_path);//Function call to play the sound from the path provided as parameter

	mAudioManager->GetAudioLength(mUserInterface.audio_path, mPlaybackPosition.audio_length);//Function call to fetch audio length

	mPlaybackPosition.InitializePlaybackVariables(&mPlaybackPosition);
	mUserInterface.InitializeUserInterfaceVariables(&mUserInterface);

	mUserInterface.PrintAudioDetails(&mUserInterface);//Function call to print the collected audio details onto the user interface(console)
	mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);//Function call to print the playback position of the audio currently playing
}

// Function to initialize other modules(Audio Manager and Audio Loader) 
void cMediaPlayer::PrepareMediaPlayer()
{
	//Initializing instances for AudioManager class and AudioLoader class
	mAudioManager = new cAudioManager();
	mAudioLoader = new cAudioLoader();

	mAudioManager->Initialize();
	mAudioLoader->ReadFromFile();

	//For loop block to load the sounds from the file path retrieved using AudioLoader class 
	for (int loop_count = 0; loop_count < 10; loop_count++)
	{
		mUserInterface.audio_path = mAudioLoader->GetAudioPath(loop_count);

		if (loop_count < 5)
			mAudioManager->LoadSound(mUserInterface.audio_path);

		else
			mAudioManager->LoadSoundStream(mUserInterface.audio_path);
	}
}

// Function to run media player until 'ESC' is pressed 
void cMediaPlayer::RunMediaPlayer()
{
	//Function call to print the menu details
	mUserInterface.PrintInfo("Menu", &mUserInterface);

	mMediaPlayerRunning = true;

	while (mMediaPlayerRunning)
	{
		mAudioManager->Update();

		if (_kbhit())//Checks if any key is pressed
		{
			int key = _getch();//Fetches the key pressed
			if (key == '1')
			{
				mUserInterface.audio_id = 0;//audio_id value depending on the key pressed 
				InitializeAudioData();//Function call to gather and initialize audio data for the selected audio_id
			}
			else if (key == '2')
			{
				mUserInterface.audio_id = 1;
				InitializeAudioData();
			}
			else if (key == '3')
			{
				mUserInterface.audio_id = 2;
				InitializeAudioData();
			}
			else if (key == '4')
			{
				mUserInterface.audio_id = 3;
				InitializeAudioData();
			}
			else if (key == '5')
			{
				mUserInterface.audio_id = 4;
				InitializeAudioData();
			}
			else if (key == '6')
			{
				mUserInterface.audio_id = 5;
				InitializeAudioData();
			}
			else if (key == '7')
			{
				mUserInterface.audio_id = 6;
				InitializeAudioData();
			}
			else if (key == '8')
			{
				mUserInterface.audio_id = 7;
				InitializeAudioData();
			}
			else if (key == '9')
			{
				mUserInterface.audio_id = 8;
				InitializeAudioData();
			}
			else if (key == '0')
			{
				mUserInterface.audio_id = 9;
				InitializeAudioData();
			}
			else if (key == 80/*Indicating 'P'*/ || key == 112/*Indicating 'p'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))//Function call to check if audio is still playing
				{
					mAudioManager->PauseSound(mAudioChannel);//Function call to pause the current audio or to resume the paused audio

					if (mAudioManager->GetPauseStatus(mAudioChannel))//Function call to fetch the pause status (paused/resumed)
					{
						mUserInterface.ErasePreviousLines(2);//Function call to erase the previous lines on the console(terminal)  
						mUserInterface.play_status = "PAUSED";
						mUserInterface.PrintInfo("Status", &mUserInterface);//Function call to print the status info of the audio currently playing
					}
					else
					{
						mUserInterface.ErasePreviousLines(2);
						mUserInterface.play_status = "PLAYING";
						mUserInterface.PrintInfo("Status", &mUserInterface);
					}

					mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);

				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);//Function call to print an error message if key is pressed when no audio is played
				}
			}
			else if (key == 83/*Indicating 'S'*/ || key == 115/*Indicating 's'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					mAudioManager->StopAudio(mAudioChannel);//Function call to stop the current audio playing

					if (mUserInterface.autoplay)
					{
						mUserInterface.autoplay = false;
						mUserInterface.autoplay_status = "OFF";
					}

					//Setting all values of member variables to default
					mPlaybackPosition.playbackpos_flag = false;
					mPlaybackPosition.position = 0;

					mUserInterface.ErasePreviousLines(2);
					mUserInterface.loop_status = "OFF";
					mUserInterface.play_status = "STOPPED";
					mUserInterface.PrintInfo("Status", &mUserInterface);

					mPlaybackPosition.CalculatePlaybackPos(&mPlaybackPosition);//Function call to caculate the playback position of the audio
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}
			else if (key == 76/*Indicating 'L'*/ || key == 108/*Indicating 'l'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					mAudioManager->LoopAudio(mAudioChannel);//Function call to loop the current audio or to stop looping the audio

					if (mUserInterface.autoplay)
					{
						mUserInterface.autoplay = false;
						mUserInterface.autoplay_status = "OFF";
					}

					if (mAudioManager->GetLoopStatus(mAudioChannel))//Function call to fetch the loop status of the audio playing
					{
						mUserInterface.ErasePreviousLines(2);
						mUserInterface.loop_status = "ON";
						mUserInterface.PrintInfo("Status", &mUserInterface);
					}
					else
					{
						mUserInterface.ErasePreviousLines(2);
						mUserInterface.loop_status = "OFF";
						mUserInterface.PrintInfo("Status", &mUserInterface);
					}

					mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}
			else if (key == 65/*Indicating 'A'*/ || key == 97/*Indicating 'a'*/)
			{
				if (mUserInterface.autoplay)
				{
					mUserInterface.autoplay = false;
					mUserInterface.autoplay_status = "OFF";
					mUserInterface.ErasePreviousLines(2);
					mUserInterface.PrintInfo("Status", &mUserInterface);
				}
				else
				{
					mUserInterface.autoplay = true;
					mUserInterface.autoplay_status = "ON";

					//When Autoplay is on, the audio starts playing even if it's not playing currently or was stopped previously
					if (mUserInterface.play_status == "STOPPED" || !(mAudioManager->IsChannelPlaying(mAudioChannel)))
					{
						if (mUserInterface.audio_id > 9)
							mUserInterface.audio_id = 0;

						InitializeAudioData();
					}
					else
					{
						mUserInterface.ErasePreviousLines(2);
						mUserInterface.PrintInfo("Status", &mUserInterface);
					}

					//Turning off Loop when Autoplay is on
					if (mAudioManager->GetLoopStatus(mAudioChannel))
					{
						mAudioManager->LoopAudio(mAudioChannel);
						mUserInterface.ErasePreviousLines(2);
						mUserInterface.loop_status = "OFF";
						mUserInterface.PrintInfo("Status", &mUserInterface);
					}
				}

				mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
			}

			else if (key == 88/*Indicating 'X'*/ || key == 120/*Indicating 'x'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					if (mAudioManager->GetChannelVolume(mAudioChannel) < 2.f)//Function call to fetch current channel volume
					{
						mAudioManager->SetChannelVolume(mAudioChannel, 0.2f);//Function call to set the channel volume(increase volume by 0.2f)

						mUserInterface.volume = (mAudioManager->GetChannelVolume(mAudioChannel) * 100) / 2;
						mUserInterface.ErasePreviousLines(6);
						mUserInterface.PrintInfo("Attributes", &mUserInterface);//Function call to print the attributes info of the audio currently playing
						mUserInterface.PrintInfo("Status", &mUserInterface);
						mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
					}
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}

			else if (key == 90/*Indicating 'Z'*/ || key == 122/*Indicating 'z'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					if (mAudioManager->GetChannelVolume(mAudioChannel) > 0)
					{
						mAudioManager->SetChannelVolume(mAudioChannel, -0.2f);//Function call to set the channel volume(decrease volume by -0.2f)

						mUserInterface.volume = (mAudioManager->GetChannelVolume(mAudioChannel) * 100) / 2;
						mUserInterface.ErasePreviousLines(6);
						mUserInterface.PrintInfo("Attributes", &mUserInterface);
						mUserInterface.PrintInfo("Status", &mUserInterface);
						mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
					}
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}

			else if (key == 86/*Indicating 'V'*/ || key == 118/*Indicating 'v'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					if (mAudioManager->GetChannelPitch(mAudioChannel) < 1.8f)//Function call to fetch the current channel pitch
					{
						mAudioManager->SetChannelPitch(mAudioChannel, 0.2f);//Function call to set the current channel pitch(increase picth by 0.2f)

						mUserInterface.pitch += 25;
						mUserInterface.ErasePreviousLines(6);
						mUserInterface.PrintInfo("Attributes", &mUserInterface);
						mUserInterface.PrintInfo("Status", &mUserInterface);
						mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
					}

				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}

			else if (key == 67/*Indicating 'C'*/ || key == 99/*Indicating 'c'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					if (mAudioManager->GetChannelPitch(mAudioChannel) > 0.4f)
					{
						mAudioManager->SetChannelPitch(mAudioChannel, -0.2f);// Function call to set the channel pitch(decrease pitch by - 0.2f)

						mUserInterface.pitch -= 25;
						mUserInterface.ErasePreviousLines(6);
						mUserInterface.PrintInfo("Attributes", &mUserInterface);
						mUserInterface.PrintInfo("Status", &mUserInterface);
						mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
					}
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}

			else if (key == 78/*Indicating 'N'*/ || key == 110/*Indicating 'n'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					if (mAudioManager->GetChannelPan(mAudioChannel) < 0.9f)//Function call to fetch the current channel pan
					{
						mAudioManager->SetChannelPan(mAudioChannel, 0.2f);//Function call to set the channel pan(increase pan by 0.2f)

						mUserInterface.pan += 10;
						mUserInterface.ErasePreviousLines(6);
						mUserInterface.PrintInfo("Attributes", &mUserInterface);
						mUserInterface.PrintInfo("Status", &mUserInterface);
						mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
					}
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}

			else if (key == 66/*Indicating 'B'*/ || key == 98/*Indicating 'b'*/)
			{
				if (mAudioManager->IsChannelPlaying(mAudioChannel))
				{
					if (mAudioManager->GetChannelPan(mAudioChannel) > -0.9f)
					{
						mAudioManager->SetChannelPan(mAudioChannel, -0.2f);//Function call to set the channel pan(decrease pan by -0.2f)

						mUserInterface.pan -= 10;
						mUserInterface.ErasePreviousLines(6);
						mUserInterface.PrintInfo("Attributes", &mUserInterface);
						mUserInterface.PrintInfo("Status", &mUserInterface);
						mPlaybackPosition.PrintPlaybackPos(&mPlaybackPosition);
					}
				}
				else
				{
					mUserInterface.PrintInfo("Error", &mUserInterface);
				}
			}

			if (key == 27/*ESC*/)
			{
				StopMediaPlayer();
			}
		}
		if (mAudioManager->IsChannelPlaying(mAudioChannel))
		{
			mAudioManager->GetPlaybackPosition(mAudioChannel, mPlaybackPosition.position);

			mPlaybackPosition.CalculatePlaybackPos(&mPlaybackPosition);
		}
		else if (mUserInterface.autoplay)//Else if block logic to play the next song if autoplay is on
		{
			mUserInterface.audio_id++;

			if (mUserInterface.audio_id > 9)
				mUserInterface.audio_id = 0;

			InitializeAudioData();
		}
	}
}

// Function to destroy the Audio Manager instance
void cMediaPlayer::DestroySoundManagerObj()
{
	mAudioManager->Destroy();//Function to cleanup audio system
	delete mAudioManager;
}

// Function to stop media player from running. Sets mMediaPLayerRunning member to false.
void cMediaPlayer::StopMediaPlayer()
{
	mMediaPlayerRunning = false;
}
