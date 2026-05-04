#include "Setting.h"

json Setting::defaultSetting() {
	return {
		{"volume", 100},
		{"playerName", "PROGRAMMER"},
	};
}

Setting::Setting(const string & filename) : filename(filename) {
	load();
}

void Setting::load() {
	ifstream inFile(filename);
	if (inFile.is_open()) {
		inFile >> data;
		inFile.close();
	} else {
		cout << "Could not open the file for reading: " << filename << endl;
	}
}

void Setting::save() {
	ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << data.dump(4); // Pretty print with 4 spaces indentation
		outFile.close();
	} else {
		cout << "Could not open the file for writing: " << filename << endl;
	}
}


// ----- Generic Getters -----
int Setting::getInt(const string & key) {
    if ( !data.contains(key) )
        return 0;
    return data[key].get<int>();
}

bool Setting::getBool(const string & key) {
    if ( !data.contains(key) )
        return false;
    return data[key].get<bool>();
}

string Setting::getString(const string & key) {
    if ( !data.contains(key) )
        return "";
    return data[key].get<string>();
}

// ----- Generic Setters -----
void Setting::setInt(const string & key, int value) {
    data[key] = value;
}

void Setting::setBool(const string & key, bool value) {
    data[key] = value;
}

void Setting::setString(const string & key, const string & value) {
    data[key] = value;
}

void Setting::Reset() {
	data = defaultSetting();
	save();
}