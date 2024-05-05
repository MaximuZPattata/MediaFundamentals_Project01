#pragma once

// This struct was created to calculate and manage playback position shown in the console(terminal). 
// On the console when an audio is played there is a vertical bar that moves from left to right that  reflects the position of the audio playing.
struct sPlaybackPosition
{
	int bar_wait_time = 0; // Amount of time the bar needs to wait before moving
	int left_spaces = 0; // Amount of spaces on the left side of the bar
	int total_spaces = 50; // Total number of spaces for the playback meter
	int right_spaces = total_spaces; // Amount of spaces on the right side of the bar
	int milliseconds_taken = 0; // Number of milliseconds the audio has been played
	int seconds_taken = 0; // Number of seconds the audio has been played
	int minutes_taken = 0; // Number of minutes the audio has been played

	unsigned int position = 0; // Playback position of the current audio being played. Value is passed from AudioManager(value in milliseconds). 
	bool playbackpos_flag = false; // Flag to keep the position in check. To avoid repeating the same position(Sometimes the position values returned by AudioManager is consecutively repetitive). 
	unsigned int audio_length = 0; // Total length of the audio being played. 

	void InitializePlaybackVariables(sPlaybackPosition* playbackObj);
	void CalculatePlaybackPos(sPlaybackPosition* playbackObj);
	void PrintPlaybackPos(sPlaybackPosition* playbackObj);
};

// This struct was created to control the user interface(console) and how it should look
struct sUserInterface
{
	int volume; // Value of volume to be reflected in the console(value is reflected as a percentage)
	int pitch; // Value of pitch to be reflected in the console(value is reflected as a percentage)
	int pan; // Value of pan to be reflected in the console(value is reflected as a percentage)
	int audio_id = 0; // Id of the audios loaded

	bool autoplay = false; // To check if autoplay is turned on
	bool playback_position_printed = false; // To check if the playback position is printed on the console
	bool error_response_displayed = false; // To check if the error response message is printed on the console

	const char* play_status; // To indicate the type of status of the current audio - PLAYING/PAUSED/STOPPED
	const char* loop_status; // To indicate if the loop is on - ON/OFF
	const char* autoplay_status = "OFF"; // To indicate if the autoplay is on - ON/OFF
	const char* audio_name; // Holds the value of the audio name
	const char* audio_path; // Holds the value of the audio path
	const char* audio_type; // Holds the value of the audio type

	void InitializeUserInterfaceVariables(sUserInterface* userInterface);
	void PrintInfo(const char* type, sUserInterface* userInterface);
	void ErasePreviousLines(int lineEraseCount);
	void CheckForPreviousLines(sUserInterface* userInterface);
	void PrintAudioDetails(sUserInterface* userInterface);
};

