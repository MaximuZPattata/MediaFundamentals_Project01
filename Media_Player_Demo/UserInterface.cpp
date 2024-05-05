#include "pch.h"
#include "UserInterface.h"
#include "cMediaPlayer.h"

// Function to initialize the sPlaybackPosition's member variables with default values everytime a new audio is played
// [param_1]: sPlaybackPosition instance's pointer is passed as the parameter to access the struct's member variables
void sPlaybackPosition::InitializePlaybackVariables(sPlaybackPosition* playback_pos)
{
	playback_pos->bar_wait_time = playback_pos->audio_length / playback_pos->total_spaces;
	playback_pos->seconds_taken = 0;
	playback_pos->minutes_taken = 0;
}

// Function to calculate the playback position depending on the position value(value in milliseconds) returned from the AudioManager
// [param_1]: sPlaybackPosition instance's pointer is passed as the parameter to access the struct's member variables
void sPlaybackPosition::CalculatePlaybackPos(sPlaybackPosition* playbackObj)
{
	//Formula for playback position------------------

	if (playbackObj->left_spaces != (playbackObj->position / playbackObj->bar_wait_time) && playbackObj->playbackpos_flag == false)
	{
		playbackObj->left_spaces = (playbackObj->position / playbackObj->bar_wait_time);

		if (playbackObj->left_spaces > playbackObj->total_spaces)
			playbackObj->left_spaces = playbackObj->total_spaces;

		playbackObj->right_spaces = abs(playbackObj->total_spaces - playbackObj->left_spaces);

		//Calculating duration-----------------
		playbackObj->seconds_taken = int(playbackObj->position / 1000);

		if (playbackObj->seconds_taken >= 60)
		{
			playbackObj->minutes_taken = playbackObj->seconds_taken / 60;
			playbackObj->seconds_taken = abs(playbackObj->minutes_taken * 60 - playbackObj->seconds_taken);
		}

		playbackObj->milliseconds_taken = position % 1000;

		//Calculation ends--------------------

		playbackObj->playbackpos_flag = true;

		PrintPlaybackPos(playbackObj);
	}
	else if (playbackObj->playbackpos_flag == true && playbackObj->left_spaces != (playbackObj->position / playbackObj->bar_wait_time))
	{
		playbackObj->playbackpos_flag = false;
	}

	//Formula ends--------------------------------
}

// Function to print the playback position
// [param_1]: sPlaybackPosition instance's pointer is passed as the parameter to access the struct's member variables
void sPlaybackPosition::PrintPlaybackPos(sPlaybackPosition* playbackObj)
{
	printf("\r[ ");

	for (int i = 0; i < playbackObj->left_spaces; i++)
	{
		printf(" ");
	}

	printf("|");

	for (int i = 0; i < playbackObj->right_spaces; i++)
	{
		printf(" ");
	}

	printf(" ]  DURATION = %d : %d : %d", playbackObj->minutes_taken, playbackObj->seconds_taken, playbackObj->milliseconds_taken);
}

// Function to initialize the sUserInterface's member variables with default values everytime a new audio is played
// [param_1]: sUserInterface instance's pointer is passed as the parameter to access the struct's member variables
void sUserInterface::InitializeUserInterfaceVariables(sUserInterface* userInterface)
{
	userInterface->playback_position_printed = true;
	userInterface->error_response_displayed = false;
	userInterface->volume = 50;
	userInterface->pitch = 0;
	userInterface->pan = 50;
}

// Function to print the info on the console. Info to be printed depends on the type passed in paramter
// [param_1]: A string value is passed as parameter. Values such as "Menu" / "Error" / "Attributes" / "Status" will print the necessary info onto the console.
// [param_2]: sUserInterface instance's pointer is passed as the parameter to access the struct's member variables
void sUserInterface::PrintInfo(const char* type, sUserInterface* userInterface)
{
	if (type == "Menu")
	{
		printf("------------------------------------------------------------------------------------------");
		printf("\n\n<<MEDIA PLAYER IS READY TO USE>> \nPress any of the following keys to play and manipulate audio : \n\n 1. Press any number from '0 - 9' to play the audio \n");
		printf(" 2. Press 'P' to PAUSE and RESUME the current audio \n 3. Press 'S' to STOP the audio \n 4. Press 'L' to LOOP the same audio and press again to stop loop \n");
		printf(" 5. Press 'Z' to decrease the VOLUME of the current audio and 'X' to increase it \n 6. Press 'C' to decrease the PITCH of the current audio and 'V' to increase it \n");
		printf(" 7. Press 'B' to decrease the PAN of the current audio and 'N' to increase it \n 8. Press 'A' to turn on AUTOPLAY. Press again to turn it off.");
		// 3. Press 'S' to stop the audio \n 4. Press 'L' to loop the same audio and press again to stop loop \n ");
	}

	else if (type == "Error")
	{
		CheckForPreviousLines(userInterface);
		printf("ERROR : There is no audio playing currently. Press any number key from '0' - '9' to play an audio.");
		userInterface->error_response_displayed = true;
	}

	else if (type == "Attributes")
	{
		printf("---> VOLUME = %d%% \n", userInterface->volume);
		printf("---> PITCH  = %d%% \n", userInterface->pitch);
		printf("---> PAN    = %d%% \n\n", userInterface->pan);
	}

	else if (type == "Status")
	{
		printf("STATUS : %s  ||  LOOP : %s  ||  AUTOPLAY : %s\n\n", userInterface->play_status, userInterface->loop_status, userInterface->autoplay_status);
	}

}

// Function to print audio details onto the console. Details such as audio name, audio source, audio type, audio attibutes - volume, picth, pan and the audio status - playing/paused/stopped/loop/autoplay.	
// [param_1]: sUserInterface instance's pointer is passed as the parameter to access the struct's member variables
void sUserInterface::PrintAudioDetails(sUserInterface* userInterface)
{
	printf("Audio Name : %s\n", userInterface->audio_name);
	printf("Audio Source : %s\n", userInterface->audio_path);
	printf("Audio Type : %s\n\n", userInterface->audio_type);

	PrintInfo("Attributes", userInterface);
	PrintInfo("Status", userInterface);
}

// Function is used to erase the previous lines on the console.
// [param_1]: Integer value is passed to indicate the number of lines to be erased
void sUserInterface::ErasePreviousLines(int lineEraseCount)
{
	for (int i = 0; i < lineEraseCount; i++)
		printf("\r\033[K\033[1A");

	printf("\r\033[K");
}

// Function is used to check if previous lines exist and erase them before starting a new audio file.
// [param_1]: sUserInterface instance's pointer is passed as the parameter to access the struct's member variables
void sUserInterface::CheckForPreviousLines(sUserInterface* userInterface)
{
	if (userInterface->playback_position_printed == false && userInterface->error_response_displayed == false)
		printf("\n\n");
	else if (userInterface->playback_position_printed == true && userInterface->error_response_displayed == false)
	{
		ErasePreviousLines(10);
		userInterface->playback_position_printed = false;
	}
	else if (userInterface->playback_position_printed == false && userInterface->error_response_displayed == true)
	{
		ErasePreviousLines(0);
		userInterface->error_response_displayed = false;
	}
}


