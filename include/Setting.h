#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

// https://github.com/nlohmann/json/releases

class Setting {
private:
	string filename;
	json data;

	json defaultSetting();

public:
	Setting(const string & filename);
	void load();
	void save();

	// Getter
	int getInt(const string & key);
	bool getBool(const string & key);
	string getString(const string & key);

	// Setter
	void setInt(const string & key, int value);
	void setBool(const string & key, bool value);
	void setString(const string & key, const string & value);

	// Reset all settings to default
	void Reset();
};