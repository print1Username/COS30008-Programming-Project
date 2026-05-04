#include "Windows.h"
#include <SFML/Window/Event.hpp>


void Windows::LoadIcon() {
    if ( !icon.loadFromFile("icon.png") ) {
        cout << "Failed to load icon.png" << endl;
    } else {
        window.setIcon(icon);
    }
}

void Windows::LoadFont() {
    // Fonts are loaded in the member initializer list
    // Additional error handling can be added here if necessary
    // Download Link: https://fonts.google.com/specimen/Roboto
    if ( !fontSemiBoldItalic.openFromFile("Roboto/static/Roboto-SemiBoldItalic.ttf") )
        cout << "Failed to load SemiBoldItalic" << endl;
    if ( !fontSemiBold.openFromFile("Roboto/static/Roboto-SemiBold.ttf") )
        cout << "Failed to load SemiBold" << endl;
    if ( !fontRegular.openFromFile("Roboto/static/Roboto-Regular.ttf") )
        cout << "Failed to load Regular" << endl;
	if ( !fontLight.openFromFile("Roboto/static/Roboto-Light.ttf") )
		cout << "Failed to load Light" << endl;
	if ( !fontThin.openFromFile("Roboto/static/Roboto-Thin.ttf") )
		cout << "Failed to load Thin" << endl;
    if ( !fontThinItalic.openFromFile("Roboto/static/Roboto-ThinItalic.ttf") )
        cout << "Failed to load ThinItalic" << endl;
}

void Windows::StopAllMusic() {
    teamo.stop();
    ayuda.stop();
    harinezumi.stop();
}

void Windows::LoadMusic(int num) {
    StopAllMusic();

    switch ( num ) {
        case 1:
        if ( !teamo.openFromFile("teamo.mp3") ) {
            cout << "Failed to load teamo.mp3" << endl;
        } else {
            teamo.setLooping(true);
            teamo.setVolume(volume);
            teamo.play();
        }
        break;

        case 2:
        if ( !ayuda.openFromFile("ayuda.mp3") ) {
            cout << "Failed to load ayuda.mp3" << endl;
        } else {
            ayuda.setLooping(true);
            ayuda.setVolume(volume);
            ayuda.play();
		}
        break;

        case 3:
        if ( !harinezumi.openFromFile("harinezumi.mp3") ) {
            cout << "Failed to load harinezumi.mp3" << endl;
        } else {
            harinezumi.setLooping(true);
            harinezumi.setVolume(volume);
            harinezumi.play();
        }
        break;

        default:
        cout << "Invalid music ID: " << num << endl;
        break;
    }
}

void Windows::LoadImage() {
    if ( !start.loadFromFile("start.png") ) {
        cout << "Failed to load start.png" << endl;
    }
    if ( !bad.loadFromFile("bad.png") ) {
        cout << "Failed to load bad.png" << endl;
    }
    if ( !good.loadFromFile("good.png") ) {
        cout << "Failed to load good.png" << endl;
	}
    if ( !dead.loadFromFile("dead.png") ) {
        cout << "Failed to load dead.png" << endl;
	}
}

Text Windows::SetText(const string & content, int size, const Color & color, const Font & font, float x, float y){
    // Implementation for setting text properties
    // This function can be expanded based on specific requirements
    Text text(font, content, size);
	text.setFillColor(color);
    text.setPosition(Vector2f{ x, y });
	return text;
}

Windows::Button Windows::SetButton(string label, float x, float y, float width, float height) {
    Button btn;

    btn.box = make_unique<RectangleShape>(Vector2f(width, height));
    btn.box->setFillColor(Color::Black);
    btn.box->setOutlineColor(Color::White);
    btn.box->setOutlineThickness(3.f);
    btn.box->setPosition({ x, y });

    btn.text = make_unique<Text>(fontRegular, label, 40);
    btn.text->setFillColor(Color::White);
    btn.text->setPosition({ x + 30.f, y + 8.f });

    return btn;
}

Text Windows::DrawPlayer() {
    // ASCII Player
    string stickman =
        "   O\n"
        "  /|\\\n"
        "  / \\";

	Text playerText = SetText(
        stickman, 
        30, 
        Color::White, 
        fontRegular, 
        game.GetPlayerRef().getPositionX(),
        game.GetPlayerRef().getPositionY()
    );

    return playerText;
}

Text Windows::DrawMonster(int index) {
    // ASCII Monster
    string monster =
        "  /@@\\\n"
        " (----)\n"
        "  {==}\n"
        "  /  \\";

    Text monsterText = SetText(
        monster,
        25,
        Color::Red,   
        fontRegular,       
        game.GetMonsterPosX(index), 
        game.GetMonsterPosY(index)
    );

    return monsterText;
}

Text Windows::DrawItem() {
    // ASCII Item - Chest
    string item =
        "  ____\n"
        " / ___|\n"
        "| |___ \n"
        "|_____|";

    Text itemText = SetText(
        item,
        20,
        Color::Yellow,
        fontRegular,
        game.GetItemPosX(),
        game.GetItemPosY()
    );

    return itemText;
}

Text Windows::DrawDoor(int index) {
    // ASCII Door
    string door =
        "  _____\n"
        " |\t-\t|\n"
        " | [] - [] |\n"
        " |\t-\t|";

    Text doorText = SetText(
        door,
        20,
        Color::Blue,
        fontRegular,
        game.GetDoorPosX(index),
        game.GetDoorPosY(index)
    );

    return doorText;
}

RectangleShape Windows::DrawHpBar(float x, float y, int hp, int maxHp) {
    float width = 200.0f;     // Total width of the HP bar
    float height = 20.0f;     // Height of the HP bar

    // Prevent hp > maxHp from causing incorrect length
    float ratio = std::max(0.f, std::min(1.f, hp / float(maxHp)));

    // Background bar (gray)
    RectangleShape back(Vector2f(width, height));
    back.setFillColor(Color(50, 50, 50));
    back.setPosition(Vector2f{ x, y });

    // Foreground bar (green)
    RectangleShape bar(Vector2f(width * ratio, height));
    bar.setFillColor(Color(100, 255, 100));
    bar.setPosition(Vector2f{ x, y });

    // Draw background first, then the foreground HP bar
    window.draw(back);
    window.draw(bar);

    return bar;
}

Text Windows::DrawHpText(float x, float y, int hp, int maxHp, int size, const Color & color, const Font & font) {
    string hpString = "HP: " + to_string(hp) + " / " + to_string(maxHp);

    Text hpText = SetText(
        hpString,
        size,
        color,
        font,
        x,
        y - 25  // Move slightly upward so it appears above the HP bar
    );

    return hpText;
}

Text Windows::DrawImage(string image) {
    Text images = SetText(
        image,
        20,
        Color::White,
        fontRegular,
        0,
        0
    );

    window.draw(images);
    return images;
}

string Windows::KeyToString(Keyboard::Key key) {
    switch ( key ) {
        // Letters
        case Keyboard::Key::A: return "A";
        case Keyboard::Key::B: return "B";
        case Keyboard::Key::C: return "C";
        case Keyboard::Key::D: return "D";
        case Keyboard::Key::E: return "E";
        case Keyboard::Key::F: return "F";
        case Keyboard::Key::G: return "G";
        case Keyboard::Key::H: return "H";
        case Keyboard::Key::I: return "I";
        case Keyboard::Key::J: return "J";
        case Keyboard::Key::K: return "K";
        case Keyboard::Key::L: return "L";
        case Keyboard::Key::M: return "M";
        case Keyboard::Key::N: return "N";
        case Keyboard::Key::O: return "O";
        case Keyboard::Key::P: return "P";
        case Keyboard::Key::Q: return "Q";
        case Keyboard::Key::R: return "R";
        case Keyboard::Key::S: return "S";
        case Keyboard::Key::T: return "T";
        case Keyboard::Key::U: return "U";
        case Keyboard::Key::V: return "V";
        case Keyboard::Key::W: return "W";
        case Keyboard::Key::X: return "X";
        case Keyboard::Key::Y: return "Y";
        case Keyboard::Key::Z: return "Z";

            // Number row
        case Keyboard::Key::Num0: return "0";
        case Keyboard::Key::Num1: return "1";
        case Keyboard::Key::Num2: return "2";
        case Keyboard::Key::Num3: return "3";
        case Keyboard::Key::Num4: return "4";
        case Keyboard::Key::Num5: return "5";
        case Keyboard::Key::Num6: return "6";
        case Keyboard::Key::Num7: return "7";
        case Keyboard::Key::Num8: return "8";
        case Keyboard::Key::Num9: return "9";

            // Controls
        case Keyboard::Key::Escape: return "Escape";
        case Keyboard::Key::LControl: return "LControl";
        case Keyboard::Key::LShift: return "LShift";
        case Keyboard::Key::LAlt: return "LAlt";
        case Keyboard::Key::LSystem: return "LSystem";
        case Keyboard::Key::RControl: return "RControl";
        case Keyboard::Key::RShift: return "RShift";
        case Keyboard::Key::RAlt: return "RAlt";
        case Keyboard::Key::RSystem: return "RSystem";
        case Keyboard::Key::Menu: return "Menu";

            // Symbols
        case Keyboard::Key::LBracket: return "[";
        case Keyboard::Key::RBracket: return "]";
        case Keyboard::Key::Semicolon: return ";";
        case Keyboard::Key::Comma: return ",";
        case Keyboard::Key::Period: return ".";
        case Keyboard::Key::Apostrophe: return "'";
        case Keyboard::Key::Slash: return "/";
        case Keyboard::Key::Backslash: return "\\";
        case Keyboard::Key::Grave: return "`";
        case Keyboard::Key::Equal: return "=";
        case Keyboard::Key::Hyphen: return "-";

            // Basic keys
        case Keyboard::Key::Space: return "Space";
        case Keyboard::Key::Enter: return "Enter";
        case Keyboard::Key::Backspace: return "Backspace";
        case Keyboard::Key::Tab: return "Tab";

            // Navigation
        case Keyboard::Key::PageUp: return "PageUp";
        case Keyboard::Key::PageDown: return "PageDown";
        case Keyboard::Key::End: return "End";
        case Keyboard::Key::Home: return "Home";
        case Keyboard::Key::Insert: return "Insert";
        case Keyboard::Key::Delete: return "Delete";

            // Math keypad
        case Keyboard::Key::Add: return "+";
        case Keyboard::Key::Subtract: return "-";
        case Keyboard::Key::Multiply: return "*";
        case Keyboard::Key::Divide: return "/";

            // Arrows
        case Keyboard::Key::Left: return "Left";
        case Keyboard::Key::Right: return "Right";
        case Keyboard::Key::Up: return "Up";
        case Keyboard::Key::Down: return "Down";

            // Numpad
        case Keyboard::Key::Numpad0: return "Numpad0";
        case Keyboard::Key::Numpad1: return "Numpad1";
        case Keyboard::Key::Numpad2: return "Numpad2";
        case Keyboard::Key::Numpad3: return "Numpad3";
        case Keyboard::Key::Numpad4: return "Numpad4";
        case Keyboard::Key::Numpad5: return "Numpad5";
        case Keyboard::Key::Numpad6: return "Numpad6";
        case Keyboard::Key::Numpad7: return "Numpad7";
        case Keyboard::Key::Numpad8: return "Numpad8";
        case Keyboard::Key::Numpad9: return "Numpad9";

            // F1-F15
        case Keyboard::Key::F1: return "F1";
        case Keyboard::Key::F2: return "F2";
        case Keyboard::Key::F3: return "F3";
        case Keyboard::Key::F4: return "F4";
        case Keyboard::Key::F5: return "F5";
        case Keyboard::Key::F6: return "F6";
        case Keyboard::Key::F7: return "F7";
        case Keyboard::Key::F8: return "F8";
        case Keyboard::Key::F9: return "F9";
        case Keyboard::Key::F10: return "F10";
        case Keyboard::Key::F11: return "F11";
        case Keyboard::Key::F12: return "F12";
        case Keyboard::Key::F13: return "F13";
        case Keyboard::Key::F14: return "F14";
        case Keyboard::Key::F15: return "F15";

        case Keyboard::Key::Pause: return "Pause";

        default:
        return "Unknown";
    }
}

void Windows::Update(float deltaTime) {

    if ( game.battleCooldown ) {
        game.battleCooldownTimer -= deltaTime;
        if ( game.battleCooldownTimer <= 0 ) {
            game.battleCooldown = false;
        }
    }

    game.MonsterMove();
    game.CheckBattle();
}

void Windows::HomePage() {
	LoadMusic(1); // Load menu BGM
    int selected = 0;
    // Implementation of HomePage
    // This function should set up and display the home page UI

	Text title = SetText("Programmer Adventure", 60, Color::White, fontSemiBoldItalic, (window.getSize().x - 500) / 2.f, 100.f);
	Text hint = SetText("use Up and Down key to choose,\nuse Enter to select", 22, Color::White, fontThinItalic, 20.f, window.getSize().y - 80.f);

    vector<Button> buttons;
    float startY = 250.f;

    buttons.push_back(SetButton("New", 450.f, startY + 0 * 100.f, 300.f, 60.f));
    buttons.push_back(SetButton("Setting", 450.f, startY + 1 * 100.f, 300.f, 60.f));
    buttons.push_back(SetButton("Quit", 450.f, startY + 2 * 100.f, 300.f, 60.f));

    // Arrow
    Text arrow = SetText(">", 40, Color::White, fontRegular, 400.f, startY);

    while ( window.isOpen() ) {

        // Key pressed
        ProcessEvents();

        if ( lastKeyPressed == "Up" && selected > 0)      selected--;
        if ( lastKeyPressed == "Down" && selected < 2)    selected++;
        if ( lastKeyPressed == "Enter" ) {
            if ( selected == 0 ) { status = 5; return; }
            if ( selected == 1 ) { status = 3; return; }
            if ( selected == 2 ) { status = 4; return; }
        }

        arrow.setPosition({ 400.f, startY + selected * 100.f });

        window.clear(Color::Black);
        window.draw(title);
        window.draw(hint);

        for ( auto & b : buttons ) {
            window.draw(*b.box);
            window.draw(*b.text);
        }

        window.draw(arrow);
        window.display();
    }
}

void Windows::StoryPage(int index) {
    LoadMusic(2); // Load intro BGM
    
    Sprite sprite(start);

    switch ( index ) {
        case 1:
        sprite.setTexture(start);
        break;

        case 2:
        sprite.setTexture(bad);
        break;

        case 3:
		sprite.setTexture(good);
		break;

		case 4:
		sprite.setTexture(dead);
        break;

        default:
        cout << "Invalid story index!" << endl;
        return;
    }

    // Get local bounds
    auto bounds = sprite.getLocalBounds();
    float width = bounds.size.x;
    float height = bounds.size.y;

    auto winSize = window.getSize();
    float winW = winSize.x;
    float winH = winSize.y;

    float scaleX = winW / width;
    float scaleY = winH / height;

    float scale = std::min(scaleX, scaleY);
    sprite.setScale({ scale, scale });

    // --- Fade-in setup ---
    RectangleShape fadeRect;
    fadeRect.setSize(Vector2f(winW, winH));
    fadeRect.setFillColor(Color(0, 0, 0, 255));   // fully black → will fade out

    float fadeDuration = 2.0f;  // fade-in duration (seconds)
    Clock fadeClock;

    Clock timer;

    while ( window.isOpen() ) {

        window.clear();
        ProcessEvents();

        // If it is the story of the start
        if ( (lastKeyPressed == "Esc" || lastKeyPressed == "Space") && index == 1 ) {
            status = 2;
            break;
        }

        if ( lastKeyPressed == "Esc" && !(index == 1) ) {
            // Back to home page
            status = 1;
            // Reset the game
            game.ResetGame();
            break;
        }

        // Auto enter game after 10 secs
        if ( timer.getElapsedTime().asSeconds() >= 10.f ) {
            status = 2;
            break;
        }

        // --- Fade-in calculation ---
        float t = fadeClock.getElapsedTime().asSeconds();
        float alpha = 255.f - (t / fadeDuration) * 255.f;

        if ( alpha < 0 ) alpha = 0;  // stop fading
        fadeRect.setFillColor(Color(0, 0, 0, static_cast<std::uint8_t>(alpha)));

        // --- Rendering ---
        window.clear(Color::Black);
        window.draw(sprite);

        // Draw fade overlay *on top*
        if ( alpha > 0 )
            window.draw(fadeRect);

        window.display();
    }
}

void Windows::GamePage() {
	LoadMusic(3); // Load game BGM
    Text player = DrawPlayer();
    
    Clock clock;

    while ( window.isOpen() ) {

        window.clear();
        ProcessEvents();

        float dt = clock.restart().asSeconds();
        Update(dt);

        if ( lastKeyPressed == "Esc" ) {
            status = 1;
            return;
        }

        // If player hp drop to 0, the game ended.
		// Handle in the game loop.
        if ( game.GetPlayerRef().getHp() <= 0 ) {
            status = 8;
            return;
		}

        if ( game.GetDungeonRef().CheckPlayerDead() ) {
            status = 6;
            return;
        }

        if ( game.GetDungeonRef().CheckPlayerWin() ) {
            status = 7;
            return;
        }

        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::W)] ) game.PlayerMove("W");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::A)] ) game.PlayerMove("A");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::S)] ) game.PlayerMove("S");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::D)] ) game.PlayerMove("D");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::Up)] ) game.PlayerMove("Up");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::Down)] ) game.PlayerMove("Down");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::Left)] ) game.PlayerMove("Left");
        if ( keyHeld[static_cast<int>(sf::Keyboard::Scan::Right)] ) game.PlayerMove("Right");

        game.MonsterMove();
        game.CheckBattle();
        game.CheckDoor();

        // Draw UI
        window.clear(Color::Black);

        // Draw Room Name
        Text room = SetText(game.GetCurrentRoomName(), 38, Color::White, fontSemiBold, (window.getSize().x / 2 ) - 50.f, 30.f);
		window.draw(room);
    
        // Draw Player
        player = DrawPlayer();
        window.draw(player);

        // Player HP
        RectangleShape hpBar = DrawHpBar(20.f, 30.f, game.GetPlayerRef().getHp(), game.GetPlayerRef().getMaxHp());
        Text hpText = DrawHpText(
            20.f, 
            30.f, 
            game.GetPlayerRef().getHp(),
            game.GetPlayerRef().getMaxHp(),
            18,
            Color::White, 
            fontRegular);
        window.draw(hpBar);
        window.draw(hpText);

        // DrawMonster
        for ( int i = 0; i < game.GetCurrentRoomMonsterCount(); i++ ) {
            Text monster = DrawMonster(i);
            Text monsterName = SetText(
                game.GetCurrentRoomMonsterName(i),
                16,
                Color::Red,
                fontLight,
                game.GetMonsterPosX(i),
                game.GetMonsterPosY(i) - 25
			);
            
            Text monsterHpText = DrawHpText(
                game.GetMonsterPosX(i) + 30,
                game.GetMonsterPosY(i),
                game.GetMonsterHp(i),
                game.GetMonsterMaxHp(i),
                16,
                Color::Red,
                fontLight
			);
            window.draw(monster);
            window.draw(monsterName);
            window.draw(monsterHpText);
        }

        // Draw Door
        // If the Room is the root, then dont draw the back room
        // else draw the back room
        if (game.GetDungeonRef().IsAtRoot()) {
            for ( int i = 1; i < game.GetDungeonRef().SubRoomSize() + 1; i++ ) {
                Text door = DrawDoor(i);
                window.draw(door);
            }

        } else {
            // Draw Door
            for ( int i = 0; i < game.GetDungeonRef().SubRoomSize() + 1; i++ ) {
                Text door = DrawDoor(i);
                window.draw(door);
            }
        }
    
        window.display();
	}
}

void Windows::SettingPage() {

    vector<string> options = {
        "Player Name",
        "Volume",
        "Reset All Settings"
    };

    int selectedIndex = 0;
    bool editing = false;         // Whether we are currently editing a value
    bool enterConsumed = false;   // Prevent Enter from triggering multiple times due to key repeat

    volume = game.GetGameSettingInt("volume");
    string playerName = game.GetGameSettingString("playerName");

    Text title = SetText("Settings Page", 52, Color::White, fontSemiBoldItalic, 70.f, 70.f);

    while ( window.isOpen() ) {

        // ===== INPUT =====
        ProcessEvents();
        string key = lastKeyPressed;   // Snapshot of key input for this frame

        // ===== Exit settings page =====
        if ( key == "Esc" ) {
            status = 1;
            return;
        }

        // =========================================================
        //               Navigation when NOT editing
        // =========================================================
        if ( !editing ) {

            // Move selection up
            if ( (key == "W" || key == "Up") && selectedIndex > 0) {
                selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
            }

            // Move selection down
            if ( (key == "S" || key == "Down") && selectedIndex < options.size() - 1 ) {
                selectedIndex = (selectedIndex + 1) % options.size();
            }

            // ENTER → Start editing or reset settings
            if ( key == "Enter" && !enterConsumed ) {

                enterConsumed = true; // Avoid repeated Enter from long press

                if ( selectedIndex == 2 ) {
                    // Reset all settings
                    game.ResetGameSettings();

                    // Reload values after reset
                    playerName = game.GetGameSettingString("playerName");
                    volume = game.GetGameSettingInt("volume");
                    LoadMusic(1);
                } else {
                    // Enter editing mode
                    editing = true;
                }
            }
        }

        // =========================================================
        //                      Editing mode
        // =========================================================
        else {

            // ===== Editing Player Name =====
            if ( selectedIndex == 0 ) {

                if ( !key.empty() ) {

                    // Delete last character
                    if ( key == "Backspace" ) {
                        if ( !playerName.empty() )
                            playerName.pop_back();
                    }

                    // Insert space
                    else if ( key == "Space" ) {
                        if ( playerName.size() < 20 )
                            playerName += ' ';
                    }

                    // Letter or number input
                    else if ( key.size() == 1 ) {
                        if ( playerName.size() < 20 )
                            playerName += key[0];
                    }

                    // Enter - Save and exit editing
                    if ( key == "Enter" && !enterConsumed ) {
                        enterConsumed = true;
                        editing = false;
                        game.GameSetting("playerName", playerName);
                    }
                }
            }

            // ===== Editing Volume =====
            if ( selectedIndex == 1 ) {

                if ( key == "A" || key == "Left" )
                    volume = max(0, volume - 10);

                if ( key == "D" || key == "Right" )
                    volume = min(100, volume + 10);

                game.GameSetting("volume", volume);
                LoadMusic(1);

                // Enter → leave editing mode
                if ( key == "Enter" && !enterConsumed ) {
                    enterConsumed = true;
                    editing = false;
                }
            }
        }

        // Release Enter flag when key is no longer Enter
        if ( key != "Enter" ) enterConsumed = false;

        // Clear key for next frame
        lastKeyPressed = "";

        // =========================================================
        //                          DRAW
        // =========================================================
        window.clear(Color::Black);
        window.draw(title);

        float startY = 200.f;
        float gap = 80.f;

        for ( int i = 0; i < options.size(); i++ ) {

            string prefix = (i == selectedIndex ? ">  " : "   ");
            string label = prefix + options[i];

            // Show additional info based on selected item
            if ( i == 0 ) {
                label += " : " + playerName;
                if ( editing && selectedIndex == 0 )
                    label += " <editing>";
            } else if ( i == 1 ) {
                label += " : " + to_string(volume);
                if ( editing && selectedIndex == 1 )
                    label += " <editing>";
            }

            Text item = SetText(label, 40, Color::White, fontRegular,
                                100.f, startY + i * gap);

            window.draw(item);
        }

        // Bottom hint text
        Text hint = SetText(
            editing ?
            "Type to edit (A-Z, 0-9), Backspace to delete, Enter to save"
            :
            "W/S to move, Enter to edit, ESC to exit",
            28, Color::White, fontThinItalic,
            100.f, 650.f);

        window.draw(hint);
        window.display();
    }
}

void Windows::QuitPage() {
    // Implementation of QuitPage
    // This function should set up and display the quit confirmation UI
	Text title = SetText("Confirm to quit the game?", 52, Color::White, fontSemiBoldItalic, 200.f, 150.f);
	Text yes = SetText("Yes", 40, Color::White, fontRegular, 450.f, 350.f);
	Text no = SetText("No", 40, Color::White, fontRegular, 650.f, 350.f);
	Text arrow = SetText(">", 40, Color::White, fontRegular, 600.f, 350.f);
	Text hint = SetText("use Left and Right key to choose,\nuse Enter to select", 22, Color::White, fontThinItalic, 20.f, window.getSize().y - 80.f);

    int selected = 1; // default = No
    // arrow position based on selection
    auto updateArrow = [&]() {
        if ( selected == 0 )
            arrow.setPosition({ 400.f, 350.f }); // Yes
        else
            arrow.setPosition({ 600.f, 350.f }); // No
    };

    // --- Main Loop ---
    while ( window.isOpen() ) {
        ProcessEvents();

        if ( lastKeyPressed == "Left" ) { selected = 0; updateArrow(); }
        if ( lastKeyPressed == "Right" ) { selected = 1; updateArrow(); }

        if ( lastKeyPressed == "Enter" ) {
            if ( selected == 0 ) { window.close(); return; }
            if ( selected == 1 ) { status = 1; return; }
        }

        if ( lastKeyPressed == "Esc" ) {
            status = 1;
            return;
        }

        // Draw UI
        window.clear(Color::Black);
        window.draw(title);

        // Buttons
        window.draw(yes);
        window.draw(no);
        window.draw(arrow);
        window.draw(hint);

        window.display();
    }
}

std::string Windows::lastKeyPressed = "";
bool Windows::keyHeld[sf::Keyboard::ScancodeCount] = {};

void Windows::ProcessEvents() {

    lastKeyPressed = "";

    while ( const auto event = window.pollEvent() ) {

        if ( event->is<sf::Event::Closed>() ) {
            window.close();
            lastKeyPressed = "__CLOSE__";
            return;
        }

        if ( auto key = event->getIf<sf::Event::KeyPressed>() ) {

            keyHeld[(int) key->scancode] = true;

            using K = sf::Keyboard::Key;

            // ===== A–Z =====
            if ( key->code >= K::A && key->code <= K::Z ) {
                char c = 'A' + (int(key->code) - int(K::A));
                lastKeyPressed = string(1, c);
                continue;
            }

            // ===== 0–9 =====
            if ( key->code >= K::Num0 && key->code <= K::Num9 ) {
                char c = '0' + (int(key->code) - int(K::Num0));
                lastKeyPressed = string(1, c);
                continue;
            }

            switch ( key->code ) {

                // Navigation
                case K::Up:       lastKeyPressed = "Up"; break;
                case K::Down:     lastKeyPressed = "Down"; break;
                case K::Left:     lastKeyPressed = "Left"; break;
                case K::Right:    lastKeyPressed = "Right"; break;

                    // WASD
                case K::W:        lastKeyPressed = "W"; break;
                case K::A:        lastKeyPressed = "A"; break;
                case K::S:        lastKeyPressed = "S"; break;
                case K::D:        lastKeyPressed = "D"; break;

                    // Controls
                case K::Enter:      lastKeyPressed = "Enter"; break;
                case K::Escape:     lastKeyPressed = "Esc"; break;
                case K::Space:      lastKeyPressed = "Space"; break;
                case K::Backspace:  lastKeyPressed = "Backspace"; break;
            }
        }

        if ( auto key = event->getIf<sf::Event::KeyReleased>() ) {
            keyHeld[(int) key->scancode] = false;
        }
    }
}


Windows::Windows() : window(
    VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
    windowTitle,
    Style::Titlebar | Style::Close
), status(1), game() {
    LoadFont();
    LoadIcon();
}

void Windows::run() {
    status = 1;
    LoadIcon();
    LoadFont();
    LoadImage();

    while ( window.isOpen() ) {
        switch ( status ) {
            case 1: HomePage(); break;
            case 2: GamePage(); break;
            case 3: SettingPage(); break;
            case 4: QuitPage(); break;

            // Story Page
			case 5: StoryPage(1); break; // Story Start
			case 6: StoryPage(2); break; // Player Drop
            case 7: StoryPage(3); break; // Player Win
			case 8: StoryPage(4); break; // Player Dead
			default: window.close(); break;
        }
    }
}