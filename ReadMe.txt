-----------------------------------------------------------------------------------<<Media Player>>-------------------------------------------------------------------------------------------------------------

- The project contains a set of programs integrated with the FMOD API that helps the user to run the media player and play around with some of the functionalities. There are 10 audio files that are pre-loaded from the AudioFiles.txt, some are loaded as streamed audio files and some as sampled audio files. The user can use functionalities like play, pause, resume, stop, loop audio, autoplay next audio, increase volume, pitch and pan, decrease volume, pitch and pan. 

-The program runs on the CLI. The CLI provides the user with instructions and details on the audio currently playing. The command line doesnt scroll down when another audio is played. Instead the audio details and playback position gets overwritten.

- This project makes use of only 1 audio channel. So multiple audios cannot be played at the same time. 

-----------------------------------------------------------------------------<<How to build and use it>>---------------------------------------------------------------------------------------------------------

- Open the solution found in the path "Media_Player/Media_Player_Demo.sln". Once opened,click on "Build" to build the entire solution with the solution configuration being "Debug" and the solution platform being "x64". Once build is successful, run the program. 

- The program starts running and the command line terminal opens showing all the audio files that are loaded successfully. The instructions on how to operate the media player is also displayed on the CLI. 

- Posting the same instructions here :
	1. Press any number from '0 - 9' to play the audio
	2. Press 'P' to PAUSE and RESUME the current audio 
	3. Press 'S' to STOP the audio
	4. Press 'L' to LOOP the same audio and press again to stop loop
	5. Press 'Z' to decrease the VOLUME of the current audio and 'X' to increase it
	6. Press 'C' to decrease the PITCH of the current audio and 'V' to increase it
	7. Press 'B' to decrease the PAN of the current audio and 'N' to increase it
	8. Press 'A' to turn on AUTOPLAY. Press again to turn it off. 

- Autoplay can be turned on even when there is no audio playing or when an audio is stopped. The audio automatically starts playing when the user turns autoplay on.

- Make sure the terminal is atleast half the length of the screen so that the audio playback position is displayed without any errors. Making the window smaller actually causes the vertical bar indicating the playback position to move to the next line in the terminal which offsets the whole neat display.  

- If new audio files need to be added = Drop the new audio files in the path "Media_Player/Media_Player_Demo/Audio". Also the text file in the path "Media_Player/Media_Player_Demo/AudioFiles.txt" needs to be appended. Add the path of the new audio file dropped into the text file. The name and loading type of the audio should also be added. 


-----------------------------------------------------------------------<<Conclusion - My thoughts on the project>>-----------------------------------------------------------------------------------------------

- This is a very simple project. I wanted to add more functionality to it. But keeping it simple felt neater since the User Interface was the CLI(Command Line Interface). Expanding the project more is a tough job because of the command line terminal being used as the UI. 

- I started off with ImGui but to understand and implement the graphical part takes a while. So I had to move on with the CLI as the user interface instead. 

- I would very much like to use ImGUI to expand the project so that more functionality could be added. Functionalities like shuffle, playing multiple audio streams, selecting a particular audio among the multiple audios played and using scrolling bars to change volume, picth and pan.

- I have also used erase functionality in the program to erase the previous lines on the terminal i.e. when a new audio is starting, it actually overlaps the previous audio displayed by moving to the top line and overwriting on top of it. 

- I have made sure all errors are handled in the program. Even when the user tries to stop an audio that isn't being played will give out an error message.   


- I will make sure that the knowledge I have gained on this project will be used to implement something better in the future. 
- Enjoy playing around with the Media Player Demo :)