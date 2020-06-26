# Speech-Based-Playlist-Player
My own speech processing project using CPP Desktop application.
Its not optimised for performance and uses Hidden Markov Model for all the process.


SPEECH RECOGNITION: FINAL PROJECT: MTECH 2015



Names: Partha Pritam Mahanta

Project: Speech based Playlist

Visual Studio version: 2013

Key Features:-

1. GUI based
2. Multi-User
3. On the fly recording and training option
4. Options from 8 languages(We have done for only 5 users).
5. Auto-Play of Songs
6. Scalable to speech based JukeBox with multiple songs

Pre-requisites:-

-> User needs to create following folders:-
	1. Common
	2. Songs
	3. Input
	4. Output
	5. Config

->Common folder needs to be created in E drive of the system.

->Copy the contents of the folder Common into that folder. 

->The config  folder contains the configuration files.

->Input folder will contain the txt files of the audio which have been recorded automatically using the application.

->Input_wav is created to save .wav files for future use .

-> Songs folder needs to be created in E drive.


->Copy the contents of the songs folder in the newly created songs folder in E drive.


->Testing folder contains the visual studio solution for tesing.exe file. After building the testing.exe copy the exe file to the common folder.


->Training folder contains the visual studio solution for training.exe file. After building the training.exe copy the exe file to the common folder.


->SpeechClient folder contains the solution for the frontend part. We need to start the frontend part after assembling the folders and pre-requisites. 


Steps to execute your code:

->Open the project folder and open the visual studio project file.

->Run the SpeechPlaylist.exe file.

->Select 1 out of the 4 buttons available on the screen

->The GUI is self-explanatory as it will prompt the user with further steps.

->Testing: Automatically detects the audio which is recorded within the 2 second period.

->Training: - Add the audio for training by selecting the word which you want to record. Then restart the application.

->Then press the train button. And please wait while the training is complete.


->then again restart the application and we are good to go for the new user.



Troubleshooting:-

1.	Fault variable error in recording module: - No audio recording device in the system. Please enable the recording device.


2.	Any of the EXE file missing: - Copy the respective exe files to the common folder.


3.	Any of the file missing error or address error: - The respective folder must not be present in the common folder. (To avoid this error please copy the common folder directly to the E drive.)

4.	Song file missing: - Copy the songs folder with the songs content in the E drive.

5.	File not available error in the input folder:- Please check the values in the input folder if that file name is available and also check the counter.txt file in the config folder if the values for respective words is not correct.


