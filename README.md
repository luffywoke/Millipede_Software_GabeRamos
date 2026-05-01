# Millipede_Software_GabeRamos

Project Overview
-This Millipede project solves the issue of figuring out how to create a safe yet fun museum experience for all
-The key features of this project are: 
  - Button that activates the experience
  - Exterior light that indicates whether the project is in use or not
  - Interior light that illuminates the room
  - Speaker that plays narration audio
  - UV lights that are controlled
  - All controlled through Arduino

System Architecture
-The Magic Millipedes Exhibit is built around an Arduino Mega 2560 as the central controller, coordinating all inputs and outputs for each of the four independent rooms. The system is organized into five major modules: input handling, lighting control, audio playback, UV illumination, and operational robustness. Input is handled through a rugged RGB momentary push button that both triggers the presentation and visually communicates room state through its built-in LED. Lighting is managed through two WS2812B NeoPixel rings — one exterior for visitor guidance and one interior for ambiance — alongside the button's RGB LED. Audio is delivered via a DFPlayer Mini MP3 module driving an 8Ω speaker, with audio files stored on a FAT32 MicroSD card. UV illumination is controlled through a Songle relay module that safely switches a 12V Waveform realUV 365nm LED strip, keeping the high voltage circuit fully isolated from the Arduino's low voltage control electronics


Key Components
-The Arduino Mega 2560 serves as the central controller, coordinating all inputs and outputs and managing the two-minute presentation cycle through a finite state machine with two states: Default and Presentation Active. The rugged RGB push button is the sole visitor input, triggering the presentation cycle while its built-in LED communicates room availability alongside the exterior NeoPixel ring. The WS2812B NeoPixel rings handle visual feedback for both visitors outside the room and inside, with the exterior ring indicating availability and the interior ring providing ambiance during the presentation. The DFPlayer Mini manages all audio playback independently, receiving serial commands from the Arduino and driving the speaker directly without requiring additional amplification. The Songle relay module acts as the bridge between the Arduino's low-voltage control electronics and the 12V UV light circuit, ensuring the two are fully electrically isolated. The Waveform realUV 365nm LED strip provides UV illumination to reveal millipede fluorescence during the designated phase of the presentation cycle.

Getting Started
- To run the project:
  - Make sure to have the Arduino IDE downloaded on your personal device
  - Download the files (I have different test files for the different parts)
  - Open a file and compile it on the IDE, then connect your personal device to the Arduino Mega 2560
  - Then upload the file to the Arduino and from there if you have everything connected, press your button to activate the experience. 


Design Notes
- The Arduino Mega 2560 can safely take 7V-12V. Make sure not to connect anything that needs more than 12V because it can overheat and damage the board.
- The design is an open-air design so that the wires can easily be modified if need be
