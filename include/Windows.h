#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

using namespace std;
using namespace sf;

class Windows {
private:
	const string windowTitle = "COS 30008 Programming Project";

	const static int WINDOW_WIDTH = 1200;
	const static int WINDOW_HEIGHT = 800;

	RenderWindow window;
	

	// Font
	Font fontSemiBoldItalic;
	Font fontSemiBold;
	Font fontRegular;
	Font fontLight;
	Font fontThin;
	Font fontThinItalic;

	Image icon;

	int status;

	Game game;

	struct Button {
		unique_ptr<RectangleShape> box;
		unique_ptr<Text> text;

		Button() = default;

		Button(Button &&) noexcept = default;
		Button & operator=(Button &&) noexcept = default;

		Button(const Button &) = delete;
		Button & operator=(const Button &) = delete;
	};

	// BGM
	Music harinezumi; // Menu BGM
	Music ayuda; // Story BGM
	Music teamo; // Game BGM

	// Image
	Texture start; // Start Image
	Texture bad; // Bad ending Image
	Texture good; // Good ending Image
	Texture dead; // Dead Image

	int volume = game.GetGameSettingInt("volume"); // Default volume

private:
	void LoadIcon();
	void LoadFont();
	void StopAllMusic();
	void LoadMusic(int num);
	void LoadImage();

	Text SetText(const string & content, int size, const Color & color, const Font & font, float x, float y);
	Button SetButton(string label, float x, float y, float width, float height);

	Text DrawPlayer();
	Text DrawMonster(int index);
	Text DrawItem();
	Text DrawDoor(int index);
	Text DrawImage(string image);

	RectangleShape DrawHpBar(float x, float y, int hp, int maxHp);
	Text DrawHpText(float x, float y, int hp, int maxHp, int size, const Color & color, const Font & font);

	string KeyToString(Keyboard::Key key);

	void Update(float deltaTime);

	void HomePage();
	void StoryPage(int index);
	void GamePage();
	void SettingPage();
	void QuitPage();

public:
	static string lastKeyPressed;
	static bool keyHeld[Keyboard::ScancodeCount];

	void ProcessEvents();

	Windows();

	void run();
};