#pragma once
#include <iostream>
#include "Setting.h"
#include "Player.h"
#include "Dungeon.h"

class Game {
private:
	Setting setting;
	Player player;
	Dungeon dungeon;

public:
	Game();

	// Game Setting
	// Automatically determine the type and write to config
	// Type-specific getters
	template<typename T>
	void GameSetting(const string & key, const T & value) {
		if constexpr ( is_same_v<T, int> ) {
			setting.setInt(key, value);
		} else if constexpr ( is_same_v<T, bool> ) {
			setting.setBool(key, value);
		} else if constexpr ( is_same_v<T, string> ) {
			setting.setString(key, value);
		} else {
			cout << "Unsupported type for GameSetting: " << key << endl;
		}

		setting.save();
	}

	// Setting Getter
	string GetGameSettingString(const string & key);
	int GetGameSettingInt(const string & key);
	bool GetGameSettingBool(const string & key);
	void ResetGameSettings();

	bool battleCooldown = false;
	float battleCooldownTimer = 0.0f;

	// Getter Room
	string GetCurrentRoomName();
	int GetCurrentRoomMonsterCount();

	// Getter Monster
	string GetCurrentRoomMonsterName(int index);

	void PlayerMove(const string & key);
	void MonsterMove();

	void CheckBattle();
	void CheckDoor();


	// Taxicab geometry/Manhattan distance/Manhattan length
	float Manhattan(float ax, float ay, float bx, float by);
	float Euclidean(float ax, float ay, float bx, float by);

	// Monster
	float GetMonsterPosX(int index);
	float GetMonsterPosY(int index);
	int GetMonsterHp(int index);
	int GetMonsterMaxHp(int index);

	float GetItemPosX();
	float GetItemPosY();

	float GetDoorPosX(int index);
	float GetDoorPosY(int index);


	Player & GetPlayerRef();
	const Player & GetPlayer() const; // optional const accessor if needed elsewhere

	Dungeon & GetDungeonRef();
	const Dungeon & GetDungeon() const;

	void ResetGame();
};