# GameBoyEmu
A gameboy emulator made using SFML and C++.
This is just a test project I made while exploring emulation for fun. There are many games that it runs properly, however there are often graphical bugs and some games that it just crashes on opening.

## Features
Doesn't provide many features other than the basic game keys and a few keys that change emulation.
  * '=' - increases the volume of the audio
  * '-' - decreases the volume of the audio
  * 'F1' - toggles the audio for the audio channel 1 on/off
  * 'F2' - toggles the audio for the audio channel 2 on/off
  * 'F3' - toggles the audio for the audio channel 3 on/off
  * '[' - slows down emulation by a factor of two
  * ']' - speeds up emulation by a factor of two
  * The arrow keys are the dpad.
  * 'a' - start
  * 's' - select
  * 'F9' - decreases the number of frames skipped for drawing (slows down game but smoother)
  * 'F10' - increases the number of frames skipped for drawing (speeds up game but choppy)
  * 'x' - the a button
  * 'z' - the b button

The default speed (assuming your computer can keep up) is 60hz (the native gameboy speed). If the game seems a bit slow on the default speed, then increase frameskip. There is no SRAM support nor save states, nor does it support the gameboy color.

## Games
I haven't tested too many games on it, however I have tested the following:
  * Kirby's Dream Land- Runs very well and only has graphical glitches.
  * Tetris - Very playable and seems to have little to no glitches.
  * Link's Awakening- Get's past the title screen but doesn't run.
  * Metroid II Return of Samus - Lots of graphical glitches but runs fine
  * Pokemon Blue Version - A good number of graphical glitches but runs fine.
  * Super Mario Land - Extreme graphical glitches to the point of non playability.
My apologies for not having a build script nor is my documentation is up to snuff (yet).
