#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;


// Forward declaration for viewLists so it's visible at call sites in main
void viewLists(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string> > >& list_of_descriptions,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear
);


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



// Function to create a new list
void createNewList(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string> > >& list_of_descriptions,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear
) {
    system("cls");

    // ===================================================
    // VARIABLE DECLARATIONS (ALL MOVED TO TOP)
    // ===================================================

    string title;                        // The title/name of the new list
    string item;                         // Stores each item typed by the user
    string descLine;                     // Stores each description line entered
    int month, date, year;  
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

    cout << "==============================\n";
    cout << "        CREATE NEW LIST       \n";
    cout << "==============================\n\n";

    cin.ignore();
    cout << "Enter list title: ";
    getline(cin, title);

    // ===================================================
    // ITEM Category
    // ===================================================

    system("cls");

    cout << "Choose a category for this item: \n";

    cout << "1. Work \n";
    cout << "2. School \n";
    cout << "3. Personal \n";
    cout << "4. Errands \n";
    cout << "5. Finance \n";
    cout << "6. Health \n";
    cout << "7. Appointment \n";
    cout << "8. Shopping \n";
    cout << "9. Others \n";
    cout << "10. None \n";

    cin >> categoryInput;

    while(categoryInput < 1 || categoryInput >10){
        cout << "Invalid Choice! Please enter a number from 1 to 10";
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
    cout << "Add Deadline?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";

    cin >> deadlineStatus;

    while(deadlineStatus < 1 || deadlineStatus > 2){
        cout << "Invalid Response! Try Again";
        cin >> deadlineStatus;
    }

    if(deadlineStatus == 1){
        system("cls");
        cin.ignore();

        cout << "Choose Deadline\n";
        cout << "1. Today\n";
        cout << "2. Tommorow\n";
        cout << "3. This Week\n";
        cout << "4. Next Week\n";
        cout << "5. Next Month\n";

        cin >> deadlineChoice;

        while(deadlineChoice < 1 || deadlineChoice > 5){
            cout << "Invalid Response! Try Again";
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

            case 5: deadline = "Next Month";
                break;
        }

        cin.ignore();
        system("cls");
        cout << "Choose Deadline Priority \n";

        cout << "1. Critical\n";
        cout << "2. High\n";
        cout << "3. Medium\n";
        cout << "4. Low\n";
        cout << "5. None\n";

        cin >> deadlinePrioChoice;

        while(deadlinePrioChoice < 1 || deadlinePrioChoice > 5){
            cout << "Invalid Response! Please Try Again.\n";
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
    system("cls");
    cout << "\n----------------------------------------\n";
    cout << " ADD TARGET DATE FOR THIS ITEM\n";
    cout << "----------------------------------------\n";
    cout << " Enter Month: ";
    do
    {
    cin >> month;
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
        cin >> year;
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
            cin >> date;
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
            cin >> date;
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
                cin >> date;
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
                cin >> date;
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
    cout << "\nItem + descriptions saved!\n\n";
    cin.ignore();
    // ===================================================
    // ITEM NOTES
    // ===================================================

    system("cls");
    cout << "Add Notes?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";

    cin >> noteChoice;

    while(noteChoice < 1 || noteChoice > 2){
        cout << "Invalid Response! Please try again.\n";
        cin >> noteChoice;
    }

    if(noteChoice == 1){
        cout << "Enter Note\n";
        cin.ignore();
        getline(cin, notes); 
    }

    // ===================================================
    // ITEM SUMMARY
    // ===================================================

 while (true) {
    system("cls");
    cout << "\nYou are about to create this list\n\n";
    cout << "[1] Name: " << title << endl;
    cout << "[2] Category: " << category << endl;
    cout << "[3] Deadline: " << deadline << endl;
    cout << "[4] Priority: " << deadlinePriority << endl;
    cout << "[5] Notes: " << notes << endl << endl;

    cout << "[1-5] Edit a field" << endl;
    cout << "[6] Confirm and Create" << endl;
    cout << "[7] Cancel" << endl;
    cout << "Choice: ";
    
    cin >> confirmationValue;

    // Make sure leftover newline won't affect getline()
    cin.ignore();

    if (confirmationValue == 6) break;  // Continue to items
    if (confirmationValue == 7){
        cout << "\nList creation cancelled.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    } 
    switch (confirmationValue) {

        case 1: {
            cout << "\nEnter new title: ";
            getline(cin, title);
            break;
        }

        case 2: {
            cout << "\nChoose a new category:\n";
            cout << "1. Work  \n2. School  \n3. Personal  \n4. Errands\n";
            cout << "\n5. Finance  \n6. Health  \n7. Appointment\n";
            cout << "8. Shopping  \n9. Others  \n10. None\n";
            int cat;
            cin >> cat;
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
            cout << "\nChoose Deadline:\n";
            cout << "1. Today\n2. Tomorrow\n3. This Week\n4. Next Week\n5. Next Month\n";
            int d;
            cin >> d;
            cin.ignore();

            const string deadlines[] = {
                "Today","Tomorrow","This Week",
                "Next Week","Next Month"
            };
            if (d >= 1 && d <= 5) deadline = deadlines[d - 1];
            break;
        }

        case 4: {
            cout << "\nChoose Priority:\n";
            cout << "1. Critical  2. High  3. Medium  4. Low  5. None\n";
            int p;
            cin >> p;
            cin.ignore();

            const string prios[] = {
                "Critical","High","Medium","Low","None"
            };
            if (p >= 1 && p <= 5) deadlinePriority = prios[p - 1];
            break;
        }

        case 5: {
            cout << "\nEnter new Notes: ";
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
    cout << "\n----------------------------------------\n";
    cout << " START ADDING ITEMS TO YOUR LIST\n";
    cout << "----------------------------------------\n";
    cout << " Type an item and press Enter\n";
    cout << " Type 'done' to finish\n";
    cout << " Type 'cancel' to discard list\n";
    cout << "----------------------------------------\n\n";

    do {
        cout << "Add item: ";
        getline(cin, item);

        // --- User wants to stop adding items ---
        if (item == "done")
            break;

        // --- User cancels entire creation process ---
        if (item == "cancel") {
            cout << "\nList creation cancelled.\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        // Add new item (resize method to avoid push_back)
        index = items.size();
        items.resize(index + 1);
        items[index] = item;

        // Give XP for adding an item
        addXP(5, gamificationEnabled, playerXP, playerLevel);

        // ===================================================
        // ENTER DESCRIPTIONS FOR THIS ITEM
        // ===================================================

        cout << "\n----------------------------------------\n";
        cout << " ADD DESCRIPTIONS FOR THIS ITEM\n";
        cout << "----------------------------------------\n";
        cout << " Type a description and press Enter\n";
        cout << " Type 'done' when finished\n";
        cout << " Type 'none' to skip descriptions\n";
        cout << "----------------------------------------\n";

        tempDescriptions.clear();  // Clear from previous item

        // DESCRIPTION ENTRY LOOP
        while (true) {
            cout << "Description: ";
            getline(cin, descLine);

            if (descLine == "done")   // Finished adding descriptions
                break;

            if (descLine == "none") { // User wants no descriptions
                tempDescriptions.clear();
                break;
            }

            if (descLine == "")       // Skip empty input silently
                continue;

            // Add description using resize
            dindex = tempDescriptions.size();
            tempDescriptions.resize(dindex + 1);
            tempDescriptions[dindex] = descLine;

            // Give XP for adding a description
            addXP(1, gamificationEnabled, playerXP, playerLevel);
        }

        // Save this item’s description list
        dsaveIndex = descriptions.size();
        descriptions.resize(dsaveIndex + 1);
        descriptions[dsaveIndex] = tempDescriptions;

        cout << "\nItem + descriptions saved!\n\n";

    } while (true);

    // ===================================================
    // SAVE FINAL LIST, ITEMS, AND DESCRIPTIONS
    // ===================================================

    int titleIndex = name_of_list.size();
    name_of_list.resize(titleIndex + 1);
    name_of_list[titleIndex] = title;

    int listIndex = list_of_lists.size();
    list_of_lists.resize(listIndex + 1);
    list_of_lists[listIndex] = items;

    list_of_descriptions.resize(listIndex + 1);
    list_of_descriptions[listIndex] = descriptions;

    listmonth.resize(listIndex + 1);
    listmonth[listIndex] = months;

    listyear.resize(listIndex + 1);
    listyear[listIndex] = years;

    listdate.resize(listIndex + 1);
    listdate[listIndex] = dates;
    // Give XP for creating a new list
    addXP(10, gamificationEnabled, playerXP, playerLevel);

    // ===================================================
    // COMPLETION MESSAGE
    // ===================================================

    cout << "\n========================================\n";
    cout << "       LIST SAVED SUCCESSFULLY!\n";
    cout << "========================================\n";
    cout << "Press Enter to continue...";
    cin.get();
}
}



void viewLists(
    vector<string>& name_of_list,
    vector<vector<string>>& list_of_lists,
    vector<vector<vector<string> > >& list_of_descriptions,
    bool gamificationEnabled,
    int& playerXP,
    int& playerLevel,
    vector<vector<int>>& listmonth,
    vector<vector<int>>& listdate,
    vector<vector<int>>& listyear
) {

    // If no lists exist, show message and exit
    if (name_of_list.size() == 0) {
        cout << "\nNo lists created yet.\n";
        cout << "Press Enter...";
        cin.ignore();
        cin.get();
        return;
    }

    // ================================
    // DISPLAY ALL LIST TITLES
    // ================================
    cout << "\n=====================================\n";
    cout << "               VIEW LISTS            \n";
    cout << "=====================================\n";

    for (int i = 0; i < (int)name_of_list.size(); i++) {
        cout << " " << i + 1 << ". " << name_of_list[i] << "\n";
    }

    cout << "\n S. Search list names\n";
    cout << "-------------------------------------\n";

    // ================================
    // ALLOW USER TO CHOOSE A LIST
    // ================================
    cout << "Select a list number: ";
    string choiceStr;
    cin >> choiceStr;

    // ================================
    // SEARCH MODE (User typed S)
    // ================================
    if (choiceStr == "S" || choiceStr == "s") {
        cin.ignore();
        string key;

        cout << "\n=====================================\n";
        cout << "           SEARCH LIST NAMES         \n";
        cout << "=====================================\n";
        cout << "Enter keyword: ";
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
        cout << "Press Enter...";
        cin.get();
        return;
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
        return;
    }
    cin.ignore();

    // Validate chosen list
    if (choice < 1 || choice > (int)name_of_list.size()) {
        cout << "\nInvalid.\nPress Enter...";
        cin.get();
        return;
    }

    int index = choice - 1; // convert to 0-based index

    // Access selected list's items and descriptions
    vector<string>& items = list_of_lists[index];
    vector<int>& months = listmonth[index];
    vector<int>& dates = listdate[index];
    vector<int>& years = listyear[index];
    // Prevent crash for lists without descriptions
    vector<vector<string>> emptyVecVec;
    vector<vector<string>>& descs =
        (index < (int)list_of_descriptions.size())
        ? list_of_descriptions[index]
        : emptyVecVec;

    // ================================
    // DISPLAY SELECTED LIST CONTENT
    // ================================
    cout << "\n=====================================\n";
    cout << "           " << name_of_list[index] << "\n";
    cout << "=====================================\n";

    if (items.size() == 0) {
        cout << "(No items)\n";
    } else {
        int completedCount = 0;

        // Print each item and its descriptions
        for (int i = 0; i < (int)items.size(); i++) {
            cout << " " << i + 1 << ". " << items[i] << "\n";
            cout << "Target date: " << months[i] << "/" << dates[i] << "/" << years[i] << "\n";
            // Print all descriptions for this item (if any)
            if (i < (int)descs.size()) {
                for (int d = 0; d < (int)descs[i].size(); d++) {
                    cout << "      > " << descs[i][d] << "\n";
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
        cout << "\n--------------- STATISTICS -----------\n";
        cout << " Total Items       : " << items.size() << "\n";
        cout << " Completed Items   : " << completedCount << "\n";
        cout << " Not Done          : " << notDone << "\n";
        cout << fixed << setprecision(2);
        cout << " % Completed       : " << percentDone << "%\n";
        cout << " % Not Completed   : " << percentNot << "%\n";
        cout << "-------------------------------------\n";
    }

    // End screen pause
    cout << "\nPress Enter...";
    cin.get();
}



// -----------------------------
// EDIT LIST
// -----------------------------
void editList(
    vector<string> &name_of_list,
    vector<vector<string>> &list_of_lists,
    vector<vector<vector<string> > > &list_of_descriptions,
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
        cin >> editChoice;
        cin.ignore();

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

            int month, date, year;
            cout << "\nSet target date for this item\n";
            cout << "-------------------------------------\n";
            cout << " Enter Month: ";
            do
            {
            cin >> month;
            if (month < 1 || month > 12)
            {
                cout << "Try again\n";
            }
            } while (month < 1 || month > 12);
            int monthIndex = months.size();
            months.resize(monthIndex + 1);
            months[monthIndex] = month;
            cout << "Enter year number: ";
            do
            {
                cin >> year;
                if (year < 2000 || year > 2100)
                {
                    cout << "Try again\n";
                }
            } while (year < 2000 || year > 2100);
            int yearIndex = years.size();
            years.resize(yearIndex + 1);
            years[yearIndex] = year;
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
                    cin >> date;
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
                    cin >> date;
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
                        cin >> date;
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
                        cin >> date;
                        if (date < 1 || date > 28)
                        {
                            cout << "Try again\n";
                        }
                    } while (date < 1 || date > 28);
                }
                break;
            } // end switch(month)
            int dateIndex = dates.size();
            dates.resize(dateIndex + 1);
            dates[dateIndex] = date;

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
            cin >> itemNum;
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
            cin >> delNum;
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
            cin >> markNum;
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
            cin >> a;
            cout << "Enter second item number: ";
            cin >> b;
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

            // Swap target dates
            int tempMonth = months[a - 1];
            months[a - 1] = months[b - 1];
            months[b - 1] = tempMonth;

            int tempDate = dates[a - 1];
            dates[a - 1] = dates[b - 1];
            dates[b - 1] = tempDate;

            int tempYear = years[a - 1];
            years[a - 1] = years[b - 1];
            years[b - 1] = tempYear;

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
            cin >> itemNum;
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
                cin >> opt;
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
                    cin >> dn;
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
                    cin >> dn;
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
                    cin >> a;
                    cout << "Enter second description number: ";
                    cin >> b;
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
    vector<vector<vector<string> > > &list_of_descriptions,
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
    cin >> choice;

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
    vector<vector<vector<string> > > newDescriptions;
    vector<vector<int>> newListmonth;
    vector<vector<int>> newListdate;
    vector<vector<int>> newListyear;

    for (int i = 0; i < (int)name_of_list.size(); i++) {

        // Skip the list marked for deletion
        if (i != index) {

            // Add list name
            int ni = newNames.size();
            newNames.resize(ni + 1);
            newNames[ni] = name_of_list[i];

            // Add items of this list
            int li = newLists.size();
            newLists.resize(li + 1);
            newLists[li] = list_of_lists[i];

            // Add target dates of this list
            int datei = newListdate.size();
            newListdate.resize(datei + 1);
            newListdate[datei] = listdate[i];

            int monthi = newListmonth.size();
            newListmonth.resize(monthi + 1);
            newListmonth[monthi] = listmonth[i];

            int yeari = newListyear.size();
            newListyear.resize(yeari + 1);
            newListyear[yeari] = listyear[i];

            // Add descriptions (if available)
            int di = newDescriptions.size();
            newDescriptions.resize(di + 1);

            if (i < (int)list_of_descriptions.size())
                newDescriptions[di] = list_of_descriptions[i];
            else
                newDescriptions[di] = vector<vector<string>>(); // create empty if none
        }
    }

    // -------------------------------
    // REPLACE OLD STORAGE WITH NEW
    // -------------------------------
    name_of_list = newNames;
    list_of_lists = newLists;
    listdate = newListdate;
    listmonth = newListmonth;
    listyear = newListyear;
    list_of_descriptions = newDescriptions;

    cout << "\nList deleted successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int updatedate(int cmonth, int cdate, int cyear
) {
    cout << "\n=====================================\n";
    cout << "               EDIT DATE             \n";
    cout << "=====================================\n";
    cout << "Enter month number: ";
    do
    {
        cin >> cmonth;
        if (cmonth < 1 || cmonth > 12)
        {
            cout << "Try again\n";
        }
        
    } while (cmonth < 1 || cmonth > 12);
    cout << "Enter year number: ";
    do
    {
        cin >> cyear;
        if (cyear < 2000 || cyear > 2100)
        {
            cout << "Try again\n";
        }
    } while (cyear < 2000 || cyear > 2100);
    cout << "Enter date number: ";
    switch (cmonth)
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
        cin >> cdate;
        if (cdate < 1 || cdate > 31)
        {
            cout << "Try again\n";
        }
        
    } while (cdate < 1 || cdate > 31);
        break;
    
    case 4:
    case 6:
    case 9:
    case 11:
   do
    {
        cin >> cdate;
        if (cdate < 1 || cdate > 30)
        {
            cout << "Try again\n";
        }
        
    } while (cdate < 1 || cdate > 30);    
        break;

    case 2:
    if (((cyear%4 == 0 && cyear%100 != 0) || (cyear%400 == 0)))
    {
        do
        {
            cin >> cdate;
            if (cdate < 1 || cdate > 29)
            {
                cout << "Try again\n";
            }
            
        } while (cdate < 1 || cdate > 29); 
    }
    else
    {
        do
        {
            cin >> cdate;
            if (cdate < 1 || cdate > 28)
            {
                cout << "Try again\n";
            }
        
        } while (cdate < 1 || cdate > 28);
    }
        break;
    }
    cout << "Current date: " << cmonth << '/' << cdate << '/' << cyear;
    return cmonth, cdate, cyear;
}



int main() {


    // -------------------------------
    // Declare storage vectors for lists
    // -------------------------------
    vector<string> name_of_list;
    vector<vector<string>> list_of_lists;
    vector<vector<vector<string> > > list_of_descriptions;
    int cmonth = 0, cdate = 0, cyear = 0;
    vector<vector<int>> listmonth;
    vector<vector<int>> listdate;
    vector<vector<int>> listyear;

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

    while (!started) {

        cout << "                                     ████████╗ █████╗ ██╗     ██╗  ██╗   ██╗     ██╗          ██╗                        \n";             
        cout << "                                     ╚══██╔══╝██╔══██╗██║     ██║  ╚██╗ ██╔╝     ██║          ██║                        \n";     
        cout << "                                        ██║   ███████║██║     ██║   ╚████╔╝  ██████████╗  ██████████╗                    \n";                       
        cout << "                                        ██║   ██╔══██║██║     ██║    ╚██╔╝   ╚═══██╔═══╝  ╚═══██╔═══╝                    \n";                      
        cout << "                                        ██║   ██║  ██║███████╗███████╗██║        ██║          ██║                        \n";     
        cout << "                                        ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝        ╚═╝          ╚═╝                        \n\n";
                                                                
        cout << "                       ██╗     ██╗███████╗████████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗   \n";
        cout << "                       ██║     ██║██╔════╝╚══██╔══╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗  \n";
        cout << "                       ██║     ██║███████╗   ██║       ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝  \n";
        cout << "                       ██║     ██║╚════██║   ██║       ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗  \n";
        cout << "                       ███████╗██║███████║   ██║       ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║  \n";
        cout << "                       ╚══════╝╚═╝╚══════╝   ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝  \n\n";

        cout << "                       ╻ ╻╻ ╻┏━╸┏━┓┏━╸   ╺┳╸┏━┓┏━┓╻┏ ┏━┓   ┏┓ ┏━╸┏━╸┏━┓┏┳┓┏━╸   ┏━┓┏━╸╻ ╻╻┏━╸╻ ╻┏━╸┏┳┓┏━╸┏┓╻╺┳╸┏━┓     \n";
        cout << "                       ┃╻┃┣━┫┣╸ ┣┳┛┣╸     ┃ ┣━┫┗━┓┣┻┓┗━┓   ┣┻┓┣╸ ┃  ┃ ┃┃┃┃┣╸    ┣━┫┃  ┣━┫┃┣╸ ┃┏┛┣╸ ┃┃┃┣╸ ┃┗┫ ┃ ┗━┓     \n";
        cout << "                       ┗┻┛╹ ╹┗━╸╹┗╸┗━╸    ╹ ╹ ╹┗━┛╹ ╹┗━┛   ┗━┛┗━╸┗━╸┗━┛╹ ╹┗━╸   ╹ ╹┗━╸╹ ╹╹┗━╸┗┛ ┗━╸╹ ╹┗━╸╹ ╹ ╹ ┗━┛╹    \n\n";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        cout << "                     ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";

        cout << "                                                       𝐀𝐫𝐢𝐬𝐭𝐨𝐤𝐢, 𝐒𝐞𝐠𝐨𝐜𝐢𝐨, 𝐎𝐜𝐜𝐞ñ𝐚 | 𝐁𝐒𝐂𝐒 1-𝐀                                 \n\n\n" ; 

        cout << "                                           ╔════════════════════════════════════════════════════╗  \n";    
        cout << "                                           ║╻╻┏━┓┏━┓┏━╸┏━┓┏━┓   ┏━┓   ╺┳╸┏━┓   ┏━╸┏┓╻╺┳╸┏━╸┏━┓╻╻║  \n";
        cout << "                                           ║  ┣━┛┣┳┛┣╸ ┗━┓┗━┓   ┃┃┃    ┃ ┃ ┃   ┣╸ ┃┗┫ ┃ ┣╸ ┣┳┛  ║  \n";
        cout << "                                           ║  ╹  ╹┗╸┗━╸┗━┛┗━┛   ┗━┛    ╹ ┗━┛   ┗━╸╹ ╹ ╹ ┗━╸╹┗╸  ║  \n";
        cout << "                                           ╚════════════════════════════════════════════════════╝  \n";

        cin >> Menu;

        if(Menu == 0){
            started = true;
             system("cls");
        } 

    }

    while (started) {

        system("cls");

        cout << " ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  \n";
        cout << " ████╗ ████║██╔══██╗██║████╗  ██║    ████╗ ████║██╔════╝████╗  ██║██║   ██║  \n";
        cout << " ██╔████╔██║███████║██║██╔██╗ ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  \n";
        cout << " ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  \n";
        cout << " ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  \n";
        cout << " ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   \n";
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄  \n\n";
                                                                          
        // Display player level & XP in main menu header
        // Show gamification header only when enabled
        if (gamificationEnabled) {
            cout << " Player Level : " << playerLevel
                << "    Player XP : " << playerXP << "\n";
            cout << " XP Progress   : " << getXPBar(playerXP)
                << " " << (playerXP % 100) << "%\n";
            cout << "-------------------------------------\n";
        }



        cout << "Current date: " << cmonth << '/' << cdate << '/' << cyear;
        cout << "\n";

        cout << "       ╔════════════════════════════════════════════════════════╗      \n";
        cout << "       ║╺┓     ┏━╸┏━┓┏━╸┏━┓╺┳╸┏━╸   ┏━┓   ┏┓╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸║      \n";
        cout << "       ║ ┃     ┃  ┣┳┛┣╸ ┣━┫ ┃ ┣╸    ┣━┫   ┃┗┫┣╸ ┃╻┃   ┃  ┃┗━┓ ┃ ║      \n";
        cout << "       ║╺┻╸╹   ┗━╸╹┗╸┗━╸╹ ╹ ╹ ┗━╸   ╹ ╹   ╹ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹ ║      \n";
        cout << "       ╚════════════════════════════════════════════════════════╝      \n\n";

        cout << "       ╔════════════════════════════════════════════════════════╗      \n";
        cout << "       ║┏━┓    ╻ ╻╻┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                          ║      \n";
        cout << "       ║┏━┛    ┃┏┛┃┣╸ ┃╻┃   ┃  ┃┗━┓ ┃                           ║      \n";
        cout << "       ║┗━╸╹   ┗┛ ╹┗━╸┗┻┛   ┗━╸╹┗━┛ ╹                           ║      \n";
        cout << "       ╚════════════════════════════════════════════════════════╝      \n\n";                                

        cout << "       ╔════════════════════════════════════════════════════════╗      \n";                          
        cout << "       ║┏━┓    ╻ ╻┏━┓╺┳┓┏━┓╺┳╸┏━╸   ╻  ╻┏━┓╺┳╸                  ║      \n";
        cout << "       ║╺━┫    ┃ ┃┣━┛ ┃┃┣━┫ ┃ ┣╸    ┃  ┃┗━┓ ┃                   ║      \n";
        cout << "       ║┗━┛╹   ┗━┛╹  ╺┻┛╹ ╹ ╹ ┗━╸   ┗━╸╹┗━┛ ╹                   ║      \n";      
        cout << "       ╚════════════════════════════════════════════════════════╝      \n\n";

        cout << "       ╔════════════════════════════════════════════════════════╗      \n";  
        cout << "       ║╻ ╻    ╺┳┓┏━╸╻  ┏━╸╺┳╸┏━╸   ┏━┓   ╻  ╻┏━┓╺┳╸            ║      \n";  
        cout << "       ║┗━┫     ┃┃┣╸ ┃  ┣╸  ┃ ┣╸    ┣━┫   ┃  ┃┗━┓ ┃             ║      \n";  
        cout << "       ║  ╹╹   ╺┻┛┗━╸┗━╸┗━╸ ╹ ┗━╸   ╹ ╹   ┗━╸╹┗━┛ ╹             ║      \n";  
        cout << "       ╚════════════════════════════════════════════════════════╝      \n\n";   

        cout << "       ╔════════════════════════════════════════════════════════╗   \n";      
        cout << "       ║┏━╸    ┏━┓┏━╸╺┳╸╻ ╻┏━┓┏┓╻    ╻   ┏━╸╻ ╻╻╺┳╸             ║   \n"; 
        cout << "       ║┗━┓    ┣┳┛┣╸  ┃ ┃ ┃┣┳┛┃┗┫   ┏┛   ┣╸ ┏╋┛┃ ┃              ║   \n"; 
        cout << "       ║┗━┛╹   ╹┗╸┗━╸ ╹ ┗━┛╹┗╸╹ ╹   ╹    ┗━╸╹ ╹╹ ╹              ║   \n"; 
        cout << "       ╚════════════════════════════════════════════════════════╝   \n\n"; 

        cout << "       ╔════════════════════════════════════════════════════════╗   \n"; 
        cout << "       ║┏━┓    ┏━┓┏━╸┏━┓┏━┓┏━╸╻ ╻   ╻  ╻┏━┓╺┳╸                  ║   \n"; 
        cout << "       ║┣━┓    ┗━┓┣╸ ┣━┫┣┳┛┃  ┣━┫   ┃  ┃┗━┓ ┃                   ║   \n"; 
        cout << "       ║┗━┛╹   ┗━┛┗━╸╹ ╹╹┗╸┗━╸╹ ╹   ┗━╸╹┗━┛ ╹                   ║   \n"; 
        cout << "       ╚════════════════════════════════════════════════════════╝   \n\n";    
        
        cout << "       ╔════════════════════════════════════════════════════════╗   \n"; 
        cout << "       ║┏━┓    ╻ ╻┏━┓┏━┓┏━┓╺┳╸┏━╸   ┏━┓┏━┓╺┳╸┏━╸                ║   \n"; 
        cout << "       ║  ┃    ┃ ┃┣━┛┃ ┃┣━┫ ┃ ┣╸    ┃ ┃┣━┫ ┃ ┣╸                 ║   \n"; 
        cout << "       ║  ╹╹   ┗━┛╹  ┗━┛╹ ╹ ╹ ┗━╸   ┗━┛╹ ╹ ╹ ┗━╸                ║   \n"; 
        cout << "       ╚════════════════════════════════════════════════════════╝   \n\n";

        cout << "       ╔════════════════════════════════════════════════════════╗   \n"; 
        cout << "       ║┏━┓    ╺┳╸┏━┓┏━╸┏━╸╻  ┏━╸   ┏━╸┏━┓┏┳┓┏━╸                ║   \n"; 
        cout << "       ║┣━┫     ┃ ┃ ┃┃╺┓┃╺┓┃  ┣╸    ┃╺┓┣━┫┃┃┃┣╸                 ║   \n"; 
        cout << "       ║┗━┛╹    ╹ ┗━┛┗━┛┗━┛┗━╸┗━╸   ┗━┛╹ ╹╹╹╹┗━╸                ║   \n"; 
        cout << "       ╚════════════════════════════════════════════════════════╝   \n\n";

        cout << "------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 8) {
            cout << "\nInvalid choice. Enter a number from 1 to 8.\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (choice) {
            case 1:
                createNewList(name_of_list, list_of_lists, list_of_descriptions, gamificationEnabled, playerXP, playerLevel, listmonth, listdate, listyear);
                break;

            case 2:
                viewLists(name_of_list, list_of_lists, list_of_descriptions, gamificationEnabled, playerXP, playerLevel, listmonth, listdate, listyear);
                break;

            case 3:
                editList(name_of_list, list_of_lists, list_of_descriptions, gamificationEnabled, playerXP, playerLevel, listmonth, listdate, listyear);
                break;

            case 4:
                deleteList(name_of_list, list_of_lists, list_of_descriptions, gamificationEnabled, playerXP, playerLevel, listmonth, listdate, listyear);
                break;

            case 5:
                cout << "\nExiting program...\n";
                return 0;

            case 6:
                searchLists(name_of_list);
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


        }
    }

    return 0;
}
