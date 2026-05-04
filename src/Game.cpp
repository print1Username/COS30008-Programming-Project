#include "Game.h"

Game::Game() :
	player("Player", 100, 5),
	dungeon(),
    setting("config.json") {

	player.setPosition(20.f, 70.f);
}

string Game::GetGameSettingString(const string & key) {
    return setting.getString(key);
}

int Game::GetGameSettingInt(const string & key) {
    return setting.getInt(key);
}

bool Game::GetGameSettingBool(const string & key) {
    return setting.getBool(key);
}

void Game::ResetGameSettings() {
    setting.Reset();
    setting.save();
}

string Game::GetCurrentRoomName() {
    Room & room = dungeon.GetCurrentRoom();
    return room.getName();
}

int Game::GetCurrentRoomMonsterCount() {
    Room & room = dungeon.GetCurrentRoom();
	return room.getMonsterCount();
}

string Game::GetCurrentRoomMonsterName(int index) {
    Monster & m = dungeon.GetCurrentRoom().getMonsterRef(index);
    return m.getName();
}

void Game::PlayerMove(const string & key){
	if ( (key == "W" || key == "Up") && player.getPositionY() > 70) {
		player.setPosition(static_cast<int>(player.getPositionX()), static_cast<int>(player.getPositionY() - player.getSpeed()));
	} else if ( (key == "S" || key == "Down") && player.getPositionY() < 600 ) {
		player.setPosition(static_cast<int>(player.getPositionX()), static_cast<int>(player.getPositionY() + player.getSpeed()));
	} else if ( (key == "A" || key == "Left") && player.getPositionX() > 0 ) {
		player.setPosition(static_cast<int>(player.getPositionX() - player.getSpeed()), static_cast<int>(player.getPositionY()));
	} else if ( (key == "D" || key == "Right") && player.getPositionX() < 1100 ) {
		player.setPosition(static_cast<int>(player.getPositionX() + player.getSpeed()), static_cast<int>(player.getPositionY()));
	}
}

void Game::MonsterMove() {
    Room & currentRoom = dungeon.GetCurrentRoom();

    // Iterate through all monsters in the current room
    for ( int i = 0; i < currentRoom.getMonsterCount(); i++ ) {
        Monster & m = currentRoom.getMonsterRef(i);

        float mx = m.getPositionX();
        float my = m.getPositionY();
        float px = player.getPositionX();
        float py = player.getPositionY();

        // Calculate Manhattan distance between monster and player
        float dist = Euclidean(mx, my, px, py);

        // If distance is too far, monster will not chase the player
        const float detectRange = 400.0f;
        if ( dist > detectRange )
            continue;

        // Monster chasing speed
        double speed = m.getSpeed();

        // Move monster in X direction toward the player
        if ( px > mx )
            mx += speed;
        else if ( px < mx )
            mx -= speed;

        // Move monster in Y direction toward the player
        if ( py > my )
            my += speed;
        else if ( py < my )
            my -= speed;

        // Update monster position
        m.setPosition(mx, my);
    }
}

void Game::CheckBattle() {

    if ( battleCooldown )
        return;

    Room & room = dungeon.GetCurrentRoom();

    float px = player.getPositionX();
    float py = player.getPositionY();

    for ( int i = 0; i < room.getMonsterCount(); i++ ) {
        Monster & m = room.getMonsterRef(i);

        float mx = m.getPositionX();
        float my = m.getPositionY();

        float dist = Manhattan(px, py, mx, my);

        if ( dist <= 70 ) {

            // --- Start ---
            player.damaging(m.getDamage());
            m.damaging(player.getDamage());

            cout << "[Battle] Damage dealt: Player - " << player.getDamage() << ". Monster - " << m.getDamage() << endl;

            if ( m.getHp() <= 0 ) {
                room.removeMonster(i);
                i--; // adjust index after removal
            }

            // 3 sec countdown
            battleCooldown = true;
            battleCooldownTimer = 0.5f;

            return;
        }
    }
}

void Game::CheckDoor() {
    float px = player.getPositionX();
    float py = player.getPositionY();
    const float doorX1 = 1100.0f; // Next Door
	const float doorX2 = 100.0f; // Previous Door
    const float doorY1 = 100.0f; // Door 0
    const float doorY2 = 300.0f; // Door 1
	const float doorY3 = 500.0f; // Door 2

    Room & previous = dungeon.GetCurrentRoom();

    if ( Manhattan(px, py, doorX1, doorY1) <= 50 ) {
        dungeon.MoveRoom(0);
        player.setPosition(50.f, 300.f); // Reset player position

    } else if ( Manhattan(px, py, doorX1, doorY2) <= 50 ) {
        dungeon.MoveRoom(1);
        player.setPosition(50.f, 300.f); // Reset player position

    } else if ( Manhattan(px, py, doorX1, doorY3) <= 50 ) {
        dungeon.MoveRoom(2);
        player.setPosition(50.f, 300.f); // Reset player position

    } else if ( (Manhattan(px, py, doorX2, doorY1) <= 50) && !dungeon.IsAtRoot() ) {
		dungeon.MoveParentRoom();
		player.setPosition(1000.f, 300.f); // Reset player position

    } else {
        return;
    }

    cout << "From [" << previous.getName() << "] move to [" << GetCurrentRoomName() << "]" << endl;

}

float Game::Manhattan(float ax, float ay, float bx, float by) {
	return (abs(ax - bx) + abs (ay - by));
}

float Game::Euclidean(float ax, float ay, float bx, float by) {
    return sqrt( (ax - bx) * (ax - bx) + (ay - by) * (ay - by) );
}

float Game::GetMonsterPosX(int index) {
    Room & room = dungeon.GetCurrentRoom();

    int count = room.getMonsterCount();

    // If no monster exists
    if ( count == 0 )
        return -9999;  // or return 0 (any safe value)

    // If index is invalid
    if ( index < 0 || index >= count )
        return -9999;  // prevent crash / throw

    Monster & m = room.getMonsterRef(index);
    return m.getPositionX();
}

float Game::GetMonsterPosY(int index) {
    Room & room = dungeon.GetCurrentRoom();

    int count = room.getMonsterCount();

    if ( count == 0 )
        return -9999;

    if ( index < 0 || index >= count )
        return -9999;

    Monster & m = room.getMonsterRef(index);
    return m.getPositionY();
}

int Game::GetMonsterHp(int index) {
    int count = dungeon.GetCurrentRoom().getMonsterCount();
    if ( count == 0 )
        return -1;
    if ( index < 0 || index >= count )
        return -1;
    Monster & m = dungeon.GetCurrentRoom().getMonsterRef(index);
    return m.getHp();
}

int Game::GetMonsterMaxHp(int index) {
    int count = dungeon.GetCurrentRoom().getMonsterCount();
    if ( count == 0 )
        return -1;
    if ( index < 0 || index >= count )
        return -1;
    Monster & m = dungeon.GetCurrentRoom().getMonsterRef(index);
    return m.getMaxHp();
}

float Game::GetItemPosX() {
	return 800.0f;
}

float Game::GetItemPosY() {
	return 500.0f;
}

float Game::GetDoorPosX(int index) {
    if ( index == 0 )
		return 100.0f;
    else
	    return 1100.0f;
}

float Game::GetDoorPosY(int index) {
	if ( index == 0 )
		return 100.0f;
    else if (index == 1 )
        return 100.0f;
	else if ( index == 2 )
        return 500.0f;
    else if ( index == 3 )
		return 300.0f;
}

Player & Game::GetPlayerRef() {
	return player;
}

const Player & Game::GetPlayer() const {
	return player;
}

Dungeon & Game::GetDungeonRef() {
    return dungeon;
}

const Dungeon & Game::GetDungeon() const {
    return dungeon;
}

void Game::ResetGame() {
    player.ResetPlayer();
    dungeon.ResetDungeon();
    player.setPosition(20.f, 70.f);
}