#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;




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

    cout << "\n>>> +" << amount << " XP!\n";

    if (newLevel > playerLevel) {
        playerLevel = newLevel;
        cout << ">>> LEVEL UP! You are now LEVEL " << playerLevel << "!\n";
    }

    cout << "-------------------------------------\n";
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
// SEARCH LIST NAMES
// -------------------------
void searchLists(const vector<string>& names) {
    cin.ignore();   // clear leftover newline
    string key;     // keyword user wants to search for

    cout << "\n=====================================\n";
    cout << "           SEARCH LIST NAMES         \n";
    cout << "=====================================\n";

    cout << "Enter keyword to search: ";
    getline(cin, key);

    cout << "\n-------------- RESULTS --------------\n";

    bool found = false;   // tracks if any match is found

    // Check every list name for the keyword
    for (int i = 0; i < (int)names.size(); i++) {
        if (names[i].find(key) != string::npos) {   // substring match
            cout << " " << i + 1 << ". " << names[i] << "\n";
            found = true;
        }
    }

    // If no list contains the keyword
    if (!found) {
        cout << "( No matching list names found )\n";
    }

    cout << "-------------------------------------\n";
    cout << "Press Enter to continue...";
    cin.get();
}

// -------------------------
// SEARCH or SORT LISTS
// -------------------------
void searchOrSortLists(
    const vector<string>& names,
    const vector<string>& categories,
    const vector<string>& deadlines,
    const vector<string>& priorities
) {
    if (names.empty()) {
        cout << "\nNo lists available.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int opt;
    cout << "\n=====================================\n";
    cout << "         SEARCH / SORT LISTS         \n";
    cout << "=====================================\n";
    cout << " 1. Search by name\n";
    cout << " 2. Sort by name (A -> Z)\n";
    cout << " 3. Sort by name (Z -> A)\n";
    cout << " 4. Filter by category\n";
    cout << " 5. Filter by deadline\n";
    cout << " 6. Filter by priority\n";
    cout << " 0. Back\n";
    cout << "-------------------------------------\n";
    cout << "Choice: ";
    while (true)
    {
        cin >> opt;

        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        cout << "Invalid input. Please try again.\n";
    }

    // ---- SEARCH MODE ----
    if (opt == 1) {
        searchLists(names);
        return;
    }

    if (opt == 0) return;

    if (opt < 2 || opt > 6) {
        cout << "\nInvalid choice.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // -----------------------------
    // SORT BY NAME (2, 3) – global
    // -----------------------------
    if (opt == 2 || opt == 3) {
        cin.ignore(); // clear newline

        int n = (int)names.size();
        vector<int> order(n);
        for (int i = 0; i < n; i++)
            order[i] = i;

        // selection sort by names[order[i]]
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                string a = names[order[i]];
                string b = names[order[j]];
                bool swapNeeded = false;

                if (opt == 2) { // A -> Z
                    if (a > b) swapNeeded = true;
                } else {        // Z -> A
                    if (a < b) swapNeeded = true;
                }

                if (swapNeeded) {
                    int tmp = order[i];
                    order[i] = order[j];
                    order[j] = tmp;
                }
            }
        }

        cout << "\n--------------- SORTED LISTS ---------\n";
        for (int k = 0; k < n; k++) {
            int idx = order[k];
            cout << " " << (idx + 1) << ". " << names[idx] << "\n";
            if (idx < (int)categories.size())
                cout << "      Category : " << categories[idx] << "\n";
            if (idx < (int)deadlines.size())
                cout << "      Deadline : " << deadlines[idx] << "\n";
            if (idx < (int)priorities.size())
                cout << "      Priority : " << priorities[idx] << "\n";
            cout << "-------------------------------------\n";
        }

        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    // -----------------------------------------
    // FILTER MODES (4 = category, 5 = deadline,
    //              6 = priority)
    // -----------------------------------------
    string target;
    int subChoice;

    // 4️⃣ Filter by CATEGORY
    if (opt == 4) {
        cout << "\nSelect category to show:\n";
        cout << " 1. Work\n";
        cout << " 2. School\n";
        cout << " 3. Personal\n";
        cout << " 4. Errands\n";
        cout << " 5. Finance\n";
        cout << " 6. Health\n";
        cout << " 7. Appointment\n";
        cout << " 8. Shopping\n";
        cout << " 9. Others\n";
        cout << "10. None\n";
        cout << "Choice: ";
        while (true)
        {
            cin >> subChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";

        }

        while (subChoice < 1 || subChoice > 10) {
            cout << "Invalid choice. Try again: ";
            cin >> subChoice;
        }

        const string catList[10] = {
            "Work","School","Personal","Errands",
            "Finance","Health","Appoinment", // note spelling matches your createNewList
            "Shopping","Others","None"
        };
        target = catList[subChoice - 1];
    }

    // 5️⃣ Filter by DEADLINE
    else if (opt == 5) {
        cout << "\nSelect deadline to show:\n";
        cout << " 1. Today\n";
        cout << " 2. Tommorow\n";     // matches stored text in createNewList()
        cout << " 3. This Week\n";
        cout << " 4. Next Week\n";
        cout << " 5. Next Month\n";
        cout << "Choice: ";
        
        while (true)
        {
            cin >> subChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";
        }

        while (subChoice < 1 || subChoice > 5) {
            cout << "Invalid choice. Try again: ";
            cin >> subChoice;
        }

        const string deadlineList[5] = {
            "Today","Tommorow","This Week","Next Week","Next Month"
        };
        target = deadlineList[subChoice - 1];
    }

    // 6️⃣ Filter by PRIORITY
    else if (opt == 6) {
        cout << "\nSelect priority to show:\n";
        cout << " 1. Critical\n";
        cout << " 2. High\n";
        cout << " 3. Medium\n";
        cout << " 4. Low\n";
        cout << " 5. None\n";
        cout << "Choice: ";

        while (true)
        {
            cin >> subChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";
        }

        while (subChoice < 1 || subChoice > 5) {
            cout << "Invalid choice. Try again: ";
            cin >> subChoice;
        }

        const string prioList[5] = {
            "Critical","High","Medium","Low","None"
        };
        target = prioList[subChoice - 1];
    }

    // now build filtered list of indices
    cin.ignore(); // clear newline

    vector<int> filtered;
    for (int i = 0; i < (int)names.size(); i++) {
        string value;
        if (opt == 4) {
            if (i < (int)categories.size()) value = categories[i];
        } else if (opt == 5) {
            if (i < (int)deadlines.size()) value = deadlines[i];
        } else if (opt == 6) {
            if (i < (int)priorities.size()) value = priorities[i];
        }

        if (value == target) {
            int fi = filtered.size();
            filtered.resize(fi + 1);
            filtered[fi] = i;
        }
    }

    if (filtered.size() == 0) {
        cout << "\nNo lists found for that selection.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    // sort filtered by NAME A -> Z
    for (int i = 0; i < (int)filtered.size() - 1; i++) {
        for (int j = i + 1; j < (int)filtered.size(); j++) {
            int idxI = filtered[i];
            int idxJ = filtered[j];
            if (names[idxI] > names[idxJ]) {
                int tmp = filtered[i];
                filtered[i] = filtered[j];
                filtered[j] = tmp;
            }
        }
    }

    // print only filtered lists (still show meta)
    cout << "\n---------- FILTERED LISTS (A -> Z) ---\n";
    for (int k = 0; k < (int)filtered.size(); k++) {
        int idx = filtered[k];
        cout << " " << (idx + 1) << ". " << names[idx] << "\n";

        if (idx < (int)categories.size())
            cout << "      Category : " << categories[idx] << "\n";
        if (idx < (int)deadlines.size())
            cout << "      Deadline : " << deadlines[idx] << "\n";
        if (idx < (int)priorities.size())
            cout << "      Priority : " << priorities[idx] << "\n";

        cout << "-------------------------------------\n";
    }

    cout << "Press Enter to continue...";
    cin.get();
}



// ----------------------------------
// Initialize Achievement Definitions
// ----------------------------------
void initAchievements(
    vector<string>& n,
    vector<string>& b,
    vector<int>& u,
    vector<int>& x
) {
    int i;

    n.clear(); b.clear(); u.clear(); x.clear();

    // Productivity
    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Add First Item"; b[i] = "🔹"; u[i] = 0; x[i] = 10;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Add 10 Items"; b[i] = "🟩"; u[i] = 0; x[i] = 20;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Add 50 Items"; b[i] = "🟪"; u[i] = 0; x[i] = 50;

    // Completion
    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Complete First Item"; b[i] = "🔸"; u[i] = 0; x[i] = 10;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Complete 10 Items"; b[i] = "🟨"; u[i] = 0; x[i] = 25;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Complete 50 Items"; b[i] = "🟫"; u[i] = 0; x[i] = 50;

    // Lists
    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Create First List"; b[i] = "📘"; u[i] = 0; x[i] = 10;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Create 5 Lists"; b[i] = "📗"; u[i] = 0; x[i] = 25;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Create 10 Lists"; b[i] = "📕"; u[i] = 0; x[i] = 50;

    // Level Achievements
    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Reach Level 3"; b[i] = "⭐"; u[i] = 0; x[i] = 20;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Reach Level 5"; b[i] = "🌟"; u[i] = 0; x[i] = 30;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "Reach Level 10"; b[i] = "🏆"; u[i] = 0; x[i] = 50;

    // Streaks
    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "1-Day Streak"; b[i] = "✨"; u[i] = 0; x[i] = 10;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "3-Day Streak"; b[i] = "🔥"; u[i] = 0; x[i] = 20;

    i = n.size(); n.resize(i + 1); b.resize(i + 1); u.resize(i + 1); x.resize(i + 1);
    n[i] = "7-Day Streak"; b[i] = "🏅"; u[i] = 0; x[i] = 40;
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

    for (i = 0; i < (int)list_of_lists.size(); i++) {
        totalItems += list_of_lists[i].size();
        for (j = 0; j < (int)list_of_lists[i].size(); j++) {
            if (list_of_lists[i][j].find("[DONE]") != string::npos)
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
        if (achUnlocked[i]) continue;

        if (achNames[i] == "Add First Item" && totalItems >= 1) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Add 10 Items" && totalItems >= 10) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Add 50 Items" && totalItems >= 50) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }

        if (achNames[i] == "Complete First Item" && totalCompleted >= 1) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Complete 10 Items" && totalCompleted >= 10) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Complete 50 Items" && totalCompleted >= 50) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }

        if (achNames[i] == "Create First List" && totalLists >= 1) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Create 5 Lists" && totalLists >= 5) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Create 10 Lists" && totalLists >= 10) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }

        if (achNames[i] == "Reach Level 3" && playerLevel >= 3) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Reach Level 5" && playerLevel >= 5) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "Reach Level 10" && playerLevel >= 10) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }

        if (achNames[i] == "1-Day Streak" && streakCount >= 1) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "3-Day Streak" && streakCount >= 3) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
        if (achNames[i] == "7-Day Streak" && streakCount >= 7) {
            achUnlocked[i] = 1;
            cout << "\n*** Achievement Unlocked: " << achBadges[i] << " " << achNames[i] << " (+" << achXP[i] << " XP) ***\n";
            addXP(achXP[i], gamificationEnabled, playerXP, playerLevel);
            continue;
        }
    }

    cout << "-------------------------------------";
}
// -------------------------
// SEARCH ITEMS IN A LIST
// -------------------------
void searchItems(const vector<string>& items) {
    cin.ignore();   // clear leftover newline
    string key;     // keyword user wants to search for

    cout << "\n=====================================\n";
    cout << "            SEARCH ITEMS             \n";
    cout << "=====================================\n";

    cout << "Enter keyword to search: ";
    getline(cin, key);

    cout << "\n-------------- RESULTS --------------\n";

    bool found = false;   // tracks if any item matches

    // Search through all items in the list
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].find(key) != string::npos) {   // substring match
            cout << " " << i + 1 << ". " << items[i] << "\n";
            found = true;
        }
    }

    // No results
    if (!found) {
        cout << "( No matching items found )\n";
    }

    cout << "-------------------------------------\n";
    cout << "Press Enter to continue...";
    cin.get();
}

// Live summary box used everywhere
void headerNewList() {

        cout << "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n";
        cout << "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n";
        cout << "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n";
        cout << "                                                ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ███╗   ██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n";
        cout << "                                               ██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ████╗  ██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══╝      \n";
        cout << "                                               ██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║           \n";
        cout << "                                               ██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n";
        cout << "                                               ╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║ ╚████║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║        \n";
        cout << "                                                ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝            \n";
        cout << "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";
    
 
}


// Live summary box used everywhere
void printLiveSummary(
    const string& title,
    const string& category,
    const string& deadline,
    const string& deadlinePriority,
    const string& notes
) {

        cout << "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n";
        cout << "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n";
        cout << "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n";
        cout << "                                                ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ███╗   ██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n";
        cout << "                                               ██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ████╗  ██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══╝      \n";
        cout << "                                               ██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║           \n";
        cout << "                                               ██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n";
        cout << "                                               ╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║ ╚████║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║        \n";
        cout << "                                                ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝            \n";
        cout << "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";
    
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "                                                                                              𝗧𝗔𝗟𝗟𝗬++ 𝗟𝗜𝗦𝗧 𝗦𝗨𝗠𝗠𝗔𝗥𝗬\n";
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "                                                                             [1] 📄 TITLE      : " << (title.empty() ? "<not set>" : title) << '\n';
        cout << "                                                                             [2] 🗂️ CATEGORY   : " << (category.empty() ? "<not set>" : category) << '\n';
        cout << "                                                                             [3] 🗓️ DEADLINE   : " << (deadline.empty() ? "<none>" : deadline) << '\n';
        cout << "                                                                             [4] ❗ PRIORITY   : " << (deadlinePriority.empty() ? "<none>" : deadlinePriority) << '\n';
        cout << "                                                                             [5] 📝 NOTES      : " << (notes.empty() ? "<none>" : notes) << '\n';
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        cout << "                                               ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  \n\n";
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


    cout << "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n";
    cout << "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n";
    cout << "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n";
    cout << "                                                ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ███╗   ██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n";
    cout << "                                               ██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ████╗  ██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══╝      \n";
    cout << "                                               ██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║           \n";
    cout << "                                               ██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n";
    cout << "                                               ╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║ ╚████║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║        \n";
    cout << "                                                ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝            \n";
    cout << "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";
      
    cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "                                                                                𝐋𝐈𝐒𝐓:: " << (title.empty() ? "<no title yet>" : title) << "\n";
    cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n\n";

    // If no items yet, show a hint
    if (items.empty()) {
        return;
    }


  // Print each item as:  ⃝  Item Name
for (size_t i = 0; i < items.size(); ++i) {
    bool highlightThisItem = (static_cast<int>(i) == highlightedItem);

    // Keep original spacing EXACT
    cout << "                                                                             〇 ";

    // Highlight item (inverse white bg + black text)
    if (highlightThisItem) {
        cout << "\033[7m";   // inverse only
    } else {
        cout << "\033[1m";   // bold only
    }

    cout << items[i] << "\033[0m\n";  // reset


    // Print descriptions (italic, highlight with inverse)
    if (i < descriptions.size()) {
        for (size_t d = 0; d < descriptions[i].size(); ++d) {
            bool highlightThisDesc =
                highlightThisItem && (static_cast<int>(d) == highlightedDesc);

            // Keep original spacing EXACT
            cout << "                                                                                • ";

            if (highlightThisDesc) {
                cout << "\033[7;3m";  // inverse + italic
            } else {
                cout << "\033[3m";    // italic only
            }

            cout << descriptions[i][d] << "\033[0m\n"; // reset
        }
    }

    cout << "\n"; // space between items
}




    cout << "\n                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
    cout << "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";

}



// Function to create a new list
void createNewList(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string>>>& list_of_descriptions,
    vector<string>& list_categories,
    vector<string>& list_deadlines,
    vector<string>& list_priorities,
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

    cout << "                                                                                ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸            \n";
    cout << "                                                                                ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸            \n";
    cout << "                                                                                ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸             \n\n";

    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";

    cout << "                                                                                      ╔════════════════════════╗                              \n";
    cout << "                                                                                     ╔║                        ║╗                             \n";
    cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 
        
    cout << "\033[2A"; // move UP 2 lines
    cout << "\033[87C"; // move RIGHT 17 columns (adjust until perfect)

    getline(cin, title);

    // ===================================================
    // ITEM Category
    // ===================================================

    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);
   
    cout << "                                                           ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ┏━┓   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓             \n";
    cout << "                                                           ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸    ┣━┫   ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃             \n";
    cout << "                                                           ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╹ ╹   ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹    ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹             \n\n";

    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "                                                                                 [𝟏] 💼 WORK         [𝟔] ❤️‍🩹 HEALTH \n";
    cout << "                                                                                 [𝟐] 🏫 SCHOOL       [𝟕] 📅 APPOINTMENT \n";
    cout << "                                                                                 [𝟑] 👤 PERSONAL     [𝟖] 🛒 SHOPPING \n";
    cout << "                                                                                 [𝟒] 🧹 ERRANDS      [𝟗] ➕ OTHERS \n";
    cout << "                                                                                 [𝟓] 💰 FINANCE      [𝟏𝟎]⛔ NONE\n";
    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
    cout << "                                                                                                ╔════╗                              \n";
    cout << "                                                                                               ╔║    ║╗                             \n";
    cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
        
    cout << "\033[2A"; // move UP 2 lines
    cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

    while (true)
    {
        cin >> categoryInput;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        cout << "Invalid input. Please try again.\n";
    }

    while(categoryInput < 1 || categoryInput >10){

        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);
    
            cout << "                                                           ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ┏━┓   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓             \n";
            cout << "                                                           ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸    ┣━┫   ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃             \n";
            cout << "                                                           ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╹ ╹   ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹    ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹             \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            cout << "                                                                                 [𝟏] 💼 WORK         [𝟔] ❤️‍🩹 HEALTH \n";
            cout << "                                                                                 [𝟐] 🏫 SCHOOL       [𝟕] 📅 APPOINTMENT \n";
            cout << "                                                                                 [𝟑] 👤 PERSONAL     [𝟖] 🛒 SHOPPING \n";
            cout << "                                                                                 [𝟒] 🧹 ERRANDS      [𝟗] ➕ OTHERS \n";
            cout << "                                                                                 [𝟓] 💰 FINANCE      [𝟏𝟎]⛔ NONE\n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 

            cout << "\033[12A"; // move UP 2 lines
            cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                        cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";

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

    cout << "                                                                                   ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸┏━┓            \n";
    cout << "                                                                                   ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸  ╺┛            \n";
    cout << "                                                                                   ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸ ╹             \n\n";

    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
    cout << "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n";
    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
    cout << "                                                                                                ╔════╗                              \n";
    cout << "                                                                                               ╔║    ║╗                             \n";
    cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
        
    cout << "\033[2A"; // move UP 2 lines
    cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)
    while (true)
    {
        cin >> deadlineStatus;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        cout << "Invalid input. Please try again.\n";
    }
    while(deadlineStatus < 1 || deadlineStatus > 2){

        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        cout << "                                                                                   ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸┏━┓            \n";
        cout << "                                                                                   ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸  ╺┛            \n";
        cout << "                                                                                   ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸ ╹             \n\n";

        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
        cout << "                                                                                                ╔════╗                              \n";
        cout << "                                                                                               ╔║    ║╗                             \n";
        cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 

        cout << "\033[8A"; // move UP 2 lines
        cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                    cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";
        cin >> deadlineStatus;
    }

    if(deadlineStatus == 1){
        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        cout << "                                                                              ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸            \n";
        cout << "                                                                              ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸           \n";
        cout << "                                                                              ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸           \n\n";

        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                 [𝟏] 🗓️ TODAY         [𝟐] 🗓️ TOMMOROW \n";
        cout << "                                                                                 [𝟑] 🗓️ THIS WEEK     [𝟒] 🗓️ NEXT WEEK \n";
        cout << "                                                                                 [𝟓] 🗓️ THIS MONTH    [𝟔] 🗓️ NEXT MNTH \n";
        cout << "                                                                                            [𝟕] ⚙️ CUSTOM    \n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
        cout << "                                                                                                ╔════╗                              \n";
        cout << "                                                                                               ╔║    ║╗                             \n";
        cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
            
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

        cin.ignore();
        while (true)
        {
            cin >> deadlineChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";
        }

        while(deadlineChoice < 1 || deadlineChoice > 7){

            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            cout << "                                                                              ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸            \n";
            cout << "                                                                              ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸           \n";
            cout << "                                                                              ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸           \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
            cout << "                                                                                 [𝟏] 🗓️ TODAY         [𝟐] 🗓️ TOMMOROW \n";
            cout << "                                                                                 [𝟑] 🗓️ THIS WEEK     [𝟒] 🗓️ NEXT WEEK \n";
            cout << "                                                                                 [𝟓] 🗓️ THIS MONTH    [𝟔] 🗓️ NEXT MNTH \n";
            cout << "                                                                                            [𝟕] ⚙️ CUSTOM    \n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 

            cout << "\033[11A"; // move UP 2 lines
            cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                    cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";
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
                cout << "\n----------------------------------------\n";
                cout << " ADD TARGET DATE FOR THIS ITEM\n";
                cout << "----------------------------------------\n";
                cout << "Enter Month: ";
                do
                {
                    while (true)
                    {
                        cin >> month;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        cout << "Invalid input. Please try again.\n";
                    }
                    if (month < 1 || month > 12)
                    {
                        cout << "Try again\n";
                    }
                } while (month < 1 || month > 12);
                Mindex = months.size();
                months.resize(Mindex + 1);
                months[Mindex] = month;
                cout << "Enter year number: ";
                do
                {
                    while (true)
                    {
                        cin >> year;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        cout << "Invalid input. Please try again.\n";
                    }
                    if (year < 2000 || year > 2100)
                    {
                        cout << "Try again\n";
                    }
                } while (year < 2000 || year > 2100);
                Yindex = years.size();
                years.resize(Yindex + 1);
                years[Yindex] = year;
                cout << "Enter date number: ";
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
                            cout << "Invalid input. Please try again.\n";
                        }
                        if (date < 1 || date > 31)
                        {
                            cout << "Try again\n";
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
                            cout << "Invalid input. Please try again.\n";
                        }
                        if (date < 1 || date > 30)
                        {
                            cout << "Try again\n";
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
                                cout << "Invalid input. Please try again.\n";
                            }
                            if (date < 1 || date > 29)
                            {
                                cout << "Try again\n";
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
                                cout << "Invalid input. Please try again.\n";
                            }
                            if (date < 1 || date > 28)
                            {
                                cout << "Try again\n";
                            }
                            
                        } while (date < 1 || date > 28);
                    }
                    break;
                }
                Dindex = dates.size();
                dates.resize(Dindex + 1);
                dates[Dindex] = date;
                break;
        }

        cin.ignore();
        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        cout << "                                                                 ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻             \n";
        cout << "                                                                 ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛           \n";
        cout << "                                                                 ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹           \n\n";

        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                 [𝟏] ⚠️ CRITICAL         [𝟐] 🟠 MEDIUM \n";
        cout << "                                                                                 [𝟑] 🔴 HIGH             [𝟒] 🟢 LOW \n";
        cout << "                                                                                            [𝟓] ⛔ NONE    \n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
        cout << "                                                                                                ╔════╗                              \n";
        cout << "                                                                                               ╔║    ║╗                             \n";
        cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
            
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)
        while (true)
        {
            cin >> deadlinePrioChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";
        }

        while(deadlinePrioChoice < 1 || deadlinePrioChoice > 5){

            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            cout << "                                                                 ┏━╸╻ ╻┏━┓┏━┓┏━┓┏━╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻             \n";
            cout << "                                                                 ┃  ┣━┫┃ ┃┃ ┃┗━┓┣╸     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛           \n";
            cout << "                                                                 ┗━╸╹ ╹┗━┛┗━┛┗━┛┗━╸   ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹           \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
            cout << "                                                                                 [𝟏] ⚠️ CRITICAL         [𝟐] 🟠 MEDIUM \n";
            cout << "                                                                                 [𝟑] 🔴 HIGH             [𝟒] 🟢 LOW \n";
            cout << "                                                                                            [𝟓] ⛔ NONE    \n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 

            cout << "\033[10A"; // move UP 2 lines
            cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                    cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";
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

        cout << "                                                                                     ┏━┓╺┳┓╺┳┓   ┏┓╻┏━┓╺┳╸┏━╸┏━┓┏━┓            \n";
        cout << "                                                                                     ┣━┫ ┃┃ ┃┃   ┃┗┫┃ ┃ ┃ ┣╸ ┗━┓ ╺┛           \n";
        cout << "                                                                                     ╹ ╹╺┻┛╺┻┛   ╹ ╹┗━┛ ╹ ┗━╸┗━┛ ╹          \n\n";

        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
        cout << "                                                                                                ╔════╗                              \n";
        cout << "                                                                                               ╔║    ║╗                             \n";
        cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
            
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

    while (true)
    {
        cin >> noteChoice;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        cout << "Invalid input. Please try again.\n";
    }

    while(noteChoice < 1 || noteChoice > 2){

        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

            cout << "                                                                                     ┏━┓╺┳┓╺┳┓   ┏┓╻┏━┓╺┳╸┏━╸┏━┓┏━┓            \n";
            cout << "                                                                                     ┣━┫ ┃┃ ┃┃   ┃┗┫┃ ┃ ┃ ┣╸ ┗━┓ ╺┛           \n";
            cout << "                                                                                     ╹ ╹╺┻┛╺┻┛   ╹ ╹┗━┛ ╹ ┗━╸┗━┛ ╹          \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
            cout << "                                                                                 [𝟏] ✅ YES         [2] ❌ NO \n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 

            cout << "\033[8A"; // move UP 2 lines
            cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                    cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";
        cin >> noteChoice;
    }

    if(noteChoice == 1){
    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

        cout << "                                                                                     ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━┓╺┳╸┏━╸            \n";
        cout << "                                                                                     ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┃ ┃ ┃ ┣╸          \n";
        cout << "                                                                                     ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━┛ ╹ ┗━╸          \n\n";

        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                      ╔════════════════════════╗                              \n";
        cout << "                                                                                     ╔║                        ║╗                             \n";
        cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 
            
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

        cin.ignore();
        getline(cin, notes); 
    }

    // ===================================================
    // ITEM SUMMARY
    // ===================================================

 while (true) {
    system("cls");
    printLiveSummary(title, category, deadline, deadlinePriority, notes);

        cout << "                                                                                   ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓   ╻  ╻┏━┓╺┳╸┏━┓             \n";
        cout << "                                                                                   ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃   ┃  ┃┗━┓ ┃  ╺┛           \n";
        cout << "                                                                                   ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹   ┗━╸╹┗━┛ ╹  ╹           \n\n";

        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                         [𝟏-𝟓] ⚠️ EDIT A FIELD      [𝟔] 🟠 CONFIRM AND CREATE           \n";
        cout << "                                                                                            [𝟕] ⛔ CANCEL                              \n";
        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                                ╔════╗                              \n";
        cout << "                                                                                               ╔║    ║╗                             \n";
        cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
            
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)
    
    while (true)
    {
        cin >> confirmationValue;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        cout << "Invalid input. Please try again.\n";
    }

    // Make sure leftover newline won't affect getline()
    cin.ignore();

    if (confirmationValue == 6) break;  // Continue to items

    if (confirmationValue == 7){
        system("cls");
        printLiveSummary(title, category, deadline, deadlinePriority, notes);

        cout << "                                                                   ╻  ╻┏━┓╺┳╸   ┏━╸┏━┓┏━╸┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏┓╻┏━╸┏━╸╻  ╻  ┏━╸╺┳┓             \n";
        cout << "                                                                   ┃  ┃┗━┓ ┃    ┃  ┣┳┛┣╸ ┣━┫ ┃ ┃┃ ┃┃┗┫   ┃  ┣━┫┃┗┫┃  ┣╸ ┃  ┃  ┣╸  ┃┃           \n";
        cout << "                                                                   ┗━╸╹┗━┛ ╹    ┗━╸╹┗╸┗━╸╹ ╹ ╹ ╹┗━┛╹ ╹   ┗━╸╹ ╹╹ ╹┗━╸┗━╸┗━╸┗━╸┗━╸╺┻┛          \n\n";
        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cout << "                                                                                       PRESS ENTER TO CONTINUE..                              \n";
        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
        cin.get();
        return;
    } 

    switch (confirmationValue) {

        case 1: {
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);
               
            cout << "                                                                                ┏━╸╺┳┓╻╺┳╸   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸            \n";
            cout << "                                                                                ┣╸  ┃┃┃ ┃    ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸             \n";
            cout << "                                                                                ┗━╸╺┻┛╹ ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸             \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";

            cout << "                                                                                      ╔════════════════════════╗                              \n";
            cout << "                                                                                     ╔║                        ║╗                             \n";
            cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 
                
            cout << "\033[2A"; // move UP 2 lines
            cout << "\033[87C"; // move RIGHT 17 columns (adjust until perfect)

            getline(cin, title);

            break;
        }

        case 2: {
            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            cout << "                                                                                   ┏━╸╺┳┓╻╺┳╸   ┏━╸┏━┓╺┳╸┏━╸┏━╸┏━┓┏━┓╻ ╻             \n";
            cout << "                                                                                   ┣╸  ┃┃┃ ┃    ┃  ┣━┫ ┃ ┣╸ ┃╺┓┃ ┃┣┳┛┗┳┛             \n";
            cout << "                                                                                   ┗━╸╺┻┛╹ ╹    ┗━╸╹ ╹ ╹ ┗━╸┗━┛┗━┛╹┗╸ ╹              \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            cout << "                                                                                 [𝟏] 💼 WORK         [𝟔] ❤️‍🩹 HEALTH \n";
            cout << "                                                                                 [𝟐] 🏫 SCHOOL       [𝟕] 📅 APPOINTMENT \n";
            cout << "                                                                                 [𝟑] 👤 PERSONAL     [𝟖] 🛒 SHOPPING \n";
            cout << "                                                                                 [𝟒] 🧹 ERRANDS      [𝟗] ➕ OTHERS \n";
            cout << "                                                                                 [𝟓] 💰 FINANCE      [𝟏𝟎]⛔ NONE\n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
                
            cout << "\033[4A"; // move UP 2 lines
            cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)
            int cat;

            while (true)
            {
                cin >> cat;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                 cout << "\033[5A"; // move UP 2 lines
                 cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                    cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";
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

            cout << "                                                                                   ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸            \n";
            cout << "                                                                                   ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸           \n";
            cout << "                                                                                   ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸           \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
            cout << "                                                                                 [𝟏] 🗓️ TODAY         [𝟐] 🗓️ TOMMOROW \n";
            cout << "                                                                                 [𝟑] 🗓️ THIS WEEK     [𝟒] 🗓️ NEXT WEEK \n";
            cout << "                                                                                 [𝟓] 🗓️ THIS MONTH    [𝟔] 🗓️ NEXT MNTH \n";
            cout << "                                                                                            [𝟕] ⚙️ CUSTOM    \n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 

            cout << "\033[4A"; // move UP 2 lines
            cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

            int d;

            
            while (true)
            {
                cin >> d;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }
            cin.ignore();

            const string deadlines[] = {
                "Today","Tomorrow","This Week",
                "Next Week","Next Month"
            };
            if (d >= 1 && d <= 5) deadline = deadlines[d - 1];
            break;
        }

        case 4: {

        // 🔒 Block priority edit if deadline is not set
        if (deadline.empty() || deadline == "None") {

            cout << "\033[5A"; // move UP 2 lines
            cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                cout << "\033[1;37;41m  ⚠️ PLEASE SELECT DEADLINE FIRST! ⚠️  \033[0m\n";

            cout << "\033[8B"; // move UP 2 lines
            cout << "\033[82C"; // move RIGHT 17 columns (adjust until perfect)
                cout << "   PRESS ANY KEY TO CONTINUE...";

            cin.get();               // waits for user to press Enter
            break;                   // go back to the summary menu
        }


            system("cls");
            printLiveSummary(title, category, deadline, deadlinePriority, notes);

            cout << "                                                                       ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━┓╺┳┓╻  ╻┏┓╻┏━╸   ┏━┓┏━┓╻┏━┓┏━┓╻╺┳╸╻ ╻             \n";
            cout << "                                                                       ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┣━┫ ┃┃┃  ┃┃┗┫┣╸    ┣━┛┣┳┛┃┃ ┃┣┳┛┃ ┃ ┗┳┛           \n";
            cout << "                                                                       ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸╹ ╹╺┻┛┗━╸╹╹ ╹┗━╸   ╹  ╹┗╸╹┗━┛╹┗╸╹ ╹  ╹            \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
            cout << "                                                                                 [𝟏] ⚠️ CRITICAL         [𝟐] 🟠 MEDIUM \n";
            cout << "                                                                                 [𝟑] 🔴 HIGH             [𝟒] 🟢 LOW \n";
            cout << "                                                                                            [𝟓] ⛔ NONE    \n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
                
            cout << "\033[4A"; // move UP 2 lines
            cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

            int p;


            while (true)
            {
                cin >> p;


                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
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

            cout << "                                                                                       ┏━╸╺┳┓╻╺┳╸   ┏┓╻┏━┓╺┳╸┏━╸            \n";
            cout << "                                                                                       ┣╸  ┃┃┃ ┃    ┃┗┫┃ ┃ ┃ ┣╸           \n";
            cout << "                                                                                       ┗━╸╺┻┛╹ ╹    ╹ ╹┗━┛ ╹ ┗━╸          \n\n";

            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";
            cout << "                                                                                      ╔════════════════════════╗                              \n";
            cout << "                                                                                     ╔║                        ║╗                             \n";
            cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 
                
            cout << "\033[4A"; // move UP 2 lines
            cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)

            getline(cin, notes);
            break;
        }

        default:
            cout << "Invalid choice.\n";
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

        cout << "                                                        ┏━┓╺┳╸┏━┓┏━┓╺┳╸   ┏━┓╺┳┓╺┳┓╻┏┓╻┏━╸   ╻╺┳╸┏━╸┏┳┓┏━┓   ╺┳╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ╻  ╻┏━┓╺┳╸╻            \n";
        cout << "                                                        ┗━┓ ┃ ┣━┫┣┳┛ ┃    ┣━┫ ┃┃ ┃┃┃┃┗┫┃╺┓   ┃ ┃ ┣╸ ┃┃┃┗━┓    ┃ ┃ ┃   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┃┗━┓ ┃ ╹  \n";
        cout << "                                                        ┗━┛ ╹ ╹ ╹╹┗╸ ╹    ╹ ╹╺┻┛╺┻┛╹╹ ╹┗━┛   ╹ ╹ ┗━╸╹ ╹┗━┛    ╹ ┗━┛    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹┗━┛ ╹ ╹          \n\n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━            \n";

        cout << "                                                                                    🟢 TYPE AN ITEM AND PRESS ENTER!\n";
        cout << "                                                                       Type 💾[1] POST / SAVE LIST | 🗑️[2] CANCEL / DISCARD LIST \n\n";

        cout << "                                                                                      ╔════════════════════════╗                              \n";
        cout << "                                                                                     ╔║                        ║╗                             \n";
        cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 
        
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[87C"; // move RIGHT 17 columns (adjust until perfect)

    cout << "Add item: ";
    
    getline(cin, item);

    // --- User wants to stop adding items ---
    if (item == "1")
        break;

    // --- User cancels entire creation process ---
    if (item == "2") {
        cout << "\nList creation cancelled.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    // Add new item
    index = items.size();
    items.resize(index + 1);
    items[index] = item;

    // Give XP for adding an item
    addXP(5, gamificationEnabled, playerXP, playerLevel);

    // 🔹 Refresh screen so the new item appears in the live list
    system("cls");
    printListLive(title, items, descriptions); // descriptions for this item not added yet


    // ===================================================
    // ENTER DESCRIPTIONS FOR THIS ITEM
    // ===================================================

        cout << "                                                         ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓╻            \n";
        cout << "                                                         ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃╹            \n";
        cout << "                                                         ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹╹          \n\n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                           \n";

        cout << "                                                                                🟢 TYPE A DESCRIPTION AND PRESS ENTER!\n";
        cout << "                                                                                          Type [1] 🗑️ SKIP \n\n";

        cout << "                                                                                      ╔════════════════════════╗                              \n";
        cout << "                                                                                     ╔║                        ║╗                             \n";
        cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 

    tempDescriptions.clear();

    while (true) {
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[90C"; // move RIGHT 17 columns (adjust until perfect)
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

            addXP(1, gamificationEnabled, playerXP, playerLevel);

            // 🔹 LIVE PREVIEW: show list including this item's in-progress descriptions
            system("cls");

            // Build a preview descriptions vector = existing ones + current temp
            vector<vector<string>> previewDescriptions = descriptions;
            previewDescriptions.push_back(tempDescriptions);

            printListLive(title, items, previewDescriptions);

            cout << "                                                         ┏━┓╺┳┓╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓╻            \n";
            cout << "                                                         ┣━┫ ┃┃ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫   ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃╹            \n";
            cout << "                                                         ╹ ╹╺┻┛╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹╹          \n\n";
            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                             \n";
            cout << "                                                                                     Type [1] 💾 FINISH DESCRIPTION \n\n";

            cout << "                                                                                      ╔════════════════════════╗                              \n";
            cout << "                                                                                     ╔║                        ║╗                             \n";
            cout << "                                                                                ═════╝╚════════════════════════╝╚═════                        \n" ; 

 
    }

    // Save this item’s description list
    dsaveIndex = descriptions.size();
    descriptions.resize(dsaveIndex + 1);
    descriptions[dsaveIndex] = tempDescriptions;

    // 🔹 Re-show the updated list after saving this item
    system("cls");
    printListLive(title, items, descriptions);

    cout << "\nItem + descriptions saved!\n\n";

} while (true);


// ===================================================
// CONFIRM ITEMS & DESCRIPTIONS (NEW SECTION)
// ===================================================

while (true) {
    system("cls");
    printListLive(title, items, descriptions);

    
    cout << "                                                         ┏━╸┏━┓┏┓╻┏━╸╻┏━┓┏┳┓   ╻╺┳╸┏━╸┏┳┓┏━┓   ┏━┓┏┓╻╺┳┓  ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻┏━┓┏━┓            \n";
    cout << "                                                         ┃  ┃ ┃┃┗┫┣╸ ┃┣┳┛┃┃┃   ┃ ┃ ┣╸ ┃┃┃┗━┓   ┣━┫┃┗┫ ┃┃   ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫┗━┓ ╺┛            \n";
    cout << "                                                         ┗━╸┗━┛╹ ╹╹  ╹╹┗╸╹ ╹   ╹ ╹ ┗━╸╹ ╹┗━┛   ╹ ╹╹ ╹╺┻┛  ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹┗━┛ ╹          \n\n";
    cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "                                                                                   [1] ✅ CONFIRM AND CREATE LIST\n";
    cout << "                                                                                   [2] ✏️ EDIT ITEMS / DESCRIPTIONS\n";
    cout << "                                                                                   [3] ❌ CANCEL / DISCARD LIST\n";
    cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
    cout << "                                                                                                ╔════╗                              \n";
    cout << "                                                                                               ╔║    ║╗                             \n";
    cout << "                                                                                          ═════╝╚════╝╚═════                        \n";

    cout << "\033[2A";
    cout << "\033[98C";

    int finalChoice;
    while (true) {
        cin >> finalChoice;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please try again.\n";
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
        cout << "\nList creation cancelled.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    // [2] EDIT ITEMS / DESCRIPTIONS
    if (finalChoice == 2) {
        while (true) {
            system("cls");
            printListLive(title, items, descriptions);

            if (items.empty()) {
                cout << "No items to edit. Press Enter to go back...";
                cin.get();
                break;
            }

            cout << "                                                             ┏━╸╺┳┓╻╺┳╸   ╻╺┳╸┏━╸┏┳┓┏━┓   ┏━┓┏┓╻╺┳┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻┏━┓┏━┓            \n";
            cout << "                                                             ┣╸  ┃┃┃ ┃    ┃ ┃ ┣╸ ┃┃┃┗━┓   ┣━┫┃┗┫ ┃┃    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫┗━┓ ╺┛            \n";
            cout << "                                                             ┗━╸╺┻┛╹ ╹    ╹ ╹ ┗━╸╹ ╹┗━┛   ╹ ╹╹ ╹╺┻┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹┗━┛ ╹           \n\n";
            cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";


            for (size_t i = 0; i < items.size(); ++i) {
                cout << "                                                                         [" << (i + 1) << "] " << items[i] << "\n";
            }
            cout << "                                                                         [0] 🔙 DONE EDITING\n\n";
            cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n";

            cout << "\033[4A";
            cout << "\033[98C";

            int itemChoice;
            while (true) {
                cin >> itemChoice;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please try again.\n";
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

                cout << "                                                                                        ┏━╸╺┳┓╻╺┳╸   ╻╺┳╸┏━╸┏┳┓           \n";
                cout << "                                                                                        ┣╸  ┃┃┃ ┃    ┃ ┃ ┣╸ ┃┃┃           \n";
                cout << "                                                                                        ┗━╸╺┻┛╹ ╹    ╹ ╹ ┗━╸╹ ╹        \n\n";
                cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━             \n";
                cout << "                                                                         EDITING ITEM #" << itemChoice << ": " << items[itemIndex] << "    \n";
                cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━             \n";
                cout << "                                                                                     [1] ✏️ EDIT ITEM NAME                           \n";
                cout << "                                                                                     [2] ✏️ EDIT / DELETE DESCRIPTIONS               \n";
                cout << "                                                                                     [3] 🗑️ DELETE THIS ITEM                         \n";
                cout << "                                                                                     [4] 🔙 BACK                                     \n";
                cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━             \n";
                cout << "                                                                                                ╔════╗                              \n";
                cout << "                                                                                               ╔║    ║╗                             \n";
                cout << "                                                                                          ═════╝╚════╝╚═════                        \n";

                cout << "\033[4A";
                cout << "\033[98C";

                int itemEditChoice;
                while (true) {
                    cin >> itemEditChoice;
                    if (!cin.fail()) break;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please try again.\n";
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

                        cout << "                                                           ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ┏┓╻┏━┓┏┳┓┏━╸   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╻╺┳╸┏━╸┏┳┓              \n";
                        cout << "                                                           ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃   ┃┗┫┣━┫┃┃┃┣╸    ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓   ┃ ┃ ┣╸ ┃┃┃            \n";
                        cout << "                                                           ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛   ╹ ╹╹ ╹╹ ╹┗━╸   ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╹ ╹ ┗━╸╹ ╹          \n\n";
                        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n";


                        cout << "                                                                                      ╔════════════════════════╗                                                   \n";
                        cout << "                                                                                     ╔║                        ║╗                                                  \n";
                        cout << "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n" ; 

                        cout << "\033[2A";
                        cout << "\033[98C";



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

                        cout << "                                                    ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ╺┳┓┏━╸┏━┓┏━╸┏━┓┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻   ╺┳╸┏━┓   ┏━╸╺┳┓╻╺┳╸    ╻   ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸       \n";
                        cout << "                                                    ┗━┓┣╸ ┃  ┣╸ ┃   ┃     ┃┃┣╸ ┗━┓┃  ┗━┓┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫    ┃ ┃ ┃   ┣╸  ┃┃┃ ┃    ┏┛    ┃┃┣╸ ┃  ┣╸  ┃ ┣╸        \n";
                        cout << "                                                    ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╺┻┛┗━╸┗━┛┗━╸┗━┛╹┗╸╹╹   ╹ ╹┗━┛╹ ╹    ╹ ┗━┛   ┗━╸╺┻┛╹ ╹    ╹    ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸        \n\n";
                        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                        cout << "                                                                         DESCRIPTIONS FOR: " << items[itemIndex] << "\n";
                        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";


                        if (itemIndex >= descriptions.size() || descriptions[itemIndex].empty()) {
                            cout << "                                                                         (No descriptions yet.)\n";
                        } else {
                            for (size_t d = 0; d < descriptions[itemIndex].size(); ++d) {
                                cout << "                                                                         (" << (d + 1) << ") " 
                                     << descriptions[itemIndex][d] << "\n";
                            }
                        }

                        cout << "\n";
                        cout << "                                                                         [0] 🔙 BACK\n";
                        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

                        cout << "                                                                                                ╔════╗                              \n";
                        cout << "                                                                                               ╔║    ║╗                             \n";
                        cout << "                                                                                          ═════╝╚════╝╚═════                        \n";

                        cout << "\033[4A";
                        cout << "\033[98C";

                        int descChoice;
                        while (true) {
                            cin >> descChoice;
                            if (!cin.fail()) break;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input. Please try again.\n";
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
                        cout << "                                                                              ┏━╸╺┳┓╻╺┳╸   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻      \n";
                        cout << "                                                                              ┣╸  ┃┃┃ ┃     ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫        \n";
                        cout << "                                                                              ┗━╸╺┻┛╹ ╹    ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹        \n\n";
                        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                        cout << "                                                                         EDITING DESCRIPTION #" << descChoice
                            << " OF ITEM #" << (itemIndex + 1) << ": " << items[itemIndex] << "\n";
                        cout << "                                                                         → \"" << descriptions[itemIndex][descIndex] << "\"\n";
                        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

                        cout << "                                                                         [1] ✏️ EDIT THIS LINE\n";
                        cout << "                                                                         [2] 🗑️ DELETE THIS LINE\n";
                        cout << "                                                                         [3] 🔙 CANCEL\n";
                        cout << "                                                                         ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                        cout << "                                                                                                ╔════╗                              \n";
                        cout << "                                                                                               ╔║    ║╗                             \n";
                        cout << "                                                                                          ═════╝╚════╝╚═════                        \n";

                        cout << "\033[2A";
                        cout << "\033[98C";



                        int descAction;
                        while (true) {
                            cin >> descAction;
                            if (!cin.fail()) break;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input. Please try again.\n";
                        }
                        cin.ignore();

                        if (descAction == 1) {
                        system("cls");
                        printListLive(title, items, descriptions,
                        static_cast<int>(itemIndex),
                        static_cast<int>(descIndex));

                            cout << "                                                       ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ┏┓╻┏━╸╻ ╻   ╺┳╸┏━╸╻ ╻╺┳╸   ┏━╸┏━┓┏━┓   ╺┳╸╻ ╻╻┏━┓   ╺┳┓┏━╸┏━┓┏━╸┏━┓╻┏━┓╺┳╸╻┏━┓┏┓╻              \n";
                            cout << "                                                       ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┃┗┫┣╸ ┃╻┃    ┃ ┣╸ ┏╋┛ ┃    ┣╸ ┃ ┃┣┳┛    ┃ ┣━┫┃┗━┓    ┃┃┣╸ ┗━┓┃  ┣┳┛┃┣━┛ ┃ ┃┃ ┃┃┗┫            \n";
                            cout << "                                                       ┗━╸╹ ╹ ╹ ┗━╸╹┗╸   ╹ ╹┗━╸┗┻┛    ╹ ┗━╸╹ ╹ ╹    ╹  ┗━┛╹┗╸    ╹ ╹ ╹╹┗━┛   ╺┻┛┗━╸┗━┛┗━╸╹┗╸╹╹   ╹ ╹┗━┛╹ ╹          \n\n";
                            cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                           \n";


                            cout << "                                                                                      ╔════════════════════════╗                                                   \n";
                            cout << "                                                                                     ╔║                        ║╗                                                  \n";
                            cout << "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n" ; 

                            cout << "\033[2A";
                            cout << "\033[98C";

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
    }
    listmonth.resize(listIndex + 1);
    listmonth[listIndex] = months;

    listyear.resize(listIndex + 1);
    listyear[listIndex] = years;

    listdate.resize(listIndex + 1);
    listdate[listIndex] = dates;

    // store category / deadline / priority for this list
    list_categories[listIndex]   = category;
    list_deadlines[listIndex]    = deadline;
    list_priorities[listIndex]   = deadlinePriority;


    // Give XP for creating a new list
    addXP(10, gamificationEnabled, playerXP, playerLevel);

    // ===================================================
    // COMPLETION MESSAGE
    // ===================================================

    system("cls");
    headerNewList();

    cout << "                                                                 ╻  ╻┏━┓╺┳╸   ┏━┓┏━┓╻ ╻┏━╸╺┳┓   ┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻╻          \n";
    cout << "                                                                 ┃  ┃┗━┓ ┃    ┗━┓┣━┫┃┏┛┣╸  ┃┃   ┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛╹          \n";
    cout << "                                                                 ┗━╸╹┗━┛ ╹    ┗━┛╹ ╹┗┛ ┗━╸╺┻┛   ┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹ ╹           \n\n";
    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                        \n";
   
    cout << "                                                                                     \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO CONTINUE...  \033[0m";

    cin.get();
}


void headerVoidList() {

        cout << "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n";
        cout << "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n";
        cout << "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n";
        cout << "                                                                      ██╗   ██╗██╗███████╗██╗    ██╗    ██╗     ██╗███████╗████████╗     \n";
        cout << "                                                                      ██║   ██║██║██╔════╝██║    ██║    ██║     ██║██╔════╝╚══██╔══     \n";
        cout << "                                                                      ██║   ██║██║█████╗  ██║ █╗ ██║    ██║     ██║███████╗   ██║          \n";
        cout << "                                                                      ╚██╗ ██╔╝██║██╔══╝  ██║███╗██║    ██║     ██║╚════██║   ██║        \n";
        cout << "                                                                       ╚████╔╝ ██║███████╗╚███╔███╔╝    ███████╗██║███████║   ██║          \n";
        cout << "                                                                        ╚═══╝  ╚═╝╚══════╝ ╚══╝╚══╝     ╚══════╝╚═╝╚══════╝   ╚═╝              \n";
        cout << "                                               ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";
    
 
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
    vector<string>& list_deadlines,
    int& cdate,
    int& cmonth,
    int& cyear
) {

        if (name_of_list.size() == 0) {
            cout << "\nNo lists created yet.\n";
            cout << "Press Enter...";
            cin.ignore();
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

    cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n";

    for (int i = 0; i < (int)name_of_list.size(); i++) {
    cout << "                                                                                 " << i + 1 << ". " << name_of_list[i] << "\n";
    }

    cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n";

    cout << "                                                                       ┏━┓┏━╸╻  ┏━╸┏━╸╺┳╸   ┏━┓   ╻  ╻┏━┓╺┳╸   ┏┓╻╻ ╻┏┳┓┏┓ ┏━╸┏━┓          \n";
    cout << "                                                                       ┗━┓┣╸ ┃  ┣╸ ┃   ┃    ┣━┫   ┃  ┃┗━┓ ┃    ┃┗┫┃ ┃┃┃┃┣┻┓┣╸ ┣┳┛          \n";
    cout << "                                                                       ┗━┛┗━╸┗━╸┗━╸┗━╸ ╹    ╹ ╹   ┗━╸╹┗━┛ ╹    ╹ ╹┗━┛╹ ╹┗━┛┗━╸╹┗╸          \n\n";
    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n";
    cout << "                                                                                      [S] 🔎 SEARCH LIST NAMES                             \n";
    cout << "                                                                                      [0] 🔙 BACK TO MAIN MENU                            \n";
    cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n";
    cout << "                                                                                                ╔════╗                                     \n";
    cout << "                                                                                               ╔║    ║╗                                    \n";
    cout << "                                                                                          ═════╝╚════╝╚═════                               \n";

    // ================================
    // ALLOW USER TO CHOOSE A LIST
    // ================================

    cout << "\033[2A";
    cout << "\033[98C";
    

    string choiceStr;
    cin >> choiceStr;

    if (choiceStr == "0") {
        cin.ignore();
        break;            // break out of while(true) and exit viewLists
    }

    // ================================
    // SEARCH MODE (User typed S)
    // ================================
    if (choiceStr == "S" || choiceStr == "s") {
        cin.ignore();
        string key;

        system("cls");
        headerVoidList();

        cout << "                                                                              ┏━┓┏━╸┏━┓┏━┓┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸   ┏┓╻┏━┓┏┳┓┏━╸               \n";
        cout << "                                                                              ┗━┓┣╸ ┣━┫┣┳┛┃  ┣━┫   ┃  ┃┗━┓ ┃    ┃┗┫┣━┫┃┃┃┣╸                \n";
        cout << "                                                                              ┗━┛┗━╸╹ ╹╹┗╸┗━╸╹ ╹   ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹┗━╸               \n\n";
        cout << "                                                                                 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                   \n";

        cout << "                                                                                      ╔════════════════════════╗                                                   \n";
        cout << "                                                                                     ╔║                        ║╗                                                  \n";
        cout << "                                                                                ═════╝╚════════════════════════╝╚═════                                             \n" ;

            cout << "\033[2A";
            cout << "\033[98C";

        getline(cin, key);

        cout << "\n--------------- RESULTS --------------\n";

        bool found = false;

        // Scan all list names for keyword match
        for (int i = 0; i < (int)name_of_list.size(); i++) {
            if (name_of_list[i].find(key) != string::npos) {
                cout << " " << i + 1 << ". " << name_of_list[i] << "\n";
                found = true;
            }
        }

              if (!found)
            cout << "( No matching list names found )\n";

        cout << "-------------------------------------\n";
        cout << "Press Enter to go back...";
        cin.get();
        continue;   // 🔁 back to the top of while(true)
    }


    // ================================
    // USER CHOSE A LIST NUMBER
    // ================================
    int choice = 0;
    try {
        choice = stoi(choiceStr); // convert input to number
    } catch (...) {
        cout << "\nInvalid.\nPress Enter...";
        cin.ignore();
        cin.get();
        continue;   // 🔁 back to list selection
    }
    cin.ignore();

    int index = choice - 1; // convert to 0-based index
    // Validate chosen list
    if (choice < 1 || choice > (int)name_of_list.size()) {
        cout << "\nInvalid.\nPress Enter...";
        cin.get();
        continue;   
    }
    string missing;
    if (!datecreated.empty() && !monthcreated.empty() && !yearcreated.empty()) {
    
        if (list_deadlines[index] == "Today")
        {
            if(cyear > yearcreated[index])
            {
                missing = to_string(cyear - yearcreated[index]) + " year(s)";
            }
            else if(cyear == yearcreated[index] && cmonth > monthcreated[index])
            {
                missing = to_string(cmonth - monthcreated[index]) + " month(s)";
            }
            else if(cyear == yearcreated[index] && cmonth == monthcreated[index] && cdate > datecreated[index])
            {
                missing = to_string(cdate - datecreated[index]) + " day(s)";
            }
        }
        else if (list_deadlines[index] == "This Week")
        {
            if(cyear > yearcreated[index])
            {
                missing = to_string(cyear - yearcreated[index]) + " year(s)";
            }
            else if(cyear == yearcreated[index] && cmonth > monthcreated[index])
            {
                missing = to_string(cmonth - monthcreated[index]) + " month(s)";
            }
            else if(cyear == yearcreated[index] && cmonth == monthcreated[index] && cdate > (datecreated[index] + 7))
            {
                missing = to_string(cdate - datecreated[index]) + " day(s)";
            }
        }
        else if (list_deadlines[index] == "Next Week")
        {
            if(cyear > yearcreated[index])
            {
                missing = to_string(cyear - yearcreated[index]) + " year(s)";
            }
            else if(cyear == yearcreated[index] && cmonth > monthcreated[index])
            {
                missing = to_string(cmonth - monthcreated[index]) + " month(s)";
            }
            else if(cyear == yearcreated[index] && cmonth == monthcreated[index] && cdate > (datecreated[index]+14))
            {
                missing = to_string(cdate - datecreated[index]) + " day(s)";
            }
        }
        else if (list_deadlines[index] == "This month")
        {
            if(cyear > yearcreated[index])
            {
                missing = to_string(cyear - yearcreated[index]) + " year(s)";
            }
            else if(cyear == yearcreated[index] && cmonth > monthcreated[index])
            {
                missing = to_string(cmonth - monthcreated[index]) + " month(s)";
            }
        }
        else if (list_deadlines[index] == "Next month")
        {
            if(cyear > yearcreated[index])
            {
                missing = to_string(cyear - yearcreated[index]) + " year(s)";
            }
            else if(cyear == yearcreated[index] && cmonth > monthcreated[index]+1)
            {
                missing = to_string(cmonth - monthcreated[index]) + " month(s)";
            }
        }  
    }
    else
        {
            if(cyear > yearcreated[index])
            {
                missing = to_string(cyear - yearcreated[index]) + " year(s)";
            }
            else if(cyear == yearcreated[index] && cmonth > monthcreated[index])
            {
                missing = to_string(cmonth - monthcreated[index]) + " month(s)";
            }
            else if(cyear == yearcreated[index] && cmonth == monthcreated[index] && cdate > datecreated[index])
            {
                missing = to_string(cdate - datecreated[index]) + " day(s)";
            }
        }
    
    
    

    

    // Access selected list's items and descriptions
    vector<string>& items = list_of_lists[index];
    
    vector<int>& months = listmonth[index];
    vector<int>& dates  = listdate[index];
    vector<int>& years  = listyear[index];

    // Prevent crash for lists without descriptions
    vector<vector<string>> emptyVecVec;
    vector<vector<string>>& descs =
        (index < (int)list_of_descriptions.size())
        ? list_of_descriptions[index]
        : emptyVecVec;

    // ================================
    // DISPLAY SELECTED LIST CONTENT
    // ================================
        system("cls");
        headerVoidList();
        
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n";
        cout << "                                                                             ""𝐋𝐈𝐒𝐓 𝐍𝐀𝐌𝐄: " << name_of_list[index] << "\n";
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n";

        cout << "                                                                              📂 CREATED ON  : "
             << monthcreated[index] << "/"
             << datecreated[index] << "/"
             << yearcreated[index] << "\n";
        cout << "                                                                              📅 TARGET DATE : ";

            if (!months.empty() && !dates.empty() && !years.empty()) {
                cout << months[0] << "/" << dates[0] << "/" << years[0] << "\n\n";
            } else {
                cout << "<none>\n";
            }

        if (items.size() == 0) {
            cout << "(No items)\n";
        } else {
            int completedCount = 0;

        cout << "                                                                                   📦 ITEMS:\n ";  
        // Print each item and its descriptions
        for (int i = 0; i < (int)items.size(); i++) {

            cout << "                                                                                       " << i + 1 << ". " << items[i] << "\n";
            
            // Print all descriptions for this item (if any)
            if (i < (int)descs.size()) {
                for (int d = 0; d < (int)descs[i].size(); d++) {
            cout << "                                                                                            • " << descs[i][d] << "\n";
                }
            }

            // Track [DONE] items
            if (items[i].find("[DONE]") != string::npos)
                completedCount++;
        }

        // ================================
        // STATISTICS CALCULATION
        // ================================
        int notDone = items.size() - completedCount;

        double percentDone = (items.size() > 0)
            ? (completedCount * 100.0) / items.size()
            : 0;

        double percentNot = (items.size() > 0)
            ? (notDone * 100.0) / items.size()
            : 0;

        // ================================
        // STATISTICS DISPLAY
        // ================================
        cout << "\n                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n";
        cout << "                                                                                                   𝐒𝐓𝐀𝐓𝐈𝐒𝐓𝐈𝐂𝐒                                \n";
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n";
        
        cout << "                                                                                       Missing         : " << missing << "\n";
        cout << "                                                                                       Total Items       : " << items.size() << "\n";
        cout << "                                                                                       Completed Items   : " << completedCount << "\n";
        cout << "                                                                                       Not Done          : " << notDone << "\n";
        cout <<                                                                                         fixed << setprecision(2);
        cout << "                                                                                       % Completed       : " << percentDone << "%\n";
        cout << "                                                                                       % Not Completed   : " << percentNot << "%\n\n";
        cout << "                                                                             ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━         \n\n";
    }

    
        cout << "                                                                                       \033[1;48;2;255;255;255m\033[38;2;0;0;0m  ➡️ PRESS ENTER TO GO BACK...  \033[0m";
    cin.get();

    } 
}



// -----------------------------
// EDIT LIST
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
    vector<vector<int>>& listyear
) {
    // If no lists exist, there is nothing to edit
    if (name_of_list.size() == 0) {
        cout << "\nNo lists to edit.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // ================================
    // DISPLAY ALL LISTS TO CHOOSE FROM
    // ================================
    cout << "\n=====================================\n";
    cout << "               EDIT LIST             \n";
    cout << "=====================================\n";

    for (int i = 0; i < (int)name_of_list.size(); i++) {
        cout << " " << i + 1 << ". " << name_of_list[i] << "\n";
    }

    cout << "\n S. Search list names\n";
    cout << "-------------------------------------\n";

    // Let the user choose which list to modify
    cout << "Select a list number to edit: ";
    string choiceStr;
    cin >> choiceStr;

    // User wants to search by keyword
    if (choiceStr == "S" || choiceStr == "s") {
        searchLists(name_of_list);
        return;
    }

    // Convert chosen list number
    int choice = 0;
    try {
        choice = stoi(choiceStr);
    } catch (...) {
        cout << "\nInvalid list number.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    cin.ignore();

    // Validate list index
    if (choice < 1 || choice > (int)name_of_list.size()) {
        cout << "\nInvalid list number.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    int index = choice - 1; // convert to 0-index

    // =============================================
    // EDIT LOOP — continues until user exits
    // =============================================
    while (true) {

        system("cls");

        cout << "=====================================\n";
        cout << "         Editing: " << name_of_list[index] << "\n";
        cout << "=====================================\n\n";

        // Items in this list
        vector<string> &items = list_of_lists[index];
        vector<int>& months = listmonth[index];
        vector<int>& dates = listdate[index];
        vector<int>& years = listyear[index];


        // Ensure description array matches list count
        if (index >= (int)list_of_descriptions.size()) {
            int oldSize = list_of_descriptions.size();
            list_of_descriptions.resize(index + 1);
            for (int t = oldSize; t < (int)list_of_descriptions.size(); t++) {
                list_of_descriptions[t] = vector<vector<string>>();
            }
        }

        vector<vector<string>> &descriptions = list_of_descriptions[index];

        // -------------------------------
        // DISPLAY ITEMS + DESCRIPTIONS
        // -------------------------------
        int completedCount = 0;

        if (items.size() == 0) {
            cout << "(No items yet)\n";
        } else {
            for (int i = 0; i < (int)items.size(); i++) {
                cout << " " << i + 1 << ". " << items[i] << "\n";

                // Show descriptions of this item
                if (i < (int)descriptions.size()) {
                    for (int d = 0; d < (int)descriptions[i].size(); d++) {
                        cout << "      > " << descriptions[i][d] << "\n";
                    }
                }

                // Count completed items
                if (items[i].find("[DONE]") != string::npos)
                    completedCount++;
            }
        }

        // -------------------------------
        // STATISTICS CALCULATION
        // -------------------------------
        int notDone = items.size() - completedCount;

        double percentDone = 0;
        double percentNotDone = 0;

        if (items.size() > 0) {
            percentDone = (completedCount * 100.0) / items.size();
            percentNotDone = (notDone * 100.0) / items.size();
        }

        // -------------------------------
        // SHOW LIST STATISTICS
        // -------------------------------
        cout << "\n--------------- STATISTICS -----------\n";
        cout << " Total Items       : " << items.size() << "\n";
        cout << " Completed Items   : " << completedCount << "\n";
        cout << " Not Done Items    : " << notDone << "\n";
        cout << fixed << setprecision(2);
        cout << " % Completed       : " << percentDone << "%\n";
        cout << " % Not Completed   : " << percentNotDone << "%\n";
        cout << "-------------------------------------\n";

        // ================================
        // EDIT MENU OPTIONS
        // ================================
        cout << "\nEDIT MENU\n";
        cout << "-------------------------------------\n";
        cout << " 1. Add New Item\n";
        cout << " 2. Edit an Item\n";
        cout << " 3. Delete an Item\n";
        cout << " 4. Mark / Unmark Item as DONE\n";
        cout << " 5. Reorder Items (Swap)\n";
        cout << " 6. Rename List\n";
        cout << " 7. Edit Item Descriptions\n";
        cout << " 8. Search Items\n";
        cout << " 9. Return to Main Menu\n";
        cout << "-------------------------------------\n";

        int editChoice;
        cout << "\nChoose an option: ";
        while (true)
        {
            cin >> editChoice;
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";
        }
        // User wants to search items within this list
        if (editChoice == 8) {
            searchItems(items);
            continue;
        }

        // ============================================
        // OPTION 1 — ADD NEW ITEM
        // ============================================
        if (editChoice == 1) {

            string newItem;
            cout << "\nEnter new item: ";
            getline(cin, newItem);

            // Add item using resize
            int newIndex = items.size();
            items.resize(newIndex + 1);
            items[newIndex] = newItem;

            // Give XP for adding an item
            addXP(5, gamificationEnabled, playerXP, playerLevel);

            // Prompt for descriptions immediately
            cout << "\nAdd descriptions for this new item\n";
            cout << "-------------------------------------\n";
            cout << "• Type a description and press Enter\n";
            cout << "• Type 'done' when finished\n";
            cout << "• Type 'none' to skip\n";
            cout << "-------------------------------------\n";

            vector<string> temp;
            string nd;

            while (true) {
                cout << "Description: ";
                getline(cin, nd);
                if (nd == "done") break;
                if (nd == "none") { temp.clear(); break; }
                if (nd == "") continue;

                int di = temp.size();
                temp.resize(di + 1);
                temp[di] = nd;

                // Give XP for adding a description
                addXP(1, gamificationEnabled, playerXP, playerLevel);
            }

            // Ensure description vector is same size as items
            int descVecOld = descriptions.size();
            descriptions.resize(items.size());
            for (int i = descVecOld; i < (int)descriptions.size(); i++)
                descriptions[i] = vector<string>();

            descriptions[newIndex] = temp;

            cout << "\nItem added!\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        // ============================================
        // OPTION 2 — EDIT ITEM TEXT
        // ============================================
        else if (editChoice == 2) {

            if (items.size() == 0) {
                cout << "\nNo items to edit.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            int itemNum;
            cout << "\nEnter item number to edit: ";
            while (true)
            {
                cin >> itemNum;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }
            
            
            cin.ignore();

            // Validate
            if (itemNum < 1 || itemNum > (int)items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            // Replace text while preserving [DONE] tag
            string updatedText;
            cout << "Enter new text: ";
            getline(cin, updatedText);

            if (items[itemNum - 1].find("[DONE]") != string::npos)
                items[itemNum - 1] = "[DONE] " + updatedText;
            else
                items[itemNum - 1] = updatedText;

            cout << "Item updated!\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        // ============================================
        // OPTION 3 — DELETE ITEM
        // ============================================
        else if (editChoice == 3) {

            if (items.size() == 0) {
                cout << "\nNo items to delete.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            int delNum;
            cout << "\nEnter item number to delete: ";
            while (true)
            {
                cin >> delNum;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }
            
            cin.ignore();

            // Validate
            if (delNum < 1 || delNum > (int)items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            // Remove item + its descriptions
            items.erase(items.begin() + (delNum - 1));
            dates.erase(dates.begin() + (delNum - 1));
            months.erase(months.begin() + (delNum - 1));
            years.erase(years.begin() + (delNum - 1));
            if (delNum - 1 < (int)descriptions.size()) {
                descriptions.erase(descriptions.begin() + (delNum - 1));
            }

            // Give XP for deleting an item (small consolation)
            addXP(2, gamificationEnabled, playerXP, playerLevel);

            cout << "Item deleted!\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        // ============================================
        // OPTION 4 — MARK / UNMARK AS DONE
        // ============================================
        else if (editChoice == 4) {

            if (items.size() == 0) {
                cout << "\nNo items to mark.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            int markNum;
            cout << "\nEnter item number to mark/unmark: ";
            while (true)
            {
                cin >> markNum;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }

            cin.ignore();

            // Validate
            if (markNum < 1 || markNum > (int)items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            string &target = items[markNum - 1];

            // Toggle DONE tag
            if (target.find("[DONE]") != string::npos) {
                if (target.size() >= 7) target = target.substr(7);
                cout << "Item unmarked.\n";
            } else {
                target = "[DONE] " + target;

                // Give XP for marking item done
                addXP(8, gamificationEnabled, playerXP, playerLevel);

                // If this marking finishes the entire list give a completion bonus
                // completedCount contains current number of done items before this toggle,
                // so if completedCount + 1 == items.size(), the list is now fully completed.
                if (completedCount + 1 == (int)items.size() && items.size() > 0) {
                    addXP(50, gamificationEnabled, playerXP, playerLevel); // completion bonus
                }

                cout << "Item marked as DONE.\n";
            }

            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        // ============================================
        // OPTION 5 — SWAP TWO ITEMS
        // ============================================
        else if (editChoice == 5) {

            if (items.size() < 2) {
                cout << "\nNot enough items to reorder.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            int a, b;
            cout << "\nEnter first item number: ";
            while (true)
            {
                cin >> a;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }
            cout << "Enter second item number: ";
            while (true)
            {
                cin >> b;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }
            cin.ignore();

            // Validate swap positions
            if (a < 1 || a > (int)items.size() || b < 1 || b > (int)items.size()) {
                cout << "\nInvalid item numbers!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            // Swap item text
            string temp = items[a - 1];
            items[a - 1] = items[b - 1];
            items[b - 1] = temp;

            

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

            cout << "Items swapped!\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        // ============================================
        // OPTION 6 — RENAME THE LIST
        // ============================================
        else if (editChoice == 6) {

            string newName;
            cout << "\nEnter new list name: ";
            getline(cin, newName);

            name_of_list[index] = newName;

            cout << "List renamed!\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        // ============================================
        // OPTION 7 — EDIT ITEM DESCRIPTIONS
        // ============================================
        else if (editChoice == 7) {

            if (items.size() == 0) {
                cout << "\nNo items to edit descriptions for.\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            int itemNum;
            cout << "\nEnter item number to edit descriptions: ";
            
            while (true)
            {
                cin >> itemNum;
                if (!cin.fail()) break;
                cin.clear();
                cin.ignore(1000 , '\n');
                cout << "Invalid input. Please try again.\n";
            }
            cin.ignore();

            // Validate index
            if (itemNum < 1 || itemNum > (int)items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            // Ensure descriptions exist for all items
            if ((int)descriptions.size() < (int)items.size()) {
                int old = descriptions.size();
                descriptions.resize(items.size());
                for (int i = old; i < (int)descriptions.size(); i++)
                    descriptions[i] = vector<string>();
            }

            // -----------------------------------------
            // DESCRIPTIONS EDIT SUB-MENU
            // -----------------------------------------
            while (true) {
                cout << "\nDescriptions for item: " << items[itemNum - 1] << "\n";

                // Display current descriptions
                if (descriptions[itemNum - 1].size() == 0) {
                    cout << "(no descriptions)\n";
                } else {
                    for (int d = 0; d < (int)descriptions[itemNum - 1].size(); d++) {
                        cout << "  " << d + 1 << ". " << descriptions[itemNum - 1][d] << "\n";
                    }
                }

                // Description editing options
                cout << "\n 1. Add new description\n";
                cout << " 2. Edit a description\n";
                cout << " 3. Delete a description\n";
                cout << " 4. Clear all descriptions\n";
                cout << " 5. Reorder descriptions (Swap)\n";
                cout << " 0. Return\n";

                int opt;
                cout << "Choose: ";
                while (true)
                {
                    cin >> opt;
                    if (!cin.fail()) break;
                    cin.clear();
                    cin.ignore(1000 , '\n');
                    cout << "Invalid input. Please try again.\n";
                }
                cin.ignore();

                if (opt == 0) break;

                // Add description
                if (opt == 1) {
                    string nd;
                    cout << "Enter new description: ";
                    getline(cin, nd);
                    int di = descriptions[itemNum - 1].size();
                    descriptions[itemNum - 1].resize(di + 1);
                    descriptions[itemNum - 1][di] = nd;

                    // Give XP for adding a description
                    addXP(1, gamificationEnabled, playerXP, playerLevel);
                }

                // Edit description
                else if (opt == 2) {
                    if (descriptions[itemNum - 1].size() == 0) {
                        cout << "No descriptions to edit.\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }

                    int dn;
                    cout << "Enter description number to edit: ";
                    while (true)
                    {
                        cin >> dn;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        cout << "Invalid input. Please try again.\n";
                    }
                    cin.ignore();

                    if (dn < 1 || dn > (int)descriptions[itemNum - 1].size()) {
                        cout << "Invalid description number.\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }

                    string updated;
                    cout << "New text: ";
                    getline(cin, updated);
                    descriptions[itemNum - 1][dn - 1] = updated;
                }

                // Delete description
                else if (opt == 3) {
                    if (descriptions[itemNum - 1].size() == 0) {
                        cout << "No descriptions to delete.\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }

                    int dn;
                    cout << "Enter description number to delete: ";
                    while (true)
                    {
                        cin >> dn;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        cout << "Invalid input. Please try again.\n";
                    }
                    cin.ignore();

                    if (dn < 1 || dn > (int)descriptions[itemNum - 1].size()) {
                        cout << "Invalid description number.\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }

                    descriptions[itemNum - 1].erase(descriptions[itemNum - 1].begin() + (dn - 1));
                }

                // Clear all descriptions
                else if (opt == 4) {
                    descriptions[itemNum - 1].clear();
                }

                // Swap descriptions
                else if (opt == 5) {
                    if (descriptions[itemNum - 1].size() < 2) {
                        cout << "Not enough descriptions to reorder.\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }

                    int a, b;
                    cout << "Enter first description number: ";
                    while (true)
                    {
                        cin >> a;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        cout << "Invalid input. Please try again.\n";
                    }
                    cin.ignore();

                    cout << "Enter second description number: ";
                    while (true)
                    {
                        cin >> b;
                        if (!cin.fail()) break;
                        cin.clear();
                        cin.ignore(1000 , '\n');
                        cout << "Invalid input. Please try again.\n";
                    }
                    cin.ignore();

                    if (a < 1 || a > (int)descriptions[itemNum - 1].size() ||
                        b < 1 || b > (int)descriptions[itemNum - 1].size()) {
                        cout << "Invalid description numbers.\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        continue;
                    }

                    string temp = descriptions[itemNum - 1][a - 1];
                    descriptions[itemNum - 1][a - 1] = descriptions[itemNum - 1][b - 1];
                    descriptions[itemNum - 1][b - 1] = temp;
                }

                cout << "Action completed. Press Enter...";
                cin.get();
            }
        }

        // Exit editList()
        else if (editChoice == 9) {
            break;
        }

        // Invalid option
        else {
            cout << "\nInvalid option.\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

    } // end while
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
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear
) {

    // If no lists exist, there's nothing to delete
    if (name_of_list.size() == 0) {
        cout << "\nNo lists to delete.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n===== DELETE A LIST =====\n";

    // -------------------------------
    // DISPLAY ALL LISTS
    // -------------------------------
    for (int i = 0; i < (int)name_of_list.size(); i++) {
        cout << i + 1 << ". " << name_of_list[i] << endl;
    }

    cout << "\n0. Cancel / Return to Main Menu\n";

    // -------------------------------
    // USER SELECTS LIST TO DELETE
    // -------------------------------
    int choice;
    cout << "\nSelect list to delete: ";
    while (true)
    {
        cin >> choice;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(1000 , '\n');
        cout << "Invalid input. Please try again.\n";
    }
    cin.ignore();

    // User cancels deletion
    if (choice == 0) {
        cout << "Returning to main menu...\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // Validate chosen list index
    if (choice < 1 || choice > (int)name_of_list.size()) {
        cout << "Invalid choice.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int index = choice - 1;

    // -------------------------------
    // DELETION CONFIRMATION
    // -------------------------------
    char confirm;
    cout << "Are you sure you want to delete \""
         << name_of_list[index] << "\"? (y/n): ";
    cin >> confirm;

    // If user cancels, stop deletion
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion cancelled.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // ----------------------------------------------------
    // MANUAL REBUILD OF LIST ARRAYS (NO push_back allowed)
    // We create new vectors and copy only the items we keep.
    // ----------------------------------------------------
    vector<string> newNames;
    vector<vector<string>> newLists;
    vector<vector<vector<string>>> newDescriptions;

    // NEW: metadata copies
    vector<string> newCategories;
    vector<string> newDeadlines;
    vector<string> newPriorities;
    vector<vector<int>> newListmonth;
    vector<vector<int>> newListdate;
    vector<vector<int>> newListyear;

   for (int i = 0; i < (int)name_of_list.size(); i++) {
        if (i != index) {
            int ni = newNames.size();
            newNames.resize(ni + 1);
            newNames[ni] = name_of_list[i];

            int li = newLists.size();
            newLists.resize(li + 1);
            newLists[li] = list_of_lists[i];

            int datei = newListdate.size();
            newListdate.resize(datei + 1);
            newListdate[datei] = listdate[i];

            int monthi = newListmonth.size();
            newListmonth.resize(monthi + 1);
            newListmonth[monthi] = listmonth[i];

            int yeari = newListyear.size();
            newListyear.resize(yeari + 1);
            newListyear[yeari] = listyear[i];

            int di = newDescriptions.size();
            newDescriptions.resize(di + 1);
            if (i < (int)list_of_descriptions.size())
                newDescriptions[di] = list_of_descriptions[i];
            else
                newDescriptions[di] = vector<vector<string>>();

            // NEW: copy metadata if present, else empty string
            int mi = newCategories.size();
            newCategories.resize(mi + 1);
            newDeadlines.resize(mi + 1);
            newPriorities.resize(mi + 1);

            newCategories[mi] = (i < (int)list_categories.size()) ? list_categories[i] : "";
            newDeadlines[mi]  = (i < (int)list_deadlines.size()) ? list_deadlines[i] : "";
            newPriorities[mi] = (i < (int)list_priorities.size()) ? list_priorities[i] : "";
        }
    }

    // -------------------------------
    // REPLACE OLD STORAGE WITH NEW
    // -------------------------------
    name_of_list = newNames;
    list_of_lists = newLists;
    list_of_descriptions = newDescriptions;
    
    listdate = newListdate;
    listmonth = newListmonth;
    listyear = newListyear;
        // NEW: replace metadata
    list_categories = newCategories;
    list_deadlines  = newDeadlines;
    list_priorities = newPriorities;

    cout << "\nList deleted successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void updatedate(int &cmonth, int &cdate, int &cyear
) {
    int tempmonth, tempdate, tempyear;
    cout << "\n=====================================\n";
    cout << "               EDIT DATE             \n";
    cout << "=====================================\n";
    cout << "Enter month number: ";
    do
    {
        while (true)
        {
            cin >> tempmonth;
            if (!cin.fail()) break;
            
            cin.clear();
            cin.ignore(1000 , '\n');
            if (tempmonth < 1 || tempmonth > 12)
            {
            cout << "Try again\n";
            }
        }
        
        
        
    } while (tempmonth < 1 || tempmonth > 12);
    cout << "Enter year number: ";
    do
    {   while (true)
        {
            cin >> tempyear;
            if (!cin.fail()) break;
            
            cin.clear();
            cin.ignore(1000 , '\n');
            if (tempyear < 2000 || tempyear > 2100)
            {
                cout << "Try again\n";
            }
        }
    
        
    } while (tempyear < 2000 || tempyear > 2100);
    cout << "Enter date number: ";
    switch (tempmonth)
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
            cin >> tempdate;
            if (!cin.fail()) break;
            
            cin.clear();
            cin.ignore(1000 , '\n');
            if (tempdate < 1 || tempdate > 31)
            {
                cout << "Try again\n";
            }
        }
    } while (tempdate < 1 || tempdate > 31);
        break;
    
    case 4:
    case 6:
    case 9:
    case 11:
   do
    {
        while (true)
        {
            cin >> tempdate;
            if (!cin.fail()) break;
            
            cin.clear();
            cin.ignore(1000 , '\n');
            if (tempdate < 1 || tempdate > 30)
            {
                cout << "Try again\n";
            }
        }
        
    } while (tempdate < 1 || tempdate > 30);    
        break;

    case 2:
    if (((tempyear%4 == 0 && tempyear%100 != 0) || (tempyear%400 == 0)))
    {
        do
        {
            while (true)
            {
                cin >> tempdate;
                if (!cin.fail()) break;
                
                cin.clear();
                cin.ignore(1000 , '\n');
                if (tempdate < 1 || tempdate > 29)
                {
                    cout << "Try again\n";
                }
            }
            
        } while (tempdate < 1 || tempdate > 29); 
    }
    else
    {
        do
        {
            while (true)
            {
                cin >> tempdate;
                if (!cin.fail()) break;
                
                cin.clear();
                cin.ignore(1000 , '\n');
                if (tempdate < 1 || tempdate > 28)
                {
                    cout << "Try again\n";
                }
            }
        
        } while (tempdate < 1 || tempdate > 28);
    }
        break;
    }
    cmonth = tempmonth;
    cdate = tempdate;
    cyear = tempyear;
    return;
}



int main() {


    // -------------------------------
    // Declare storage vectors for lists
    // -------------------------------
    vector<string> name_of_list;
    vector<vector<string>> list_of_lists;
    vector<vector<vector<string>>> list_of_descriptions;
    int cmonth = 0, cdate = 0, cyear = 0;
    vector<int> monthcreated;
    vector<int> datecreated;
    vector<int> yearcreated;
    vector<vector<int>> listmonth;
    vector<vector<int>> listdate;
    vector<vector<int>> listyear;

    vector<string> list_categories;
    vector<string> list_deadlines;
    vector<string> list_priorities;

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

        cout << "                                                                  ████████╗ █████╗ ██╗     ██╗  ██╗   ██╗     ██╗          ██╗                        \n";             
        cout << "                                                                  ╚══██╔══╝██╔══██╗██║     ██║  ╚██╗ ██╔╝     ██║          ██║                        \n";     
        cout << "                                                                     ██║   ███████║██║     ██║   ╚████╔╝  ██████████╗  ██████████╗                    \n";                       
        cout << "                                                                     ██║   ██╔══██║██║     ██║    ╚██╔╝   ╚═══██╔═══╝  ╚═══██╔═══╝                    \n";                      
        cout << "                                                                     ██║   ██║  ██║███████╗███████╗██║        ██║          ██║                        \n";     
        cout << "                                                                     ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝        ╚═╝          ╚═╝                        \n\n";
                                                                
        cout << "                                                   ██╗     ██╗███████╗████████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗   \n";
        cout << "                                                   ██║     ██║██╔════╝╚══██╔══╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗  \n";
        cout << "                                                   ██║     ██║███████╗   ██║       ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝  \n";
        cout << "                                                   ██║     ██║╚════██║   ██║       ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗  \n";
        cout << "                                                   ███████╗██║███████║   ██║       ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║  \n";
        cout << "                                                   ╚══════╝╚═╝╚══════╝   ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝  \n\n";

        cout << "                                                   ╻ ╻╻ ╻┏━╸┏━┓┏━╸   ╺┳╸┏━┓┏━┓╻┏ ┏━┓   ┏┓ ┏━╸┏━╸┏━┓┏┳┓┏━╸   ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏┓╻╺┳╸┏━┓     \n";
        cout << "                                                   ┃╻┃┣━┫┣╸ ┣┳┛┣╸     ┃ ┣━┫┗━┓┣┻┓┗━┓   ┣┻┓┣╸ ┃  ┃ ┃┃┃┃┣╸    ┣━┫┃  ┣━┫┃┣╸ ┃┏┛┣╸ ┃┃┃┣╸ ┃┗┫ ┃ ┗━┓     \n";
        cout << "                                                   ┗┻┛╹ ╹┗━╸╹┗╸┗━╸    ╹ ╹ ╹┗━┛╹ ╹┗━┛   ┗━┛┗━╸┗━╸┗━┛╹ ╹┗━╸   ╹ ╹┗━╸╹ ╹╹┗━╸┗┛ ┗━╸╹ ╹┗━╸╹ ╹ ╹ ┗━┛╹    \n\n";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        cout << "                                                    ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";

        cout << "                                                                                      𝐀𝐫𝐢𝐬𝐭𝐨𝐤𝐢, 𝐒𝐞𝐠𝐨𝐜𝐢𝐨, 𝐎𝐜𝐜𝐞ñ𝐚 | 𝐁𝐒𝐂𝐒 1-𝐀                                 \n\n" ; 

        cout << "                                                                       ╔════════════════════════════════════════════════════╗  \n";    
        cout << "                                                                       ║╻╻┏━┓┏━┓┏━╸┏━┓┏━┓   ┏━┓   ╺┳╸┏━┓   ┏━╸┏┓╻╺┳╸┏━╸┏━┓╻╻║  \n";
        cout << "                                                                       ║  ┣━┛┣┳┛┣╸ ┗━┓┗━┓   ┃┃┃    ┃ ┃ ┃   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛  ║  \n";
        cout << "                                                                       ║  ╹  ╹┗╸┗━╸┗━┛┗━┛   ┗━┛    ╹ ┗━┛   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸  ║  \n";
        cout << "                                                                       ╚════════════════════════════════════════════════════╝  \n";

        while (true)
        {
            cin >> Menu;
            if (Menu != 0)
            {
                cout << "Invalid input. Please try again.\n";
                continue;
            }
            
            if (!cin.fail()) break;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Invalid input. Please try again.\n";
        }
        
        
        if(Menu == 0){
            started = true;
             system("cls");
        } 

    while (started) {

        system("cls");
       
        cout << "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n";
        cout << "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n";
        cout << "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n";
        cout << "                                                               ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  \n";
        cout << "                                                               ████╗ ████║██╔══██╗██║████╗  ██║    ████╗ ████║██╔════╝████╗  ██║██║   ██║  \n";
        cout << "                                                               ██╔████╔██║███████║██║██╔██╗ ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  \n";
        cout << "                                                               ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  \n";
        cout << "                                                               ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  \n";
        cout << "                                                               ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   \n";
        cout << "                                                              ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";


                                                                          
        // Display player level & XP in main menu header
        // Show gamification header only when enabled
        if (gamificationEnabled) {
            cout << " Player Level : " << playerLevel
                << "    Player XP : " << playerXP << "\n";
            cout << " XP Progress   : " << getXPBar(playerXP)
                << " " << (playerXP % 100) << "%\n";
            cout << "-------------------------------------\n";
        }

        cout << "                                                             Current date: " << cmonth << '/' << cdate << '/' << cyear;
        cout << "\n";

        cout << "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n";
        cout << "       ║╺┓     ┏━╸┏━┓┏━╸┏━┓╺┳╸┏━╸   ┏━┓   ┏┓╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸║      ║╻ ╻    ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸   ┏━┓   ╻  ╻┏━┓╺┳╸            ║      ║┏━┓    ╻ ╻┏━┓┏━┓┏━┓╺┳╸┏━╸   ┏━┓┏━┓╺┳╸┏━╸                ║\n";
        cout << "       ║ ┃     ┃  ┣┳┛┣╸ ┣━┫ ┃ ┣╸    ┣━┫   ┃┗┫┣╸ ┃╻┃   ┃  ┃┗━┓ ┃ ║      ║┗━┫     ┃┃┣╸ ┃  ┣╸  ┃ ┣╸    ┣━┫   ┃  ┃┗━┓ ┃             ║      ║  ┃    ┃ ┃┣━┛┃ ┃┣━┫ ┃ ┣╸    ┃ ┃┣━┫ ┃ ┣╸                 ║\n";
        cout << "       ║╺┻╸╹   ┗━╸╹┗╸┗━╸╹ ╹ ╹ ┗━╸   ╹ ╹   ╹ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹ ║      ║  ╹╹   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸   ╹ ╹   ┗━╸╹┗━┛ ╹             ║      ║  ╹╹   ┗━┛╹  ┗━┛╹ ╹ ╹ ┗━╸   ┗━┛╹ ╹ ╹ ┗━╸                ║\n";
        cout << "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n";

        cout << "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n";
        cout << "       ║┏━┓    ╻ ╻╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                          ║      ║┏━╸    ┏━┓┏━╸╺┳╸╻ ╻┏━┓┏┓╻    ╻   ┏━╸╻ ╻╻╺┳╸             ║      ║┏━┓    ╺┳╸┏━┓┏━╸┏━╸╻  ┏━╸   ┏━╸┏━┓┏┳┓┏━╸                ║\n";
        cout << "       ║┏━┛    ┃┏┛┃┣╸ ┃╻┃   ┃  ┃┗━┓ ┃                           ║      ║┗━┓    ┣┳┛┣╸  ┃ ┃ ┃┣┳┛┃┗┫   ┏┛   ┣╸ ┏╋┛┃ ┃              ║      ║┣━┫     ┃ ┃ ┃┃╺┓┃╺┓┃  ┣╸    ┃╺┓┣━┫┃┃┃┣╸                 ║\n";
        cout << "       ║┗━╸╹   ┗┛ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹                           ║      ║┗━┛╹   ╹┗╸┗━╸ ╹ ┗━┛╹┗╸╹ ╹   ╹    ┗━╸╹ ╹╹ ╹              ║      ║┗━┛╹    ╹ ┗━┛┗━┛┗━┛┗━╸┗━╸   ┗━┛╹ ╹╹╹╹┗━╸                ║\n";
        cout << "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n";                                

        cout << "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n";                          
        cout << "       ║┏━┓    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╻  ╻┏━┓╺┳╸                  ║      ║┏━┓    ┏━┓┏━╸┏━┓┏━┓┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                  ║      ║┏━┓    ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏━┓╺┳╸┏━╸               ║\n";
        cout << "       ║╺━┫    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸    ┃  ┃┗━┓ ┃                   ║      ║┣━┓    ┗━┓┣╸ ┣━┫┣┳┛┃  ┣━┫   ┃  ┃┗━┓ ┃                   ║      ║┗━┫    ┣━┫┃  ┣━┫┃┣╸ ┃ ┃┣╸ ┃┃┃┣╸ ┃ ┃ ┃ ┗━┓               ║\n";
        cout << "       ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ┗━╸╹┗━┛ ╹                   ║      ║┗━┛╹   ┗━┛┗━╸╹ ╹╹┗╸┗━╸╹ ╹   ┗━╸╹┗━┛ ╹                   ║      ║╺━┛╹   ╹ ╹┗━╸╹ ╹╹┗━╸┗━┛┗━╸╹╹╹┗━╸╹ ╹ ╹ ╺━┛               ║ \n";      
        cout << "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n";


        cout << "                                                                          ________________  ________________  ________________      \n";
        cout << "                                                                         |________________||________________||________________|     \n\n";                                                                                                                                     
        cout << "                                                                            ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ┏━╸╻ ╻┏━┓╻┏━╸┏━╸         \n";
        cout << "                                                                            ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┣━┫┃ ┃┃┃  ┣╸ ╹        \n";
        cout << "                                                                            ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹ ╹┗━┛╹┗━╸┗━╸╹        \n";
        cout << "                                                                                                ╔════╗                              \n";
        cout << "                                                                                               ╔║    ║╗                             \n";
        cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
        
        cout << "\033[2A"; // move UP 2 lines
        cout << "\033[98C"; // move RIGHT 17 columns (adjust until perfect)
        while (true)
        {
                cin >> choice;
                if (!cin.fail()) break;
                
                cin.clear();
                cin.ignore(1000 , '\n');
                if (choice < 1 || choice > 9) {

            system("cls");
        
            cout << "                                                                       ╺┳╸┏━┓╻  ╻  ╻ ╻ ╻  ╻    ╻  ╻┏━┓╺┳╸   ┏┳┓┏━┓┏┓╻┏━┓┏━╸┏━╸┏━┓    \n";
            cout << "                                                                        ┃ ┣━┫┃  ┃  ┗┳┛╺╋╸╺╋╸   ┃  ┃┗━┓ ┃    ┃┃┃┣━┫┃┗┫┣━┫┃╺┓┣╸ ┣┳┛    \n";
            cout << "                                                                        ╹ ╹ ╹┗━╸┗━╸ ╹  ╹  ╹    ┗━╸╹┗━┛ ╹    ╹ ╹╹ ╹╹ ╹╹ ╹┗━┛┗━╸╹┗╸    \n";
            cout << "                                                               ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  \n";
            cout << "                                                               ████╗ ████║██╔══██╗██║████╗  ██║    ████╗ ████║██╔════╝████╗  ██║██║   ██║  \n";
            cout << "                                                               ██╔████╔██║███████║██║██╔██╗ ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  \n";
            cout << "                                                               ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  \n";
            cout << "                                                               ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  \n";
            cout << "                                                               ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   \n";
            cout << "                                                              ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";


                                                                            
            // Display player level & XP in main menu header
            // Show gamification header only when enabled
            if (gamificationEnabled) {
                cout << " Player Level : " << playerLevel
                    << "    Player XP : " << playerXP << "\n";
                cout << " XP Progress   : " << getXPBar(playerXP)
                    << " " << (playerXP % 100) << "%\n";
                cout << "-------------------------------------\n";
            }

            cout << "                                                             Current date: " << cmonth << '/' << cdate << '/' << cyear;
            cout << "\n";

            cout << "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n";
            cout << "       ║╺┓     ┏━╸┏━┓┏━╸┏━┓╺┳╸┏━╸   ┏━┓   ┏┓╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸║      ║╻ ╻    ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸   ┏━┓   ╻  ╻┏━┓╺┳╸            ║      ║┏━┓    ╻ ╻┏━┓┏━┓┏━┓╺┳╸┏━╸   ┏━┓┏━┓╺┳╸┏━╸                ║\n";
            cout << "       ║ ┃     ┃  ┣┳┛┣╸ ┣━┫ ┃ ┣╸    ┣━┫   ┃┗┫┣╸ ┃╻┃   ┃  ┃┗━┓ ┃ ║      ║┗━┫     ┃┃┣╸ ┃  ┣╸  ┃ ┣╸    ┣━┫   ┃  ┃┗━┓ ┃             ║      ║  ┃    ┃ ┃┣━┛┃ ┃┣━┫ ┃ ┣╸    ┃ ┃┣━┫ ┃ ┣╸                 ║\n";
            cout << "       ║╺┻╸╹   ┗━╸╹┗╸┗━╸╹ ╹ ╹ ┗━╸   ╹ ╹   ╹ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹ ║      ║  ╹╹   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸   ╹ ╹   ┗━╸╹┗━┛ ╹             ║      ║  ╹╹   ┗━┛╹  ┗━┛╹ ╹ ╹ ┗━╸   ┗━┛╹ ╹ ╹ ┗━╸                ║\n";
            cout << "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n";

            cout << "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n";
            cout << "       ║┏━┓    ╻ ╻╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                          ║      ║┏━╸    ┏━┓┏━╸╺┳╸╻ ╻┏━┓┏┓╻    ╻   ┏━╸╻ ╻╻╺┳╸             ║      ║┏━┓    ╺┳╸┏━┓┏━╸┏━╸╻  ┏━╸   ┏━╸┏━┓┏┳┓┏━╸                ║\n";
            cout << "       ║┏━┛    ┃┏┛┃┣╸ ┃╻┃   ┃  ┃┗━┓ ┃                           ║      ║┗━┓    ┣┳┛┣╸  ┃ ┃ ┃┣┳┛┃┗┫   ┏┛   ┣╸ ┏╋┛┃ ┃              ║      ║┣━┫     ┃ ┃ ┃┃╺┓┃╺┓┃  ┣╸    ┃╺┓┣━┫┃┃┃┣╸                 ║\n";
            cout << "       ║┗━╸╹   ┗┛ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹                           ║      ║┗━┛╹   ╹┗╸┗━╸ ╹ ┗━┛╹┗╸╹ ╹   ╹    ┗━╸╹ ╹╹ ╹              ║      ║┗━┛╹    ╹ ┗━┛┗━┛┗━┛┗━╸┗━╸   ┗━┛╹ ╹╹╹╹┗━╸                ║\n";
            cout << "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n";                                

            cout << "       ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗      ╔════════════════════════════════════════════════════════╗\n";                          
            cout << "       ║┏━┓    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╻  ╻┏━┓╺┳╸                  ║      ║┏━┓    ┏━┓┏━╸┏━┓┏━┓┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                  ║      ║┏━┓    ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏━┓╺┳╸┏━╸               ║\n";
            cout << "       ║╺━┫    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸    ┃  ┃┗━┓ ┃                   ║      ║┣━┓    ┗━┓┣╸ ┣━┫┣┳┛┃  ┣━┫   ┃  ┃┗━┓ ┃                   ║      ║┗━┫    ┣━┫┃  ┣━┫┃┣╸ ┃ ┃┣╸ ┃┃┃┣╸ ┃ ┃ ┃ ┗━┓               ║\n";
            cout << "       ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ┗━╸╹┗━┛ ╹                   ║      ║┗━┛╹   ┗━┛┗━╸╹ ╹╹┗╸┗━╸╹ ╹   ┗━╸╹┗━┛ ╹                   ║      ║╺━┛╹   ╹ ╹┗━╸╹ ╹╹┗━╸┗━┛┗━╸╹╹╹┗━╸╹ ╹ ╹ ╺━┛               ║ \n";      
            cout << "       ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝      ╚════════════════════════════════════════════════════════╝\n\n";


            cout << "                                                                          ________________  ________________  ________________      \n";
            cout << "                                                                         |________________||________________||________________|     \n\n";                                                                                                                                     
            cout << "                                                                            ┏━╸┏┓╻╺┳╸┏━╸┏━┓   ╻ ╻┏━┓╻ ╻┏━┓   ┏━╸╻ ╻┏━┓╻┏━╸┏━╸         \n";
            cout << "                                                                            ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛   ┗┳┛┃ ┃┃ ┃┣┳┛   ┃  ┣━┫┃ ┃┃┃  ┣╸ ╹        \n";
            cout << "                                                                            ┗━╸╹ ╹ ╹ ┗━╸╹┗╸    ╹ ┗━┛┗━┛╹┗╸   ┗━╸╹ ╹┗━┛╹┗━╸┗━╸╹        \n";
            cout << "                                                                                                ╔════╗                              \n";
            cout << "                                                                                               ╔║    ║╗                             \n";
            cout << "                                                                                          ═════╝╚════╝╚═════                        \n" ; 
            

            cout << "\033[0B"; // move UP 2 lines
            cout << "\033[80C"; // move RIGHT 17 columns (adjust until perfect)
                    cout << "\033[1;37;41m  ⚠️ INVALID INPUT. PLEASE TRY AGAIN. ⚠️  \033[0m\n";
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
                gamificationEnabled,
                playerXP,
                playerLevel,
                listmonth,
                listdate,
                listyear,
                monthcreated,
                datecreated,
                yearcreated,
                cmonth, cdate, cyear
                );
                // Check achievements after creating a list
                checkAchievements(name_of_list, list_of_lists, list_of_descriptions,
                                  achNames, achBadges, achUnlocked, achXP,
                                  gamificationEnabled, playerXP, playerLevel,
                                  streakCount, lastActiveDay, cmonth, cdate, cyear);
                break;

            case 2:
                viewLists(name_of_list, list_of_lists, list_of_descriptions, gamificationEnabled, playerXP, playerLevel, listmonth, listdate, listyear,datecreated, monthcreated, yearcreated, list_deadlines, cdate, cmonth, cyear);
                break;

            case 3:
                editList(name_of_list, list_of_lists, list_of_descriptions, gamificationEnabled, playerXP, playerLevel, listmonth, listdate, listyear);
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
                gamificationEnabled,
                playerXP,
                playerLevel,
                listmonth, listdate, listyear
                );
                // Re-check achievements after deletion
                checkAchievements(name_of_list, list_of_lists, list_of_descriptions,
                                  achNames, achBadges, achUnlocked, achXP,
                                  gamificationEnabled, playerXP, playerLevel,
                                  streakCount, lastActiveDay, cmonth, cdate, cyear);
                break;

            case 5:
                cout << "\nExiting program...\n";
                return 0;

            case 6:
                  searchOrSortLists(
            name_of_list,
            list_categories,
            list_deadlines,
            list_priorities
                );
                break;
            case 7:
             updatedate(cmonth, cdate, cyear);
             break;
            case 8:
                gamificationEnabled = !gamificationEnabled;
                cout << "\nGamification is now " << (gamificationEnabled ? "ENABLED" : "DISABLED") << ".\n";
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 9:
                // Show Achievements & Badges
                system("cls");
                cout << "\n=====================================\n";
                cout << "         ACHIEVEMENTS & BADGES       \n";
                cout << "=====================================\n\n";
                for (int i = 0; i < (int)achNames.size(); i++) {
                    cout << " " << i + 1 << ". " << achBadges[i] << " " << achNames[i];
                    if (achUnlocked[i]) cout << "  (Unlocked)";
                    else cout << "  (Locked)";
                    cout << "   +" << achXP[i] << " XP\n";
                }
                cout << "\n-------------------------------------\n";
                if (gamificationEnabled) {
                    cout << "Player Level : " << playerLevel << "    Player XP : " << playerXP << "\n";
                    cout << "Streak Days  : " << streakCount << "\n";
                    cout << "XP Progress   : " << getXPBar(playerXP) << " " << (playerXP % 100) << "%\n";
                }
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
        }
    }

    return 0;
}
