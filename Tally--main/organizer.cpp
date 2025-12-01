#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#define NOMINMAX
#include <windows.h>
#include <sstream>
#include <conio.h>
#include <limits>
using namespace std;

// Slow print 
void slowprint(const string& message, int delay_ms = 0.67) {
    for (char c : message) {
        cout << c << flush;
        Sleep(delay_ms);
    }
    cout << "\033[0m"; // Reset color after printing
}
// Standard "invalid input" error popup + pause
void showInvalidInputPause(const string& msg = "INVALID INPUT. PLEASE TRY AGAIN.") {
    slowprint("\n \033[1;37;41m ⚠️ " + msg + " ⚠️ \033[0m\n\n");
    slowprint(" \033[1;48;2;255;255;255m\033[38;2;0;0;0m ➡️ PRESS ENTER TO CONTINUE... \033[0m\n");
    cin.get(); // wait for Enter
}

enum PlayerClass {
    DEFAULT_CLASS,
    HERO_CLASS,
    GAMBLER_CLASS,
    ASSASSIN_CLASS,
    WIZARD_CLASS,
    ARCHER_CLASS,
    TANK_CLASS

};

// Global class system variables
PlayerClass playerClass = DEFAULT_CLASS;
int assassinStreak = 0; // Assassin consecutive success counter
int assassinStacks = 0; // Assassin stack system
int wizardCounter = 0; // Wizard spell combo counter
int archerStreak = 0; // Archer hit streak
int tankStacks = 0;   // Tank momentum system

// Class ownership flags
bool ownsHero = false;
bool ownsGambler = false;
bool ownsAssassin = false;
bool ownsWizard = false;
bool ownsArcher = false;
bool ownsTank = false;

// Achievement system global flag(for saving unlocked characters and have them as an achievement)
bool achievementsNeedUpdate = false;

//function to get current date
void getCurrentDate(int &month, int &day, int &year) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    month = ltm->tm_mon + 1;
    day   = ltm->tm_mday;
    year  = ltm->tm_year + 1900;
}

//function for formatting doubles to 2 decimal places
string fmt2(double n) {
    ostringstream oss;
    oss << fixed << setprecision(2) << n;
    return oss.str();
}

// -------------------------
// XP / LEVELING FUNCTION
// -------------------------
// Adds XP, prints XP gained, and handles leveling.
// Level formula: level = (playerXP / 100) + 1
void addXP(int amount, bool gamificationEnabled, int& playerXP, int& playerLevel) {

    if (!gamificationEnabled)
        return;

    playerXP += amount;

    int newLevel = (playerXP / 100) + 1;  // 100 XP per level

    slowprint( "\n>>> +" + to_string(amount) + " XP!\n");

    if (newLevel > playerLevel) {
        playerLevel = newLevel;
        slowprint(">>> LEVEL UP! You are now LEVEL " + to_string(playerLevel) + "!\n");
    }

    slowprint("-------------------------------------\n");
}

// Live summary box used everywhere
void headerClassList() {

        slowprint("                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint("                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint("                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint("                                                      ██████╗██╗      █████╗ ███████╗███████╗    ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗     \n");
        slowprint("                                                     ██╔════╝██║     ██╔══██╗██╔════╝██╔════╝    ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║     \n");
        slowprint("                                                     ██║     ██║     ███████║███████╗███████╗    ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║        \n");
        slowprint("                                                     ██║     ██║     ██╔══██║╚════██║╚════██║    ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║      \n");
        slowprint("                                                     ╚██████╗███████╗██║  ██║███████║███████║    ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║      \n");
        slowprint("                                                      ╚═════╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝    ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝           \n");
        slowprint("                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}

void showClassInfo(int c) {
    system("cls");
    headerClassList();

    slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    slowprint("                                                                                          CLASS INFORMATION\n");
    slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");


    switch (c) {

    case 1:
        slowprint("                                                                                         [DEFAULT CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • No XP bonus\n");
        slowprint("                                                                          • Balanced starter class\n");
        slowprint("                                                                          • Good for new players\n");
        break;

    case 2:
        slowprint("                                                                                           [HERO CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • +25 XP on every action\n");
        slowprint("                                                                          • Best constant XP gain\n");
        slowprint("                                                                          • Reliable and simple\n");
        break;

    case 3:
        slowprint("                                                                                            [GAMBLER CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • RNG-based XP system\n");
        slowprint("                                                                          • Can gain massive XP\n");
        slowprint("                                                                          • 20% chance to lose XP\n");
        slowprint("                                                                          • High-risk, high-reward\n");
        break;

    case 4:
        slowprint("                                                                                            [ASSASSIN CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • XP streak mechanic starts after 3 actions\n");
        slowprint("                                                                          • +5% XP per stack (up to 10 stacks)\n");
        slowprint("                                                                          • Strong burst XP class\n");
        break;

    case 5:
        slowprint("                                                                                             [WIZARD CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • Spell Combo: bonus every 3rd XP gain\n");
        slowprint("                                                                          • Crit Combo: double bonus every 5th gain\n");
        slowprint("                                                                          • Wisdom Scaling: +5 XP per level\n");
        slowprint("                                                                          • Very strategic class\n");
        break;

    case 6:
        slowprint("                                                                                             [ARCHER CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • Precision Shot streak system\n");
        slowprint("                                                                          • Big streak = big XP\n");
        slowprint("                                                                          • Headshots = crit XP\n");
        slowprint("                                                                          • Rare Perfect Shot = huge burst\n");
        break;

    case 7:
        slowprint("                                                                                               [TANK CLASS]\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint("                                                                          • Shield Momentum stacking system\n");
        slowprint("                                                                          • Gains stacks every action\n");
        slowprint("                                                                          • Max stacks = 20 - level\n");
        slowprint("                                                                          • Strong early, weaker late\n");
        slowprint("                                                                          • Always gives a bonus\n");
        break;

    default:
        slowprint("Invalid class selection.\n");
        break;
    }

    slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}




// Live summary box used everywhere
void ClassListCopy(PlayerClass& playerClass, int& playerXP) {

        system("cls");
        headerClassList();


        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint("                                                                                     Current XP: " + to_string(playerXP) + "\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        slowprint("                                                                          🏷️ Available Classes:\n\n");
        slowprint("                                                                          [1] Default            (Free)           "
             + string(playerClass == DEFAULT_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [2] Hero               (Cost: 500 XP)   "
             + string(ownsHero ? "[OWNED]" : "")
             + string(playerClass == HERO_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [3] Gambler            (Cost: 300 XP)   "
             + string(ownsGambler ? "[OWNED]" : "")
             + string(playerClass == GAMBLER_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [4] Assassin           (Cost: 400 XP)   "
             + string(ownsAssassin ? "[OWNED]" : "")
             + string(playerClass == ASSASSIN_CLASS ? " <== Equipped" : "") + "\n");
        slowprint("                                                                          [5] Wizard             (Cost: 700 XP)   "
             + string(ownsWizard ? "[OWNED]" : "")
             + string(playerClass == WIZARD_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [6] Archer             (Cost: 600 XP)   "
             + string(ownsArcher ? "[OWNED]" : "")
             + string(playerClass == ARCHER_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [7] Tank               (Cost: 500 XP)   "
             + string(ownsTank ? "[OWNED]" : "")
             + string(playerClass == TANK_CLASS ? " <== Equipped" : "") + "\n");

     
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint("                                                                          [8] View Class Details\n");
        slowprint("                                                                          [0] Back\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
 
}

void classMenu(PlayerClass& playerClass, int& playerXP) {
    while (true) {
        system("cls");
        headerClassList();


        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint("                                                                                     Current XP: " + to_string(playerXP) + "\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        slowprint("                                                                          🏷️ Available Classes:\n\n");
        slowprint("                                                                          [1] ⚪ Default            (Free)           "
             + string(playerClass == DEFAULT_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [2] ⚔️ Hero               (Cost: 500 XP)   "
             + string(ownsHero ? "[OWNED]" : "")
             + string(playerClass == HERO_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [3] 🎭 Gambler            (Cost: 300 XP)   "
             + string(ownsGambler ? "[OWNED]" : "")
             + string(playerClass == GAMBLER_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [4] 🗡️ Assassin           (Cost: 400 XP)   "
             + string(ownsAssassin ? "[OWNED]" : "")
             + string(playerClass == ASSASSIN_CLASS ? " <== Equipped" : "") + "\n");
        slowprint("                                                                          [5] 🔮 Wizard             (Cost: 700 XP)   "
             + string(ownsWizard ? "[OWNED]" : "")
             + string(playerClass == WIZARD_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [6] 🏹 Archer             (Cost: 600 XP)   "
             + string(ownsArcher ? "[OWNED]" : "")
             + string(playerClass == ARCHER_CLASS ? " <== Equipped" : "") + "\n");

        slowprint("                                                                          [7] 🛡️ Tank               (Cost: 500 XP)   "
             + string(ownsTank ? "[OWNED]" : "")
             + string(playerClass == TANK_CLASS ? " <== Equipped" : "") + "\n");


        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint("                                                                          [8] View Class Details\n");
        slowprint("                                                                          [0] Back\n");
        slowprint("                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        slowprint("                                                                         ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏━╸╻ ╻┏━┓╻┏━╸┏━╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━╸            \n");
        slowprint("                                                                         ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃  ┣━┫┃ ┃┃┃  ┣╸    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛          \n");
        slowprint("                                                                         ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹ ╹┗━┛╹┗━╸┗━╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸      \n\n");
        slowprint("                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
        slowprint("                                                                                                ╔════╗                              \n");
        slowprint("                                                                                               ╔║    ║╗                             \n");
        slowprint("                                                                                          ═════╝╚════╝╚═════                        \n" );

        slowprint("\033[2A"); // move UP 2 lines
        slowprint("\033[98C"); // move RIGHT 17 columns (adjust until perfect)


        int c;

        // ================================
        // ERROR-HANDLED INPUT FOR MAIN CHOICE (0–8)
        // ================================
        if (!(cin >> c)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            slowprint("\n");
            slowprint(" \033[1;37;41m ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️ \033[0m\n\n");
            slowprint(" \033[1;48;2;255;255;255m\033[38;2;0;0;0m ➡️ PRESS ANY KEY TO CONTINUE... \033[0m\n");

            cin.get(); // consume leftover '\n'
            cin.get(); // wait for key press
            continue;  // redraw whole menu
        }

        // clean rest of the line
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c < 0 || c > 8) {
            slowprint("\n");
            slowprint(" \033[1;37;41m ⚠️ INVALID CHOICE. PLEASE SELECT BETWEEN 0-8. ⚠️ \033[0m\n\n");
            slowprint(" \033[1;48;2;255;255;255m\033[38;2;0;0;0m ➡️ PRESS ANY KEY TO CONTINUE... \033[0m\n");

            cin.get();
            continue; // redraw menu
        }

        if (c == 0) return;

        // Class info cards
        if (c == 8) {
            int infoChoice;

            system("cls");
            headerClassList();
            ClassListCopy(playerClass, playerXP);

            slowprint("                                                                         ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏━╸╻  ┏━┓┏━┓┏━┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓            \n");
            slowprint("                                                                         ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃  ┃  ┣━┫┗━┓┗━┓   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛         \n");
            slowprint("                                                                         ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸┗━╸╹ ╹┗━┛┗━┛   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸      \n\n");
            slowprint("                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint("                                                                                                ╔════╗                              \n");
            slowprint("                                                                                               ╔║    ║╗                             \n");
            slowprint("                                                                                          ═════╝╚════╝╚═════                        \n" );

            slowprint("\033[2A"); // move UP 2 lines
            slowprint("\033[98C"); // move RIGHT 17 columns (adjust until perfect)

            // ================================
            // ERROR-HANDLED INPUT FOR CLASS INFO CHOICE (1–7)
            // ================================
            if (!(cin >> infoChoice)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                slowprint("\n");
                slowprint(" \033[1;37;41m ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️ \033[0m\n\n");
                slowprint(" \033[1;48;2;255;255;255m\033[38;2;0;0;0m ➡️ PRESS ANY KEY TO CONTINUE... \033[0m\n");

                cin.get();
                cin.get();
                continue;   // go back to main class menu
            }

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (infoChoice < 1 || infoChoice > 7) {
                slowprint("\n");
                slowprint(" \033[1;37;41m ⚠️ INVALID CHOICE. PLEASE SELECT BETWEEN 1-7. ⚠️ \033[0m\n\n");
                slowprint(" \033[1;48;2;255;255;255m\033[38;2;0;0;0m ➡️ PRESS ANY KEY TO CONTINUE... \033[0m\n");

                cin.get();
                continue;
            }

            showClassInfo(infoChoice);
            slowprint("                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            slowprint("\n");
            system("pause");

            continue;
        }

        // Select default (free)
        if (c == 1) {
            playerClass = DEFAULT_CLASS;
            slowprint("Switched to Default Class.\n");
            system("pause");
            continue;
        }

        int cost = 0;
        PlayerClass chosen;

        if (c == 2) { chosen = HERO_CLASS; cost = 5; }
        else if (c == 3) { chosen = GAMBLER_CLASS; cost = 3; }
        else if (c == 4) { chosen = ASSASSIN_CLASS; cost = 4; }
        else if (c == 5) { chosen = WIZARD_CLASS; cost = 7; }
        else if (c == 6) { chosen = ARCHER_CLASS; cost = 6; }
        else if (c == 7) { chosen = TANK_CLASS; cost = 5; }
        else { continue; }

        // If already own → equip it
        if ((chosen == HERO_CLASS && ownsHero) ||
            (chosen == GAMBLER_CLASS && ownsGambler) ||
            (chosen == ASSASSIN_CLASS && ownsAssassin) ||
            (chosen == WIZARD_CLASS && ownsWizard) ||
            (chosen == ARCHER_CLASS && ownsArcher) ||
            (chosen == TANK_CLASS && ownsTank))
        {
            playerClass = chosen;
            slowprint("Class equipped!\n");

            system("pause");
            continue;
        }

        // Not owned → check XP
        if (playerXP < cost) {

            slowprint("\033[5A"); // move UP 2 lines
            slowprint("\033[80C"); // move RIGHT 17 columns (adjust until perfect)
            slowprint("\033[1;37;41m  ⚠️ NOT ENOUGH XP TO BUY THIS CLASS. ⚠️  \033[0m\n");

            system("pause");
            continue;
        }

        // Deduct cost & unlock
        playerXP -= cost;

        if (chosen == HERO_CLASS)   ownsHero   = true;
        if (chosen == GAMBLER_CLASS) ownsGambler = true;
        if (chosen == ASSASSIN_CLASS) ownsAssassin = true;
        if (chosen == WIZARD_CLASS)  ownsWizard  = true;
        if (chosen == ARCHER_CLASS)  ownsArcher  = true;
        if (chosen == TANK_CLASS)    ownsTank    = true;

        playerClass = chosen;

        slowprint("Class purchased and equipped!\n");
        system("pause");
        achievementsNeedUpdate = true;

    }
}




// for the class xp system
void addClassXP(
    int baseXP,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    PlayerClass playerClass,
    int& assassinStreak,
    int& assassinStacks,
    int& wizardCounter,
    int& archerStreak,
    int& tankStacks
) {
    int finalXP = baseXP;

    switch (playerClass) {

    case HERO_CLASS:
        finalXP += 25;
        break;

    case GAMBLER_CLASS: {
        int bonus = rand() % (baseXP + 100);
        bool lose = (rand() % 5 == 0);

        if (lose) {
            finalXP -= bonus;
            if (finalXP < 1) finalXP = 1;
        } else {
            finalXP += bonus;
        }
        break;
    }

    case ASSASSIN_CLASS: {
        assassinStreak++;

        if (assassinStreak >= 3) {
            if (assassinStacks < 10)
                assassinStacks++;

            int percent = 5 * assassinStacks;
            finalXP += (baseXP * percent) / 100;
        }
        break;
    }

    case WIZARD_CLASS: {
        wizardCounter++;   // Count every wizard action

        int wisdomBonus = playerLevel * 5;

        if (wizardCounter % 5 == 0) {
            finalXP += wisdomBonus * 2;  // Critical spell
        }
        else if (wizardCounter % 3 == 0) {
            finalXP += wisdomBonus;      // Spell combo
        }

        // Reset AFTER the bonuses are applied to avoid skipping
        if (wizardCounter >= 5)
            wizardCounter = 0;

        break;
    }

    case ARCHER_CLASS: {

        float hitChance = 80.0f + (playerLevel * 0.5f);
        if (hitChance > 97.0f) hitChance = 97.0f;

        int roll = rand() % 100;

        if (roll < hitChance) {
            archerStreak++;
            if (archerStreak > 15)
                archerStreak = 15;

            // Streak damage XP
            int bonus = (baseXP * (archerStreak * 8)) / 100 + (3 + archerStreak);
            finalXP += bonus;

            // Headshot crit
            int headshotChance = hitChance * 0.20f;
            if (headshotChance > 30) headshotChance = 30;

            if (roll < headshotChance) {
                int crit = baseXP * 2 + (archerStreak * 3);
                finalXP += crit;
            }

            // Perfect shot burst
            if (rand() % 100 < 5) {
                int superCrit = baseXP * 4 + archerStreak * 10;
                finalXP += superCrit;
            }
        }
        else {
            // Soft reset instead of full reset for smoother streaks
            archerStreak = max(0, archerStreak - 2);
        }

        break;
    }

    case TANK_CLASS: {
        tankStacks++;

        int maxStacks = 20 - playerLevel;
        if (maxStacks < 3) maxStacks = 3;

        if (tankStacks > maxStacks)
            tankStacks = maxStacks;

        int percentBonus = (baseXP * (tankStacks * 4)) / 100;
        int flatBonus = tankStacks / 2;

        finalXP += percentBonus + flatBonus;

        break;
    }

    default:
        break;
    }

    // Apply XP to actual player XP
    addXP(finalXP, gamificationEnabled, playerXP, playerLevel);
}


// -----------------------------
// XP PROGRESS BAR 
// -----------------------------
string getXPBar(int xp) {

    // XP needed to reach next level (always 100)
    int currentXP = xp % 100;

    // Calculate how many of the 12 blocks are filled
    int filled = (currentXP * 12) / 100;

    string bar = "[";

    // Build the bar manually
    for (int i = 0; i < filled; i++)
        bar += "█";   // filled segment
        
    for (int i = filled; i < 12; i++)
        bar += "-";   // empty segment

    bar += "]";

    return bar;
}

// -------------------------
// PLAYER PROGRESS BAR  
// -------------------------
string getProgressBar(float percent) {
    int filled = percent / 5;  // 0–20 blocks
    string bar = "[";
    for (int i = 0; i < 20; i++) {
        bar += (i < filled ? "█" : "-");
    }
    bar += "]";
    return bar;
}


// ------------------------------------------------------------
// Initialize All Achievement Definitions
// (Names, Badges, Unlock Flags, XP Rewards)
// ------------------------------------------------------------
void initAchievements(
    vector<string>& achievementNames,      // Names of each achievement
    vector<string>& achievementBadges,     // Badge / emoji shown when unlocked
    vector<int>& achievementUnlocked,      // 0 = locked, 1 = unlocked
    vector<int>& achievementXPRewards      // XP gained when unlocked
) {
    int i;

    // Clear all existing data
    achievementNames.clear();
    achievementBadges.clear();
    achievementUnlocked.clear();
    achievementXPRewards.clear();


    // ============================================================
    // PRODUCTIVITY ACHIEVEMENTS
    // ============================================================

    // Add First Item
  
    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Add First Item";
    achievementBadges[i] = "🔹";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 10;


    // Add 10 Items
    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Add 10 Items";
    achievementBadges[i] = "🟩";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 20;


    // Add 50 Items
    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Add 50 Items";
    achievementBadges[i] = "🟪";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 50;



    // ============================================================
    // COMPLETION ACHIEVEMENTS
    // ============================================================

    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Complete First Item";
    achievementBadges[i] = "🔸";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 10;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Complete 10 Items";
    achievementBadges[i] = "🟨";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 25;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Complete 50 Items";
    achievementBadges[i] = "🟫";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 50;



    // ============================================================
    // LIST CREATION ACHIEVEMENTS
    // ============================================================

    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Create First List";
    achievementBadges[i] = "📘";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 10;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Create 5 Lists";
    achievementBadges[i] = "📗";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 25;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Create 10 Lists";
    achievementBadges[i] = "📕";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 50;



    // ============================================================
    // LEVEL ACHIEVEMENTS
    // ============================================================

    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Reach Level 3";
    achievementBadges[i] = "⭐";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 20;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Reach Level 5";
    achievementBadges[i] = "🌟";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 30;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Reach Level 10";
    achievementBadges[i] = "🏆";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 50;



    // ============================================================
    // DAILY STREAK ACHIEVEMENTS
    // ============================================================

    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "1-Day Streak";
    achievementBadges[i] = "✨";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 10;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "3-Day Streak";
    achievementBadges[i] = "🔥";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 20;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "7-Day Streak";
    achievementBadges[i] = "🏅";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 40;



    // ============================================================
    // CLASS UNLOCK ACHIEVEMENTS
    // ============================================================

    // Unlock ANY class
    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock First Class";
    achievementBadges[i] = "🎉";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 20;


    // -------- Individual Class Unlocks --------

    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock Hero Class";
    achievementBadges[i] = "🦸";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 25;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock Gambler Class";
    achievementBadges[i] = "🎲";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 25;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock Assassin Class";
    achievementBadges[i] = "🗡️";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 25;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock Wizard Class";
    achievementBadges[i] = "🔮";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 30;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock Archer Class";
    achievementBadges[i] = "🏹";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 30;


    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock Tank Class";
    achievementBadges[i] = "🛡️";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 25;


    // -------- Unlock ALL Classes --------

    i = achievementNames.size();
    achievementNames.resize(i + 1);
    achievementBadges.resize(i + 1);
    achievementUnlocked.resize(i + 1);
    achievementXPRewards.resize(i + 1);

    achievementNames[i] = "Unlock All Classes";
    achievementBadges[i] = "👑";
    achievementUnlocked[i] = 0;
    achievementXPRewards[i] = 100;
}

void headerAchievementList() {

        slowprint("                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint("                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint("                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint("              █████╗  ██████╗██╗  ██╗██╗███████╗██╗   ██╗███████╗███╗   ███╗███████╗███╗   ██╗████████╗███████╗         █████╗ ███╗   ██╗██████╗     ██████╗  █████╗ ██████╗  ██████╗ ███████╗███████╗   \n");
        slowprint("             ██╔══██║██║     ██╔══██║██║██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ╚════██║        ██╔══██║██║╚██╗██║██║  ██║    ██╔══██╗██╔══██║██║  ██║██║   ██║██╔══╝  ╚════██║       \n");
        slowprint("             ██║  ██║╚██████╗██║  ██║██║███████╗ ╚████╔╝ ███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ███████║        ██║  ██║██║ ╚████║██████╔╝    ██████╔╝██║  ██║██████╔╝╚██████╔╝███████╗███████║      \n");
        slowprint("             ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚═╝╚══════╝  ╚═══╝  ╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝        ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝     ╚═════╝ ╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚══════╝╚══════╝          \n");
        slowprint("                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}


// ----------------------------------
// Achievement Evaluation & Unlock
// ----------------------------------
void checkAchievements(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string>>>& list_of_descriptions,
    vector<string>& achNames,
    vector<string>& achBadges,
    vector<int>& achUnlocked,
    vector<int>& achXP,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    int& streakCount,
    int& lastActiveDay,
    int cmonth,
    int cdate,
    int cyear
) {

  
    int i, j, totalItems, totalCompleted, totalLists, currentDay;
    totalLists = name_of_list.size();
    totalItems = 0; totalCompleted = 0;
    int totalClassesOwned =
    (ownsHero ? 1 : 0) +
    (ownsGambler ? 1 : 0) +
    (ownsAssassin ? 1 : 0) +
    (ownsWizard ? 1 : 0) +
    (ownsArcher ? 1 : 0) +
    (ownsTank ? 1 : 0);


    for (i = 0; i < (int)list_of_lists.size(); i++) {
        totalItems += list_of_lists[i].size();
        for (j = 0; j < (int)list_of_lists[i].size(); j++) {
            if (list_of_lists[i][j].find("✅") != string::npos)
                totalCompleted++;
        }
    }

    currentDay = cdate;

    if (cdate > 0) {
        if (lastActiveDay == 0) {
            streakCount = 1; lastActiveDay = currentDay;
        } else if (lastActiveDay == currentDay) {
            // same day, do nothing
        } else if (lastActiveDay + 1 == currentDay) {
            streakCount++; lastActiveDay = currentDay;
        } else {
            streakCount = 1; lastActiveDay = currentDay;
        }
    }

for (i = 0; i < (int)achNames.size(); i++) {
    // Skip if already unlocked
    if (achUnlocked[i]) continue;

    // -----------------------------
    // ADD FIRST ITEM
    // -----------------------------
    if (achNames[i] == "Add First Item" && totalItems >= 1) {
        achUnlocked[i] = 1;
        
        slowprint("\n");
        slowprint("\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint("\n");
        slowprint("\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
              " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // ADD ITEMS
    // -----------------------------
    if (achNames[i] == "Add 10 Items" && totalItems >= 10) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint("\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Add 50 Items" && totalItems >= 50) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // COMPLETE ITEMS
    // -----------------------------
    if (achNames[i] == "Complete First Item" && totalCompleted >= 1) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Complete 10 Items" && totalCompleted >= 10) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Complete 50 Items" && totalCompleted >= 50) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // CREATE LISTS
    // -----------------------------
    if (achNames[i] == "Create First List" && totalLists >= 1) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Create 5 Lists" && totalLists >= 5) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Create 10 Lists" && totalLists >= 10) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // REACH LEVELS
    // -----------------------------
    if (achNames[i] == "Reach Level 3" && playerLevel >= 3) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Reach Level 5" && playerLevel >= 5) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Reach Level 10" && playerLevel >= 10) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // STREAK ACHIEVEMENTS
    // -----------------------------
    if (achNames[i] == "1-Day Streak" && streakCount >= 1) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "3-Day Streak" && streakCount >= 3) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "7-Day Streak" && streakCount >= 7) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // CLASS UNLOCKS (TOTAL & PER CLASS)
    // -----------------------------
    if (achNames[i] == "Unlock First Class" && totalClassesOwned >= 1) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // Individual class unlocks
    if (achNames[i] == "Unlock Hero Class" && ownsHero) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Unlock Gambler Class" && ownsGambler) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Unlock Assassin Class" && ownsAssassin) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Unlock Wizard Class" && ownsWizard) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Unlock Archer Class" && ownsArcher) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    if (achNames[i] == "Unlock Tank Class" && ownsTank) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

    // -----------------------------
    // UNLOCK ALL CLASSES
    // -----------------------------
    if (achNames[i] == "Unlock All Classes" && totalClassesOwned == 6) {
        achUnlocked[i] = 1;

        slowprint( "\n");
        slowprint( "\033[1;37;42m ✔ ACHIEVEMENT UNLOCKED! \033[0m\n");
        slowprint( "\n");
        slowprint( "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  "
             + achBadges[i] + " " + achNames[i]
             + " (+" + to_string(achXP[i]) + " XP)  "
             + " \033[0m\n\n");
        slowprint( "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        cin.get();

        addClassXP(achXP[i], gamificationEnabled, playerXP, playerLevel,
                   playerClass, assassinStreak, assassinStacks,
                   wizardCounter, archerStreak, tankStacks);
        continue;
    }

}


   // slowprint( "-------------------------------------");
}


// -------------------------
// SEARCH ITEMS IN A LIST
// -------------------------
void searchItems(const vector<string>& items) {
    cin.ignore();   // clear leftover newline
    string key;     // keyword user wants to search for

    slowprint( "\n=====================================\n");
    slowprint( "            SEARCH ITEMS             \n");
    slowprint( "=====================================\n");

    slowprint( "Enter keyword to search: ");
    getline(cin, key);

    slowprint( "\n-------------- RESULTS --------------\n");

    bool found = false;   // tracks if any item matches

    // Search through all items in the list
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].find(key) != string::npos) {   // substring match
            slowprint( " " + to_string(i + 1) + ". " + items[i] + "\n");
            found = true;
        }
    }

    // No results
    if (!found) {
        slowprint( "( No matching items found )\n");
    }

    slowprint( "-------------------------------------\n");
    slowprint( "Press Enter to continue...");
    cin.get();
}

// Live summary box used everywhere
void headerNewList() {

        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ███╗   ██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n");
        slowprint( "                                               ██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ████╗  ██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══╝      \n");
        slowprint( "                                               ██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║           \n");
        slowprint( "                                               ██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n");
        slowprint( "                                               ╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║ ╚████║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║        \n");
        slowprint( "                                                ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝            \n");
        slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}


// Live summary box used everywhere
void printLiveSummary(
    const string& title,
    const string& category,
    const string& deadline,
    const string& deadlinePriority,
    const string& notes
) {

        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ███╗   ██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n");
        slowprint( "                                               ██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ████╗  ██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══╝      \n");
        slowprint( "                                               ██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║           \n");
        slowprint( "                                               ██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n");
        slowprint( "                                               ╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║ ╚████║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║        \n");
        slowprint( "                                                ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝            \n");
        slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
        slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint( "                                                                                              𝗧𝗔𝗟𝗟𝗬++ 𝗟𝗜𝗦𝗧 𝗦𝗨𝗠𝗠𝗔𝗥𝗬\n");
        slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint( "                                                                             [1] 📄 TITLE      : " + (title.empty() ? "<not set>" : title) + "\n");
        slowprint( "                                                                             [2] 🗂️ CATEGORY   : " + (category.empty() ? "<not set>" : category) + "\n");
        slowprint( "                                                                             [3] 🗓️ DEADLINE   : " + (deadline.empty() ? "<none>" : deadline) + "\n");
        slowprint( "                                                                             [4] ❗ PRIORITY   : " + (deadlinePriority.empty() ? "<none>" : deadlinePriority) + "\n");
        slowprint( "                                                                             [5] 📝 NOTES      : " + (notes.empty() ? "<none>" : notes) + "\n");
        slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint( "                                               ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  \n\n");
}

// Live summary box used everywhere
// NEW: Live list view (title + items + descriptions)
void printListLive(
    const string& title,
    const vector<string>& items,
    const vector<vector<string>>& descriptions,
    int highlightedItem = -1,     // which item index to highlight (0-based)
    int highlightedDesc  = -1     // which description index to highlight (0-based)

    
) {


    slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
    slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
    slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
    slowprint( "                                                ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ███╗   ██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n");
    slowprint( "                                               ██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ████╗  ██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══╝      \n");
    slowprint( "                                               ██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║           \n");
    slowprint( "                                               ██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n");
    slowprint( "                                               ╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║ ╚████║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║        \n");
    slowprint( "                                                ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝            \n");
    slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
      
    slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    slowprint( "                                                                                𝐋𝐈𝐒𝐓:: " + (title.empty() ? "<no title yet>" : title) + "\n");
    slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n\n");

    // If no items yet, show a hint
    if (items.empty()) {
        return;
    }


  // Print each item as:  ⃝  Item Name
for (size_t i = 0; i < items.size(); ++i) {
    bool highlightThisItem = (static_cast<int>(i) == highlightedItem);

    // Keep original spacing EXACT
    slowprint( "                                                                             〇 ");

    // Highlight item (inverse white bg + black text)
    if (highlightThisItem) {
        slowprint( "\033[7m");   // inverse only
    } else {
        slowprint( "\033[1m");   // bold only
    }

    slowprint( items[i] + "\033[0m\n");  // reset


    // Print descriptions (italic, highlight with inverse)
    if (i < descriptions.size()) {
        for (size_t d = 0; d < descriptions[i].size(); ++d) {
            bool highlightThisDesc =
                highlightThisItem && (static_cast<int>(d) == highlightedDesc);

            // Keep original spacing EXACT
            slowprint( "                                                                                • ");

            if (highlightThisDesc) {
                slowprint( "\033[7;3m");  // inverse + italic
            } else {
                slowprint( "\033[3m");    // italic only
            }

            slowprint( descriptions[i][d] + "\033[0m\n"); // reset
        }
    }

    slowprint( "\n"); // space between items
}




    slowprint( "\n                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");

}



// Function to create a new list
void createNewList(
  vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string>>>& list_of_descriptions,
    vector<string>& list_categories,
    vector<string>& list_deadlines,
    vector<string>& list_priorities,
    vector<string>& list_notes,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear, 
    vector<int>& monthcreated,
    vector<int>& datecreated,
    vector<int>& yearcreated,
    int cmonth,
    int cdate,
    int cyear
) {
    system("cls");

    // ===================================================
    // VARIABLE DECLARATIONS (ALL MOVED TO TOP)
    // ===================================================

    string title;                        // The title/name of the new list
    string item;                         // Stores each item typed by the user
    string descLine;
    int cremonth, credate, creyear;                     // Stores each description line entered
    int month, date, year;               // Deadline date components
    int categoryInput;
    string category;

    int deadlineStatus;
    int deadlineChoice;
    string deadline;

    string deadlinePriority;
    int deadlinePrioChoice;

    string notes;
    int noteChoice;

    int confirmationValue;



    vector<string> items;                // Holds all items belonging to this list
    vector<vector<string>> descriptions; // Holds descriptions for all items
    vector<int> months;
    vector<int> dates;
    vector<int> years;
    vector<string> tempDescriptions;     // Temporary storage for current item's descriptions
    int Mindex = 0;
    int Dindex = 0;
    int Yindex = 0;
    int index = 0;                       // Index for adding new item
    int dindex = 0;                      // Index for adding a description
    int dsaveIndex = 0;                  // Index for saving full description set

    // ===================================================
    // GET LIST TITLE
    // ===================================================

                                                                                                                 

    cin.ignore();
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

    slowprint( "                                                                                ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸            \n");
    slowprint( "                                                                                ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸            \n");
    slowprint( "                                                                                ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸             \n\n");

    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");

    slowprint( "                                                                                      ╔════════════════════════╗                              \n");
    slowprint( "                                                                                     ╔║                        ║╗                             \n");
    slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 
        
    slowprint( "\033[2A"); // move UP 2 lines
    slowprint( "\033[87C"); // move RIGHT 17 columns (adjust until perfect)

    getline(cin, title);

    // ===================================================
    // ITEM Category
    // ===================================================

    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);
   
    slowprint( "                                                           ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ┏━┓   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓             \n");
    slowprint( "                                                           ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸    ┣━┫   ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃             \n");
    slowprint( "                                                           ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╹ ╹   ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹    ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹             \n\n");

    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    slowprint( "                                                                                 [𝟏] 💼 WORK         [𝟔] ❤️‍🩹 HEALTH \n");
    slowprint( "                                                                                 [𝟐] 🏫 SCHOOL       [𝟕] 📅 APPOINTMENT \n");
    slowprint( "                                                                                 [𝟑] 👤 PERSONAL     [𝟖] 🛒 SHOPPING \n");
    slowprint( "                                                                                 [𝟒] 🧹 ERRANDS      [𝟗] ➕ OTHERS \n");
    slowprint( "                                                                                 [𝟓] 💰 FINANCE      [𝟏𝟎]⛔ NONE\n");
    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    slowprint( "                                                                                                ╔════╗                              \n");
    slowprint( "                                                                                               ╔║    ║╗                             \n");
    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
        
    slowprint( "\033[2A"); // move UP 2 lines
    slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

    while (true)
    {
        cin >> categoryInput;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        slowprint( "Invalid input. Please try again.\n");
    }

    while(categoryInput < 1 || categoryInput >10){

        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);
    
            slowprint( "                                                           ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ┏━┓   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓             \n");
            slowprint( "                                                           ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸    ┣━┫   ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃             \n");
            slowprint( "                                                           ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╹ ╹   ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹    ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹             \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
            slowprint( "                                                                                 [𝟏] 💼 WORK         [𝟔] ❤️‍🩹 HEALTH \n");
            slowprint( "                                                                                 [𝟐] 🏫 SCHOOL       [𝟕] 📅 APPOINTMENT \n");
            slowprint( "                                                                                 [𝟑] 👤 PERSONAL     [𝟖] 🛒 SHOPPING \n");
            slowprint( "                                                                                 [𝟒] 🧹 ERRANDS      [𝟗] ➕ OTHERS \n");
            slowprint( "                                                                                 [𝟓] 💰 FINANCE      [𝟏𝟎]⛔ NONE\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

            slowprint( "\033[12A"); // move UP 2 lines
            slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                        slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");

            cin >> categoryInput;
    }

    switch(categoryInput){
        case 1: category = "Work";
            break;
        
        case 2: category = "School";
            break;

        case 3: category = "Personal";
            break;

        case 4: category = "Errands";
            break;

        case 5: category = "Finance";
            break;

        case 6: category = "Health";
            break;

        case 7: category = "Appoinment";
            break;

        case 8: category = "Shopping";
            break;

        case 9: category = "Others";
            break;

        case 10: category = "None";
            break;
    }

    // ===================================================
    // ITEM Deadline
    // ===================================================
    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

    slowprint( "                                                                                   ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸┏━┓            \n");
    slowprint( "                                                                                   ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸  ╺┛            \n");
    slowprint( "                                                                                   ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸ ╹             \n\n");

    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
    slowprint( "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n");
    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
    slowprint( "                                                                                                ╔════╗                              \n");
    slowprint( "                                                                                               ╔║    ║╗                             \n");
    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
        
    slowprint( "\033[2A"); // move UP 2 lines
    slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)
    while (true)
    {
        cin >> deadlineStatus;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        slowprint( "Invalid input. Please try again.\n");
    }
    while(deadlineStatus < 1 || deadlineStatus > 2){

        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                                   ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸┏━┓            \n");
        slowprint( "                                                                                   ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸  ╺┛            \n");
        slowprint( "                                                                                   ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸ ╹             \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

        slowprint( "\033[8A"); // move UP 2 lines
        slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                    slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");
        cin >> deadlineStatus;
    }

    if(deadlineStatus == 1){
        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                              ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸            \n");
        slowprint( "                                                                              ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸           \n");
        slowprint( "                                                                              ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸           \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                 [𝟏] 🗓️ TODAY         [𝟐] 🗓️ TOMMOROW \n");
        slowprint( "                                                                                 [𝟑] 🗓️ THIS WEEK     [𝟒] 🗓️ NEXT WEEK \n");
        slowprint( "                                                                                 [𝟓] 🗓️ THIS MONTH    [𝟔] 🗓️ NEXT MNTH \n");
        slowprint( "                                                                                            [𝟕] ⚙️ CUSTOM    \n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
            
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

        cin.ignore();
        while (true)
        {
            cin >> deadlineChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            slowprint( "Invalid input. Please try again.\n");
        }

        while(deadlineChoice < 1 || deadlineChoice > 7){

            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                              ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸            \n");
            slowprint( "                                                                              ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸           \n");
            slowprint( "                                                                              ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸           \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                 [𝟏] 🗓️ TODAY         [𝟐] 🗓️ TOMMOROW \n");
            slowprint( "                                                                                 [𝟑] 🗓️ THIS WEEK     [𝟒] 🗓️ NEXT WEEK \n");
            slowprint( "                                                                                 [𝟓] 🗓️ THIS MONTH    [𝟔] 🗓️ NEXT MNTH \n");
            slowprint( "                                                                                            [𝟕] ⚙️ CUSTOM    \n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

            slowprint( "\033[11A"); // move UP 2 lines
            slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                    slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");
            cin >> deadlineChoice;
        }

        switch(deadlineChoice){
            case 1: deadline = "Today";
                break;

            case 2: deadline = "Tommorow";
                break;

            case 3: deadline = "This Week";
                break;

            case 4: deadline = "Next Week";
                break;

            case 5: deadline = "This Month";
                break;
            case 6: deadline = "Next Month";
                break;

        case 7:
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                                   ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┳┓┏━┓┏┓╻╺┳╸╻ ╻            \n");
            slowprint( "                                                                                   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┃┃┃ ┃┃┗┫ ┃ ┣━┫           \n");
            slowprint( "                                                                                   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━┛╹ ╹ ╹ ╹ ╹           \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

            slowprint( "\033[2A"); // move UP 2 lines
            slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

        
                do
                {
                    while (true)
                    {
                        cin >> month;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        slowprint( "Invalid input. Please try again.\n");
                    }
                    if (month < 1 || month > 12)
                    {
                        slowprint( "Try again\n");
                    }
                } while (month < 1 || month > 12);
                Mindex = months.size();
                months.resize(Mindex + 1);
                months[Mindex] = month;

                    system("cls");
                    printLiveSummary(title, category, deadline, deadlinePriority, notes);

                    slowprint( "                                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━╸┏━┓┏━┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓            \n");
                    slowprint( "                                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┣╸ ┣━┫┣┳┛   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛           \n");
                    slowprint( "                                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━╸╹ ╹╹┗╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸         \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
                    slowprint( "                                                                                                ╔════╗                              \n");
                    slowprint( "                                                                                               ╔║    ║╗                             \n");
                    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

                    slowprint( "\033[2A"); // move UP 2 lines
                    slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)
                do
                {
                    while (true)
                    {
                        cin >> year;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        slowprint( "Invalid input. Please try again.\n");
                    }
                    if (year < 2000 || year > 2100)
                    {
                        slowprint( "Try again\n");
                    }
                } while (year < 2000 || year > 2100);
                Yindex = years.size();
                years.resize(Yindex + 1);
                years[Yindex] = year;

                    system("cls");
                    printLiveSummary(title, category, deadline, deadlinePriority, notes);

                    slowprint( "                                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╺┳┓┏━┓╺┳╸┏━╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓            \n");
                    slowprint( "                                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛    ┃┃┣━┫ ┃ ┣╸    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛           \n");
                    slowprint( "                                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╺┻┛╹ ╹ ╹ ┗━╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸         \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
                    slowprint( "                                                                                                ╔════╗                              \n");
                    slowprint( "                                                                                               ╔║    ║╗                             \n");
                    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

                    slowprint( "\033[2A"); // move UP 2 lines
                    slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

                switch (month)
                {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    do
                    {
                        while (true)
                        {
                            cin >> date;
                            if (!cin.fail()) break;
                            cin.clear();
                            cin.ignore(1000 , '\n');
                            slowprint( "Invalid input. Please try again.\n");
                        }
                        if (date < 1 || date > 31)
                        {
                            slowprint( "Try again\n");
                        }
                        
                    } while (date < 1 || date > 31);
                        break;
                
                case 4:
                case 6:
                case 9:
                case 11:
                    do
                    {
                        while (true)
                        {
                            cin >> date;
                            if (!cin.fail()) break;
                            cin.clear();
                            cin.ignore(1000 , '\n');
                            slowprint( "Invalid input. Please try again.\n");
                        }
                        if (date < 1 || date > 30)
                        {
                            slowprint( "Try again\n");
                        }
                        
                    } while (date < 1 || date > 30);    
                        break;

                case 2:
                    if (((year%4 == 0 && year%100 != 0) || (year%400 == 0)))
                    {
                        do
                        {
                            while (true)
                            {
                                cin >> date;
                                if (!cin.fail()) break;
                                cin.clear();
                                cin.ignore(1000 , '\n');
                                slowprint( "Invalid input. Please try again.\n");
                            }
                            if (date < 1 || date > 29)
                            {
                                slowprint( "Try again\n");
                            }
                            
                        } while (date < 1 || date > 29); 
                    }
                    else
                    {
                        do
                        {
                            while (true)
                            {
                                cin >> date;
                                if (!cin.fail()) break;
                                cin.clear();
                                cin.ignore(1000 , '\n');
                                slowprint( "Invalid input. Please try again.\n");
                            }
                            if (date < 1 || date > 28)
                            {
                                slowprint( "Try again\n");
                            }
                            
                        } while (date < 1 || date > 28);
                    }
                    break;
                }

                Dindex = dates.size();
                dates.resize(Dindex + 1);
                dates[Dindex] = date;

                // 🔹 NEW: show custom date in live summary as MM/DD/YYYY
                deadline = to_string(month) + "/" + to_string(date) + "/" + to_string(year);

                break;

        }

        cin.ignore();
        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                 ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻             \n");
        slowprint( "                                                                 ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛           \n");
        slowprint( "                                                                 ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹           \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                 [𝟏] ⚠️ CRITICAL         [𝟐] 🟠 MEDIUM \n");
        slowprint( "                                                                                 [𝟑] 🔴 HIGH             [𝟒] 🟢 LOW \n");
        slowprint( "                                                                                            [𝟓] ⛔ NONE    \n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
            
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)
        while (true)
        {
            cin >> deadlinePrioChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            slowprint( "Invalid input. Please try again.\n");
        }

        while(deadlinePrioChoice < 1 || deadlinePrioChoice > 5){

            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                 ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻             \n");
            slowprint( "                                                                 ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛           \n");
            slowprint( "                                                                 ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹           \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                 [𝟏] ⚠️ CRITICAL         [𝟐] 🟠 MEDIUM \n");
            slowprint( "                                                                                 [𝟑] 🔴 HIGH             [𝟒] 🟢 LOW \n");
            slowprint( "                                                                                            [𝟓] ⛔ NONE    \n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

            slowprint( "\033[10A"); // move UP 2 lines
            slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                    slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");
            cin >> deadlinePrioChoice;
        }

        switch(deadlinePrioChoice){
            case 1: deadlinePriority = "Critical";
                break;

            case 2: deadlinePriority = "High";
                break;

            case 3: deadlinePriority = "Medium";
                break;

            case 4: deadlinePriority = "Low";
                break;

            case 5: deadlinePriority = "None";
                break;
        }
    }
    
    // ===================================================
    // ITEM NOTES
    // ===================================================

    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                                     ┏━┓╺┳┓╺┳┓   ┏┓╻┏━┓╺┳╸┏━╸┏━┓┏━┓            \n");
        slowprint( "                                                                                     ┣━┫ ┃┃ ┃┃   ┃┗┫┃ ┃ ┃ ┣╸ ┗━┓ ╺┛           \n");
        slowprint( "                                                                                     ╹ ╹╺┻┛╺┻┛   ╹ ╹┗━┛ ╹ ┗━╸┗━┛ ╹          \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
            
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

    while (true)
    {
        cin >> noteChoice;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        slowprint( "Invalid input. Please try again.\n");
    }

    while(noteChoice < 1 || noteChoice > 2){

        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                                     ┏━┓╺┳┓╺┳┓   ┏┓╻┏━┓╺┳╸┏━╸┏━┓┏━┓            \n");
            slowprint( "                                                                                     ┣━┫ ┃┃ ┃┃   ┃┗┫┃ ┃ ┃ ┣╸ ┗━┓ ╺┛           \n");
            slowprint( "                                                                                     ╹ ╹╺┻┛╺┻┛   ╹ ╹┗━┛ ╹ ┗━╸┗━┛ ╹          \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

            slowprint( "\033[8A"); // move UP 2 lines
            slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                    slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");
        cin >> noteChoice;
    }

    if(noteChoice == 1){
    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                                     ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━┓╺┳╸┏━╸            \n");
        slowprint( "                                                                                     ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┃ ┃ ┃ ┣╸          \n");
        slowprint( "                                                                                     ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━┛ ╹ ┗━╸          \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                      ╔════════════════════════╗                              \n");
        slowprint( "                                                                                     ╔║                        ║╗                             \n");
        slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 
            
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

        cin.ignore();
        getline(cin, notes); 
    }

    // ===================================================
    // ITEM SUMMARY
    // ===================================================

 while (true) {
    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                                   ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓   ╻  ╻┏━┓╺┳╸┏━┓             \n");
        slowprint( "                                                                                   ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃   ┃  ┃┗━┓ ┃  ╺┛           \n");
        slowprint( "                                                                                   ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹   ┗━╸╹┗━┛ ╹  ╹           \n\n");

        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                         [𝟏-𝟓] ⚠️ EDIT A FIELD      [𝟔] 🟠 CONFIRM AND CREATE           \n");
        slowprint( "                                                                                            [𝟕] ⛔ CANCEL                              \n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
            
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)
    
    while (true)
    {
        cin >> confirmationValue;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        slowprint( "Invalid input. Please try again.\n");
    }

    // Make sure leftover newline won't affect getline()
    cin.ignore();

    if (confirmationValue == 6) break;  // Continue to items

    if (confirmationValue == 7){
        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        slowprint( "                                                                   ╻  ╻┏━┓╺┳╸   ┏━╸┏━┓┏━╸┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓             \n");
        slowprint( "                                                                   ┃  ┃┗━┓ ┃    ┃  ┣┳┛┣╸ ┣━┫ ┃ ┃┃ ┃┃┗┫   ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃           \n");
        slowprint( "                                                                   ┗━╸╹┗━┛ ╹    ┗━╸╹┗╸┗━╸╹ ╹ ╹ ╹┗━┛╹ ╹   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛          \n\n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                       PRESS ENTER TO CONTINUE..                              \n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        cin.get();
        return;
    } 

    switch (confirmationValue) {

        case 1: {
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);
               
            slowprint( "                                                                                ┏━╸╺┳┓╻╺┳╸   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸            \n");
            slowprint( "                                                                                ┣╸  ┃┃┃ ┃    ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸             \n");
            slowprint( "                                                                                ┗━╸╺┻┛╹ ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸             \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");

            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
            slowprint( "                                                                                     ╔║                        ║╗                             \n");
            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 
                
            slowprint( "\033[2A"); // move UP 2 lines
            slowprint( "\033[87C"); // move RIGHT 17 columns (adjust until perfect)

            getline(cin, title);

            break;
        }

        case 2: {
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                                   ┏━╸╺┳┓╻╺┳╸   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻             \n");
            slowprint( "                                                                                   ┣╸  ┃┃┃ ┃    ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛             \n");
            slowprint( "                                                                                   ┗━╸╺┻┛╹ ╹    ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹              \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
            slowprint( "                                                                                 [𝟏] 💼 WORK         [𝟔] ❤️‍🩹 HEALTH \n");
            slowprint( "                                                                                 [𝟐] 🏫 SCHOOL       [𝟕] 📅 APPOINTMENT \n");
            slowprint( "                                                                                 [𝟑] 👤 PERSONAL     [𝟖] 🛒 SHOPPING \n");
            slowprint( "                                                                                 [𝟒] 🧹 ERRANDS      [𝟗] ➕ OTHERS \n");
            slowprint( "                                                                                 [𝟓] 💰 FINANCE      [𝟏𝟎]⛔ NONE\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
                
            slowprint( "\033[4A"); // move UP 2 lines
            slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)
            int cat;

            while (true)
            {
                cin >> cat;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                 slowprint( "\033[5A"); // move UP 2 lines
                 slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                    slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");
            }
            cin.ignore();

            const string categories[] = {
                "Work","School","Personal","Errands",
                "Finance","Health","Appointment",
                "Shopping","Others","None"
            };
            if (cat >= 1 && cat <= 10) category = categories[cat - 1];
            break;
        }

        case 3: {
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                                   ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸            \n");
            slowprint( "                                                                                   ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸           \n");
            slowprint( "                                                                                   ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸           \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                 [𝟏] 🗓️ TODAY         [𝟐] 🗓️ TOMMOROW \n");
            slowprint( "                                                                                 [𝟑] 🗓️ THIS WEEK     [𝟒] 🗓️ NEXT WEEK \n");
            slowprint( "                                                                                 [𝟓] 🗓️ THIS MONTH    [𝟔] 🗓️ NEXT MNTH \n");
            slowprint( "                                                                                            [𝟕] ⚙️ CUSTOM    \n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

            slowprint( "\033[4A"); // move UP 2 lines
            slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

            int d;

            while (true)
            {
                cin >> d;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                slowprint( "Invalid input. Please try again.\n");
            }
            cin.ignore();

            // ✅ Predefined shortcuts (1–6)
            if (d >= 1 && d <= 6) {
                switch (d) {
                    case 1: deadline = "Today";       break;
                    case 2: deadline = "Tomorrow";    break;
                    case 3: deadline = "This Week";   break;
                    case 4: deadline = "Next Week";   break;
                    case 5: deadline = "This Month";  break;
                    case 6: deadline = "Next Month";  break;
                }
            }
            // ✅ Custom date (7) – same logic as earlier case 7
            else if (d == 7) {
                system("cls");
                printLiveSummary(title, category, deadline, deadlinePriority, notes);

                slowprint( "                                                                                   ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┳┓┏━┓┏┓╻╺┳╸╻ ╻            \n");
                slowprint( "                                                                                   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┃┃┃ ┃┃┗┫ ┃ ┣━┫           \n");
                slowprint( "                                                                                   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━┛╹ ╹ ╹ ╹ ╹           \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

                slowprint( "\033[2A"); // move UP 2 lines
                slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

                // 🔹 MONTH
                do
                {
                    while (true)
                    {
                        cin >> month;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        slowprint( "Invalid input. Please try again.\n");
                    }
                    if (month < 1 || month > 12)
                    {
                        slowprint( "Try again\n");
                    }
                } while (month < 1 || month > 12);
                Mindex = months.size();
                months.resize(Mindex + 1);
                months[Mindex] = month;

                // 🔹 YEAR
                system("cls");
                printLiveSummary(title, category, deadline, deadlinePriority, notes);

                slowprint( "                                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━╸┏━┓┏━┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓            \n");
                slowprint( "                                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┣╸ ┣━┫┣┳┛   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛           \n");
                slowprint( "                                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━╸╹ ╹╹┗╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸         \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

                slowprint( "\033[2A"); // move UP 2 lines
                slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

                do
                {
                    while (true)
                    {
                        cin >> year;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        slowprint( "Invalid input. Please try again.\n");
                    }
                    if (year < 2000 || year > 2100)
                    {
                        slowprint( "Try again\n");
                    }
                } while (year < 2000 || year > 2100);
                Yindex = years.size();
                years.resize(Yindex + 1);
                years[Yindex] = year;

                // 🔹 DATE (day)
                system("cls");
                printLiveSummary(title, category, deadline, deadlinePriority, notes);

                slowprint( "                                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╺┳┓┏━╓╺┳╸┏━╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━╓            \n");
                slowprint( "                                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛    ┃┃┣━┫ ┃ ┣╸    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛           \n");
                slowprint( "                                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╺┻┛╹ ╹ ╹ ┗━╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸         \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 

                slowprint( "\033[2A"); // move UP 2 lines
                slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

                switch (month)
                {
                    case 1: case 3: case 5: case 7:
                    case 8: case 10: case 12:
                        do
                        {
                            while (true)
                            {
                                cin >> date;
                                if (!cin.fail()) break;
                                cin.clear();
                                cin.ignore(1000 , '\n');
                                slowprint( "Invalid input. Please try again.\n");
                            }
                            if (date < 1 || date > 31)
                            {
                                slowprint( "Try again\n");
                            }
                        } while (date < 1 || date > 31);
                        break;

                    case 4: case 6: case 9: case 11:
                        do
                        {
                            while (true)
                            {
                                cin >> date;
                                if (!cin.fail()) break;
                                cin.clear();
                                cin.ignore(1000 , '\n');
                                slowprint( "Invalid input. Please try again.\n");
                            }
                            if (date < 1 || date > 30)
                            {
                                slowprint( "Try again\n");
                            }
                        } while (date < 1 || date > 30);
                        break;

                    case 2:
                        if (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
                        {
                            do
                            {
                                while (true)
                                {
                                    cin >> date;
                                    if (!cin.fail()) break;
                                    cin.clear();
                                    cin.ignore(1000 , '\n');
                                    slowprint( "Invalid input. Please try again.\n");
                                }
                                if (date < 1 || date > 29)
                                {
                                    slowprint( "Try again\n");
                                }
                            } while (date < 1 || date > 29);
                        }
                        else
                        {
                            do
                            {
                                while (true)
                                {
                                    cin >> date;
                                    if (!cin.fail()) break;
                                    cin.clear();
                                    cin.ignore(1000 , '\n');
                                    slowprint( "Invalid input. Please try again.\n");
                                }
                                if (date < 1 || date > 28)
                                {
                                    slowprint( "Try again\n");
                                }
                            } while (date < 1 || date > 28);
                        }
                        break;
                }

                Dindex = dates.size();
                dates.resize(Dindex + 1);
                dates[Dindex] = date;

                // 🔹 Show custom date in summary as MM/DD/YYYY
                deadline = to_string(month) + "/" + to_string(date) + "/" + to_string(year);
            }

            break;
        }


        case 4: {

        // 🔒 Block priority edit if deadline is not set
        if (deadline.empty() || deadline == "None") {

            slowprint( "\033[5A"); // move UP 2 lines
            slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                slowprint( "\033[1;37;41m  ⚠️ PLEASE SELECT DEADLINE FIRST! ⚠️  \033[0m\n");

            slowprint( "\033[8B"); // move UP 2 lines
            slowprint( "\033[82C"); // move RIGHT 17 columns (adjust until perfect)
                slowprint( "   PRESS ANY KEY TO CONTINUE...");

            cin.get();               // waits for user to press Enter
            break;                   // go back to the summary menu
        }


            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                       ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻             \n");
            slowprint( "                                                                       ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛           \n");
            slowprint( "                                                                       ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹            \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                 [𝟏] ⚠️ CRITICAL         [𝟐] 🟠 MEDIUM \n");
            slowprint( "                                                                                 [𝟑] 🔴 HIGH             [𝟒] 🟢 LOW \n");
            slowprint( "                                                                                            [𝟓] ⛔ NONE    \n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
                
            slowprint( "\033[4A"); // move UP 2 lines
            slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

            int p;


            while (true)
            {
                cin >> p;


                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                slowprint( "Invalid input. Please try again.\n");
            }
            cin.ignore();

            const string prios[] = {
                "Critical","High","Medium","Low","None"
            };
            if (p >= 1 && p <= 5) deadlinePriority = prios[p - 1];
            break;
        }

        case 5: {
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            slowprint( "                                                                                       ┏━╸╺┳┓╻╺┳╸   ┏┓╻┏━┓╺┳╸┏━╸            \n");
            slowprint( "                                                                                       ┣╸  ┃┃┃ ┃    ┃┗┫┃ ┃ ┃ ┣╸           \n");
            slowprint( "                                                                                       ┗━╸╺┻┛╹ ╹    ╹ ╹┗━┛ ╹ ┗━╸          \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
            slowprint( "                                                                                     ╔║                        ║╗                             \n");
            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 
                
            slowprint( "\033[4A"); // move UP 2 lines
            slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)

            getline(cin, notes);
            break;
        }

        default:
            slowprint( "Invalid choice.\n");
    }

}

    

// ===================================================
// ITEM INPUT LOOP
// ===================================================

system("cls");


do {
    system("cls");


    // 🔹 Show live list (title + ⃝ items + sub-bullets)
    printListLive(title, items, descriptions);

        slowprint( "                                                        ┏━┓╺┳╸┏━┓┏━┓╺┳╸   ┏━┓╺┳┓╺┳┓╻┏┓╻┏━╸   ╻╺┳╸┏━╸┏┳┓┏━┓   ╺┳╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ╻  ╻┏━┓╺┳╸╻            \n");
        slowprint( "                                                        ┗━┓ ┃ ┣━┫┣┳┛ ┃    ┣━┫ ┃┃ ┃┃┃┃┗┫┃╺┓   ┃ ┃ ┣╸ ┃┃┃┗━┓    ┃ ┃ ┃   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┃┗━┓ ┃ ╹  \n");
        slowprint( "                                                        ┗━┛ ╹ ╹ ╹╹┗╸ ╹    ╹ ╹╺┻┛╺┻┛╹╹ ╹┗━┛   ╹ ╹ ┗━╸╹ ╹┗━┛    ╹ ┗━┛    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹┗━┛ ╹ ╹          \n\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");

        slowprint( "                                                                                    🟢 TYPE AN ITEM AND PRESS ENTER!\n");
        slowprint( "                                                                       Type 💾[1] POST / SAVE LIST | 🗑️[2] CANCEL / DISCARD LIST \n\n");

        slowprint( "                                                                                      ╔════════════════════════╗                              \n");
        slowprint( "                                                                                     ╔║                        ║╗                             \n");
        slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 
        
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[87C"); // move RIGHT 17 columns (adjust until perfect)

    slowprint( "Add item: ");
    
    getline(cin, item);

    // --- User wants to stop adding items ---
    if (item == "1")
        break;

    // --- User cancels entire creation process ---
    if (item == "2") {
        slowprint( "\nList creation cancelled.\n");
        slowprint( "Press Enter to continue...");
        cin.get();
        return;
    }

    // Add new item
    index = items.size();
    items.resize(index + 1);
    items[index] = item;

    // Give XP for adding an item
    addClassXP(5, gamificationEnabled, playerXP, playerLevel,
           playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);


    // 🔹 Refresh screen so the new item appears in the live list
    system("cls");
    printListLive(title, items, descriptions); // descriptions for this item not added yet


    // ===================================================
    // ENTER DESCRIPTIONS FOR THIS ITEM
    // ===================================================

        slowprint( "                                                         ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓╻            \n");
        slowprint( "                                                         ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃╹            \n");
        slowprint( "                                                         ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹╹          \n\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                           \n");

        slowprint( "                                                                                🟢 TYPE A DESCRIPTION AND PRESS ENTER!\n");
        slowprint( "                                                                                          Type [1] 🗑️ SKIP \n\n");

        slowprint( "                                                                                      ╔════════════════════════╗                              \n");
        slowprint( "                                                                                     ╔║                        ║╗                             \n");
        slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 

    tempDescriptions.clear();

    while (true) {
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[90C"); // move RIGHT 17 columns (adjust until perfect)
            getline(cin, descLine);

            if (descLine == "1")
                break;


            //if (descLine == "2") {
            //    tempDescriptions.clear();
            //    break;
            //}

            if (descLine.empty())
                continue;

            dindex = tempDescriptions.size();
            tempDescriptions.resize(dindex + 1);
            tempDescriptions[dindex] = descLine;

            addClassXP(1, gamificationEnabled, playerXP, playerLevel,
           playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);


            // 🔹 LIVE PREVIEW: show list including this item's in-progress descriptions
            system("cls");

            // Build a preview descriptions vector = existing ones + current temp
            vector<vector<string>> previewDescriptions = descriptions;
            previewDescriptions.push_back(tempDescriptions);

            printListLive(title, items, previewDescriptions);

            slowprint( "                                                         ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓╻            \n");
            slowprint( "                                                         ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃╹            \n");
            slowprint( "                                                         ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹╹          \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                             \n");
            slowprint( "                                                                                     Type [1] 💾 FINISH DESCRIPTION \n\n");

            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
            slowprint( "                                                                                     ╔║                        ║╗                             \n");
            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n"); 

 
    }

    // Save this item’s description list
    dsaveIndex = descriptions.size();
    descriptions.resize(dsaveIndex + 1);
    descriptions[dsaveIndex] = tempDescriptions;

    // 🔹 Re-show the updated list after saving this item
    system("cls");
    printListLive(title, items, descriptions);

    slowprint( "\nItem + descriptions saved!\n\n");

} while (true);


// ===================================================
// CONFIRM ITEMS & DESCRIPTIONS (NEW SECTION)
// ===================================================

while (true) {
    system("cls");
    printListLive(title, items, descriptions);

    
    slowprint( "                                                         ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓   ╻╺┳╸┏━╸┏┳┓┏━┓   ┏━┓┏┓╻╺┳┓  ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻┏━┓┏━┓            \n");
    slowprint( "                                                         ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃   ┃ ┃ ┣╸ ┃┃┃┗━┓   ┣━┫┃┗┫ ┃┃   ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫┗━┓ ╺┛            \n");
    slowprint( "                                                         ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹   ╹ ╹ ┗━╸╹ ╹┗━┛   ╹ ╹╹ ╹╺┻┛  ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹┗━┛ ╹          \n\n");
    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    slowprint( "                                                                                   [1] ✅ CONFIRM AND CREATE LIST\n");
    slowprint( "                                                                                   [2] ✏️ EDIT ITEMS / DESCRIPTIONS\n");
    slowprint( "                                                                                   [3] ❌ CANCEL / DISCARD LIST\n");
    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    slowprint( "                                                                                                ╔════╗                              \n");
    slowprint( "                                                                                               ╔║    ║╗                             \n");
    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

    slowprint( "\033[2A");
    slowprint( "\033[98C");

    int finalChoice;
    while (true) {
        cin >> finalChoice;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000, '\n');
        slowprint( "Invalid input. Please try again.\n");
    }
    cin.ignore(); // clear newline for getline later

    // [1] CONFIRM -> go save list
    if (finalChoice == 1) {
        break;
    }

    // [3] CANCEL -> discard list and exit
    if (finalChoice == 3) {
        system("cls");
        printListLive(title, items, descriptions);
        slowprint( "\nList creation cancelled.\n");
        slowprint( "Press Enter to continue...");
        cin.get();
        return;
    }

    // [2] EDIT ITEMS / DESCRIPTIONS
    if (finalChoice == 2) {
        while (true) {
            system("cls");
            printListLive(title, items, descriptions);

            if (items.empty()) {
                slowprint( "No items to edit. Press Enter to go back...");
                cin.get();
                break;
            }

            slowprint( "                                                             ┏━╸╺┳┓╻╺┳╸   ╻╺┳╸┏━╸┏┳┓┏━┓   ┏━┓┏┓╻╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻┏━┓┏━┓            \n");
            slowprint( "                                                             ┣╸  ┃┃┃ ┃    ┃ ┃ ┣╸ ┃┃┃┗━┓   ┣━┫┃┗┫ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫┗━┓ ╺┛            \n");
            slowprint( "                                                             ┗━╸╺┻┛╹ ╹    ╹ ╹ ┗━╸╹ ╹┗━┛   ╹ ╹╹ ╹╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹┗━┛ ╹           \n\n");
            slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");


            for (size_t i = 0; i < items.size(); ++i) {
                slowprint( "                                                                         [" + to_string(i + 1) + "] " + items[i] + "\n");
            }
            slowprint( "                                                                         [0] 🔙 DONE EDITING\n\n");
            slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

            slowprint( "\033[4A");
            slowprint( "\033[98C");

            int itemChoice;
            while (true) {
                cin >> itemChoice;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000, '\n');
                slowprint( "Invalid input. Please try again.\n");
            }
            cin.ignore();

            if (itemChoice == 0) {
                break; // back to main confirm menu
            }
            if (itemChoice < 1 || itemChoice > (int)items.size()) {
                continue;
            }

            size_t itemIndex = static_cast<size_t>(itemChoice - 1);

            // ── Submenu for selected item ─────────────────────────────
            while (true) {
                system("cls");
                 printListLive(title, items, descriptions,
                  static_cast<int>(itemIndex), -1);

                slowprint( "                                                                                        ┏━╸╺┳┓╻╺┳╸   ╻╺┳╸┏━╸┏┳┓           \n");
                slowprint( "                                                                                        ┣╸  ┃┃┃ ┃    ┃ ┃ ┣╸ ┃┃┃           \n");
                slowprint( "                                                                                        ┗━╸╺┻┛╹ ╹    ╹ ╹ ┗━╸╹ ╹        \n\n");
                slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━             \n");
                slowprint( "                                                                         EDITING ITEM #" + to_string(itemChoice) + ": " + items[itemIndex] + "    \n");
                slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━             \n");
                slowprint( "                                                                                     [1] ✏️ EDIT ITEM NAME                           \n");
                slowprint( "                                                                                     [2] ✏️ EDIT / DELETE DESCRIPTIONS               \n");
                slowprint( "                                                                                     [3] 🗑️ DELETE THIS ITEM                         \n");
                slowprint( "                                                                                     [4] 🔙 BACK                                     \n");
                slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━             \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[4A");
                slowprint( "\033[98C");

                int itemEditChoice;
                while (true) {
                    cin >> itemEditChoice;
                    if (!cin.fail()) break;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    slowprint( "Invalid input. Please try again.\n");
                }
                cin.ignore();

                // [4] back to item list
                if (itemEditChoice == 4) {
                    break;
                }

                // [1] EDIT ITEM NAME
                if (itemEditChoice == 1) {
                    system("cls");
                    printListLive(title, items, descriptions,
                    static_cast<int>(itemIndex), -1);

                        slowprint( "                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ┏┓╻┏━┓┏┳┓┏━╸   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓              \n");
                        slowprint( "                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃   ┃┗┫┣━┫┃┃┃┣╸    ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃            \n");
                        slowprint( "                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛   ╹ ╹╹ ╹╹ ╹┗━╸   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹          \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");


                        slowprint( "                                                                                      ╔════════════════════════╗                                                   \n");
                        slowprint( "                                                                                     ╔║                        ║╗                                                  \n");
                        slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n"); 

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");



                    string newName;
                    getline(cin, newName);
                    if (!newName.empty()) {
                        items[itemIndex] = newName;
                    }
                }

                // [3] DELETE ITEM
                else if (itemEditChoice == 3) {
                    items.erase(items.begin() + itemIndex);
                    if (itemIndex < descriptions.size()) {
                        descriptions.erase(descriptions.begin() + itemIndex);
                    }
                    break; // item list changed, go back to item selection
                }

                // [2] EDIT / DELETE DESCRIPTIONS
                else if (itemEditChoice == 2) {
                    while (true) {
                        system("cls");
                        printListLive(title, items, descriptions,
                        static_cast<int>(itemIndex));

                        slowprint( "                                                    ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ╺┳┓┏━╸┏━┓┏━╸┏━┓┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ╺┳╸┏━┓   ┏━╸╺┳┓╻╺┳╸    ╻   ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸       \n");
                        slowprint( "                                                    ┗━┓┣╸ ┃  ┣╸ ┃   ┃     ┃┃┣╸ ┗━┓┃  ┗━┓┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫    ┃ ┃ ┃   ┣╸  ┃┃┃ ┃    ┏┛    ┃┃┣╸ ┃  ┣╸  ┃ ┣╸        \n");
                        slowprint( "                                                    ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╺┻┛┗━╸┗━┛┗━╸┗━┛╹┗╸╹╹   ╹ ╹┗━┛╹ ╹    ╹ ┗━┛   ┗━╸╺┻┛╹ ╹    ╹    ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸        \n\n");
                        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                         DESCRIPTIONS FOR: " + items[itemIndex] + "\n");
                        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");


                        if (itemIndex >= descriptions.size() || descriptions[itemIndex].empty()) {
                            slowprint( "                                                                         (No descriptions yet.)\n");
                        } else {
                            for (size_t d = 0; d < descriptions[itemIndex].size(); ++d) {
                                slowprint( "                                                                         (" + to_string(d + 1) + ") " 
                                     + descriptions[itemIndex][d] + "\n");
                            }
                        }

                        slowprint( "\n");
                        slowprint( "                                                                         [0] 🔙 BACK\n");
                        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

                        slowprint( "                                                                                                ╔════╗                              \n");
                        slowprint( "                                                                                               ╔║    ║╗                             \n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                        slowprint( "\033[4A");
                        slowprint( "\033[98C");

                        int descChoice;
                        while (true) {
                            cin >> descChoice;
                            if (!cin.fail()) break;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            slowprint( "Invalid input. Please try again.\n");
                        }
                        cin.ignore();

                        if (descChoice == 0) {
                            break; // back to item submenu
                        }

                        if (itemIndex >= descriptions.size() ||
                            descChoice < 1 ||
                            descChoice > (int)descriptions[itemIndex].size()) {
                            continue;
                        }

                        size_t descIndex = static_cast<size_t>(descChoice - 1);

                        system("cls");
                       printListLive(title, items, descriptions,
                        static_cast<int>(itemIndex),
                        static_cast<int>(descIndex));
                        // ── New header for the selected description ─────────────────────────────
                        slowprint( "                                                                              ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻      \n");
                        slowprint( "                                                                              ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫        \n");
                        slowprint( "                                                                              ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹        \n\n");
                        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                         EDITING DESCRIPTION #" + to_string(descChoice)
                            + " OF ITEM #" + to_string(itemIndex + 1) + ": " + items[itemIndex] + "\n");
                        slowprint( "                                                                         → \"" + descriptions[itemIndex][descIndex] + "\"\n");
                        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

                        slowprint( "                                                                         [1] ✏️ EDIT THIS LINE\n");
                        slowprint( "                                                                         [2] 🗑️ DELETE THIS LINE\n");
                        slowprint( "                                                                         [3] 🔙 CANCEL\n");
                        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗                              \n");
                        slowprint( "                                                                                               ╔║    ║╗                             \n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");



                        int descAction;
                        while (true) {
                            cin >> descAction;
                            if (!cin.fail()) break;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            slowprint( "Invalid input. Please try again.\n");
                        }
                        cin.ignore();

                        if (descAction == 1) {
                        system("cls");
                        printListLive(title, items, descriptions,
                        static_cast<int>(itemIndex),
                        static_cast<int>(descIndex));

                            slowprint( "                                                       ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ╺┳╸┏━╸╻ ╻╺┳╸   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻              \n");
                            slowprint( "                                                       ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃    ┃ ┣╸ ┏╋┛ ┃    ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫            \n");
                            slowprint( "                                                       ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛    ╹ ┗━╸╹ ╹ ╹    ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹          \n\n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");


                            slowprint( "                                                                                      ╔════════════════════════╗                                                   \n");
                            slowprint( "                                                                                     ╔║                        ║╗                                                  \n");
                            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n"); 

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            string newDesc;
                            getline(cin, newDesc);
                            if (!newDesc.empty()) {
                                descriptions[itemIndex][descIndex] = newDesc;
                            }
                        } else if (descAction == 2) {
                            descriptions[itemIndex].erase(descriptions[itemIndex].begin() + descIndex);
                        } else {
                            // cancel -> do nothing, loop again
                        }
                    } // end description loop
                }

            } // end item submenu loop

        } // end while editing items
    } // end if finalChoice == 2

} // end confirm-items while

cremonth = cmonth;
creyear = cyear;
credate = cdate;

// ===================================================
// SAVE FINAL LIST, ITEMS, AND DESCRIPTIONS
// (UNCHANGED LOGIC – just moved below confirmation)
// ===================================================

    int titleIndex = name_of_list.size();
    name_of_list.resize(titleIndex + 1);
    name_of_list[titleIndex] = title;

    monthcreated.resize(titleIndex + 1);
    monthcreated[titleIndex] = cremonth;

    yearcreated.resize(titleIndex + 1);
    yearcreated[titleIndex] = creyear;

    datecreated.resize(titleIndex + 1);
    datecreated[titleIndex] = credate;


    int listIndex = list_of_lists.size();
    list_of_lists.resize(listIndex + 1);
    list_of_lists[listIndex] = items;

    list_of_descriptions.resize(listIndex + 1);
    list_of_descriptions[listIndex] = descriptions;

        // NEW: make sure metadata arrays are large enough
        if ((int)list_categories.size() <= listIndex) {
            list_categories.resize(listIndex + 1);
            list_deadlines.resize(listIndex + 1);
            list_priorities.resize(listIndex + 1);
            list_notes.resize(listIndex + 1);      // 🔹 NEW
        }
        listmonth.resize(listIndex + 1);
        listmonth[listIndex] = months;

        listyear.resize(listIndex + 1);
        listyear[listIndex] = years;

        listdate.resize(listIndex + 1);
        listdate[listIndex] = dates;

        // store category / deadline / priority / notes for this list
        list_categories[listIndex] = category;
        list_deadlines[listIndex]  = deadline;
        list_priorities[listIndex] = deadlinePriority;
        list_notes[listIndex]      = notes;        // 🔹 NEW



    // Give XP for creating a new list
    addClassXP(10, gamificationEnabled, playerXP, playerLevel,
           playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);


    // ===================================================
    // COMPLETION MESSAGE
    // ===================================================

    system("cls");
    headerNewList();

    slowprint( "                                                                 ╻  ╻┏━┓╺┳╸   ┏━┓┏━┓╻ ╻┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻╻          \n");
    slowprint( "                                                                 ┃  ┃┗━┓ ┃    ┗━┓┣━┫┃┏┛┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛╹          \n");
    slowprint( "                                                                 ┗━╸╹┗━┛ ╹    ┗━┛╹ ╹┗┛ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹ ╹           \n\n");
    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
   
    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");

    cin.get();
}


void headerVoidList() {

        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                                      ██╗   ██╗██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n");
        slowprint( "                                                                      ██║   ██║██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══     \n");
        slowprint( "                                                                      ██║   ██║██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║          \n");
        slowprint( "                                                                      ╚██╗ ██╔╝██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n");
        slowprint( "                                                                       ╚████╔╝ ██║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║          \n");
        slowprint( "                                                                        ╚═══╝  ╚═╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝              \n");
        slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}

// NEW: helper to display one selected list by index
void showSingleList(
    int index,
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string>>>& list_of_descriptions,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear,
    vector<int>& monthcreated,
    vector<int>& datecreated,
    vector<int>& yearcreated,
    vector<string>& list_deadlines,
    int& cdate,
    int& cmonth,
    int& cyear
) {
    int dmonth = 0, dday = 0, dyear = 0;

    if (list_deadlines[index] == "Today") {
        dmonth = monthcreated[index];
        dday   = datecreated[index];
        dyear  = yearcreated[index];
    } else if (list_deadlines[index] == "Tomorrow") {
        dmonth = monthcreated[index];
        dyear  = yearcreated[index];
        switch (dmonth) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (datecreated[index] + 1 > 31) { dmonth += 1; dday = 1; }
                else { dday = datecreated[index] + 1; }
                break;
            case 4: case 6: case 9: case 11:
                if (datecreated[index] + 1 > 30) { dmonth += 1; dday = 1; }
                else { dday = datecreated[index] + 1; }
                break;
            case 2:
                if (((yearcreated[index]%4 == 0 && yearcreated[index]%100 != 0) || (yearcreated[index]%400 == 0))) {
                    if (datecreated[index] + 1 > 29) { dmonth += 1; dday = 1; }
                    else { dday = datecreated[index] + 1; }
                } else {
                    if (datecreated[index] + 1 > 28) { dmonth += 1; dday = 1; }
                    else { dday = datecreated[index] + 1; }
                }
                break;
        }
        if (dmonth > 12) { dmonth = 1; dyear = yearcreated[index] + 1; }
    } else if (list_deadlines[index] == "This Week") {
        dmonth = monthcreated[index];
        dyear  = yearcreated[index];
        switch (dmonth) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (datecreated[index] + 7 > 31) { dmonth += 1; dday = (datecreated[index] + 7) - 31; }
                else { dday = datecreated[index] + 7; }
                break;
            case 4: case 6: case 9: case 11:
                if (datecreated[index] + 7 > 30) { dmonth += 1; dday = (datecreated[index] + 7) - 30; }
                else { dday = datecreated[index] + 7; }
                break;
            case 2:
                if (((yearcreated[index]%4 == 0 && yearcreated[index]%100 != 0) || (yearcreated[index]%400 == 0))) {
                    if (datecreated[index] + 7 > 29) { dmonth += 1; dday = (datecreated[index] + 7) - 29; }
                    else { dday = datecreated[index] + 7; }
                } else {
                    if (datecreated[index] + 7 > 28) { dmonth += 1; dday = (datecreated[index] + 7) - 28; }
                    else { dday = datecreated[index] + 7; }
                }
                break;
        }
        if (dmonth > 12) { dmonth = 1; dyear = yearcreated[index] + 1; }
    } else if (list_deadlines[index] == "Next Week") {
        dmonth = monthcreated[index];
        dyear  = yearcreated[index];
        switch (dmonth) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (datecreated[index] + 14 > 31) { dmonth += 1; dday = (datecreated[index] + 14) - 31; }
                else { dday = datecreated[index] + 14; }
                break;
            case 4: case 6: case 9: case 11:
                if (datecreated[index] + 14 > 30) { dmonth += 1; dday = (datecreated[index] + 14) - 30; }
                else { dday = datecreated[index] + 14; }
                break;
            case 2:
                if (((yearcreated[index]%4 == 0 && yearcreated[index]%100 != 0) || (yearcreated[index]%400 == 0))) {
                    if (datecreated[index] + 14 > 29) { dmonth += 1; dday = (datecreated[index] + 14) - 29; }
                    else { dday = datecreated[index] + 14; }
                } else {
                    if (datecreated[index] + 14 > 28) { dmonth += 1; dday = (datecreated[index] + 14) - 28; }
                    else { dday = datecreated[index] + 14; }
                }
                break;
        }
        if (dmonth > 12) { dmonth = 1; dyear = yearcreated[index] + 1; }
    } else if (list_deadlines[index] == "This Month") {
        dmonth = monthcreated[index];
        dyear  = yearcreated[index];
        dday   = datecreated[index];

        if (dmonth == 2) {
            bool leap = ((dyear % 4 == 0 && dyear % 100 != 0) || (dyear % 400 == 0));
            if (!leap && dday > 28) dday = 1;
            if (leap && dday > 29)  dday = 1;
        } else if (dmonth==4 || dmonth==6 || dmonth==9 || dmonth==11) {
            if (dday > 30) dday = 1;
        } else {
            if (dday > 31) dday = 1;
        }
        if (dmonth > 12) { dmonth = 1; dyear = yearcreated[index] + 1; }
    } else if (list_deadlines[index] == "Next Month") {
        dmonth = monthcreated[index] + 1;
        dyear  = yearcreated[index];
        if (dmonth > 12) {
            dmonth = 1;
            dyear  = yearcreated[index] + 1;
        }
        switch (dmonth) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (datecreated[index] > 31) { dmonth += 1; dday = 1; }
                else { dday = datecreated[index]; }
                break;
            case 4: case 6: case 9: case 11:
                if (datecreated[index] > 30) { dmonth += 1; dday = 1; }
                else { dday = datecreated[index]; }
                break;
            case 2:
                if (((yearcreated[index]%4 == 0 && yearcreated[index]%100 != 0) || (yearcreated[index]%400 == 0))) {
                    if (datecreated[index] > 29) { dmonth += 1; dday = 1; }
                    else { dday = datecreated[index]; }
                } else {
                    if (datecreated[index] > 28) { dmonth += 1; dday = 1; }
                    else { dday = datecreated[index]; }
                }
                break;
        }
    }

    string missing = "False";
    if (!datecreated.empty() && !monthcreated.empty() && !yearcreated.empty()) {
        auto diffCalc = [&](int td, int tm, int ty) {
            if (cyear > ty)                        return to_string(cyear - ty) + " year(s)";
            else if (cyear == ty && cmonth > tm)   return to_string(cmonth - tm) + " month(s)";
            else if (cyear == ty && cmonth == tm && cdate > td)
                                                  return to_string(cdate - td) + " day(s)";
            return string("False");
        };

        if (list_deadlines[index] == "Today"     ||
            list_deadlines[index] == "Tomorrow"  ||
            list_deadlines[index] == "This Week" ||
            list_deadlines[index] == "Next Week" ||
            list_deadlines[index] == "This Month"||
            list_deadlines[index] == "Next Month")
        {
            missing = diffCalc(dday, dmonth, dyear);
        }
    } else {
        if (cyear > yearcreated[index])                         missing = to_string(cyear - yearcreated[index]) + " year(s)";
        else if (cyear == yearcreated[index] && cmonth > monthcreated[index])
            missing = to_string(cmonth - monthcreated[index]) + " month(s)";
        else if (cyear == yearcreated[index] && cmonth == monthcreated[index] && cdate > datecreated[index])
            missing = to_string(cdate - datecreated[index]) + " day(s)" ;
    }

    vector<string>& items = list_of_lists[index];
    vector<int>&    months= listmonth[index];
    vector<int>&    dates = listdate[index];
    vector<int>&    years = listyear[index];

    vector<vector<string>> emptyVecVec;
    vector<vector<string>>& descs =
        (index < (int)list_of_descriptions.size()) ? list_of_descriptions[index] : emptyVecVec;

    system("cls");
    headerVoidList();

    slowprint( "                                                                               ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    slowprint( "                                                                         " "𝐋𝐈𝐒𝐓 𝐍𝐀𝐌𝐄: " + name_of_list[index] + "\n");
    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n\n");

    slowprint( "                                                                           📂 CREATED ON : " + to_string(monthcreated[index]) + "/" + to_string(datecreated[index]) + "/" + to_string(yearcreated[index]) + "\n");
    slowprint( "                                                                           📅 TARGET DATE : ");
    if (!months.empty() && !dates.empty() && !years.empty()) {
        slowprint( to_string(months[0]) + "/" + to_string(dates[0]) + "/" + to_string(years[0]) + "\n\n");
    } else {
        if (missing != "False") {
            slowprint( "Already Late for " + missing + "\n\n");
        } else {
            slowprint( to_string(dmonth) + '/' + to_string(dday) + '/' + to_string(dyear) + "\n\n");
        }
    }

    if (items.empty()) {
        slowprint( "                                                                               (No items)\n");
    } else {
        int completedCount = 0;
        slowprint( "                                                                               📦 ITEMS:\n ");

        for (int i = 0; i < (int)items.size(); i++) {
            slowprint( "                                                                                     " + to_string(i + 1) + ". " + items[i] + "\n");
            
            if (i < (int)descs.size()) {
                for (int d = 0; d < (int)descs[i].size(); d++) {
                    slowprint( "                                                                                       • " + descs[i][d] + "\n");
                }
            }

            if (items[i].find("✅") != string::npos) completedCount++;
        }

        int    notDone     = (int)items.size() - completedCount;
        double percentDone = items.empty() ? 0 : (completedCount * 100.0) / items.size();
        double percentNot  = items.empty() ? 0 : (notDone * 100.0) / items.size();

        slowprint("\n");
        
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
        slowprint( "                                                                                               𝐒𝐓𝐀𝐓𝐈𝐒𝐓𝐈𝐂𝐒 \n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
        slowprint( "                                                                          Missing : "          + missing      + "\n");
        slowprint( "                                                                          Total Items : "      + to_string(items.size()) + "\n");
        slowprint( "                                                                          Completed Items : "  + to_string(completedCount) + "\n");
        slowprint( "                                                                          Not Done : "         + to_string(notDone)      + "\n");
        cout <<                                                                            fixed << setprecision(2);
        slowprint( "                                                                          % Completed : "      + fmt2(percentDone) + "%\n");
        slowprint( "                                                                          % Not Completed : "  + fmt2(percentNot)  + "%\n\n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    }

    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
    cin.get();
}


void viewLists(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string>>>& list_of_descriptions,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear,
    vector<int>& monthcreated,
    vector<int>& datecreated,
    vector<int>& yearcreated,
    vector<string>& list_categories,
    vector<string>& list_deadlines,
    vector<string>& list_priorities,
    vector<string>& list_notes,
    int& cdate,
    int& cmonth,
    int& cyear
) {
    if (name_of_list.size() == 0) {

        slowprint("\n");
        slowprint( "\033[0B"); // move UP 2 lines
        slowprint( "\033[84C"); // move RIGHT 17 columns (adjust until perfect)
        slowprint( "\033[1;37;41m  ⚠️ NO LISTS TO EDIT⚠️  \033[0m\n");
        slowprint( "\n");
        slowprint( "                                                                                  \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // ===== MAIN VIEW LOOP =====
    while (true) {

        // ================================
        // DISPLAY ALL LIST TITLES
        // ================================
        system("cls");
        headerVoidList();

        slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n");

        for (int i = 0; i < (int)name_of_list.size(); i++) {
            slowprint( "                                                                                 " + to_string(i + 1) + ". " + name_of_list[i] + "\n");
            slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[i]  + "\n");
            slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[i]   + "\n");
            slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[i]  + "\n");
            slowprint( "                                                                                      📋 NOTES   : " 
                 + (list_notes[i].empty() ? "None" : list_notes[i]) + "\n");
            slowprint( "\n");
        }

        slowprint( "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n");

        slowprint( "                                                                       ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓          \n");
        slowprint( "                                                                       ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┣━┫   ┃  ┃┗━┓ ┃    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛          \n");
        slowprint( "                                                                       ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹   ┗━╸╹┗━┛ ╹    ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸          \n\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");
        slowprint( "                                                                                      [S] 🔎 SEARCH LIST NAMES                             \n");
        slowprint( "                                                                                      [0] 🔙 BACK TO MAIN MENU                            \n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");
        slowprint( "                                                                                                ╔════╗                                     \n");
        slowprint( "                                                                                               ╔║    ║╗                                    \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

        slowprint( "\033[2A");
        slowprint( "\033[98C");

        string choiceStr;
        cin >> choiceStr;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // ==================================
        // 0 → BACK TO MAIN MENU
        // ==================================
        if (choiceStr == "0") {
            break;
        }

        // ==================================
        // S → SEARCH / SORT / FILTER MENU
        // ==================================
        if (choiceStr == "S" || choiceStr == "s") {

            while (true) {
                system("cls");
                headerVoidList();

                slowprint( "                                                                                          ┏━┓┏━╸┏━┓┏━┓┏━╸╻ ╻    \n");
                slowprint( "                                                                                          ┗━┓┣╸ ┣━┫┣┳┛┃  ┣━┫    \n");
                slowprint( "                                                                                          ┗━┛┗━╸╹ ╹╹┗╸┗━╸╹ ╹    \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                slowprint( "                                                                                       [1] 🔎 SEARCH BY NAME\n");
                slowprint( "                                                                                       [2] 🔎 SORT BY NAME (A-Z)\n");
                slowprint( "                                                                                       [3] 🔎 SORT BY NAME (Z-A)\n");
                slowprint( "                                                                                       [4] 🗂️ FILTER BY CATEGORY\n");
                slowprint( "                                                                                       [5] 📅 FILTER BY DEADLINE\n");
                slowprint( "                                                                                       [6] ❗ FILTER BY PRIORITY\n");
                slowprint( "                                                                                       [0] ↩ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                slowprint( "                                                                                                ╔════╗                                     \n");
                slowprint( "                                                                                               ╔║    ║╗                                    \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                string sStr;
                int s = 0;

                cin >> sStr;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (sStr == "0") {
                    // back to main viewLists
                    break;
                }

                try {
                    s = stoi(sStr);
                }
                catch (...) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue; // back to SEARCH menu
                }

                if (s < 1 || s > 6) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;
                }

                // ================================
                // 1️⃣ SEARCH BY NAME
                // ================================
                if (s == 1) {

                    system("cls");
                    headerVoidList();

                    slowprint( "                                                                              ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸            \n");
                    slowprint( "                                                                              ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸            \n");
                    slowprint( "                                                                              ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸         \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                    slowprint( "                                                                                      ╔════════════════════════╗                                                   \n");
                    slowprint( "                                                                                     ╔║                        ║╗                                                  \n");
                    slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n");

                    slowprint( "\033[2A");
                    slowprint( "\033[98C");

                    string key;
                    getline(cin, key);

                    vector<int> found;
                    for (int i = 0; i < (int)name_of_list.size(); i++) {
                        if (name_of_list[i].find(key) != string::npos)
                            found.push_back(i);
                    }

                    if (found.empty()) {

                        system("cls");
                        headerVoidList();

                        slowprint( "                                                                                    ┏┓╻┏━┓   ┏━┓┏━╸┏━┓╻ ╻╻  ╺┳╸┏━┓            \n");
                        slowprint( "                                                                                    ┃┗┫┃ ┃   ┣┳┛┣╸ ┗━┓┃ ┃┃   ┃ ┗━┓          \n");
                        slowprint( "                                                                                    ╹ ╹┗━┛   ╹┗╸┗━╸┗━┛┗━┛┗━╸ ╹ ┗━┛        \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                        slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                        cin.get();
                        continue;
                    }

                    while (true) {
                        system("cls");
                        headerVoidList();

                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                        slowprint( "                                                                                         🔎 Search Results 🔎\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                        for (int i = 0; i < (int)found.size(); i++) {
                            int idx = found[i];

                            slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[idx] + "\n");
                            slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[idx]  + "\n");
                            slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[idx]   + "\n");
                            slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[idx]  + "\n");
                            slowprint( "                                                                                      📋 NOTES   : "
                                + (list_notes[idx].empty() ? "None" : list_notes[idx]) + "\n");
                            slowprint( "\n");
                        }


                        slowprint( "\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                        slowprint( "                                                                                ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏━┓┏━╸┏━┓╻ ╻╻  ╺┳╸   \n");
                        slowprint( "                                                                                ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┣┳┛┣╸ ┗━┓┃ ┃┃   ┃     \n");
                        slowprint( "                                                                                ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹┗╸┗━╸┗━┛┗━┛┗━╸ ╹    \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                        slowprint( "                                                                                                ╔════╗                                     \n");
                        slowprint( "                                                                                               ╔║    ║╗                                    \n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        string pickStr;
                        int pick = 0;
                        cin >> pickStr;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        try {
                            pick = stoi(pickStr);
                        }
                        catch (...) {
                            slowprint( "\n\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            cin.get();
                            continue;
                        }

                        if (pick < 1 || pick > (int)found.size()) {
                            slowprint( "\n\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            cin.get();
                            continue;
                        }

                        int realIndex = found[pick - 1];

                        showSingleList(
                            realIndex,
                            name_of_list,
                            list_of_lists,
                            list_of_descriptions,
                            listmonth,
                            listdate,
                            listyear,
                            monthcreated,
                            datecreated,
                            yearcreated,
                            list_deadlines,
                            cdate, cmonth, cyear
                        );
                        break; // back to SEARCH menu
                    }

                    continue;
                }

                // ================================
                // 2️⃣ SORT A-Z and 3️⃣ SORT Z-A
                // ================================
                else if (s == 2 || s == 3) {

                    while (true) {
                        vector<int> order(name_of_list.size());
                        for (int i = 0; i < (int)order.size(); i++) order[i] = i;

                        for (int i = 0; i < (int)order.size() - 1; i++) {
                            for (int j = i + 1; j < (int)order.size(); j++) {

                                bool swapNeeded = false;

                                if (s == 2 && name_of_list[order[i]] > name_of_list[order[j]])
                                    swapNeeded = true;

                                if (s == 3 && name_of_list[order[i]] < name_of_list[order[j]])
                                    swapNeeded = true;

                                if (swapNeeded) swap(order[i], order[j]);
                            }
                        }

                        system("cls");
                        headerVoidList();

                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                        slowprint( "                                                                                         🗂️ SORTED LIST 🗂️\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                        for (int i = 0; i < (int)order.size(); i++) {
                            int idx = order[i];

                            slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[idx] + "\n");
                            slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[idx]  + "\n");
                            slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[idx]   + "\n");
                            slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[idx]  + "\n");
                            slowprint( "                                                                                      📋 NOTES   : "
                                + (list_notes[idx].empty() ? "None" : list_notes[idx]) + "\n");
                            slowprint( "\n");
                        }


                        slowprint( "\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                        slowprint( "                                                                    ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓   ╺┳╸┏━┓   ┏━┓┏━┓┏━╸┏┓╻         \n");
                        slowprint( "                                                                    ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛    ┃ ┃ ┃   ┃ ┃┣━┛┣╸ ┃┗┫             \n");
                        slowprint( "                                                                    ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸    ╹ ┗━┛   ┗━┛╹  ┗━╸╹ ╹          \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                  \n\n");
                        slowprint( "                                                                                             [0] ↩️ BACK\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                  \n\n");

                        slowprint( "                                                                                                ╔════╗                                     \n");
                        slowprint( "                                                                                               ╔║    ║╗                                    \n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        string pickStr;
                        int pick = 0;

                        cin >> pickStr;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (pickStr == "0") {
                            break; // back to SEARCH menu
                        }

                        try {
                            pick = stoi(pickStr);
                        }
                        catch (...) {
                            slowprint( "\n\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            cin.get();
                            continue;
                        }

                        if (pick < 1 || pick > (int)order.size()) {
                            slowprint( "\n\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            cin.get();
                            continue;
                        }

                        int realIndex = order[pick - 1];

                        showSingleList(
                            realIndex,
                            name_of_list,
                            list_of_lists,
                            list_of_descriptions,
                            listmonth,
                            listdate,
                            listyear,
                            monthcreated,
                            datecreated,
                            yearcreated,
                            list_deadlines,
                            cdate, cmonth, cyear
                        );

                        // after showing, go back to SORT screen
                        continue;
                    }

                    continue; // back to SEARCH menu
                }

              
          
            // ------------------------------------------------
            // 4️⃣ 5️⃣ 6️⃣ FILTERS (Category / Deadline / Priority)
            // ------------------------------------------------
            else if (s == 4 || s == 5 || s == 6) {

                // ===========================
                // DISPLAY + REAL VALUE ARRAYS
                // ===========================
                vector<string> displayOptions;
                vector<string> valueOptions;

                if (s == 4) {
                    displayOptions = {
                        "💼 WORK","🏫 SCHOOL","👤 PERSONAL","🧹 ERRANDS",
                        "💰 FINANCE","❤️‍🩹 HEALTH","📅 APPOINTMENT",
                        "🛒 SHOPPING","➕ OTHERS","⛔ NONE"
                    };

                    valueOptions = {
                        "Work","School","Personal","Errands",
                        "Finance","Health","Appointment",
                        "Shopping","Others","None"
                    };
                }
                else if (s == 5) {
                    displayOptions = {
                        "📅 TODAY","📅 TOMORROW","📅 THIS WEEK",
                        "📅 NEXT WEEK","📅 NEXT MONTH"
                    };

                    valueOptions = {
                        "Today","Tomorrow","This Week",
                        "Next Week","Next Month"
                    };
                }
                else if (s == 6) {
                    displayOptions = {
                        "⚠️ CRITICAL","🔴 HIGH","🟠 MEDIUM",
                        "🟢 LOW","⛔ NONE"
                    };

                    valueOptions = {
                        "Critical","High","Medium","Low","None"
                    };
                }


                // ========= SELECT FILTER TYPE =========
                vector<string> options;
                if (s == 4) {
                    options = { "💼 WORK ","🏫 SCHOOL ","👤 PERSONAL","🧹 ERRANDS","💰 FINANCE","❤️‍🩹 HEALTH","📅 APPOINTMENT","🛒 SHOPPING","➕ OTHERS","⛔ NONE" };
                }
                else if (s == 5) {
                    options = { "📅 TODAY","📅 TOMORROW","📅 THIS WEEK","📅 NEXXT WEEK","📅 NEXT MONTH" };
                }
                else if (s == 6) {
                    options = { "⚠️ CRITICAL","🔴 HIGH ","🟠 MEDIUM","🟢 LOW","⛔ NONE" };
                }

                // ========== STEP 1: CHOOSE FILTER OPTION (fc) ==========
                string fcStr;
                int    fc      = 0;
                bool   goBack  = false;

                while (true) {
                    system("cls");
                    headerVoidList();

                    slowprint( "                                                                                  ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏━┓┏━┓╺┳╸╻┏━┓┏┓╻   \n");
                    slowprint( "                                                                                  ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃ ┃┣━┛ ┃ ┃┃ ┃┃┗┫    \n");
                    slowprint( "                                                                                  ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ┗━┛╹   ╹ ╹┗━┛╹ ╹    \n\n");

                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

                    for (int i = 0; i < (int)options.size(); i++) {
                        slowprint( "                                                                                 " + to_string(i + 1) + ". " + options[i] + "\n");
                    }

                    slowprint( "                                                                                 [0] ↩️ BACK\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                    slowprint( "                                                                                                ╔════╗                                     \n");
                    slowprint( "                                                                                               ╔║    ║╗                                    \n");
                    slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                    slowprint( "\033[2A");
                    slowprint( "\033[98C");

                    cin >> fcStr;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (fcStr == "0") {
                        goBack = true;   // back to SEARCH / SORT menu
                        break;
                    }

                    try {
                        fc = stoi(fcStr);
                    }
                    catch (...) {
                        slowprint( "\n\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                        cin.get();
                        continue;   // 🔁 redraw filter options
                    }

                    if (fc < 1 || fc > (int)options.size()) {
                        slowprint( "\n\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                        cin.get();
                        continue;   // 🔁 redraw filter options
                    }

                    // valid selection
                    break;
                }

                if (goBack) {
                    // user pressed 0 in filter menu
                    continue;   // back to main viewLists loop
                }

                string selected = options[fc - 1];

                // ========= BUILD FILTER RESULT =========
                vector<int> filtered;
                for (int i = 0; i < (int)name_of_list.size(); i++) {

                    string value;
                    if (s == 4) value = list_categories[i];
                    if (s == 5) value = list_deadlines[i];
                    if (s == 6) value = list_priorities[i];

                    if (value == valueOptions[fc - 1])

                        filtered.push_back(i);
                }

                if (filtered.empty()) {

                    system("cls");
                    headerVoidList();

                    slowprint( "                                                                                 ┏┓╻┏━┓   ╻  ╻┏━┓╺┳╸┏━┓   ┏━╸┏━┓╻ ╻┏┓╻╺┳┓       \n");
                    slowprint( "                                                                                 ┃┗┫┃ ┃   ┃  ┃┗━┓ ┃ ┗━┓   ┣╸ ┃ ┃┃ ┃┃┗┫ ┃┃   \n");
                    slowprint( "                                                                                 ╹ ╹┗━┛   ┗━╸╹┗━┛ ╹ ┗━┛   ╹  ┗━┛┗━┛╹ ╹╺┻┛    \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");

                    cin.get();
                    continue;   // back to main viewLists loop
                }

                // ========= DISPLAY RESULTS & LET USER PICK =========
                while (true) {
                    system("cls");
                    headerVoidList();


                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                        slowprint( "                                                                                         🔍 Filtered Results 🔍\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                        slowprint("\n");
                  

                        for (int i = 0; i < (int)filtered.size(); i++) {
                            int idx = filtered[i];

                            slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[idx] + "\n");
                            slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[idx]  + "\n");
                            slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[idx]   + "\n");
                            slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[idx]  + "\n");
                            slowprint( "                                                                                      📋 NOTES   : "
                                + (list_notes[idx].empty() ? "None" : list_notes[idx]) + "\n");
                            slowprint( "\n");
                        }


                        slowprint( "\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                    

                    
                        slowprint( "                                                                                 [0] ↩️ BACK\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                        slowprint( "                                                                                                ╔════╗                                     \n");
                        slowprint( "                                                                                               ╔║    ║╗                                    \n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                    slowprint( "\033[2A");
                    slowprint( "\033[98C");


                    string pickStr;
                    int    pick = 0;
                    cin >> pickStr;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (pickStr == "0") {
                        // cancel filter view, go back to main viewLists
                        break;
                    }

                    try {
                        pick = stoi(pickStr);
                    }
                    catch (...) {
                        slowprint( "\n\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                        cin.get();
                        continue;   // 🔁 redraw filtered list
                    }

                    if (pick < 1 || pick > (int)filtered.size()) {
                        slowprint( "\n\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                        cin.get();
                        continue;   // 🔁 redraw filtered list
                    }

                    int realIndex = filtered[pick - 1];

                    showSingleList(
                        realIndex,
                        name_of_list,
                        list_of_lists,
                        list_of_descriptions,
                        listmonth,
                        listdate,
                        listyear,
                        monthcreated,
                        datecreated,
                        yearcreated,
                        list_deadlines,
                        cdate, cmonth, cyear
                    );

                    // after showing single list, go back to main viewLists
                    break;
                }

                continue;   // back to main viewLists loop
            }

            } // end SEARCH/SORT/FILTER while

            continue; // back to MAIN viewLists menu
        }

        // ================================
        // USER CHOSE A LIST NUMBER
        // ================================
        int choice = 0;
        try {
            choice = stoi(choiceStr);
        }
        catch (...) {
            slowprint( "\n\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            cin.get();
            continue;
        }

        if (choice < 1 || choice > (int)name_of_list.size()) {
            slowprint( "\n\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            cin.get();
            continue;
        }

        int index = choice - 1;

        showSingleList(
            index,
            name_of_list,
            list_of_lists,
            list_of_descriptions,
            listmonth,
            listdate,
            listyear,
            monthcreated,
            datecreated,
            yearcreated,
            list_deadlines,
            cdate,
            cmonth,
            cyear
        );
    }
}


void headerEditList() {

        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                           ██╗   ██╗██████╗ ██████╗  █████╗ ████████╗███████╗    ██╗     ██╗███████╗████████╗    \n");
        slowprint( "                                                           ██║   ██║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██╔════╝    ██║     ██║██╔════╝╚══██╔══      \n");
        slowprint( "                                                           ██║   ██║██████╔╝██║  ██║███████║   ██║   █████╗      ██║     ██║███████╗   ██║           \n");
        slowprint( "                                                           ██║   ██║██╔═══╝ ██║  ██║██╔══██║   ██║   ██╔══╝      ██║     ██║╚════██║   ██║        \n");
        slowprint( "                                                           ╚██████╔╝██║     ██████╔╝██║  ██║   ██║   ███████╗    ███████╗██║███████║   ██║         \n");
        slowprint( "                                                            ╚═════╝ ╚═╝     ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚══════╝╚═╝╚══════╝   ╚═╝            \n");
        slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}

int searchLists(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string>>>& list_of_descriptions,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear,
    vector<int>& monthcreated,
    vector<int>& datecreated,
    vector<int>& yearcreated,
    vector<string>& list_categories,
    vector<string>& list_deadlines,
    vector<string>& list_priorities,
    vector<string>& list_notes,
    int& cdate,
    int& cmonth,
    int& cyear
) {
    // If no lists exist, nothing to search
    if (name_of_list.empty()) {
        slowprint( "\n");
        slowprint( "\033[0B");  // move DOWN
        slowprint( "\033[84C"); // move RIGHT
        slowprint( "\033[1;37;41m  ⚠️ NO LISTS TO SEARCH ⚠️  \033[0m\n\n");
        slowprint( string("                                                                                  ")
             + "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return -1;
    }

    while (true) {
        system("cls");
        headerVoidList();

        slowprint( "                                                                                          ┏━┓┏━╸┏━┓┏━┓┏━╸╻ ╻    \n");
        slowprint( "                                                                                          ┗━┓┣╸ ┣━┫┣┳┛┃  ┣━┫    \n");
        slowprint( "                                                                                          ┗━┛┗━╸╹ ╹╹┗╸┗━╸╹ ╹    \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint( "                                                                                       [1] 🔎 SEARCH BY NAME\n");
        slowprint( "                                                                                       [2] 🔎 SORT BY NAME (A-Z)\n");
        slowprint( "                                                                                       [3] 🔎 SORT BY NAME (Z-A)\n");
        slowprint( "                                                                                       [4] 🗂️ FILTER BY CATEGORY\n");
        slowprint( "                                                                                       [5] 📅 FILTER BY DEADLINE\n");
        slowprint( "                                                                                       [6] ❗ FILTER BY PRIORITY\n");
        slowprint( "                                                                                       [0] ↩ BACK\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

        slowprint( "                                                                                                ╔════╗                                     \n");
        slowprint( "                                                                                               ╔║    ║╗                                    \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

        slowprint( "\033[2A");
        slowprint( "\033[98C");

        string sStr;
        int s = 0;

        cin >> sStr;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (sStr == "0") {
            // back to caller
            return -1;
        }

        try {
            s = stoi(sStr);
        }
        catch (...) {
            slowprint( "\n\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            cin.get();
            continue; // back to SEARCH menu
        }

        if (s < 1 || s > 6) {
            slowprint( "\n\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                    "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            cin.get();
            continue;
        }

        // ================================
        // 1️⃣ SEARCH BY NAME
        // ================================
        if (s == 1) {

            system("cls");
            headerVoidList();

            slowprint( "                                                                              ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸            \n");
            slowprint( "                                                                              ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸            \n");
            slowprint( "                                                                              ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸         \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

            slowprint( "                                                                                      ╔════════════════════════╗                                                   \n");
            slowprint( "                                                                                     ╔║                        ║╗                                                  \n");
            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n");

            slowprint( "\033[2A");
            slowprint( "\033[98C");

            string key;
            getline(cin, key);

            vector<int> found;
            for (int i = 0; i < (int)name_of_list.size(); i++) {
                if (name_of_list[i].find(key) != string::npos)
                    found.push_back(i);
            }

            if (found.empty()) {

                system("cls");
                headerVoidList();

                slowprint( "                                                                                    ┏┓╻┏━┓   ┏━┓┏━╸┏━┓╻ ╻╻  ╺┳╸┏━┓            \n");
                slowprint( "                                                                                    ┃┗┫┃ ┃   ┣┳┛┣╸ ┗━┓┃ ┃┃   ┃ ┗━┓          \n");
                slowprint( "                                                                                    ╹ ╹┗━┛   ╹┗╸┗━╸┗━┛┗━┛┗━╸ ╹ ┗━┛        \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                        "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                cin.get();
                continue;
            }

            while (true) {
                system("cls");
                headerVoidList();

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint( "                                                                                         🔎 Search Results 🔎\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                for (int i = 0; i < (int)found.size(); i++) {
                    int idx = found[i];

                    slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[idx] + "\n");
                    slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[idx]  + "\n");
                    slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[idx]   + "\n");
                    slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[idx]  + "\n");
                    slowprint( "                                                                                      📋 NOTES   : "
                        + (list_notes[idx].empty() ? "None" : list_notes[idx]) + "\n");
                    slowprint( "\n");
                }

                slowprint("\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint( "                                                                                [0] ↩️ BACK\n\n");

                slowprint( "                                                                                                ╔════╗                                     \n");
                slowprint( "                                                                                               ╔║    ║╗                                    \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                string pickStr;
                int pick = 0;
                cin >> pickStr;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pickStr == "0") {
                    // back to search menu
                    break;
                }

                try {
                    pick = stoi(pickStr);
                }
                catch (...) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;
                }

                if (pick < 1 || pick > (int)found.size()) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;
                }

                int realIndex = found[pick - 1];

                // ✅ return this index to editList so it can open the edit screen
                return realIndex;
            }

            continue; // back to main search menu
        }

        // ================================
        // 2️⃣ SORT A-Z and 3️⃣ SORT Z-A
        // ================================
        else if (s == 2 || s == 3) {

            while (true) {
                vector<int> order(name_of_list.size());
                for (int i = 0; i < (int)order.size(); i++) order[i] = i;

                for (int i = 0; i < (int)order.size() - 1; i++) {
                    for (int j = i + 1; j < (int)order.size(); j++) {

                        bool swapNeeded = false;

                        if (s == 2 && name_of_list[order[i]] > name_of_list[order[j]])
                            swapNeeded = true;

                        if (s == 3 && name_of_list[order[i]] < name_of_list[order[j]])
                            swapNeeded = true;

                        if (swapNeeded) swap(order[i], order[j]);
                    }
                }

                system("cls");
                headerVoidList();

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint( "                                                                                         🗂️ SORTED LIST 🗂️\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");

                for (int i = 0; i < (int)order.size(); i++) {
                    int idx = order[i];

                    slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[idx] + "\n");
                    slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[idx]  + "\n");
                    slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[idx]   + "\n");
                    slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[idx]  + "\n");
                    slowprint( "                                                                                      📋 NOTES   : "
                        + (list_notes[idx].empty() ? "None" : list_notes[idx]) + "\n");
                    slowprint( "\n");
                }

                slowprint("\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint( "                                                                                 [0] ↩️ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                  \n\n");

                slowprint( "                                                                                                ╔════╗                                     \n");
                slowprint( "                                                                                               ╔║    ║╗                                    \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                string pickStr;
                int pick = 0;

                cin >> pickStr;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pickStr == "0") {
                    break; // back to search menu
                }

                try {
                    pick = stoi(pickStr);
                }
                catch (...) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;
                }

                if (pick < 1 || pick > (int)order.size()) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;
                }

                int realIndex = order[pick - 1];

                // ✅ return this index to editList
                return realIndex;
            }

            continue; // back to main search menu
        }

        // ------------------------------------------------
        // 4️⃣ 5️⃣ 6️⃣ FILTERS (Category / Deadline / Priority)
        // ------------------------------------------------
        else if (s == 4 || s == 5 || s == 6) {

            // ===========================
            // DISPLAY + REAL VALUE ARRAYS
            // ===========================
            vector<string> displayOptions;
            vector<string> valueOptions;

            if (s == 4) {
                displayOptions = {
                    "💼 WORK","🏫 SCHOOL","👤 PERSONAL","🧹 ERRANDS",
                    "💰 FINANCE","❤️‍🩹 HEALTH","📅 APPOINTMENT",
                    "🛒 SHOPPING","➕ OTHERS","⛔ NONE"
                };

                valueOptions = {
                    "Work","School","Personal","Errands",
                    "Finance","Health","Appointment",
                    "Shopping","Others","None"
                };
            }
            else if (s == 5) {
                displayOptions = {
                    "📅 TODAY","📅 TOMORROW","📅 THIS WEEK",
                    "📅 NEXT WEEK","📅 NEXT MONTH"
                };

                valueOptions = {
                    "Today","Tomorrow","This Week",
                    "Next Week","Next Month"
                };
            }
            else if (s == 6) {
                displayOptions = {
                    "⚠️ CRITICAL","🔴 HIGH","🟠 MEDIUM",
                    "🟢 LOW","⛔ NONE"
                };

                valueOptions = {
                    "Critical","High","Medium","Low","None"
                };
            }

            // ========= SELECT FILTER TYPE =========
            vector<string> options;
            if (s == 4) {
                options = { "💼 WORK ","🏫 SCHOOL ","👤 PERSONAL","🧹 ERRANDS","💰 FINANCE","❤️‍🩹 HEALTH","📅 APPOINTMENT","🛒 SHOPPING","➕ OTHERS","⛔ NONE" };
            }
            else if (s == 5) {
                options = { "📅 TODAY","📅 TOMORROW","📅 THIS WEEK","📅 NEXXT WEEK","📅 NEXT MONTH" };
            }
            else if (s == 6) {
                options = { "⚠️ CRITICAL","🔴 HIGH ","🟠 MEDIUM","🟢 LOW","⛔ NONE" };
            }

            // ========== STEP 1: CHOOSE FILTER OPTION (fc) ==========
            string fcStr;
            int    fc      = 0;
            bool   goBack  = false;

            while (true) {
                system("cls");
                headerVoidList();

                slowprint( "                                                                                  ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏━┓┏━┓╺┳╸╻┏━┓┏┓╻   \n");
                slowprint( "                                                                                  ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃ ┃┣━┛ ┃ ┃┃ ┃┃┗┫    \n");
                slowprint( "                                                                                  ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ┗━┛╹   ╹ ╹┗━┛╹ ╹    \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

                for (int i = 0; i < (int)options.size(); i++) {
                    slowprint( "                                                                                  " + to_string(i + 1) + ". " + options[i] + "\n");
                }

                slowprint( "                                                                                 [0] ↩️ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                slowprint( "                                                                                                ╔════╗                                     \n");
                slowprint( "                                                                                               ╔║    ║╗                                    \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                cin >> fcStr;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (fcStr == "0") {
                    goBack = true;   // back to SEARCH / SORT menu
                    break;
                }

                try {
                    fc = stoi(fcStr);
                }
                catch (...) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;   // 🔁 redraw filter options
                }

                if (fc < 1 || fc > (int)options.size()) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;   // 🔁 redraw filter options
                }

                // valid selection
                break;
            }

            if (goBack) {
                // user pressed 0 in filter menu
                continue;   // back to main SEARCH menu
            }

            // ========= BUILD FILTER RESULT =========
            vector<int> filtered;
            for (int i = 0; i < (int)name_of_list.size(); i++) {

                string value;
                if (s == 4) value = list_categories[i];
                if (s == 5) value = list_deadlines[i];
                if (s == 6) value = list_priorities[i];

                if (value == valueOptions[fc - 1])
                    filtered.push_back(i);
            }

            if (filtered.empty()) {

                system("cls");
                headerVoidList();

                slowprint( "                                                                                 ┏┓╻┏━┓   ╻  ╻┏━┓╺┳╸┏━┓   ┏━╸┏━┓╻ ╻┏┓╻╺┳┓       \n");
                slowprint( "                                                                                 ┃┗┫┃ ┃   ┃  ┃┗━┓ ┃ ┗━┓   ┣╸ ┃ ┃┃ ┃┃┗┫ ┃┃   \n");
                slowprint( "                                                                                 ╹ ╹┗━┛   ┗━╸╹┗━┛ ╹ ┗━┛   ╹  ┗━┛┗━┛╹ ╹╺┻┛    \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                        "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");

                cin.get();
                continue;   // back to SEARCH menu
            }

            // ========= DISPLAY RESULTS & LET USER PICK =========
            while (true) {
                system("cls");
                headerVoidList();

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint( "                                                                                         🔍 Filtered Results 🔍\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint("\n");

                for (int i = 0; i < (int)filtered.size(); i++) {
                    int idx = filtered[i];

                    slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[idx] + "\n");
                    slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[idx]  + "\n");
                    slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[idx]   + "\n");
                    slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[idx]  + "\n");
                    slowprint( "                                                                                      📋 NOTES   : "
                        + (list_notes[idx].empty() ? "None" : list_notes[idx]) + "\n");
                    slowprint( "\n");
                }

                slowprint( "\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n");
                slowprint( "                                                                                 [0] ↩️ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                slowprint( "                                                                                                ╔════╗                                     \n");
                slowprint( "                                                                                               ╔║    ║╗                                    \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                string pickStr;
                int    pick = 0;
                cin >> pickStr;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pickStr == "0") {
                    // cancel filter view, go back to SEARCH menu
                    break;
                }

                try {
                    pick = stoi(pickStr);
                }
                catch (...) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;   // 🔁 redraw filtered list
                }

                if (pick < 1 || pick > (int)filtered.size()) {
                    slowprint( "\n\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                 \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    cin.get();
                    continue;   // 🔁 redraw filtered list
                }

                int realIndex = filtered[pick - 1];

                // ✅ return this index to editList
                return realIndex;
            }

            continue;   // back to SEARCH menu
        }

    } // end main while

    // Fallback (shouldn't normally hit)
    return -1;
}

// ------------------------------------------------------
// Reusable list preview for edit screens
// ------------------------------------------------------
void printListPreviewForEdit(
    const vector<string>& items,
    const vector<vector<string>>& descriptions,
    const string& listTitle,
    const string& category,
    const string& deadline,
    const string& priority,
    const string& notes
) {
    slowprint( "\n");
    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    slowprint( "                                                                                         📝 LIST PREVIEW\n");
    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

    // 🔹 Print list header (same format as main view)
    slowprint( "                                                                          📝 LISTNAME : " + listTitle + "\n");
    slowprint( "                                                                          🗂️ CATEGORY : " + category + "\n");
    slowprint( "                                                                          📅 DEADLINE : " + deadline + "\n");
    slowprint( "                                                                          ❗ PRIORITY : " + priority + "\n");
    slowprint( "                                                                          📋 NOTES    : "
         + (notes.empty() ? "None" : notes) + "\n\n");
    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    // 🔹 No items?
    if (items.empty()) {
        slowprint( "                                                                                 (No items in this list yet)\n\n");
        return;
    }

    // 🔹 Print items + descriptions
    for (int i = 0; i < (int)items.size(); ++i) {
        slowprint( "                                                                           " + to_string(i + 1) + ". " + items[i] + "\n");

        if (i < (int)descriptions.size()) {
            for (const string& desc : descriptions[i]) {
        slowprint( "                                                                               • \033[3m" + desc + "\033[0m\n"); // italic description
            }
        }
        slowprint( "\n");
    }

    slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}


// ------------------------------------------------------
// Helper: show all descriptions for a given item number
// ------------------------------------------------------
void printDescriptionsForItem(const vector<vector<string>>& descriptions,
                              int itemNum)
{
    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");
    slowprint( "                                                                                  Current descriptions:\n");

    // safety + empty check
    if (itemNum - 1 < 0 ||
        itemNum - 1 >= (int)descriptions.size() ||
        descriptions[itemNum - 1].empty())
    {
 
        slowprint( "                                                                                               (no descriptions)\n");
        return;
    }

    for (int d = 0; d < (int)descriptions[itemNum - 1].size(); ++d) {
        slowprint( "                                                                                  " + to_string(d + 1) + ". " + descriptions[itemNum - 1][d] + "\n");
    }

    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");
    slowprint( "\n");
    
}


// -----------------------------
void editList(
    vector<string> &name_of_list,
    vector<vector<string>> &list_of_lists,
    vector<vector<vector<string>>> &list_of_descriptions,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear,
    vector<string>& list_categories,
    vector<string>& list_deadlines,
    vector<string>& list_priorities,
    vector<string>& list_notes,
    vector<int>& monthcreated,
    vector<int>& datecreated,
    vector<int>& yearcreated,
    int& cdate,
    int& cmonth,
    int& cyear
)
 {
    // If no lists exist, there is nothing to edit
    if (name_of_list.size() == 0) {

        slowprint( "\n");
        slowprint( "\033[0B");  // move DOWN 1 line
        slowprint( "\033[84C"); // move RIGHT
        slowprint( "\033[1;37;41m  ⚠️ NO LISTS TO EDIT ⚠️  \033[0m\n\n");
        slowprint( string("                                                                                  ")
             + "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");

        getch();
        return;
    }

    // =================================================
    // NEW: LOOP UNTIL USER PICKS A VALID LIST INDEX
    // =================================================
    int index = -1;   // final 0-based index of list to edit

    while (true) {
        system("cls");
        headerEditList();

        slowprint( "                                                             ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓   ╺┳╸┏━┓   ┏━╸╺┳┓╻╺┳╸          \n");
        slowprint( "                                                             ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┣━┫   ┃  ┃┗━┓ ┃    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛    ┃ ┃ ┃   ┣╸  ┃┃┃ ┃         \n");
        slowprint( "                                                             ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹   ┗━╸╹┗━┛ ╹    ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸    ╹ ┗━┛   ┗━╸╺┻┛╹ ╹           \n\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n\n");


        for (int i = 0; i < (int)name_of_list.size(); i++) {
            slowprint( "                                                                                  " + to_string(i + 1) + ". " + name_of_list[i] + "\n");
            slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[i]  + "\n");
            slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[i]   + "\n");
            slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[i]  + "\n");
            slowprint( "                                                                                      📋 NOTES   : "
                 + (list_notes[i].empty() ? "None" : list_notes[i]) + "\n");
            slowprint( "\n");
        }

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");


        slowprint("\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");
        slowprint( "                                                                                      [S] 🔎 SEARCH LIST NAMES                             \n");
        slowprint( "                                                                                      [0] 🔙 BACK TO MAIN MENU                            \n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n");
        slowprint( "                                                                                                ╔════╗                                     \n");
        slowprint( "                                                                                               ╔║    ║╗                                    \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                               \n");

        string choiceStr;
        cin >> choiceStr;

        if (choiceStr == "S" || choiceStr == "s") {
            int foundIndex = searchLists(
                name_of_list,
                list_of_lists,
                list_of_descriptions,
                listmonth,
                listdate,
                listyear,
                monthcreated,
                datecreated,
                yearcreated,
                list_categories,
                list_deadlines,
                list_priorities,
                list_notes,
                cdate,
                cmonth,
                cyear
            );

            if (foundIndex == -1) {
                // user backed out of search → redraw list selection
                continue;
            }

            // ✅ use this index as the list to edit
            index = foundIndex;
            break;   // jump down into the EDIT LOOP for that list
        }


        // Back to main menu
        if (choiceStr == "0") {
            return;
        }

        int choice = 0;

        try {
            choice = stoi(choiceStr);
        } catch (...) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            slowprint( "\n");
            slowprint( "                                            \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
            getch();
            // 🔁 go back to top, redraw list selection screen
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Validate list index
        if (choice < 1 || choice > (int)name_of_list.size()) {
            slowprint( "\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
            getch();
            // 🔁 invalid but we stay inside editList and re-show lists
            continue;
        }

        // ✅ valid choice → convert to 0-based index and leave the loop
        index = choice - 1;
        break;
    }

    // =================================================
    // BELOW THIS POINT: your existing EDIT MENU LOOP
    // (no changes needed)
    // =================================================

    // =============================================
    // EDIT LOOP — continues until user exits
    // =============================================
    while (true) {

        system("cls");
        headerEditList();

        slowprint( "                                                                            ┏━╸╺┳┓╻╺┳╸   ┏┳┓┏━╸┏┓╻╻ ╻   ┏━┓┏━┓╺┳╸╻┏━┓┏┓╻            \n");
        slowprint( "                                                                            ┣╸  ┃┃┃ ┃    ┃┃┃┣╸ ┃┗┫┃ ┃   ┃ ┃┣━┛ ┃ ┃┃ ┃┃┗┫         \n");
        slowprint( "                                                                            ┗━╸╺┻┛╹ ╹    ╹ ╹┗━╸╹ ╹┗━┛   ┗━┛╹   ╹ ╹┗━┛╹ ╹          \n\n");

        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        slowprint( "                                                                         📋 LIST NAME : " + name_of_list[index]      + "\n");
        slowprint( "                                                                         🗂️ CATEGORY  : " + list_categories[index]   + "\n");
        slowprint( "                                                                         📅 DEADLINE  : " + list_deadlines[index]    + "\n");
        slowprint( "                                                                         ❗ PRIORITY  : " + list_priorities[index]   + "\n");
        slowprint( "                                                                         📝 NOTES     : "
             + (list_notes[index].empty() ? "None" : list_notes[index])       + "\n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        slowprint( "\n");

        vector<string> &items = list_of_lists[index];

        if (index >= (int)list_of_descriptions.size()) {
            int oldSize = list_of_descriptions.size();
            list_of_descriptions.resize(index + 1);
            for (int t = oldSize; t < (int)list_of_descriptions.size(); t++) {
                list_of_descriptions[t] = vector<vector<string>>();
            }
        }

        vector<vector<string>> &descriptions = list_of_descriptions[index];

        int completedCount = 0;

        if (items.empty()) {
            slowprint( "(No items yet)\n");
        } else {
            for (int i = 0; i < (int)items.size(); i++) {
                slowprint( "                                                                            " + to_string(i + 1) + ". " + items[i] + "\n");

                if (i < (int)descriptions.size()) {
                    for (string &d : descriptions[i]) {
                        slowprint( "                                                                               • " + d + "\n");
                    }
                }

                if (items[i].find("✅") != string::npos)
                    completedCount++;
            }
        }

        int notDone = items.size() - completedCount;
        double percentDone = items.size() > 0 ? (completedCount * 100.0) / items.size() : 0;

        slowprint( "\n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n");
        slowprint( "                                                                                             𝐒𝐓𝐀𝐓𝐈𝐒𝐓𝐈𝐂𝐒                                \n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n");

        slowprint( "                                                                          Total Items       : " + to_string(items.size()) + "\n");
        slowprint( "                                                                          Completed Items   : " + to_string(completedCount) + "\n");
        slowprint( "                                                                          Not Done          : " + to_string(notDone) + "\n");
        cout << fixed << setprecision(2);
        slowprint( "                                                                          % Completed       : " + fmt2(percentDone) + "%\n");
        slowprint( "\n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n");
        slowprint( "                                                                         [1] ✚ ADD NEW ITEM            [2] ✏️ EDIT AN ITEM                \n");
        slowprint( "                                                                         [3] 🗑️ DELETE AN ITEM         [4] ✅ MARK / UNMARK DONE       \n");
        slowprint( "                                                                         [5] 🔁 REORDER ITEMS (SWAP)   [6] 📝 RENAME LIST               \n");
        slowprint( "                                                                         [7] ✏️ EDIT LIST DETAILS      [8] 🔙 RETURN TO MAIN MENU        \n\n");
        slowprint( "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

        slowprint( "\033[2A");  
        slowprint( "\033[98C");  

        string editChoiceStr;
        int editChoice = 0;

        cin >> editChoiceStr;

        try {
            editChoice = stoi(editChoiceStr);
        } 
        catch (...) {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
            getch();
            continue;    // 🔥 RESTART WHOLE MENU
        }

        if (editChoice < 1 || editChoice > 8) {
            slowprint( "\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
            getch();
            continue;    // 🔥 RESTART WHOLE MENU
        }

        // VALID → BREAK OUT AND HANDLE OPTION
        // You keep your logic after this.


        // ============================================
        // OPTION 1 — ADD NEW ITEM
        // ============================================
        if (editChoice == 1) {

            // 🔹 Clear leftover newline from "cin >> editChoice"
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Local variables that mirror createNewList logic
            string item, descLine;
            vector<string> tempDescriptions;
            int itemIndex, dindex, dsaveIndex;

        while (true) {
            system("cls");
            headerEditList();
            printListPreviewForEdit(
                list_of_lists[index],        // items
                list_of_descriptions[index], // descriptions
                name_of_list[index],         // title
                list_categories[index],      // category
                list_deadlines[index],       // deadline
                list_priorities[index],      // priority
                list_notes[index]            // notes
            );
   // current list state

            slowprint( "                                                        ┏━┓╺┳╸┏━┓┏━┓╺┳╸   ┏━┓╺┳┓╺┳┓╻┏┓╻┏━╸   ╻╺┳╸┏━╸┏┳┓┏━┓   ╺┳╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ╻  ╻┏━┓╺┳╸╻            \n");
            slowprint( "                                                        ┗━┓ ┃ ┣━┫┣┳┛ ┃    ┣━┫ ┃┃ ┃┃┃┃┗┫┃╺┓   ┃ ┃ ┣╸ ┃┃┃┗━┓    ┃ ┃ ┃   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┃┗━┓ ┃ ╹  \n");
            slowprint( "                                                        ┗━┛ ╹ ╹ ╹╹┗╸ ╹    ╹ ╹╺┻┛╺┻┛╹╹ ╹┗━┛   ╹ ╹ ┗━╸╹ ╹┗━┛    ╹ ┗━┛    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹┗━┛ ╹ ╹          \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");

            slowprint( "                                                                                    🟢 TYPE AN ITEM AND PRESS ENTER!\n");
            slowprint( "                                                                       Type 💾[1] DONE ADDING ITEMS | 🗑️[2] CANCEL THIS NEW ITEM \n\n");

            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
            slowprint( "                                                                                     ╔║                        ║╗                             \n");
            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

            slowprint( "\033[2A"); // move UP 2 lines
            slowprint( "\033[87C"); // move RIGHT (adjust as needed)

            slowprint( "Add item: ");
            getline(cin, item);

            // --- EXIT OPTION 1 ---
            if (item == "1") {
                break; 
            }

            // --- CANCEL this new item ---
            if (item == "2") {
                slowprint( "\nNew item creation cancelled.\n");
                slowprint( "Press Enter to continue...");
                cin.get();
                break;
            }

            // ======================================================
            // UPDATED ERROR HANDLING  — SAME STYLE AS deleteList
            // ======================================================
            if (item.empty() || item.find_first_not_of(" \t\r\n") == string::npos)
            {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

                getch();   // wait for key
                continue;  // 🔥 restart OPTION 1 (NOT whole menu)
            }

                // ========== IF VALID, ADD ITEM ==========
                items.push_back(item);
                descriptions.resize(items.size()); // ensure description array aligns

                slowprint("\n");
                slowprint( "                                                                                 \033[1;48;2;255;255;255m\033[38;2;0;128;0m  ✅ ITEM ADDED SUCCESSFULLY!  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

                getch();   // same behavior as your other handlers


                // Add new item at the end (same pattern as createNewList)
                itemIndex = static_cast<int>(items.size());
                items.resize(itemIndex + 1);
                items[itemIndex] = item;

                // Give XP for adding an item
                addClassXP(5, gamificationEnabled, playerXP, playerLevel,
                    playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);

                // 🔹 Refresh screen so the new item appears in the live list
                system("cls");
                headerEditList();
                printListPreviewForEdit(
                    list_of_lists[index],        // items
                    list_of_descriptions[index], // descriptions
                    name_of_list[index],         // title
                    list_categories[index],      // category
                    list_deadlines[index],       // deadline
                    list_priorities[index],      // priority
                    list_notes[index]            // notes
                );
   // still no descriptions for this new item yet

                // ===================================================
                // ENTER DESCRIPTIONS FOR THIS NEW ITEM
                // ===================================================
                slowprint( "                                                         ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓╻            \n");
                slowprint( "                                                         ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃╹            \n");
                slowprint( "                                                         ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹╹          \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                           \n");

                slowprint( "                                                                                🟢 TYPE A DESCRIPTION AND PRESS ENTER!\n");
                slowprint( "                                                                                   Type [1] 🗑️ FINISH / SKIP DESCRIPTIONS \n\n");

                slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                slowprint( "                                                                                     ╔║                        ║╗                             \n");
                slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

                tempDescriptions.clear();

                while (true) {
                    slowprint( "\033[2A"); // move UP 2 lines
                    slowprint( "\033[90C"); // move RIGHT
                    getline(cin, descLine);

                    // Finish / skip descriptions for this item
                    if (descLine == "1")
                        break;

                    if (descLine.empty())
                        continue;

                    // Add this description line to tempDescriptions
                    dindex = static_cast<int>(tempDescriptions.size());
                    tempDescriptions.resize(dindex + 1);
                    tempDescriptions[dindex] = descLine;

                    addClassXP(1, gamificationEnabled, playerXP, playerLevel,
                        playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);

                    // 🔹 LIVE PREVIEW: show list including this item's in-progress descriptions
                    system("cls");
                    headerEditList();

                    // 👇 build preview copy = existing descriptions + current tempDescriptions
                    vector<vector<string>> previewDescriptions = descriptions;
                    previewDescriptions.push_back(tempDescriptions);

                    // 👈 IMPORTANT: use previewDescriptions here
                    printListPreviewForEdit(
                    list_of_lists[index],        // items
                    list_of_descriptions[index], // descriptions
                    name_of_list[index],         // title
                    list_categories[index],      // category
                    list_deadlines[index],       // deadline
                    list_priorities[index],      // priority
                    list_notes[index]            // notes
                );


                    slowprint( "                                                         ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓╻            \n");
                    slowprint( "                                                         ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃╹            \n");
                    slowprint( "                                                         ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹╹          \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                             \n");
                    slowprint( "                                                                                     Type [1] 💾 FINISH DESCRIPTION \n\n");

                    slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                    slowprint( "                                                                                     ╔║                        ║╗                             \n");
                    slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");
                }

                // Save this item’s description list to the real descriptions vector
                dsaveIndex = static_cast<int>(descriptions.size());
                descriptions.resize(dsaveIndex + 1);
                descriptions[dsaveIndex] = tempDescriptions;

                // 🔹 Re-show the updated list after saving this item
                system("cls");
                headerEditList();
                printListPreviewForEdit(
                    list_of_lists[index],        // items
                    list_of_descriptions[index], // descriptions
                    name_of_list[index],         // title
                    list_categories[index],      // category
                    list_deadlines[index],       // deadline
                    list_priorities[index],      // priority
                    list_notes[index]            // notes
                );


                slowprint( "\nItem + descriptions saved!\n\n");

                slowprint( "                                                                        ╻╺┳╸┏━╸┏┳┓    ╻    ╺┳┓┏━╸┏━┓┏━╸┏━╓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━┓┏━┓╻ ╻┏━╸╺┳┓       \n");
                slowprint( "                                                                        ┃ ┃ ┣╸ ┃┃┃   ╺╋╸    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┗━┓┣━┫┃┏┛┣╸  ┃┃    \n");
                slowprint( "                                                                        ╹ ╹ ┗━╸╹ ╹    ╹    ╺┻┛┗━╸┗━┛┗━╸╹┗ ╹╹   ╹ ╹┗━┛╹ ╹   ┗━┛╹ ╹┗┛ ┗━╸╺┻┛     \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                getch();

                // After one item + description cycle, we return to the main edit menu
                break;
            }

            continue;
        }

        // ============================================
        // OPTION 2 — EDIT ITEM (NAME / DESCRIPTIONS / DELETE)
        // ============================================
        else if (editChoice == 2) {

        // no items yet
        if (items.empty()) {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ NO ITEMS TO EDIT. PLEASE ADD ONE FIRST. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
            getch();
            continue;   // restart edit menu
        }

        // -----------------------------------
        // 2A — CHOOSE WHICH ITEM TO EDIT
        // -----------------------------------
        int itemNum = 0;
        string itemNumStr;

        while (true)
        {
            system("cls");
            headerEditList();
            printListPreviewForEdit(
            list_of_lists[index],        // items
            list_of_descriptions[index], // descriptions
            name_of_list[index],         // title
            list_categories[index],      // category
            list_deadlines[index],       // deadline
            list_priorities[index],      // priority
            list_notes[index]            // notes
            );


            slowprint( "                                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━╓   ╻╺┳╸┏━╸┏┳┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓\n");
            slowprint( "                                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃ ┃ ┣╸ ┃┃┃   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛ \n");
            slowprint( "                                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹ ┗━╸╹ ╹   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸\n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

            slowprint( "\033[2A"); // move cursor up 2 lines
            slowprint( "\033[98C");

            // ask user
            cin >> itemNumStr;

            // try to convert
            try {
                itemNum = stoi(itemNumStr);
            }
            catch (...) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                getch();
                continue;   // restart entire item selection
            }

            // valid number format, now range check
            if (itemNum < 1 || itemNum > (int)items.size()) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                getch();
                continue;   // restart entire item selection
            }

            // SUCCESS — user selected a valid item
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            break;
        }

            // ------------------------------------
            // At this point, itemNum is VALID.
            // Continue OPTION 2 logic (rename, edit desc, delete, etc.)
            // ------------------------------------

            // -------- 2B: main ITEM EDIT MENU for that item --------
            bool itemDeleted = false;

            while (true) {
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                                 ╻╺┳╸┏━╸┏┳┓   ┏━╸╺┳┓╻╺┳╸   ┏┳┓┏━╸┏┓╻╻ ╻                  \n");
                slowprint( "                                                                                 ┃ ┃ ┣╸ ┃┃┃   ┣╸  ┃┃┃ ┃    ┃┃┃┣╸ ┃┗┫┃ ┃                 \n");
                slowprint( "                                                                                 ╹ ╹ ┗━╸╹ ╹   ┗━╸╺┻┛╹ ╹    ╹ ╹┗━╸╹ ╹┗━┛                \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                  Editing item: " + items[itemNum - 1] + "\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                  [1] ✏️ EDIT ITEM NAME\n");
                slowprint( "                                                                                  [2] 📝 EDIT ITEM DESCRIPTIONS\n");
                slowprint( "                                                                                  [3] 🗑️ DELETE ITEM\n");
                slowprint( "                                                                                  [4] ↩️ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2B");   // move cursor down into the small box
                slowprint( "\033[98C");  // move cursor horizontally to center input

                int subChoice;
                cin >> subChoice;

                // ==============================
                // INVALID INPUT (letters, etc.)
                // ==============================
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw 2B menu
                }

                // ==============================
                // INVALID CHOICE (not 1–4)
                // ==============================
                if (subChoice < 1 || subChoice > 4) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw 2B menu
                }

                // clean leftover newline once input is valid
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // -------- SUB 4: back to main edit menu --------
                if (subChoice == 4) {
                    break;
                }

                // -------- SUB 1: edit item name (with confirmation) --------
                else if (subChoice == 1) {
                    string newName;

                    system("cls");
                    headerEditList();
                    printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                    slowprint( "                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ┏┓╻┏━╓┏┳┓┏━╸   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓            \n");
                    slowprint( "                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃   ┃┗┫┣━┫┃┃┃┣╸    ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃            \n");
                    slowprint( "                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛   ╹ ╹╹ ╹╹ ╹┗━╸   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹            \n\n");

                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");

                    slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                    slowprint( "                                                                                     ╔║                        ║╗                             \n");
                    slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

                    slowprint( "\033[2A");   // move cursor up into the small box
                    slowprint( "\033[98C");  // move cursor horizontally to center input

                    getline(cin, newName);

                    // confirmation
                    system("cls");
                    headerEditList();
                    printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                    slowprint( "                                                                                           ┏━┓┏━╸┏┓╻┏━┓┏┳┓┏━╸                 \n");
                    slowprint( "                                                                                           ┣┳┛┣╸ ┃┗┫┣━┫┃┃┃┣╸             \n");
                    slowprint( "                                                                                           ╹┗╸┗━╸╹ ╹╹ ╹╹ ╹┗━╸               \n\n");

                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                    slowprint( "                                                                                  \"" + items[itemNum - 1] + "\"\n");
                    slowprint( "                                                                                   to \"" + newName + "\" ?\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                    slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                    slowprint( "                                                                                                ╔════╗                              \n");
                    slowprint( "                                                                                               ╔║    ║╗                             \n");
                    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                    slowprint( "\033[2A");   // move cursor up into the small box
                    slowprint( "\033[98C");  // move cursor horizontally to center input

                    int confirm;

                    while (true) {
                        // keep cursor inside the small box every retry
                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        cin >> confirm;

                        // non-numeric / failed input
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // 🔁 re-ask for confirm
                        }

                        // flush leftover chars (e.g. "12a")
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // must be 1 or 2
                        if (confirm == 1 || confirm == 2) {
                            break;
                        }

                        slowprint("\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                        getch();
                        // loop again, cursor is repositioned at top by the two ESC codes
                    }

                    if (confirm == 1) {
                        if (items[itemNum - 1].find("✅") != string::npos)
                            items[itemNum - 1] = "✅" + newName;
                        else
                            items[itemNum - 1] = newName;

                        // confirmation
                        system("cls");
                        headerEditList();
                        printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                        slowprint( "                                                                                  ╻╺┳╸┏━╸┏┳┓   ┏━┓┏━╸┏┓╻┏━┓┏┳┓┏━╸╺┳┓╻         \n");
                        slowprint( "                                                                                  ┃ ┃ ┣╸ ┃┃┃   ┣┳┛┣╸ ┃┗┫┣━┫┃┃┃┣╸  ┃┃╹      \n");
                        slowprint( "                                                                                  ╹ ╹ ┗━╸╹ ╹   ╹┗╸┗━╸╹ ╹╹ ╹╹ ╹┗━╸╺┻┛╹          \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                    } else {
                        slowprint( "Rename cancelled.\n");

                        system("cls");
                        headerEditList();
                        printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                        slowprint( "                                                                           ┏━┓┏━╸┏┓╻┏━╸┏┳┓┏━╸   ┏━╸┏━┓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓         \n");
                        slowprint( "                                                                           ┣┳┛┣╸ ┃┗┫┣━┫┃┃┃┣╸    ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃   \n");
                        slowprint( "                                                                           ╹┗╸┗━╸╹ ╹╹ ╹╹ ╹┗━╸   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛      \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                    }

                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                    getch();
                }

                // -------- SUB 2: edit descriptions (edit/add/delete) --------
                else if (subChoice == 2) {

                    while (true) {
                        system("cls");
                        headerEditList();

                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n\n");
                        slowprint( "                                                                                 Descriptions for item: " + items[itemNum - 1] + "\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n\n");

                        // show current descriptions
                        printDescriptionsForItem(descriptions, itemNum);

                        slowprint( "                                                                        ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸╺┳┓╻╺┳╸   ┏┳┓┏━╸┏┓╻╻ ╻                  \n");
                        slowprint( "                                                                         ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸  ┃┃┃ ┃    ┃┃┃┣╸ ┃┗┫┃ ┃                \n");
                        slowprint( "                                                                        ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ┗━╸╺┻┛╹ ╹    ╹ ╹┗━╸╹ ╹┗━┛          \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                        slowprint( "                                                                                  [1] ✏️ EDIT DESCRIPTION TEXT\n");
                        slowprint( "                                                                                  [2] 📝 ADD NEW DESCRIPTION\n");
                        slowprint( "                                                                                  [3] 🗑️ DELETE A DESCRIPTION\n");
                        slowprint( "                                                                                  [4] ↩️ BACK\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                        slowprint( "                                                                                                ╔════╗                              \n");
                        slowprint( "                                                                                               ╔║    ║╗                             \n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                        slowprint( "\033[2A");   // move cursor down into the small box
                        slowprint( "\033[98C");  // move cursor horizontally to center input

                        int descChoice;
                        cin >> descChoice;

                        // =============== INVALID INPUT (letters etc.) ===============
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // 🔁 restart description menu
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // =============== INVALID CHOICE (not 1–4) ===============
                        if (descChoice < 1 || descChoice > 4) {
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // 🔁 restart description menu
                        }

                        if (descChoice == 4) break; // back

                        // ---------- Ensure vector exists ----------
                        if ((int)descriptions.size() <= itemNum - 1)
                            descriptions.resize(itemNum);

                        // ==================================================================
                        //  [1] EDIT DESCRIPTION TEXT
                        // ==================================================================
                        if (descChoice == 1) {

                            if (descriptions[itemNum - 1].empty()) {
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ NO DESCRIPTIONS TO EDIT. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                                getch();
                                continue;
                            }

                            int dn;

                            system("cls");
                            headerEditList();
                            printDescriptionsForItem(descriptions, itemNum);

                            slowprint( "                                                                 ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╺┳┓┏━╸┏━╸┏━╸┏━╓╻┏━╓╺┳╸╻┏━┓┏┓╻   ┏┓╻┏━╓┏┳┓┏┓ ┏━╸\n");
                            slowprint( "                                                                 ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┫ ┃ ┃┃ ┃┃┗┫   ┃┗┫┣━┫┃┃┃┣┻┓┣╸ \n");
                            slowprint( "                                                                 ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹ ╹ ╹ ╹┗━┛╹ ╹   ╹ ╹╹ ╹╹ ╹┗━┛┗━╸\n\n");

                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                            slowprint( "                                                                                                ╔════╗                              \n");
                            slowprint( "                                                                                               ╔║    ║╗                             \n");
                            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            cin >> dn;

                            // invalid # input
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;
                            }

                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            // invalid description #
                            if (dn < 1 || dn > (int)descriptions[itemNum - 1].size()) {
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID DESCRIPTION NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;
                            }

                            string newDesc;

                            system("cls");
                            headerEditList();
                            printDescriptionsForItem(descriptions, itemNum);

                            slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━╸┏━╸┏━╓╻┏━╓╺┳╸╻┏━┓┏┓╻             \n");
                            slowprint( "                                                                               ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━╓ ┃ ┃┃ ┃┃┗┫             \n");
                            slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹             \n\n");

                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                            slowprint( "                                                                                     ╔║                        ║╗                             \n");
                            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            getline(cin, newDesc);

                            // ========== CONFIRMATION ==========
                            system("cls");
                            headerEditList();
                            printDescriptionsForItem(descriptions, itemNum);

                            slowprint( "                                                                                        ┏━╸┏━╸┏┓╻┏━╸╻┏━┓┏┳┓┏━┓                 \n");
                            slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛             \n");
                            slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                  Change description to:\n");
                            slowprint( "                                                                                    \"" + newDesc + "\" ?\n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                                ╔════╗                              \n");
                            slowprint( "                                                                                               ╔║    ║╗                             \n");
                            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            int c;
                            cin >> c;

                            if (cin.fail() || (c != 1 && c != 2)) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;
                            }

                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (c == 1) {
                                descriptions[itemNum - 1][dn - 1] = newDesc;

                                system("cls");
                                headerEditList();
                                printDescriptionsForItem(descriptions, itemNum);

                                slowprint( "                                                                        ╺┳┓┏━╸┏━╸┏━╓┏━╓╺┳╸╻┏━╓┏┓╻   ╻ ╻┏━╓╺┳┓┏━╓╺┳┓        \n");
                                slowprint( "                                                                         ┃┃┣╸ ┗━┓┃  ┣━┫┃┃┃ ┃ ┃┃ ┃┃┗┫   ┃ ┃┣━┓ ┃┃┣━┫ ┃┃    \n");
                                slowprint( "                                                                        ╺┻┛┗━╸┗━┛┗━╸╹ ╹╹╹   ╹ ╹┗━┛╹ ╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   \n\n");
                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                            } else {
                                // cancel edit
                                slowprint( "Edit cancelled.\n");
                                system("cls");
                                headerEditList();
                                printDescriptionsForItem(descriptions, itemNum);

                                slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                                slowprint( "                                                                               ┣╸  ┃┃┃ ┃    ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃    \n");
                                slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛    \n\n");
                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                            }

                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            getch();
                        }

                        // ==================================================================
                        //  [2] ADD NEW DESCRIPTION
                        // ==================================================================
                        else if (descChoice == 2) {

                            string nd;

                            system("cls");
                            headerEditList();
                            printDescriptionsForItem(descriptions, itemNum);

                            slowprint( "                                                                       ┏━╸╺┳┓╺┳┓   ┏┓╻┏━╸╻ ╻   ╺┳┓┏━╸┏━╓┏━╓╺┳╸╻┏━╓┏┓╻           \n");
                            slowprint( "                                                                       ┣━┫ ┃┃ ┃┃   ┃┗┫┣╸ ┃╻┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━╓ ┃┃            \n");
                            slowprint( "                                                                       ╹ ╹╺┻┛╺┻┛   ╹ ╹┗━╸┗┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹           \n\n");

                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                            slowprint( "                                                                                     ╔║                        ║╗                             \n");
                            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            getline(cin, nd);

                            if (!nd.empty()) {
                                descriptions[itemNum - 1].push_back(nd);

                                // XP gain kept intact
                                addClassXP(1, gamificationEnabled, playerXP, playerLevel,
                                    playerClass, assassinStreak, assassinStacks,
                                    wizardCounter, archerStreak, tankStacks);

                                system("cls");
                                headerEditList();
                                printDescriptionsForItem(descriptions, itemNum);

                                slowprint( "                                                                            ╺┳┓┏━╓┏━╓┏━╓╺┳╸╻┏━╓┏┓╻   ┏━╓╺┳┓╺┳┓┏━╓╺┳┓        \n");
                                slowprint( "                                                                             ┃┃┣╸ ┗━┓┃  ┣╸ ┃ ┃┃ ┃┃┗┫   ┣━┫ ┃┃ ┃┃┣╸  ┃┃    \n");
                                slowprint( "                                                                            ╺┻┛┗━╸┗━┛┗━╸╹   ╹ ╹┗━┛╹ ╹   ╹ ╹╺┻┛╺┻┛┗━╸╺┻┛    \n\n");

                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                            }

                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            getch();
                        }

                        // ==================================================================
                        //  [3] DELETE A DESCRIPTION
                        // ==================================================================
                        else if (descChoice == 3) {

                            if (descriptions[itemNum - 1].empty()) {
                                slowprint("\n");
                                slowprint( "                                                                                  \033[1;37;41m  ⚠️ NO DESCRIPTIONS TO DELETE. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m")   ;
                                getch();
                                continue;
                            }

                            int dnDel;

                            system("cls");
                            headerEditList();
                            printDescriptionsForItem(descriptions, itemNum);

                            slowprint( "                                                                    ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏━╸┏━╓╻┏━╓╺┳╸╻┏━╓┏┓╻   ┏━╸┏━╓╻╻ ╻         \n");
                            slowprint( "                                                                    ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┣╸ ┣━┫┃┣━┫ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┃┗┳┛         \n");
                            slowprint( "                                                                    ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹ ╹╹╹ ╹ ╹ ╹┗━┛╹ ╹   ┗━╸┗━╓╹ ╹          \n\n");

                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                            slowprint( "                                                                                                ╔════╗                              \n");
                            slowprint( "                                                                                               ╔║    ║╗                             \n");
                            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            cin >> dnDel;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;
                            }

                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (dnDel < 1 || dnDel > (int)descriptions[itemNum - 1].size()) {
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID DESCRIPTION NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;
                            }

                            string toDelete = descriptions[itemNum - 1][dnDel - 1];

                            // ========== CONFIRMATION ==========
                            system("cls");
                            headerEditList();
                            printDescriptionsForItem(descriptions, itemNum);

                            slowprint( "                                                                                        ┏━╸┏━╸┏┓╻┏━╸╻┏━┓┏┳┓┏━┓                 \n");
                            slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛             \n");
                            slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                  Delete description:\n");
                            slowprint( "                                                                                    \"" + toDelete + "\" ?\n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                   [1] 🗑️ CONFIRM   [2] 🔙 CANCEL\n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                            slowprint( "                                                                                                ╔════╗                              \n");
                            slowprint( "                                                                                               ╔║    ║╗                             \n");
                            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            int confirmDel;
                            cin >> confirmDel;

                            if (cin.fail() || (confirmDel != 1 && confirmDel != 2)) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;
                            }

                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (confirmDel == 1) {
                                // actually delete
                                descriptions[itemNum - 1].erase(descriptions[itemNum - 1].begin() + (dnDel - 1));

                                system("cls");
                                headerEditList();
                                printDescriptionsForItem(descriptions, itemNum);

                                slowprint( "                                                                        ╺┳┓┏━╸┏━╸┏━╓┏━╓╺┳╸╻┏━╓┏┓╻   ╻ ╻┏━╓╺┳┓┏━╓╺┳┓        \n");
                                slowprint( "                                                                            ┃┃┣╸ ┗━┓┃  ┣━┫┃┃┃ ┃ ┃┃ ┃┃┗┫   ┃ ┃┣━┓ ┃┃┣━┫ ┃┃    \n");
                                slowprint( "                                                                        ╺┻┛┗━╸┗━┛┗━╸╹ ╹╹╹   ╹ ╹┗━┛╹ ╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   \n\n");
                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                            } else {
                                // cancel delete
                                system("cls");
                                headerEditList();
                                printDescriptionsForItem(descriptions, itemNum);

                                slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                                slowprint( "                                                                               ┣╸  ┃┃┃ ┃    ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃    \n");
                                slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛    \n\n");
                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                            }

                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                            getch();
                        }
                    }



                                    while (true) {
                                        system("cls");
                                        headerEditList();

                                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n\n");
                                        slowprint( "                                                                                 Descriptions for item: " + items[itemNum - 1] + "\n");
                                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n\n");

                                        // show current descriptions
                                        printDescriptionsForItem(descriptions, itemNum);

                                        slowprint( "                                                                        ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸╺┳┓╻╺┳╸   ┏┳┓┏━╸┏┓╻╻ ╻                  \n");
                                        slowprint( "                                                                         ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸  ┃┃┃ ┃    ┃┃┃┣╸ ┃┗┫┃ ┃                \n");
                                        slowprint( "                                                                        ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ┗━╸╺┻┛╹ ╹    ╹ ╹┗━╸╹ ╹┗━┛          \n");
                                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                        slowprint( "                                                                                  [1] ✏️ EDIT DESCRIPTION TEXT\n");
                                        slowprint( "                                                                                  [2] 📝 ADD NEW DESCRIPTION\n");
                                        slowprint( "                                                                                  [3] 🗑️ DELETE A DESCRIPTION\n");
                                        slowprint( "                                                                                  [4] ↩️ BACK\n");
                                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                        slowprint( "                                                                                                ╔════╗                              \n");
                                        slowprint( "                                                                                               ╔║    ║╗                             \n");
                                        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                                        slowprint( "\033[2A");
                                        slowprint( "\033[98C");

                                        int descChoice;
                                        cin >> descChoice;

                                        // =============== INVALID INPUT (letters etc.) ===============
                                        if (cin.fail()) {
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                            slowprint("\n");
                                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                            getch();
                                            continue;   // 🔁 restart description menu
                                        }

                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                        // =============== INVALID CHOICE (not 1–4) ===============
                                        if (descChoice < 1 || descChoice > 4) {
                                            slowprint("\n");
                                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                            getch();
                                            continue;   // 🔁 restart description menu
                                        }

                                        if (descChoice == 4) break; // back


                                        // ---------- Ensure vector exists ----------
                                        if ((int)descriptions.size() <= itemNum - 1)
                                            descriptions.resize(itemNum);

                                        // ==================================================================
                                        //  [1] EDIT DESCRIPTION TEXT
                                        // ==================================================================
                                        if (descChoice == 1) {

                                            if (descriptions[itemNum - 1].empty()) {
                                                slowprint("\n");
                                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ NO DESCRIPTIONS TO EDIT. ⚠️  \033[0m\n\n");
                                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                                                getch();
                                                continue;
                                            }

                                            int dn;

                                            system("cls");
                                            headerEditList();
                                            printDescriptionsForItem(descriptions, itemNum);

                                            slowprint( "                                                                 ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╺┳┓┏━╸┏━╸┏━╸┏━╓╻┏━╓╺┳╸╻┏━┓┏┓╻   ┏┓╻┏━┓┏┳┓┏┓ ┏━╸\n");
                                            slowprint( "                                                                 ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┫ ┃ ┃┃ ┃┃┗┫   ┃┗┫┣━┫┃┃┃┣┻┓┣╸ \n");
                                            slowprint( "                                                                 ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹ ╹ ╹ ╹┗━┛╹ ╹   ╹ ╹╹ ╹╹ ╹┗━┛┗━╸\n\n");

                                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                                            slowprint( "                                                                                                ╔════╗                              \n");
                                            slowprint( "                                                                                               ╔║    ║╗                             \n");
                                            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                                            slowprint( "\033[2A");
                                            slowprint( "\033[98C");


                                            cin >> dn;

                                            // invalid # input
                                            if (cin.fail()) {
                                                cin.clear();
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                                slowprint("\n");
                                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                                getch();
                                                continue;
                                            }

                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                            // invalid description #
                                            if (dn < 1 || dn > (int)descriptions[itemNum - 1].size()) {
                                                slowprint("\n");
                                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID DESCRIPTION NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                                getch();
                                                continue;
                                            }

                                            string newDesc;

                                            system("cls");
                                            headerEditList();
                                            printDescriptionsForItem(descriptions, itemNum);

                                            slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━╸┏━╸┏━╓╻┏━╓╺┳╸╻┏━┓┏┓╻             \n");
                                            slowprint( "                                                                               ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━╓ ┃ ┃┃ ┃┃┗┫             \n");
                                            slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹             \n\n");

                                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                                            slowprint( "                                                                                     ╔║                        ║╗                             \n");
                                            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

                                            slowprint( "\033[2A");
                                            slowprint( "\033[98C");

                                            getline(cin, newDesc);

                                            // ========== CONFIRMATION ==========
                                            system("cls");
                                            headerEditList();
                                            printDescriptionsForItem(descriptions, itemNum);

                                            slowprint( "                                                                                        ┏━╸┏━╸┏┓╻┏━╸╻┏━┓┏┳┓┏━┓                 \n");
                                            slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛             \n");
                                            slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

                                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                            slowprint( "                                                                                  Change description to:\n");
                                            slowprint( "                                                                                    \"" + newDesc + "\" ?\n");
                                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                            slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                            slowprint( "                                                                                                ╔════╗                              \n");
                                            slowprint( "                                                                                               ╔║    ║╗                             \n");
                                            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                                            slowprint( "\033[2A");
                                            slowprint( "\033[98C");

                                            int c;
                                            cin >> c;

                                            if (cin.fail() || (c != 1 && c != 2)) {
                                                cin.clear();
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                slowprint("\n");
                                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                                                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                                getch();
                                                continue;
                                            }

                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                            if (c == 1) {
                                                descriptions[itemNum - 1][dn - 1] = newDesc;

                                                system("cls");
                                                headerEditList();
                                                printDescriptionsForItem(descriptions, itemNum);

                                                slowprint( "                                                                        ╺┳┓┏━╸┏━╸┏━╓╻┏━╓╺┳╸╻┏━┓┏┓╻   ╻ ╻┏━╓╺┳┓┏━╓╺┳┓        \n");
                                                slowprint( "                                                                         ┃┃┣╸ ┗━┓┃  ┣━┫┃┃┃ ┃ ┃┃ ┃┃┗┫   ┃ ┃┣━┓ ┃┃┣━┫ ┃┃    \n");
                                                slowprint( "                                                                        ╺┻┛┗━╸┗━┛┗━╸╹ ╹╹╹   ╹ ╹┗━┛╹ ╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   \n\n");
                                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                                            } else {
                                                // cancel edit
                                                slowprint( "Edit cancelled.\n");
                                                system("cls");
                                                headerEditList();
                                                printDescriptionsForItem(descriptions, itemNum);

                                                slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                                                slowprint( "                                                                               ┣╸  ┃┃┃ ┃    ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃    \n");
                                                slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛    \n\n");
                                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                                            }

                                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                                            getch();
                                        }

                                        // ==================================================================
                                        //  [2] ADD NEW DESCRIPTION
                                        // ==================================================================
                                        else if (descChoice == 2) {

                                            string nd;

                                            system("cls");
                                            headerEditList();
                                            printDescriptionsForItem(descriptions, itemNum);

                                            slowprint( "                                                                       ┏━╸╺┳┓╺┳┓   ┏┓╻┏━╸╻ ╻   ╺┳┓┏━╸┏━╓┏━╓╺┳╸╻┏━╓┏┓╻           \n");
                                            slowprint( "                                                                       ┣━┫ ┃┃ ┃┃   ┃┗┫┣╸ ┃╻┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━╓ ┃┃            \n");
                                            slowprint( "                                                                       ╹ ╹╺┻┛╺┻┛   ╹ ╹┗━╸┗┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹           \n\n");

                                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                                            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
                                            slowprint( "                                                                                     ╔║                        ║╗                             \n");
                                            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

                                            slowprint( "\033[2A");
                                            slowprint( "\033[98C");

                                            getline(cin, nd);

                                            if (!nd.empty()) {
                                                descriptions[itemNum - 1].push_back(nd);

                                                // XP gain kept intact
                                                addClassXP(1, gamificationEnabled, playerXP, playerLevel,
                                                    playerClass, assassinStreak, assassinStacks,
                                                    wizardCounter, archerStreak, tankStacks);

                                                system("cls");
                                                headerEditList();
                                                printDescriptionsForItem(descriptions, itemNum);

                                                slowprint( "                                                                            ╺┳┓┏━╓┏━╓┏━╓╺┳╸╻┏━╓┏┓╻   ┏━╓╺┳┓╺┳┓┏━╓╺┳┓        \n");
                                                slowprint( "                                                                             ┃┃┣╸ ┗━┓┃  ┣╸ ┃ ┃┃ ┃┃┗┫   ┣━┫ ┃┃ ┃┃┣╸  ┃┃    \n");
                                                slowprint( "                                                                            ╺┻┛┗━╸┗━┛┗━╸╹   ╹ ╹┗━┛╹ ╹   ╹ ╹╺┻┛╺┻┛┗━╸╺┻┛    \n\n");

                                                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                                            }

                                            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                                            getch();
                                        }
                                    }
                                }

                    // -------- SUB 3: delete whole item (with confirmation) --------
                else if (subChoice == 3) {

                    system("cls");
                    headerEditList();
                    printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                    slowprint( "                                                                                  ┏━╸┏━╸┏┓╻╻  ╻┏━╸╺┳┓╻╺┳╸   ┏━╸╻╻ ╻╺┳┓         \n");
                    slowprint( "                                                                                  ┣╸ ┣╸ ┃┗┫┃  ┃┣╸  ┃┃┃ ┃    ┣╸ ┃┃ ┃ ┃┃     \n");
                    slowprint( "                                                                                  ┗━╸┗━╸╹ ╹┗━╸┗┗━╸╺┻┛╹ ╹    ┗━╸╹┗━┛╺┻┛         \n\n");

                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                    slowprint( "                                                                                  Are you sure you want to delete:\n");
                    slowprint( "                                                                                      \"" + items[itemNum - 1] + "\" ?\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                    slowprint( "                                                                                   [1] 🗑️ CONFIRM   [2] 🔙 CANCEL\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                    slowprint( "                                                                                                ╔════╗                              \n");
                    slowprint( "                                                                                               ╔║    ║╗                             \n");
                    slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                    slowprint( "\033[2A");   // move cursor up into the small box
                    slowprint( "\033[98C");  // move cursor horizontally to center input

                    int confirm;

                    while (true) {
                        // keep cursor inside the small box every retry
                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        cin >> confirm;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            slowprint( "\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // 🔁 re-ask for confirm
                        }

                        // flush leftover characters
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (confirm == 1 || confirm == 2) {
                            break;
                        }

                        slowprint( "\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                        getch();
                        // loop; cursor gets repositioned again at top of box
                    }

                    if (confirm == 1) {
                        // ===============================
                        // ACTUALLY DELETE THE ITEM
                        // ===============================
                        int eraseIndex = itemNum - 1;

                        // erase the item
                        if (eraseIndex >= 0 && eraseIndex < (int)items.size()) {
                            items.erase(items.begin() + eraseIndex);
                        }

                        // erase its descriptions (if any exist)
                        if (eraseIndex >= 0 && eraseIndex < (int)descriptions.size()) {
                            descriptions.erase(descriptions.begin() + eraseIndex);
                        }

                        itemDeleted = true;  // flag for parent logic if you use it

                        system("cls");
                        headerEditList();
                        printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                        slowprint( "                                                                ╻  ╻┏━┓╺┳╸   ┏━╸┏━┓╻  ╻ ╻┏━╸┏━╓╻┏━╓┏━╸╻ ╻╻  ╻  ╻ ╻                 \n");
                        slowprint( "                                                                ┃  ┃┗━┓ ┃    ┣╸ ┣━┫┃  ┃ ┃┣╸ ┃ ┃┃┃ ┃┣╸ ┃ ┃┃  ┃  ┗┳┛          \n");
                        slowprint( "                                                                ┗━╸╹┗━┛ ╹    ┗━╸╹ ╹┗━╸┗━┛┗━╸╹ ╹╹┗━┛┗━╸┗━╸┗━╸┗━╸ ╹        \n\n");

                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                        slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                        getch();

                        // leave the item-edit submenu after deletion
                        break;
                    }
                    else {
                        // CANCELLED
                        system("cls");
                        headerEditList();
                        printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                        slowprint( "                                                                        ╺┳┓┏━╸┏━┓┏━╸┏━╸╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                        slowprint( "                                                                         ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃    \n");
                        slowprint( "                                                                        ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛    \n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                        slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                        getch();
                        // go back to the item edit submenu without deleting
                    }
                }

                else {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                }
            } // end while item edit menu

            if (itemDeleted) {
                // go back to main edit loop with updated list
                continue;
            }
        }

        // ============================================
        // OPTION 3 — DELETE ITEM (QUICK DELETE MODE)
        // ============================================
        else if (editChoice == 3) {

            // No items to delete
            if (items.empty()) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ NO ITEMS TO DELETE. PLEASE ADD ONE FIRST. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                getch();
                continue;   // back to main EDIT LIST menu
            }

            while (true) {
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                        ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┳┓┏━╸┏┓╻╻ ╻   ┏━╸╺┳┓╻╺┳╸   ┏┓╻╻ ╻╺┳╸┏━╸              \n");
                slowprint( "                                                                        ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┃┃┣╸ ┃┗┫┃ ┃   ┣╸  ┃┃┃ ┃    ┃┗┫┃ ┃ ┃ ┣╸               \n");
                slowprint( "                                                                        ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸╹ ╹┗━┛   ┗━╸╺┻┛╹ ╹    ╹ ╹┗━┛ ╹ ┗━╸              \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                  QUICK DELETE MODE\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                  Enter the ITEM NUMBER to delete.\n");
                slowprint( "                                                                                  [0] ↩️ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                int deleteNum;
                cin >> deleteNum;

                // ===== INVALID RAW INPUT (letters, symbols, etc.) =====
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 stay in quick delete mode
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // BACK
                if (deleteNum == 0) {
                    break;  // exit quick delete mode back to main item edit menu
                }

                // Out-of-range item #
                if (deleteNum < 1 || deleteNum > (int)items.size()) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 stay in quick delete mode
                }

                int realIndex = deleteNum - 1;
                string toDelete = items[realIndex];

                // ========== CONFIRMATION SCREEN ==========
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                    ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏━╸┏━╓╻┏━╓╺┳╸╻┏━╓┏┓╻   ┏━╸┏━╓╻╻ ╻         \n");
                slowprint( "                                                                    ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┣╸ ┣━┫┃┣━┫ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┃┗┳┛         \n");
                slowprint( "                                                                    ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹ ╹╹╹ ╹ ╹ ╹┗━┛╹ ╹   ┗━╸┗━╓╹ ╹          \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                  Are you sure you want to delete:\n");
                slowprint( "                                                                                       \"" + toDelete + "\" ?\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                   [1] 🗑️ CONFIRM   [2] 🔙 CANCEL\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                int confirmDel;
                cin >> confirmDel;

                if (cin.fail() || (confirmDel != 1 && confirmDel != 2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // back to confirm
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (confirmDel == 2) {
                    // CANCEL
                    system("cls");
                    headerEditList();
                    printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                    slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                    slowprint( "                                                                               ┣╸  ┃┃┃ ┃    ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃    \n");
                    slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛    \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                    getch();
                    continue;   // back to quick delete menu
                }

                // ====== ACTUAL DELETE ======
                if (confirmDel == 1) {
                    items.erase(items.begin() + realIndex);

                    if (realIndex < (int)descriptions.size()) {
                        descriptions.erase(descriptions.begin() + realIndex);
                    }

                    system("cls");
                    headerEditList();
                    printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                    slowprint( "                                                                ╻  ╻┏━┓╺┳╸   ┏━╸┏━╓╻┏━╓╺┳╸╻┏━╓┏┓╻   ┏━╸┏━╓╻╻ ╻         \n");
                    slowprint( "                                                                ┃  ┃┗━┓ ┃    ┣╸ ┣━┫┃┣━┫ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┃┗┳┛         \n");
                    slowprint( "                                                                ┗━╸╹┗━┛ ╹    ┗━╸╹ ╹╹╹ ╹ ╹ ╹┗━┛╹ ╹   ┗━╸┗━╓╹ ╹          \n\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                    getch();

                    // If list is now empty, leave quick delete mode
                    if (items.empty()) {
                        break;
                    }
                    // else: stay in quick delete mode so user can delete more
                }
            }
        


            system("cls");
            headerEditList();
            printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


            if (items.size() == 0) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ NO ITEMS TO DELETE. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                getch();
                continue;
            }

            int delNum;

            slowprint( "                                                        ┏━╸┏┓╻╺┳╸┏━╸┏━╓   ╻╺┳╸┏━╸┏┳┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━╓   ╺┳╸┏━╓   ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸               \n");
            slowprint( "                                                        ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃ ┃ ┣╸ ┃┃┃   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛    ┃ ┃ ┃    ┃┃┣╸ ┃  ┣╸  ┃ ┣╸           \n");
            slowprint( "                                                        ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹ ┗━╸╹ ╹   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸    ╹ ┗━┛   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸             \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

            slowprint( "\033[2A");   // move cursor up into the small box
            slowprint( "\033[98C");  // move cursor horizontally to center input

            while (true)
            {
                cin >> delNum;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                getch();
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Validate
            if (delNum < 1 || delNum > (int)items.size()) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                getch();
                continue;
            }

            // ==========================
            // CONFIRMATION UI
            // ==========================
            system("cls");
            headerEditList();
            printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


            slowprint( "                                                                                        ┏━╸┏━╓┏┓╻┏━╸╻┏━╓┏┳┓┏━╓                 \n");
            slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛             \n");
            slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                  You chose to DELETE item:\n");
            slowprint( "                                                                                      -> " + items[delNum - 1] + "\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                      [1] 🗑️ CONFIRM DELETE\n");
            slowprint( "                                                                                      [2] 🔙 CANCEL\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

            slowprint( "\033[2A");   // move cursor up into the small box
            slowprint( "\033[98C");  // move cursor horizontally to center input

            int confirmDel;
            while (true) {
                slowprint( "\033[2A\033[98C");
                cin >> confirmDel;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                getch();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (confirmDel != 1) {

                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                            ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                slowprint( "                                                                             ┃┃┣╸ ┃  ┣╸  ┃ ┣╸    ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃    \n");
                slowprint( "                                                                            ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛   \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                getch();
                continue;
            }

            // Remove item + its descriptions
            items.erase(items.begin() + (delNum - 1));
            if (delNum - 1 < (int)descriptions.size()) {
                descriptions.erase(descriptions.begin() + (delNum - 1));
            }

            // Give XP for deleting an item (small consolation)
            addClassXP(2, gamificationEnabled, playerXP, playerLevel,
                playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);

            system("cls");
            headerEditList();
            printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


            slowprint( "                                                                                    ╻╺┳╸┏━╸┏┳┓┏━╓   ┏━╓╻ ╻┏━╓┏━╓┏━╓┏━╸╺┳┓        \n");
            slowprint( "                                                                                    ┃ ┃ ┣╸ ┃┃┃┗━┓   ┗━┓┃╻┃┣━┫┣━┛┣━┛┣╸  ┃┃   \n");
            slowprint( "                                                                                    ╹ ╹ ┗━╸╹ ╹┗━┛   ┗━┛┗┻┛╹ ╹╹  ╹  ┗━╸╺┻┛  \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            getch();
            continue;
        }

        // ============================================
        // OPTION 4 — MARK / UNMARK AS DONE
        // ============================================
        else if (editChoice == 4) {

            if (items.empty()) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ NO ITEMS TO MARK. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                getch();
                continue;
            }

            int    markNum = 0;
            string markNumStr;

            // =======================================
            // STEP 1: CHOOSE WHICH ITEM TO MARK
            // (same pattern as OPTION 2 item chooser)
            // =======================================
            while (true)
            {
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                    ┏━╸┏┓╻╺┳╸┏━╸┏━╓   ╻╺┳╸┏━╸┏┳┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━╓   ╺┳╸┏━╓   ┏┳┓┏━╓┏━╓╻┏     ╻   ╻ ╻┏┓╻┏┳┓┏━╓┏━╓╻┏                \n");
                slowprint( "                                                    ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃ ┃ ┣╸ ┃┃┃   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛    ┃ ┃ ┃   ┃┃┃┣━┫┣┳┛┣┻┓   ┏┛   ┃ ┃┃┗┫┃┃┃┣━┫┣┳┛┣┻┓           \n");
                slowprint( "                                                    ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹ ┗━╸╹ ╹   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸    ╹ ┗━┛   ╹ ╹╹ ╹╹┗╸╹ ╹   ╹    ┗━┛╹ ╹╹ ╹╹ ╹╹┗╸╹ ╹           \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");   // move cursor up into the small box
                slowprint( "\033[98C");  // move cursor horizontally to center input

                cin >> markNumStr;

                // try to convert safely
                try {
                    markNum = stoi(markNumStr);
                }
                catch (...) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw whole MARK screen
                }

                // range check
                if (markNum < 1 || markNum > (int)items.size()) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw whole MARK screen
                }

                // SUCCESS
                break;
            }

            // =======================================
            // STEP 2: CONFIRM TOGGLE DONE STATUS
            // (same pattern: string + stoi + retry)
            // =======================================
            int    confirmMark = 0;
            string confirmMarkStr;

            while (true)
            {
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                                        ┏━╸┏━╓┏┓╻┏━╸╻┏━╓┏┳┓┏━╓                 \n");
                slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛             \n");
                slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint( "                                                                                  Toggle DONE status for:\n");
                slowprint( "                                                                                      -> " + items[markNum - 1] + "\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint( "                                                                                      [1] ✅ CONFIRM TOGGLE\n");
                slowprint( "                                                                                      [2] 🔙 CANCEL\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                cin >> confirmMarkStr;

                try {
                    confirmMark = stoi(confirmMarkStr);
                }
                catch (...) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw confirm screen
                }

                if (confirmMark != 1 && confirmMark != 2) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw confirm screen
                }

                // valid 1 or 2
                break;
            }

            // ============================
            // STEP 3: APPLY OR CANCEL
            // ============================
            if (confirmMark != 1) {

                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                            ┏━╸┏━╓╺┳╸╻┏━╓┏┓╻   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                slowprint( "                                                                            ┣━╫┃   ┃ ┃┃ ┃┃┗┫   ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃   \n");
                slowprint( "                                                                            ╹ ╹┗━╸ ╹ ╹┗━┛╹ ╹   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛  \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                slowprint( string("                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m"));
                getch();
                continue;
            }

            // actually toggle
            {
                string &target = items[markNum - 1];

              // Toggle DONE tag
            if (target.rfind("✅ ", 0) == 0) {
                // Currently marked: remove the EXACT "✅ " prefix
                target = target.substr(3);  // 3 chars: "✅" + space

                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                    ╻  ╻┏━┓╺┳╸   ┏━╸┏━╓╺┳┓╻┏━╓┏┓╻   ┏━╓┏━╓┏━╓╺┳╸╻┏━╓┏┓╻        \n");
                slowprint( "                                                                    ┃  ┃┗━┓ ┃    ┣╸ ┣━┫ ┃┃┃┣━╫┃┗┫   ┃ ┃┣━┓ ┃┃┣━┫┃┃┃ ┃┃┗┫   \n");
                slowprint( "                                                                    ┗━╸╹┗━┛ ╹    ┗━╸╹ ╹╺┻┛╹╹ ╹╹ ╹   ┗━┛╹  ╺┻┛╹ ╹╹ ╹╹╹ ╹╹ ╹   \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            }
            else {
                // Not yet marked: add the "✅ " prefix
                target = "✅ " + target;

                // Give XP for marking item done
                addClassXP(8, gamificationEnabled, playerXP, playerLevel,
                    playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);

                // If this marking finishes the entire list give a completion bonus
                if (completedCount + 1 == (int)items.size() && items.size() > 0) {
                    addClassXP(50, gamificationEnabled, playerXP, playerLevel,
                        playerClass, assassinStreak, assassinStacks, wizardCounter, archerStreak, tankStacks);
                }

                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                            ╻╺┳╸┏━╸┏┳┓   ┏┳┓┏━╓┏━╓╻┏ ┏━╸╺┳┓   ┏━╓┏━╓   ╺┳┓┏━╓┏┓╻┏━╸        \n");
                slowprint( "                                                                            ┃ ┃ ┣╸ ┃┃┃   ┃┃┃┣━╫┣┳┛┣┻┓┣╸  ┃┃   ┣━╫┗━┓    ┃┃┃ ┃┃┗┫┣╸    \n");
                slowprint( "                                                                            ╹ ╹ ┗━╸╹ ╹   ╹ ╹╹ ╹╹┗╸╹ ╹┗━╸╺┻┛   ╹ ╹┗━┛   ╺┻┛┗━┛╹ ╹┗━╸  \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            }
        }

            continue;
        }

        // ============================================
        // OPTION 5 — SWAP TWO ITEMS
        // ============================================
        else if (editChoice == 5) {

            if (items.size() < 2) {
                slowprint("\n");
                slowprint( "                                                                                 \033[1;37;41m  ⚠️ NOT ENOUGH ITEMS TO REORDER. ⚠️  \033[0m\n\n");
                slowprint( "                                                                                 \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");
                getch();
                continue;
            }

            int    a = 0, b = 0;
            string aStr, bStr;

            // ====================================================
            // STEP 1: CHOOSE FIRST ITEM POSITION (A)
            // (same pattern as OPTION 4 / markNum)
            // ====================================================
            while (true)
            {
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                   ┏━╸┏┓╻╺┳╸┏━╸┏━╓   ┏━╸╻┏━╓┏━╓╺┳╸   ╻╺┳╸┏━╸┏┳┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━╓                \n");
                slowprint( "                                                                   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┣╸ ┃┣┳┛┗━┓ ┃    ┃ ┃ ┣╸ ┃┃┃   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛           \n");
                slowprint( "                                                                   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹  ╹╹┗╸┗━┛ ╹    ╹ ╹ ┗━╸╹ ╹   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸         \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");

                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");   // move cursor up into the small box
                slowprint( "\033[98C");  // move cursor horizontally to center input

                cin >> aStr;

                try {
                    a = stoi(aStr);
                }
                catch (...) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw STEP 1 screen
                }

                if (a < 1 || a > (int)items.size()) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw STEP 1 screen
                }

                // valid A
                break;
            }

            // ====================================================
            // STEP 2: CHOOSE SECOND ITEM POSITION (B)
            // (same pattern, with its own full redraw)
            // ====================================================
            while (true)
            {
                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                   ┏━╸┏┓╻╺┳╸┏━╸┏━╓   ┏━╓┏━╸┏━╸┏━╓┏┓╻╺┳┓   ╻╺┳╸┏━╸┏┳┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━╓                \n");
                slowprint( "                                                                   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗━┓┣╸ ┃  ┃ ┃┃┗┫ ┃┃   ┃ ┃ ┣╸ ┃┃┃   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛         \n");
                slowprint( "                                                                   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━┛┗━╸┗━╸┗━┛╹ ╹╺┻┛   ╹ ╹ ┗━╸╹ ╹   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸       \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");

                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");   // move cursor up into the small box
                slowprint( "\033[98C");  // move cursor horizontally to center input

                cin >> bStr;

                try {
                    b = stoi(bStr);
                }
                catch (...) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw STEP 2 screen
                }

                if (b < 1 || b > (int)items.size()) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID ITEM NUMBER. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw STEP 2 screen
                }

                // valid B
                break;
            }

            // ====================================================
            // STEP 3: CONFIRM SWAP (1 / 2)
            // (same confirm pattern as confirmMark)
            // ====================================================
            int    confirmSwap    = 0;
            string confirmSwapStr;

            while (true)
            {
                system("cls");
                headerEditList();

                slowprint( "                                                                                        ┏━╸┏━╓┏┓╻┏━╸╻┏━╓┏┳┓┏━╓                 \n");
                slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛             \n");
                slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint( "                                                                                  You are about to SWAP:\n");
                slowprint( "                                                                                      A) " + items[a - 1] + "\n");
                slowprint( "                                                                                      B) " + items[b - 1] + "\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint( "                                                                                      [1] 🔁 CONFIRM SWAP\n");
                slowprint( "                                                                                      [2] 🔙 CANCEL\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint( "                                                                                                ╔════╗                              \n");
                slowprint( "                                                                                               ╔║    ║╗                             \n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

                slowprint( "\033[2A");   // move cursor up into the small box
                slowprint( "\033[98C");  // move cursor horizontally to center input

                cin >> confirmSwapStr;

                try {
                    confirmSwap = stoi(confirmSwapStr);
                }
                catch (...) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw confirm screen
                }

                if (confirmSwap != 1 && confirmSwap != 2) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;   // 🔁 redraw confirm screen
                }

                // valid 1 or 2
                break;
            }

            // ============================
            // STEP 4: APPLY OR CANCEL
            // ============================
            if (confirmSwap != 1) {

                system("cls");
                headerEditList();
                printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


                slowprint( "                                                                               ┏━╓╻ ╻┏━╓┏━╓   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓        \n");
                slowprint( "                                                                               ┗━┓┃╻┃┣━┫┣━┛   ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃  \n");
                slowprint( "                                                                               ┗━┛┗┻┛╹ ╹╹     ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛ \n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                getch();
                continue;
            }

            // ============================
            // STEP 5: PERFORM THE SWAP
            // ============================
            {
                string temp = items[a - 1];
                items[a - 1] = items[b - 1];
                items[b - 1] = temp;
            }

            // Swap descriptions too
            if (a - 1 < (int)descriptions.size() && b - 1 < (int)descriptions.size()) {
                vector<string> tempD = descriptions[a - 1];
                descriptions[a - 1] = descriptions[b - 1];
                descriptions[b - 1] = tempD;
            } else {
                // Ensure array is large enough before swap
                int needed = (a > b ? a : b);
                if ((int)descriptions.size() < needed) {
                    int oldSize = descriptions.size();
                    descriptions.resize(needed);
                    for (int i = oldSize; i < (int)descriptions.size(); i++)
                        descriptions[i] = vector<string>();
                }
                vector<string> tempD = descriptions[a - 1];
                descriptions[a - 1] = descriptions[b - 1];
                descriptions[b - 1] = tempD;
            }

            system("cls");
            headerEditList();
            printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


            slowprint( "                                                                                  ╻╺┳╸┏━╸┏┳┓┏━╓   ┏━╓╻ ╻┏━╓┏━╓┏━╓┏━╸╺┳┓        \n");
            slowprint( "                                                                                  ┃ ┃ ┣╸ ┃┃┃┗━┓   ┗━┓┃╻┃┣━┫┣━┛┣━┛┣╸  ┃┃   \n");
            slowprint( "                                                                                  ╹ ╹ ┗━╸╹ ╹┗━┛   ┗━┛┗┻┛╹ ╹╹  ╹  ┗━╸╺┻┛  \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            getch();
            continue;
        }

        // ============================================
        // OPTION 6 — RENAME THE LIST
        // ============================================
        else if (editChoice == 6) {

            string newName;

            system("cls");
            headerEditList();
            printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


            slowprint( "                                                                      ┏━╸┏┓╻╺┳╸┏━╸┏━╓   ┏┓╻┏━╸╻ ╻   ╻  ╻┏━╓╺┳╸   ┏┓╻┏━╓┏┳┓┏━╸           \n");
            slowprint( "                                                                      ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃   ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸           \n");
            slowprint( "                                                                      ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸       \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                       \n");

            slowprint( "                                                                                      ╔════════════════════════╗                              \n");
            slowprint( "                                                                                     ╔║                        ║╗                             \n");
            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════                        \n");

            slowprint( "\033[2A");   // move cursor up into the small box
            slowprint( "\033[98C");  // move cursor horizontally to center input

            getline(cin >> ws, newName);

            name_of_list[index] = newName;

            system("cls");
            headerEditList();
            printListPreviewForEdit(
    list_of_lists[index],        // items
    list_of_descriptions[index], // descriptions
    name_of_list[index],         // title
    list_categories[index],      // category
    list_deadlines[index],       // deadline
    list_priorities[index],      // priority
    list_notes[index]            // notes
);


            slowprint( "                                                                                  ╻  ╻┏━╓╺┳╸   ┏━╓┏━╸┏┓╻┏━╓┏┳┓┏━╸╺┳┓        \n");
            slowprint( "                                                                                  ┃  ┃┗━┓ ┃    ┣┳┛┣╸ ┃┗┫┣━┫┃┃┃┣╸  ┃┃ \n");
            slowprint( "                                                                                  ┗━╸╹┗━┛ ╹    ╹┗╸┗━╸╹ ╹╹ ╹╹ ╹┗━╸╺┻┛ \n\n");
            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n");

            slowprint( "                                                                                      \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
            getch();
            continue;
        }

        // ============================================
        // OPTION 7 — EDIT LIST CATEGORY / DEADLINE / PRIORITY / NOTES
        // ============================================
        else if (editChoice == 7) {

            while (true) {
                system("cls");
                headerEditList();

        

                slowprint( "                                                                               ┏━╸╺┳┓╻╺┳╸   ╻  ╻┏━┓╺┳╸   ╺┳┓┏━╸╺┳╸┏━┓╻╻  ┏━┓\n");
                slowprint( "                                                                               ┣╸  ┃┃┃ ┃    ┃  ┃┗━┓ ┃     ┃┃┣╸  ┃ ┣━┫┃┃  ┗━┓\n");
                slowprint( "                                                                               ┗━╸╺┻┛╹ ╹    ┗━╸╹┗━┛ ╹    ╺┻┛┗━╸ ╹ ╹ ╹╹┗━╸┗━┛\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                slowprint( "                                                                                  Current values:\n");
                slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[index]  + "\n");
                slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[index]   + "\n");
                slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[index]  + "\n");
                slowprint( "                                                                                      📋 NOTES   : "
                     + (list_notes[index].empty() ? "None" : list_notes[index]) + "\n\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                slowprint( "                                                                                  [1] 🗂️ EDIT CATEGORY\n");
                slowprint( "                                                                                  [2] 📅 EDIT DEADLINE\n");
                slowprint( "                                                                                  [3] ✏️ EDIT PRIORITY\n");
                slowprint( "                                                                                  [4] ❗ EDIT NOTES\n");
                slowprint( "                                                                                  [5] ↩️ BACK\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                slowprint( "                                                                                                ╔════╗\n");
                slowprint( "                                                                                               ╔║    ║╗\n");
                slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                slowprint( "\033[2A");
                slowprint( "\033[98C");

                int metaChoice;
                cin >> metaChoice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (metaChoice < 1 || metaChoice > 5) {
                    slowprint("\n");
                    slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                    slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                            "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                    getch();
                    continue;
                }

                // BACK
                if (metaChoice == 5) {
                    break;
                }

                // ======================================================
                // [1] EDIT CATEGORY  (select from predefined list)
                // ======================================================
                if (metaChoice == 1) {
                    const string categories[] = {
                        "Work","School","Personal","Errands",
                        "Finance","Health","Appointment",
                        "Shopping","Others","None"
                    };
                    const int CAT_COUNT = sizeof(categories) / sizeof(categories[0]);

                    while (true) {
                        system("cls");
                        headerEditList();
                       

                   
                        slowprint( "                                                                       ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏┓╻┏━╸╻ ╻   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻\n");
                        slowprint( "                                                                       ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃┗┫┣╸ ┃╻┃   ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛\n");
                        slowprint( "                                                                       ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹┗━╸┗┻┛   ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹ \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━       \n\n");

                        for (int i = 0; i < CAT_COUNT; ++i) {
                            slowprint( "                                                                                      [" + to_string(i + 1) + "] " + categories[i] + "\n");
                        }
                        slowprint( "\n");
                        slowprint( "                                                                                      [0] 🔙 CANCEL\n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗\n");
                        slowprint( "                                                                                               ╔║    ║╗\n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        int catChoice;
                        cin >> catChoice;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (catChoice == 0) {
                            break;  // cancel category edit
                        }

                        if (catChoice < 1 || catChoice > CAT_COUNT) {
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;
                        }

                        string oldCat = list_categories[index];
                        string newCat = categories[catChoice - 1];

                        // confirmation
                        system("cls");
                        headerEditList();
                     

                        slowprint( "                                                                                         ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓┏━┓    \n");
                        slowprint( "                                                                                         ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛    \n");
                        slowprint( "                                                                                         ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹     \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                  Change CATEGORY from:\n");
                        slowprint( "                                                                                      \"" + oldCat + "\"\n");
                        slowprint( "                                                                                  to:\n");
                        slowprint( "                                                                                      \"" + newCat + "\" ?\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗\n");
                        slowprint( "                                                                                               ╔║    ║╗\n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        int confirm;
                        cin >> confirm;

                        if (cin.fail() || (confirm != 1 && confirm != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (confirm == 1) {
                            list_categories[index] = newCat;

                            system("cls");
                            headerEditList();
                         

                            slowprint( "                                                          ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻   ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻    \n");
                            slowprint( "                                                          ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛   ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛    \n");
                            slowprint( "                                                          ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹    ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹     \n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                        }

                        // either way, leave category edit loop
                        break;
                    }
                }

                // ======================================================
                // [2] EDIT DEADLINE (preset list + custom)
                // ======================================================
                else if (metaChoice == 2) {

                    // Same preset style you already use in createNewList (example)
                    const string deadlineOptions[] = {
                        "Today",
                        "Tomorrow",
                        "This Week",
                        "Next Week",
                        "This Month",
                        "Next Month",
                        "No Deadline",
                        "Custom (type manually)"
                    };
                    const int DEADLINE_COUNT = sizeof(deadlineOptions) / sizeof(deadlineOptions[0]);

                    while (true) {
                        system("cls");
                        headerEditList();
                     

                        slowprint( "                                                                        ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏┓╻┏━╸╻ ╻   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   \n");
                        slowprint( "                                                                        ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃┗┫┣╸ ┃╻┃    ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    \n");
                        slowprint( "                                                                        ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹┗━╸┗┻┛   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸    \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

                        for (int i = 0; i < DEADLINE_COUNT; ++i) {
                            slowprint( "                                                                                      [" + to_string(i + 1) + "] " + deadlineOptions[i] + "\n");
                        }
                        slowprint( "\n");
                        slowprint( "                                                                                      [0] 🔙 CANCEL\n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗\n");
                        slowprint( "                                                                                               ╔║    ║╗\n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        int dChoice;
                        cin >> dChoice;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // back to deadline menu
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // cancel edit
                        if (dChoice == 0) {
                            break;
                        }

                        if (dChoice < 1 || dChoice > DEADLINE_COUNT) {
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // back to deadline menu
                        }

                        string newDeadline;

                        // Last option = Custom (type manually)
                        if (dChoice == DEADLINE_COUNT) {
                            system("cls");
                            headerEditList();
                         

                            slowprint( "                                                                         ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   \n");
                            slowprint( "                                                                         ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃    ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    \n");
                            slowprint( "                                                                         ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   \n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
                            slowprint( "                                                                                      ╔════════════════════════╗\n");
                            slowprint( "                                                                                     ╔║                        ║╗\n");
                            slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════\n");

                            slowprint( "\033[2A");
                            slowprint( "\033[98C");

                            getline(cin, newDeadline);

                            if (newDeadline.empty()) {
                                slowprint("\n");
                                slowprint( "                                                                                 \033[1;37;41m  ⚠️ DEADLINE CANNOT BE EMPTY. ⚠️  \033[0m\n\n");
                                slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                        "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                                getch();
                                continue;   // go back to deadline main menu
                            }
                        } else {
                            // picked one of the preset entries: Today, Tomorrow, etc.
                            newDeadline = deadlineOptions[dChoice - 1];
                        }

                        string oldDeadline = list_deadlines[index];

                        // ===== confirmation screen =====
                        system("cls");
                        headerEditList();
                     

                        slowprint( "                                                                                         ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓┏━┓    \n");
                        slowprint( "                                                                                         ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛    \n");
                        slowprint( "                                                                                         ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹     \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                  Change DEADLINE from:\n");
                        slowprint( "                                                                                      \"" + oldDeadline + "\"\n");;
                        slowprint( "                                                                                  to:\n");
                        slowprint( "                                                                                      \"" + newDeadline + "\" ?\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗\n");
                        slowprint( "                                                                                               ╔║    ║╗\n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        int confirm;
                        cin >> confirm;

                        if (cin.fail() || (confirm != 1 && confirm != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;   // back to deadline menu
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (confirm == 1) {
                            list_deadlines[index] = newDeadline;

                            system("cls");
                            headerEditList();
                      

                            slowprint( "                                                        ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻   \n");
                            slowprint( "                                                         ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛   \n");
                            slowprint( "                                                        ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹     \n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                        }

                        // after a valid confirm/cancel, leave the deadline edit loop
                        break;
                    }
                }


                // ======================================================
                // [3] EDIT PRIORITY (select from predefined list)
                // ======================================================
                else if (metaChoice == 3) {
                    const string priorities[] = {
                        "Critical","High","Medium","Low","None"
                    };
                    const int PRI_COUNT = sizeof(priorities) / sizeof(priorities[0]);

                    while (true) {
                        system("cls");
                        headerEditList();
                   

                        slowprint( "                                                                         ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏┓╻┏━╸╻ ╻   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻      \n");
                        slowprint( "                                                                         ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃┗┫┣╸ ┃╻┃   ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛     \n");
                        slowprint( "                                                                         ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹┗━╸┗┻┛   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹       \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

                        for (int i = 0; i < PRI_COUNT; ++i) {
                            slowprint( "                                                                                      [" + to_string(i + 1) + "] " + priorities[i] + "\n");
                        }
                        slowprint( "\n");
                        slowprint( "                                                                                      [0] 🔙 CANCEL\n\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗\n");
                        slowprint( "                                                                                               ╔║    ║╗\n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        int priChoice;
                        cin >> priChoice;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (priChoice == 0) {
                            break;  // cancel
                        }

                        if (priChoice < 1 || priChoice > PRI_COUNT) {
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;
                        }

                        string oldPri = list_priorities[index];
                        string newPri = priorities[priChoice - 1];

                        system("cls");
                        headerEditList();
                     

                        slowprint( "                                                                                         ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓┏━┓    \n");
                        slowprint( "                                                                                         ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛    \n");
                        slowprint( "                                                                                         ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹     \n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                  Change PRIORITY from:\n");
                        slowprint( "                                                                                      \"" + oldPri + "\"\n");
                        slowprint( "                                                                                  to:\n");
                        slowprint( "                                                                                      \"" + newPri + "\" ?\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                                ╔════╗\n");
                        slowprint( "                                                                                               ╔║    ║╗\n");
                        slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                        slowprint( "\033[2A");
                        slowprint( "\033[98C");

                        int confirm;
                        cin >> confirm;

                        if (cin.fail() || (confirm != 1 && confirm != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            slowprint("\n");
                            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                            continue;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (confirm == 1) {
                            list_priorities[index] = newPri;

                            system("cls");
                            headerEditList();
                         

                            slowprint( "                                                          ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻   ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻   \n");
                            slowprint( "                                                          ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛   ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛  \n");
                            slowprint( "                                                          ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹    ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹     \n");
                            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                            slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                    "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                            getch();
                        }

                        break; // leave priority loop
                    }
                }

                // ======================================================
                // [4] EDIT NOTES (free text, can be empty / None)
                // ======================================================
                else if (metaChoice == 4) {
                    string newNote;

                    system("cls");
                    headerEditList();
                 

                    slowprint( "                                                                             ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ┏┓╻┏━┓╺┳╸┏━╸┏━┓      \n");
                    slowprint( "                                                                             ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃   ┃┗┫┃ ┃ ┃ ┣╸ ┗━┓   \n");
                    slowprint( "                                                                             ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛   ╹ ╹┗━┛ ╹ ┗━╸┗━┛     \n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                    slowprint( "                                                                                       (leave blank for None)\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                    slowprint( "                                                                                      ╔════════════════════════╗\n");
                    slowprint( "                                                                                     ╔║                        ║╗\n");
                    slowprint( "                                                                                ═════╝╚════════════════════════╝╚═════\n");

                    slowprint( "\033[2A");
                    slowprint( "\033[98C");

                    getline(cin, newNote);

                    string oldNote = list_notes[index];
                    string displayNew = newNote.empty() ? "None" : newNote;
                    string displayOld = oldNote.empty() ? "None" : oldNote;

                    system("cls");
                    headerEditList();
                 

                    slowprint( "                                                                                         ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓┏━┓    \n");
                    slowprint( "                                                                                         ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛    \n");
                    slowprint( "                                                                                         ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹     \n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                    slowprint( "                                                                                  Change NOTES from:\n");
                    slowprint( "                                                                                      \"" + displayOld + "\"\n");
                    slowprint( "                                                                                  to:\n");
                    slowprint( "                                                                                      \"" + displayNew + "\" ?\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                    slowprint( "                                                                                   [1] ✅ CONFIRM   [2] 🔙 CANCEL\n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                    slowprint( "                                                                                                ╔════╗\n");
                    slowprint( "                                                                                               ╔║    ║╗\n");
                    slowprint( "                                                                                          ═════╝╚════╝╚═════\n");

                    slowprint( "\033[2A");
                    slowprint( "\033[98C");

                    int confirm;
                    cin >> confirm;

                    if (cin.fail() || (confirm != 1 && confirm != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        slowprint("\n");
                        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
                        slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                        getch();
                        continue;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (confirm == 1) {
                        list_notes[index] = newNote; // can be empty (treated as None in display)

                        system("cls");
                        headerEditList();
                     

                    slowprint( "                                                             ┏┓╻┏━┓╺┳╸┏━╸┏━┓   ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻  \n");
                    slowprint( "                                                             ┃┗┫┃ ┃ ┃ ┣╸ ┗━┓   ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛  \n");
                    slowprint( "                                                             ╹ ╹┗━┛ ╹ ┗━╸┗━┛   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹    \n");
                    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                        slowprint( "                                                                                     \033[1;48;2;255;255;255m"
                                "\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
                        getch();
                    }
                }

            } // end while(meta edit)
        }

        // ============================================
        // OPTION 8 — EXIT
        // ============================================
        else if (editChoice == 8) {
            break;
        }

        // Invalid option
        else {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
            getch();
            continue;
        }

    } // end while
}


void headerDeleteList() {

        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                             ██████╗ ███████╗██╗     ███████╗████████╗███████╗    ██╗     ██╗███████╗████████╗   \n");
        slowprint( "                                                             ██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔════╝    ██║     ██║██╔════╝╚══██╔══╝     \n");
        slowprint( "                                                             ██║  ██║█████╗  ██║     █████╗     ██║   █████╗      ██║     ██║███████╗   ██          \n");
        slowprint( "                                                             ██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══╝      ██║     ██║╚════██║   ██║        \n");
        slowprint( "                                                             ██████╔╝███████╗███████╗███████╗   ██║   ███████╗    ███████╗██║███████║   ██║         \n");
        slowprint( "                                                             ╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚══════╝    ╚══════╝╚═╝╚══════╝   ╚═╝           \n");
        slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}

// -----------------------------
// DELETE LIST
// -----------------------------
void deleteList(
    vector<string> &name_of_list,
    vector<vector<string>> &list_of_lists,
    vector<vector<vector<string>>> &list_of_descriptions,
    vector<string> &list_categories,
    vector<string> &list_deadlines,
    vector<string> &list_priorities,
    vector<string>& list_notes,

    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear,
    vector<int>& monthcreated,
    vector<int>& datecreated,
    vector<int>& yearcreated
) {
    // If no lists exist, there's nothing to deletea
    if (name_of_list.empty()) {

        slowprint("\n");
        slowprint( "\033[0B");
        slowprint( "\033[84C");
        slowprint( "\033[1;37;41m  ⚠️ NO LISTS TO DELETE ⚠️  \033[0m\n\n");
        slowprint( string("                                                                                  ")
             + "\033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m");

        getch();
        return;
    }

    // ============================
    // STEP 1: CHOOSE WHICH LIST
    // ============================
    int choice = 0;

    while (true)
    {
        system("cls");
        headerDeleteList();

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");

            // DISPLAY ALL LISTS (full header layout)
        for (int i = 0; i < (int)name_of_list.size(); i++) {

            slowprint( "                                                                                 " + to_string(i + 1) + ". " + name_of_list[i] + "\n");
            slowprint( "                                                                                      🗂️ CATEGORY: " + list_categories[i]  + "\n");
            slowprint( "                                                                                      📅 DEADLINE: " + list_deadlines[i]   + "\n");
            slowprint( "                                                                                      ❗ PRIORITY: " + list_priorities[i]  + "\n");
            slowprint( "                                                                                      📋 NOTES   : " 
                + string("(None)")  // deleteList has no list_notes parameter here yet
                + "\n\n");
        }


        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                      ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ╻  ╻┏━┓╺┳╸   ╺┳╸┏━┓   ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸                 \n");
        slowprint( "                                                                      ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┃  ┃┗━┓ ┃     ┃ ┃ ┃    ┃┃┣╸ ┃  ┣╸  ┃ ┣╸           \n");
        slowprint( "                                                                      ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ┗━╸╹┗━┛ ╹     ╹ ┗━┛   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸       \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                        [0] ↩️ BACK TO MAIN MENU\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

        slowprint( "\033[2A");
        slowprint( "\033[98C");

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw list selection
        }

        // User cancels deletion
        if (choice == 0) {
            return;
        }

        if (choice < 1 || choice > (int)name_of_list.size())
        {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw list selection
        }

        // valid choice
        break;
    }

    int index = choice - 1;

    // ============================
    // STEP 2: CONFIRM DELETION
    // ============================
    char confirm;

    while (true)
    {
        system("cls");
        headerDeleteList();

        slowprint( "                                                                                        ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓┏━┓                 \n");
        slowprint( "                                                                                        ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃ ╺┛                \n");
        slowprint( "                                                                                        ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹ ╹                \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                               Are you sure you want to delete \"" + name_of_list[index] + "\"?\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                           [1] 🗑️ CONFIRM\n");
        slowprint( "                                                                                           [2] 🔙 CANCEL\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

        slowprint( "\033[2A");
        slowprint( "\033[98C");

        cin >> confirm;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw confirm screen
        }

        if (confirm == '2')
        {
            system("cls");
            headerDeleteList();

            slowprint( "                                                                        ╺┳┓┏━╸╻  ┏━╸╺┳╸╻┏━┓┏┓╻   ┏━╸┏━╓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓                \n");
            slowprint( "                                                                         ┃┃┣╸ ┃  ┣╸  ┃ ┃┃ ┃┃┗┫   ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃          \n");
            slowprint( "                                                                        ╺┻┛┗━╸┗━╸┗━╸ ╹ ╹┗━┛╹ ╹   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛       \n\n");

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            return;
        }

        if (confirm == '1')
        {
            // confirmed
            break;
        }

        // any other key = invalid choice
        slowprint("\n");
        slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID CHOICE. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
        slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");
        getch();
    }

    // ----------------------------------------------------
    // MANUAL REBUILD OF LIST ARRAYS (NO push_back allowed)
    // ----------------------------------------------------
    vector<string> newNames;
    vector<vector<string>> newLists;
    vector<vector<vector<string>>> newDescriptions;

    vector<string> newCategories;
    vector<string> newDeadlines;
    vector<string> newPriorities;

    vector<int> newMonthCreated;
    vector<int> newDateCreated;
    vector<int> newYearCreated;

    vector<vector<int>> newListmonth;
    vector<vector<int>> newListdate;
    vector<vector<int>> newListyear;

    for (int i = 0; i < (int)name_of_list.size(); i++) {
        if (i == index) continue; // skip deleted

        int ni = newNames.size();
        newNames.resize(ni + 1);
        newNames[ni] = name_of_list[i];

        int li = newLists.size();
        newLists.resize(li + 1);
        newLists[li] = list_of_lists[i];

        int di = newDescriptions.size();
        newDescriptions.resize(di + 1);
        if (i < (int)list_of_descriptions.size())
            newDescriptions[di] = list_of_descriptions[i];
        else
            newDescriptions[di] = vector<vector<string>>();

        int mi = newCategories.size();
        newCategories.resize(mi + 1);
        newDeadlines.resize(mi + 1);
        newPriorities.resize(mi + 1);

        newCategories[mi] = (i < (int)list_categories.size()) ? list_categories[i] : "";
        newDeadlines[mi]  = (i < (int)list_deadlines.size()) ? list_deadlines[i] : "";
        newPriorities[mi] = (i < (int)list_priorities.size()) ? list_priorities[i] : "";

        int dli = newListdate.size();
        newListdate.resize(dli + 1);
        newListdate[dli] = listdate[i];

        int mli = newListmonth.size();
        newListmonth.resize(mli + 1);
        newListmonth[mli] = listmonth[i];

        int yli = newListyear.size();
        newListyear.resize(yli + 1);
        newListyear[yli] = listyear[i];

        int mci = newMonthCreated.size();
        newMonthCreated.resize(mci + 1);
        newMonthCreated[mci] = monthcreated[i];

        int dci = newDateCreated.size();
        newDateCreated.resize(dci + 1);
        newDateCreated[dci] = datecreated[i];

        int yci = newYearCreated.size();
        newYearCreated.resize(yci + 1);
        newYearCreated[yci] = yearcreated[i];
    }

    // -------------------------------
    // REPLACE OLD STORAGE WITH NEW
    // -------------------------------
    name_of_list      = newNames;
    list_of_lists     = newLists;
    list_of_descriptions = newDescriptions;

    list_categories   = newCategories;
    list_deadlines    = newDeadlines;
    list_priorities   = newPriorities;

    listmonth         = newListmonth;
    listdate          = newListdate;
    listyear          = newListyear;

    monthcreated      = newMonthCreated;
    datecreated       = newDateCreated;
    yearcreated       = newYearCreated;

    // ============================
    // SUCCESS MESSAGE
    // ============================
    system("cls");
    headerDeleteList();

    slowprint( "                                                                ╻  ╻┏━┓╺┳╸   ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━╓┏━╓┏━╸╻ ╻╻  ╻  ╻ ╻                 \n");
    slowprint( "                                                                ┃  ┃┗━┓ ┃     ┃┃┣╸ ┃  ┣╸  ┃ ┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛          \n");
    slowprint( "                                                                ┗━╸╹┗━┛ ╹    ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹        \n\n");

    slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
    slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

    getch();
}

void headerEditDate() {

        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                                    ███████╗██████╗ ██╗████████╗    ██████╗  █████╗ ████████╗███████╗    \n");
        slowprint( "                                                                    ██╔════╝██╔══██╗██║╚══██╔══╝    ██╔══██╗██╔══██╗╚══██╔══╝██╔════╝     \n");
        slowprint( "                                                                    █████╗  ██║  ██║██║   ██║       ██║  ██║███████║   ██║   █████╗         \n");
        slowprint( "                                                                    ██╔══╝  ██║  ██║██║   ██║       ██║  ██║██╔══██║   ██║   ██╔══╝           \n");
        slowprint( "                                                                    ███████╗██████╔╝██║   ██║       ██████╔╝██║  ██║   ██║   ███████╗           \n");
        slowprint( "                                                                    ╚══════╝╚═════╝ ╚═╝   ╚═╝       ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝              \n");
        slowprint( "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");
    
 
}


void updatedate(int &cmonth, int &cdate, int &cyear)
{
    int tempmonth, tempdate, tempyear;

    // ============================
    // STEP 1: ENTER MONTH NUMBER
    // ============================
    while (true)
    {
        system("cls");
        headerEditDate();

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                         ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┳┓┏━┓┏┓╻╺┳╸╻ ╻   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓                 \n");
        slowprint( "                                                                         ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┃┃┃ ┃┃┗┫ ┃ ┣━┫   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛          \n");
        slowprint( "                                                                         ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━┛╹ ╹ ╹ ╹ ╹   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸       \n\n");

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                       [0] ↩️ BACK TO MAIN MENU\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

        slowprint( "\033[2A");   // move cursor up into the small box
        slowprint( "\033[98C");  // move cursor horizontally to center input

        // --- read month ---
        cin >> tempmonth;

        // invalid type (letter, symbol, etc.)
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw "ENTER MONTH" screen
        }

        // 0 = back to main menu
        if (tempmonth == 0)
        {
            return;
        }

        // out of range
        if (tempmonth < 1 || tempmonth > 12)
        {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ MONTH MUST BE BETWEEN 1 AND 12. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw "ENTER MONTH" screen
        }

        // valid month
        break;
    }

    // ============================
    // STEP 2: ENTER YEAR NUMBER
    // ============================
    while (true)
    {
        system("cls");
        headerEditDate();

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                          ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━╸┏━┓┏━┓   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓                 \n");
        slowprint( "                                                                          ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┣╸ ┣━┫┣┳┛   ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛          \n");
        slowprint( "                                                                          ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━╸╹ ╹╹┗╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸     \n\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

        slowprint( "\033[2A");
        slowprint( "\033[98C");

        cin >> tempyear;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw "ENTER YEAR" screen
        }

        if (tempyear < 2025 || tempyear > 2100)
        {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ YEAR MUST BE BETWEEN 2025 AND 2100. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw "ENTER YEAR" screen
        }

        // valid year
        break;
    }

    // ============================
    // STEP 3: ENTER DATE NUMBER
    // ============================

    // compute max valid day based on month + leap year
    bool leap = ((tempyear % 4 == 0 && tempyear % 100 != 0) || (tempyear % 400 == 0));
    int maxDay;
    if (tempmonth == 2)
        maxDay = leap ? 29 : 28;
    else if (tempmonth == 4 || tempmonth == 6 || tempmonth == 9 || tempmonth == 11)
        maxDay = 30;
    else
        maxDay = 31;

    while (true)
    {
        system("cls");
        headerEditDate();

        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                          ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╺┳┓┏━┓╺┳╸┏━╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓                \n");
        slowprint( "                                                                          ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛    ┃┃┣━┫ ┃ ┣╸    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛         \n");
        slowprint( "                                                                          ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╺┻┛╹ ╹ ╹ ┗━╸   ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸     \n\n");
        slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n");

        slowprint( "\033[2A");
        slowprint( "\033[98C");

        cin >> tempdate;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw "ENTER DATE" screen
        }

        if (tempdate < 1 || tempdate > maxDay)
        {
            slowprint("\n");
            slowprint( "                                                                                 \033[1;37;41m  ⚠️ DATE MUST BE BETWEEN 1 AND " + to_string(maxDay) + ". ⚠️  \033[0m\n\n");
            slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ANY KEY TO CONTINUE...  \033[0m\n");

            getch();
            continue; // redraw "ENTER DATE" screen
        }

        // valid date
        break;
    }

    // finally commit
    cmonth = tempmonth;
    cdate  = tempdate;
    cyear  = tempyear;
}



int main() {


    // -------------------------------
    // Declare storage vectors for lists
    // -------------------------------
    vector<string> name_of_list;
    vector<vector<string>> list_of_lists;
    vector<vector<vector<string>>> list_of_descriptions;
    int cmonth, cdate, cyear;
    getCurrentDate(cmonth, cdate, cyear); // get current date for default creation date
    vector<int> monthcreated;
    vector<int> datecreated;
    vector<int> yearcreated;
    vector<vector<int>> listmonth;
    vector<vector<int>> listdate;
    vector<vector<int>> listyear;

    vector<string> list_categories;
    vector<string> list_deadlines;
    vector<string> list_priorities;
    vector<string> list_notes;   


    //For SpecialCharacter Translation Compatability with Terminal
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    //Main Menu
    int Menu;
    bool started = false;
    int choice;

    // Gamification system (no globals)
    int playerXP = 0;
    int playerLevel = 1;
    bool gamificationEnabled = false;

    // =====================================
    // ACHIEVEMENT SYSTEM STORAGE (inside main, not global)
    // =====================================
    vector<string> achNames;
    vector<string> achBadges;
    vector<int> achUnlocked;
    vector<int> achXP;
    int streakCount = 0;
    int lastActiveDay = 0;



    // Initialize achievements once on startup
    initAchievements(achNames, achBadges, achUnlocked, achXP);

    system("cls");

        slowprint( "                                                                  ████████╗ █████╗ ██╗     ██╗  ██╗   ██╗     ██╗          ██╗                        \n");             
        slowprint( "                                                                  ╚══██╔══╝██╔══██╗██║     ██║  ╚██╗ ██╔╝     ██║          ██║                        \n");     
        slowprint( "                                                                     ██║   ███████║██║     ██║   ╚████╔╝  ██████████╗  ██████████╗                    \n");                       
        slowprint( "                                                                     ██║   ██╔══██║██║     ██║    ╚██╔╝   ╚═══██╔═══╝  ╚═══██╔═══╝                    \n");                      
        slowprint( "                                                                     ██║   ██║  ██║███████╗███████╗██║        ██║          ██║                        \n");     
        slowprint( "                                                                     ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝        ╚═╝          ╚═╝                        \n\n");
                                                                
        slowprint( "                                                   ██╗     ██╗███████╗████████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗   \n");
        slowprint( "                                                   ██║     ██║██╔════╝╚══██╔══╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗  \n");
        slowprint( "                                                   ██║     ██║███████╗   ██║       ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝  \n");
        slowprint( "                                                   ██║     ██║╚════██║   ██║       ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗  \n");
        slowprint( "                                                   ███████╗██║███████║   ██║       ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║  \n");
        slowprint( "                                                   ╚══════╝╚═╝╚══════╝   ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝  \n\n");

        slowprint( "                                                   ╻ ╻╻ ╻┏━╸┏━┓┏━╸   ╺┳╸┏━┓┏━┓╻┏ ┏━┓   ┏┓ ┏━╸┏━╸┏━┓┏┳┓┏━╸   ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏┓╻╺┳╸┏━┓     \n");
        slowprint( "                                                   ┃╻┃┣━┫┣╸ ┣┳┛┣╸     ┃ ┣━┫┗━┓┣┻┓┗━┓   ┣┻┓┣╸ ┃  ┃ ┃┃┃┃┣╸    ┣━┫┃  ┣━┫┃┣╸ ┃┏┛┣╸ ┃┃┃┣╸ ┃┗┫ ┃ ┗━┓     \n");
        slowprint( "                                                   ┗┻┛╹ ╹┗━╸╹┗╸┗━╸    ╹ ╹ ╹┗━┛╹ ╹┗━┛   ┗━┛┗━╸┗━╸┗━┛╹ ╹┗━╸   ╹ ╹┗━╸╹ ╹╹┗━╸┗┛ ┗━╸╹ ╹┗━╸╹ ╹ ╹ ┗━┛╹    \n\n");
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        slowprint( "                                                    ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");

        slowprint( "                                                                                      𝐀𝐫𝐢𝐬𝐭𝐨𝐤𝐢, 𝐒𝐞𝐠𝐨𝐜𝐢𝐨, 𝐎𝐜𝐜𝐞ñ𝐚 | 𝐁𝐒𝐂𝐒 1-𝐀                                 \n\n"); 

        slowprint( "                                                                       ╔════════════════════════════════════════════════════╗  \n");    
        slowprint( "                                                                       ║╻╻┏━┓┏━┓┏━╸┏━┓┏━┓   ┏━┓   ╺┳╸┏━┓   ┏━╸┏┓╻╺┳╸┏━╸┏━┓╻╻║  \n");
        slowprint( "                                                                       ║  ┣━┛┣┳┛┣╸ ┗━┓┗━┓   ┃┃┃    ┃ ┃ ┃   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛  ║  \n");
        slowprint( "                                                                       ║  ╹  ╹┗╸┗━╸┗━┛┗━┛   ┗━┛    ╹ ┗━┛   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸  ║  \n");
        slowprint( "                                                                       ╚════════════════════════════════════════════════════╝  \n");

        while (true)
        {
            cin >> Menu;
            if (Menu != 0)
            {
                slowprint( "Invalid input. Please try again.\n");
                continue;
            }
            
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            slowprint( "Invalid input. Please try again.\n");
        }
        
        
        if(Menu == 0){
            started = true;
             system("cls");
        } 

    while (started) {

        system("cls");
       
        slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
        slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
        slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
        slowprint( "                                                               ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  \n");
        slowprint( "                                                               ████╗ ████║██╔══██╗██║████╗  ██║    ████╗ ████║██╔════╝████╗  ██║██║   ██║  \n");
        slowprint( "                                                               ██╔████╔██║███████║██║██╔██╗ ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  \n");
        slowprint( "                                                               ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  \n");
        slowprint( "                                                               ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  \n");
        slowprint( "                                                               ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   \n");
        slowprint( "                                                              ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");


                                                                          
        // Display player level & XP in main menu header
        // Show gamification header only when enabled
        if (gamificationEnabled) {

            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
            

            slowprint( "                                                                                 📊 Player Level : " + to_string(playerLevel)
                + "    ✨ Player XP : " + to_string(playerXP) + "\n");

            slowprint( "                                                                                 ✨ XP Progress   : " + getXPBar(playerXP)
                + " " + to_string(playerXP % 100) + "%\n");
            // Class display
            slowprint( "                                                                                 📚 Current Class : ");
            switch (playerClass) {
                case DEFAULT_CLASS:  slowprint( "Default"); break;




                
                case HERO_CLASS:     slowprint( "Hero (+25 XP)"); break;
                case GAMBLER_CLASS:  slowprint( "Gambler (RNG XP)"); break;
                case ASSASSIN_CLASS: slowprint( "Assassin (Streak XP)"); break;
                case WIZARD_CLASS:   slowprint( "Wizard (Combo + Wisdom XP)"); break;
                case ARCHER_CLASS:   slowprint( "Archer (Precision Shot XP)"); break;
                case TANK_CLASS:     slowprint( "Tank (Shield Momentum XP)"); break;   
            }
            slowprint( "\n");

            // Assassin display
            if (playerClass == ASSASSIN_CLASS) {

                float percent = (assassinStacks / 10.0f) * 100.0f; 
                slowprint( " Assassin Streak : " + to_string(assassinStreak)
                    + "   Stacks: " + to_string(assassinStacks) + "/10\n"
                    + " Progress: " + getProgressBar(percent)
                    + " " + to_string((int)percent) + "%\n");
            }

            // Wizard display
            if (playerClass == WIZARD_CLASS) {

                float percent = (wizardCounter / 5.0f) * 100.0f;
                slowprint( " Wizard Counter : " + to_string(wizardCounter) + "/5\n"
                    + " Progress: " + getProgressBar(percent)
                    + " " + to_string((int)percent) + "%\n");
            }

            // Archer display
            if (playerClass == ARCHER_CLASS) {

                float percent = (archerStreak / 10.0f) * 100.0f;
                if (percent > 100) percent = 100;

                slowprint( " Archer Streak : " + to_string(archerStreak)
                    + "  Bonus: " + to_string(archerStreak * 5) + "%\n"
                    + " Progress: " + getProgressBar(percent)
                    + " " + to_string((int)percent) + "%\n");
            }

            // Tank display
            if (playerClass == TANK_CLASS) {

                int maxStacks = 20 - playerLevel;
                if (maxStacks < 3) maxStacks = 3;

                // Tank progress decays with level
                // Level 1: 19/19 = 100%
                // Level 20: 3/3 = 100% but lower cap → shows weakness differently
                float percent = (maxStacks / 20.0f) * 100.0f;

                slowprint( " Tank Stacks : " + to_string(tankStacks)
                    + " / " + to_string(maxStacks)
                    + "  (Shield Momentum)\n"
                    + " Durability: " + getProgressBar(percent)
                    + " " + to_string((int)percent) + "%\n");
            }


            slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
        }



        slowprint( "                                                                                     Current streak count: " + to_string(streakCount) + " | Current date: " + to_string(cmonth) + '/' + to_string(cdate) + '/' + to_string(cyear));
        slowprint("\n");
        slowprint( "\n");

        slowprint( "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n");
        slowprint( "       ║╺┓     ┏━╸┏━┓┏━╸┏━┓╺┳╸┏━╸   ┏━┓   ┏┓╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸║      ║╻ ╻    ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸   ┏━┓   ╻  ╻┏━┓╺┳╸            ║      ║┏━┓    ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏┓╻╺┳╸┏━┓               ║\n");
        slowprint( "       ║ ┃     ┃  ┣┳┛┣╸ ┣━┫ ┃ ┣╸    ┣━┫   ┃┗┫┣╸ ┃╻┃   ┃  ┃┗━┓ ┃ ║      ║┗━┫     ┃┃┣╸ ┃  ┣╸  ┃ ┣╸    ┣━┫   ┃  ┃┗━┓ ┃             ║      ║  ┃    ┣━┫┃  ┣━┫┃┣╸ ┃┏┛┣╸ ┃┃┃┣╸ ┃┗┫ ┃ ┗━┓               ║\n");
        slowprint( "       ║╺┻╸╹   ┗━╸╹┗╸┗━╸╹ ╹ ╹ ┗━╸   ╹ ╹   ╹ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹ ║      ║  ╹╹   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸   ╹ ╹   ┗━╸╹┗━┛ ╹             ║      ║  ╹╹   ╹ ╹┗━╸╹ ╹╹┗━╸┗┛ ┗━╸╹ ╹┗━╸╹ ╹ ╹ ┗━┛               ║\n");
        slowprint( "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n");

        slowprint( "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n");
        slowprint( "       ║┏━┓    ╻ ╻╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                          ║      ║┏━╸    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╺┳┓┏━┓╺┳╸┏━╸                ║      ║┏━┓    ┏━╸╻  ┏━┓┏━┓┏━┓┏━╸┏━┓                            ║\n");
        slowprint( "       ║┏━┛    ┃┏┛┃┣╸ ┃╻┃   ┃  ┃┗━┓ ┃                           ║      ║┗━┓    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸     ┃┃┣━┫ ┃ ┣╸                 ║      ║┣━┫    ┃  ┃  ┣━┫┗━┓┗━┓┣╸ ┗━┓                            ║\n");
        slowprint( "       ║┗━╸╹   ┗┛ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹                           ║      ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ╺┻┛╹ ╹ ╹ ┗━╸                ║      ║┗━┛╹   ┗━╸┗━╸╹ ╹┗━┛┗━┛┗━╸┗━┛                            ║\n");
        slowprint( "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n");                                

        slowprint( "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n");                          
        slowprint( "       ║┏━┓    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╻  ╻┏━┓╺┳╸                  ║      ║┏━┓    ╺┳╸┏━┓┏━╸┏━╸╻  ┏━╸   ┏━╸┏━┓┏┳┓┏━╸                ║      ║┏━┓    ┏━╸╻ ╻╻╺┳╸                                       ║\n");
        slowprint( "       ║╺━┫    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸    ┃  ┃┗━┓ ┃                   ║      ║┣━┓     ┃ ┃ ┃┃╺┓┃╺┓┃  ┣╸    ┃╺┓┣━┫┃┃┃┣╸                 ║      ║┗━┫    ┣╸ ┏╋┛┃ ┃                                        ║\n");
        slowprint( "       ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ┗━╸╹┗━┛ ╹                   ║      ║┗━┛╹    ╹ ┗━┛┗━┛┗━┛┗━╸┗━╸   ┗━┛╹ ╹╹ ╹┗━╸                ║      ║┗━┛╹   ┗━╸╹ ╹╹ ╹                                        ║ \n");      
        slowprint( "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n");


        slowprint( "                                                                          ________________  ________________  ________________      \n");
        slowprint( "                                                                         |________________||________________||________________|     \n\n");                                                                                                                                     
        slowprint( "                                                                            ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ┏━╸╻ ╻┏━┓╻┏━╸┏━╸         \n");
        slowprint( "                                                                            ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┣━┫┃ ┃┃┃  ┣╸ ╹        \n");
        slowprint( "                                                                            ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹ ╹┗━┛╹┗━╸┗━╸╹        \n");
        slowprint( "                                                                                                ╔════╗                              \n");
        slowprint( "                                                                                               ╔║    ║╗                             \n");
        slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
        
        slowprint( "\033[2A"); // move UP 2 lines
        slowprint( "\033[98C"); // move RIGHT 17 columns (adjust until perfect)
        while (true)
        {
                cin >> choice;
                if (!cin.fail()) break;
                
                cin.clear();
                cin.ignore(1000 , '\n');
                if (choice < 1 || choice > 9) {

            system("cls");
        
            slowprint( "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n");
            slowprint( "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n");
            slowprint( "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n");
            slowprint( "                                                               ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  \n");
            slowprint( "                                                               ████╗ ████║██╔══██╗██║████╗  ██║    ████╗ ████║██╔════╝████╗  ██║██║   ██║  \n");
            slowprint( "                                                               ██╔████╔██║███████║██║██╔██╗ ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  \n");
            slowprint( "                                                               ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  \n");
            slowprint( "                                                               ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  \n");
            slowprint( "                                                               ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   \n");
            slowprint( "                                                              ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n");


                                                                            
            // Display player level & XP in main menu header
            // Show gamification header only when enabled
            if (gamificationEnabled) {
                slowprint( " Player Level : " + to_string(playerLevel)
                    + "    Player XP : " + to_string(playerXP) + "\n");

                slowprint( " XP Progress   : " + getXPBar(playerXP)
                    + " " + to_string(playerXP % 100) + "%\n");
                // Class display 
                slowprint( " Current Class : ");
                switch (playerClass) {
                    case DEFAULT_CLASS:  slowprint( "Default"); break;
                    case HERO_CLASS:     slowprint( "Hero (+25 XP)"); break;
                    case GAMBLER_CLASS:  slowprint( "Gambler (RNG XP)"); break;
                    case ASSASSIN_CLASS: slowprint( "Assassin (Streak XP)"); break;
                    case WIZARD_CLASS:   slowprint( "Wizard (Combo + Wisdom XP)"); break;
                    case ARCHER_CLASS:   slowprint( "Archer (Precision Shot XP)"); break;
                    case TANK_CLASS:     slowprint( "Tank (Shield Momentum XP)"); break;   
                }
                slowprint( "\n");

                // Assassin display
                if (playerClass == ASSASSIN_CLASS) {

                    float percent = (assassinStacks / 10.0f) * 100.0f; 
                    slowprint( " Assassin Streak : " + to_string(assassinStreak)
                        + "   Stacks: " + to_string(assassinStacks) + "/10\n"
                        + " Progress: " + getProgressBar(percent)
                        + " " + to_string((int)percent) + "%\n");
                }

                // Wizard display
                if (playerClass == WIZARD_CLASS) {

                    float percent = (wizardCounter / 5.0f) * 100.0f;
                    slowprint( " Wizard Counter : " + to_string(wizardCounter) + "/5\n"
                        + " Progress: " + getProgressBar(percent)
                        + " " + to_string((int)percent) + "%\n");
                }

                // Archer display
                if (playerClass == ARCHER_CLASS) {

                    float percent = (archerStreak / 10.0f) * 100.0f;
                    if (percent > 100) percent = 100;

                    slowprint( " Archer Streak : " + to_string(archerStreak) 
                        + "  Bonus: " + to_string(archerStreak * 5) + "%\n"
                        + " Progress: " + getProgressBar(percent)
                        + " " + to_string((int)percent) + "%\n");
                }

                // Tank display
                if (playerClass == TANK_CLASS) {

                    int maxStacks = 20 - playerLevel;
                    if (maxStacks < 3) maxStacks = 3;

                    // Tank progress decays with level
                    // Level 1: 19/19 = 100%
                    // Level 20: 3/3 = 100% but lower cap (shows weakness differently)
                    float percent = (maxStacks / 20.0f) * 100.0f;

                    slowprint( " Tank Stacks : " + to_string(tankStacks) 
                        + " / " + to_string(maxStacks)
                        + "  (Shield Momentum)\n"
                        + " Durability: " + getProgressBar(percent)
                        + " " + to_string((int)percent) + "%\n");
                }


                slowprint( "-------------------------------------\n");
            }


            slowprint( "                                                                                     Current streak count: " + to_string(streakCount) + " | Current date: " + to_string(cmonth) + '/' + to_string(cdate) + '/' + to_string(cyear));
            slowprint("\n");
            slowprint( "\n");

            slowprint( "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n");
            slowprint( "       ║╺┓     ┏━╸┏━┓┏━╸┏━┓╺┳╸┏━╸   ┏━┓   ┏┓╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸║      ║╻ ╻    ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸   ┏━┓   ╻  ╻┏━┓╺┳╸            ║      ║┏━┓    ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏┓╻╺┳╸┏━┓               ║\n");
            slowprint( "       ║ ┃     ┃  ┣┳┛┣╸ ┣━┫ ┃ ┣╸    ┣━┫   ┃┗┫┣╸ ┃╻┃   ┃  ┃┗━┓ ┃ ║      ║┗━┫     ┃┃┣╸ ┃  ┣╸  ┃ ┣╸    ┣━┫   ┃  ┃┗━┓ ┃             ║      ║  ┃    ┣━┫┃  ┣━┫┗━┓┗━┓┣╸ ┗━┓                            ║\n");
            slowprint( "       ║╺┻╸╹   ┗━╸╹┗╸┗━╸╹ ╹ ╹ ┗━╸   ╹ ╹   ╹ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹ ║      ║  ╹╹   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸   ╹ ╹   ┗━╸╹┗━┛ ╹             ║      ║  ╹╹   ╹ ╹┗━╸╹ ╹╹┗━╸┗┛ ┗━╸╹ ╹┗━╸╹ ╹ ╹ ┗━┛               ║\n");
            slowprint( "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n");

            slowprint( "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n");
            slowprint( "       ║┏━┓    ╻ ╻╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                          ║      ║┏━╸    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╺┳┓┏━┓╺┳╸┏━╸                ║      ║┏━┓    ┏━╸╻  ┏━┓┏━┓┏━┓┏━╸┏━┓                            ║\n");
            slowprint( "       ║┏━┛    ┃┏┛┃┣╸ ┃╻┃   ┃  ┃┗━┓ ┃                           ║      ║┗━┓    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸     ┃┃┣━┫ ┃ ┣╸                 ║      ║┣━┫    ┃  ┃  ┣━┫┗━┓┗━┓┣╸ ┗━┓                            ║\n");
            slowprint( "       ║┗━╸╹   ┗┛ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹                           ║      ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ╺┻┛╹ ╹ ╹ ┗━╸                ║      ║┗━┛╹   ┗━╸┗━╸╹ ╹┗━┛┗━┛┗━╸┗━┛                            ║\n");
            slowprint( "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n");                                

            slowprint( "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n");                          
            slowprint( "       ║┏━┓    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╻  ╻┏━┓╺┳╸                  ║      ║┏━┓    ╺┳╸┏━┓┏━╸┏━╸╻  ┏━╸   ┏━╸┏━┓┏┳┓┏━╸                ║      ║┏━┓    ┏━╸╻ ╻╻╺┳╸                                       ║\n");
            slowprint( "       ║╺━┫    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸    ┃  ┃┗━┓ ┃                   ║      ║┣━┓     ┃ ┃ ┃┃╺┓┃╺┓┃  ┣╸    ┃╺┓┣━┫┃┃┃┣╸                 ║      ║┗━┫    ┣╸ ┏╋┛┃ ┃                                        ║\n");
            slowprint( "       ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ┗━╸╹┗━┛ ╹                   ║      ║┗━┛╹    ╹ ┗━┛┗━┛┗━┛┗━╸┗━╸   ┗━┛╹ ╹╹ ╹┗━╸                ║      ║┗━┛╹   ┗━╸╹ ╹╹ ╹                                        ║ \n");      
            slowprint( "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n");


            slowprint( "                                                                          ________________  ________________  ________________      \n");
            slowprint( "                                                                         |________________||________________||________________|     \n\n");                                                                                                                                     
            slowprint( "                                                                            ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ┏━╸╻ ╻┏━┓╻┏━╸┏━╸         \n");
            slowprint( "                                                                            ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┣━┫┃ ┃┃┃  ┣╸ ╹        \n");
            slowprint( "                                                                            ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹ ╹┗━┛╹┗━╸┗━╸╹        \n");
            slowprint( "                                                                                                ╔════╗                              \n");
            slowprint( "                                                                                               ╔║    ║╗                             \n");
            slowprint( "                                                                                          ═════╝╚════╝╚═════                        \n"); 
            

            slowprint( "\033[0B"); // move UP 2 lines
            slowprint( "\033[80C"); // move RIGHT 17 columns (adjust until perfect)
                    slowprint( "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n");
                    cin.ignore();
                    cin.get();
                    continue;
        }
        }
        switch (choice) {
            case 1:
            createNewList(
            name_of_list,
            list_of_lists,
            list_of_descriptions,
            list_categories,
            list_deadlines,
            list_priorities,
            list_notes,          // 👈 must be here
            gamificationEnabled,
            playerXP,
            playerLevel,
            listmonth,
            listdate,
            listyear,
            monthcreated,
            datecreated,
            yearcreated,
            cmonth,
            cdate,
            cyear
        );

                // Check achievements after creating a list
                checkAchievements(name_of_list, list_of_lists, list_of_descriptions,
                                  achNames, achBadges, achUnlocked, achXP,
                                  gamificationEnabled, playerXP, playerLevel,
                                  streakCount, lastActiveDay, cmonth, cdate, cyear);
                break;

            case 2:
                viewLists(
                name_of_list,
                list_of_lists,
                list_of_descriptions,
                gamificationEnabled,
                playerXP,
                playerLevel,
                listmonth,
                listdate,
                listyear,
                monthcreated,
                datecreated,
                yearcreated,
                list_categories,
                list_deadlines,
                list_priorities,
                list_notes,    // ⭐ new
                cdate,
                cmonth,
                cyear
            );

            break;


            case 3:
              editList(
                name_of_list,
                list_of_lists,
                list_of_descriptions,
                gamificationEnabled,
                playerXP,
                playerLevel,
                listmonth,
                listdate,
                listyear,
                list_categories,
                list_deadlines,
                list_priorities,
                list_notes,
                monthcreated,
                datecreated,
                yearcreated,
                cdate,
                cmonth,
                cyear
            );

                // Re-check achievements after editing (edits may have changed counts)
                checkAchievements(name_of_list, list_of_lists, list_of_descriptions,
                                  achNames, achBadges, achUnlocked, achXP,
                                  gamificationEnabled, playerXP, playerLevel,
                                  streakCount, lastActiveDay, cmonth, cdate, cyear);
                break;

            case 4:
                        deleteList(
                name_of_list,
                list_of_lists,
                list_of_descriptions,
                list_categories,
                list_deadlines,
                list_priorities,
                list_notes,          // ✅ added
                gamificationEnabled,
                playerXP,
                playerLevel,
                listmonth,
                listdate, 
                listyear, 
                monthcreated, 
                datecreated,
                yearcreated
            );

                // Re-check achievements after deletion
                checkAchievements(name_of_list, list_of_lists, list_of_descriptions,
                                  achNames, achBadges, achUnlocked, achXP,
                                  gamificationEnabled, playerXP, playerLevel,
                                  streakCount, lastActiveDay, cmonth, cdate, cyear);
                break;

            case 9:
            system("cls");
                slowprint("   ┏┓┏┓┏┓┳┓┳┓┓┏┏┓          ┳┳┏┓┏┓┳┓\n");
                slowprint("   ┃┓┃┃┃┃┃┃┣┫┗┫┣           ┃┃┗┓┣ ┣┫\n");
                slowprint("   ┗┛┗┛┗┛┻┛┻┛┗┛┗┛          ┗┛┗┛┗┛┛┗\n");
                return 0;

            case 5:
             updatedate(cmonth, cdate, cyear);
             break;
            case 6:
               gamificationEnabled = !gamificationEnabled;
                slowprint( "\033[2B");   // move DOWN 2 lines (you labeled this UP, but 0B is down)
                slowprint( "\033[80C");  // move RIGHT 80 columns (adjust as needed)

                slowprint( string("\033[1;97;") + (gamificationEnabled ? "42" : "41") + "m"
                    + "  ✔  GAMIFICATION IS NOW:  "
                    + (gamificationEnabled ? "ENABLED" : "DISABLED")
                    + "  \033[0m\n");

           


                break;

            case 7:
                // Show Achievements & Badges
                system("cls");
                headerAchievementList();

                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint("\n");

                for (int i = 0; i < (int)achNames.size(); i++) {
                    
                    slowprint( string(82, ' '));      // center padding
                    slowprint( to_string(i + 1) + ". "
                        + achBadges[i] + " "
                        + achNames[i]);

                    if (achUnlocked[i])
                        slowprint( "  (Unlocked)");
                    else
                        slowprint( "  (Locked)");

                    slowprint( "   +" + to_string(achXP[i]) + " XP\n");
                }

             

                // Extra gamification info
                if (gamificationEnabled) {

                    slowprint( " Player Level : " + to_string(playerLevel)
                        + "    Player XP : " + to_string(playerXP) + "\n");

                    slowprint( " XP Progress  : "
                        + getXPBar(playerXP)
                        + " " + to_string(playerXP % 100) + "%\n");
                    
                    // Current Class Display
                    slowprint( " Current Class: ");
                    switch (playerClass) {
                        case DEFAULT_CLASS:  slowprint( "Default"); break;
                        case HERO_CLASS:     slowprint( "Hero (+25 XP)"); break;
                        case GAMBLER_CLASS:  slowprint( "Gambler (RNG XP)"); break;
                        case ASSASSIN_CLASS: slowprint( "Assassin (Streak XP)"); break;
                        case WIZARD_CLASS:   slowprint( "Wizard (Combo + Wisdom XP)"); break;
                        case ARCHER_CLASS:   slowprint( "Archer (Precision Shot XP)"); break;
                        case TANK_CLASS:     slowprint( "Tank (Shield Momentum XP)"); break;
                    }
                    slowprint( "\n");


                    // Class-Specific Details
                    // Assassin Progress
                    if (playerClass == ASSASSIN_CLASS) {
                        float percent = (assassinStacks / 10.0f) * 100.0f;

                        slowprint( " Assassin Streak : " + to_string(assassinStreak)
                            + "   Stacks: " + to_string(assassinStacks) + "/10\n"
                            + " Progress: " + getProgressBar(percent)
                            + " " + to_string((int)percent) + "%\n");
                    }

                    // Wizard Progress
                    if (playerClass == WIZARD_CLASS) {
                        float percent = (wizardCounter / 5.0f) * 100.0f;

                        slowprint( " Wizard Counter : " + to_string(wizardCounter) + "/5\n"
                            + " Progress: " + getProgressBar(percent)
                            + " " + to_string((int)percent) + "%\n");
                    }

                    // Archer Progress
                    if (playerClass == ARCHER_CLASS) {
                        float percent = (archerStreak / 10.0f) * 100.0f;
                        if (percent > 100) percent = 100;

                        slowprint( " Archer Streak : " + to_string(archerStreak)
                            + "   Bonus: " + to_string(archerStreak * 5) + "%\n"
                            + " Progress: " + getProgressBar(percent)
                            + " " + to_string((int)percent) + "%\n");
                    }

                    // Tank Progress
                    if (playerClass == TANK_CLASS) {
                        int maxStacks = 20 - playerLevel;
                        if (maxStacks < 3) maxStacks = 3;

                        float percent = (tankStacks * 100.0f) / maxStacks;
                        if (percent > 100) percent = 100;

                        slowprint( " Tank Stacks : " + to_string(tankStacks) + " / " + to_string(maxStacks)
                            + "  (Shield Momentum)\n"
                            + " Durability: " + getProgressBar(percent)
                            + " " + to_string((int)percent) + "%\n");
                    }

                  
                }
                slowprint( "\n");
                slowprint( "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n");
                slowprint("\n");
                slowprint( "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m");
                cin.ignore();
                cin.get();
                break;

            
            case 8:
                classMenu(playerClass, playerXP);
                break;

        }
        if (achievementsNeedUpdate) {
        checkAchievements(
            name_of_list,
            list_of_lists,
            list_of_descriptions,
            achNames,
            achBadges,
            achUnlocked,
            achXP,
            gamificationEnabled,
            playerXP,
            playerLevel,
            streakCount,
            lastActiveDay,
            cmonth,
            cdate,
            cyear
        );

        achievementsNeedUpdate = false;
    }

    system("pause");
    }

    return 0;
}


