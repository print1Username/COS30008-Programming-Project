# COS30008 Programming Project
This is the Programming project for the COS 30008 Data Structure and Patterns.

## Game Descriptions
This is a lightweight RPG developed entirely in C++.

The core narrative centers around the player, a programmer, who is literally snatched from the real world and pulled into a perilous digital adventure by a pair of mysterious, unseen hands.

Gameplay involves navigating a labyrinthian environment: The player must strategically choose between different rooms, each presenting a unique combat challenge defined by varying monster quantities and threat levels. The ultimate objective is to successfully identify and secure the correct escape route needed to safely return home.

## Basic Setup
1. Install MSYS2
  Download and install MSYS2, then open "MSYS2 MinGW64"
1. Open MSYS2 MinGW64 terminal
1. Install GCC:
```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain

```
Press **Enter** to install all package

4. In you Powershell or CMD terminal, run:
```bash
# Build exe
g++ src/*.cpp -Iinclude -I external/SFML-3.0.1-mingw/include -L external/SFML-3.0.1-mingw/lib -o ./external/SFML-3.0.1-mingw/bin/app.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
# Run exe
./external/SFML-3.0.1-mingw/bin/app.exe

```

## Source
### Backgound Music
[NoCopyrightSounds Official Website](https://ncs.io/)

#### Music Name:

[AYUDA: by MXRCVRY](https://ncs.io/AYUDA)
\
[teamo: by c8o](https://ncs.io/teamo)
\
[harinezumi: by waera](https://ncs.io/harinezumi)

### Image (Generate by Gemini: Nano Banana Pro)
[Gemini Google](https://gemini.google.com)
\
[Google AI Studio](https://aistudio.google.com/)