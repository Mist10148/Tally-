#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;




// Function to create a new list
void createNewList(vector<string>& name_of_list, vector<vector<string>>& list_of_lists) {
    system("cls");

    cout << "==============================\n";
    cout << "       CREATE NEW LIST        \n";
    cout << "==============================\n";

    cin.ignore(); // Clears leftover newline
    string title;
    cout << "Enter list title: ";
    getline(cin, title);

    vector<string> items;  // temporary storage for items

    cout << "\nStart adding items to your list.\n";
    cout << "Type an item and press Enter.\n";
    cout << "Type 'done' to finish or 'cancel' to discard.\n\n";

    string item;

    // DO-WHILE LOOP FOR ADDING ITEMS
    do {
        cout << "Add item: ";
        getline(cin, item);

        if (item == "done")
            break;

        if (item == "cancel") {
            cout << "\nList creation cancelled. Returning to menu...\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        // Add item using assignment + resize
        int index = items.size();
        items.resize(index + 1);
        items[index] = item;

    } while (true);

    // Save the title
    int titleIndex = name_of_list.size();
    name_of_list.resize(titleIndex + 1);
    name_of_list[titleIndex] = title;

    // Save the items list
    int listIndex = list_of_lists.size();
    list_of_lists.resize(listIndex + 1);
    list_of_lists[listIndex] = items;

    cout << "\nList saved successfully!\n";
    cout << "Press Enter to continue...";
    cin.get();
}


void viewLists(vector<string> &name_of_list, vector<vector<string>> &list_of_lists) {

    if (name_of_list.size() == 0) {
        cout << "\nNo lists created yet.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n========= VIEW LISTS =========\n";

    for (int i = 0; i < name_of_list.size(); i++) {
        cout << i + 1 << ". " << name_of_list[i] << endl;
    }

    int choice;

    cout << "\nSelect a list number to view: ";
    cin >> choice;

    // clear only 1 leftover newline
    cin.ignore();

    if (choice < 1 || choice > name_of_list.size()) {
        cout << "\nInvalid list number.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    int index = choice - 1;

    cout << "\n====== " << name_of_list[index] << " ======\n";

    vector<string> &items = list_of_lists[index];

    if (items.size() == 0) {
        cout << "(No items in this list)\n";
    }
    else {
        int completedCount = 0;

        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i] << endl;

            if (items[i].find("[DONE]") != string::npos) {
                completedCount++;
            }
        }

        //cout << "\nTotal Items: " << items.size() << endl;
        //cout << "Completed Items: " << completedCount << endl;
        int notDone = items.size() - completedCount;

        // Calculate percentages
        double percentDone = 0;
        double percentNotDone = 0;

        if (items.size() > 0) {
            percentDone = (completedCount * 100.0) / items.size();
            percentNotDone = (notDone * 100.0) / items.size();
        }

        // Minimalistic statistics table
        cout << "\n----------------------------------\n";
        cout << "           STATISTICS             \n";
        cout << "----------------------------------\n";
        cout << " Total Items       : " << items.size() << "\n";
        cout << " Completed Items   : " << completedCount << "\n";
        cout << " Not Done Items    : " << notDone << "\n";
        cout << fixed;
        cout << setprecision(2);
        cout << " % Completed       : " << percentDone << "%\n";
        cout << " % Not Completed   : " << percentNotDone << "%\n";
        cout << "----------------------------------\n";

    }

    cout << "\nPress Enter to continue...";
    cin.get();  // waits for enter
}


void editList(vector<string> &name_of_list, vector<vector<string>> &list_of_lists) {

    if (name_of_list.size() == 0) {
        cout << "\nNo lists to edit.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n========= EDIT LIST =========\n";

    for (int i = 0; i < name_of_list.size(); i++) {
        cout << i + 1 << ". " << name_of_list[i] << endl;
    }

    int choice;

    cout << "\nSelect a list number to edit: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > name_of_list.size()) {
        cout << "\nInvalid list number.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    int index = choice - 1;

    while (true) {

        system("cls");

        cout << "=============================\n";
        cout << " Editing: " << name_of_list[index] << endl;
        cout << "=============================\n\n";

        vector<string> &items = list_of_lists[index];

        int completedCount = 0;

        if (items.size() == 0) {
            cout << "(No items yet)\n";
        } else {
            for (int i = 0; i < items.size(); i++) {
                cout << i + 1 << ". " << items[i] << endl;

                if (items[i].find("[DONE]") != string::npos)
                    completedCount++;
            }
        }

        //cout << "\nTotal Items: " << items.size() << endl;
        //cout << "Completed Items: " << completedCount << endl;
        int notDone = items.size() - completedCount;

// Calculate percentages
        double percentDone = 0;
        double percentNotDone = 0;

        if (items.size() > 0) {
            percentDone = (completedCount * 100.0) / items.size();
            percentNotDone = (notDone * 100.0) / items.size();
        }

        // Minimalistic statistics table
        cout << "\n----------------------------------\n";
        cout << "           STATISTICS             \n";
        cout << "----------------------------------\n";
        cout << " Total Items       : " << items.size() << "\n";
        cout << " Completed Items   : " << completedCount << "\n";
        cout << " Not Done Items    : " << notDone << "\n";
        cout << fixed;
        cout << setprecision(2);
        cout << " % Completed       : " << percentDone << "%\n";
        cout << " % Not Completed   : " << percentNotDone << "%\n";
        cout << "----------------------------------\n";



        cout << "\nEDIT MENU\n";
        cout << "1. Add New Item\n";
        cout << "2. Edit an Item\n";
        cout << "3. Delete an Item\n";
        cout << "4. Mark / Unmark Item as DONE\n";
        cout << "5. Reorder Items (Swap)\n";
        cout << "6. Rename List\n";
        cout << "7. Return to Main Menu\n";

        int editChoice;
        cout << "\nChoose an option: ";
        cin >> editChoice;
        cin.ignore();

        // --------------------------------------------------------
        // 1. ADD NEW ITEM
        // --------------------------------------------------------
        if (editChoice == 1) {

            string newItem;
            cout << "\nEnter new item: ";
            getline(cin, newItem);

            int newIndex = items.size();
            items.resize(newIndex + 1);
            items[newIndex] = newItem;

            cout << "Item added!\n";
            cout << "Press Enter to continue...";
            cin.get();
        }

        // --------------------------------------------------------
        // 2. EDIT EXISTING ITEM
        // --------------------------------------------------------
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

            if (itemNum < 1 || itemNum > items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

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
        }

        // --------------------------------------------------------
        // 3. DELETE ITEM
        // --------------------------------------------------------
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

            if (delNum < 1 || delNum > items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            items.erase(items.begin() + (delNum - 1));

            cout << "Item deleted!\n";
            cout << "Press Enter to continue...";
            cin.get();
        }

        // --------------------------------------------------------
        // 4. MARK / UNMARK ITEM
        // --------------------------------------------------------
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

            if (markNum < 1 || markNum > items.size()) {
                cout << "\nInvalid item number!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            string &target = items[markNum - 1];

            if (target.find("[DONE]") != string::npos) {
                target = target.substr(7); // remove "[DONE] "
                cout << "Item unmarked.\n";
            } else {
                target = "[DONE] " + target;
                cout << "Item marked as DONE.\n";
            }

            cout << "Press Enter to continue...";
            cin.get();
        }

        // --------------------------------------------------------
        // 5. REORDER ITEMS — SWAP
        // --------------------------------------------------------
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

            if (a < 1 || a > items.size() || b < 1 || b > items.size()) {
                cout << "\nInvalid item numbers!\n";
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }

            string temp = items[a - 1];
            items[a - 1] = items[b - 1];
            items[b - 1] = temp;

            cout << "Items swapped!\n";
            cout << "Press Enter to continue...";
            cin.get();
        }

        // --------------------------------------------------------
        // 6. RENAME LIST
        // --------------------------------------------------------
        else if (editChoice == 6) {

            string newName;
            cout << "\nEnter new list name: ";
            getline(cin, newName);

            name_of_list[index] = newName;

            cout << "List renamed!\n";
            cout << "Press Enter to continue...";
            cin.get();
        }

        // --------------------------------------------------------
        // 7. EXIT EDIT MENU
        // --------------------------------------------------------
        else if (editChoice == 7) {
            break;
        }

        else {
            cout << "\nInvalid option.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
}


void deleteList(vector<string> &name_of_list, vector<vector<string>> &list_of_lists) {
    
    if (name_of_list.size() == 0) {
        cout << "\nNo lists to delete.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n===== DELETE A LIST =====\n";

    // Show lists
    for (int i = 0; i < name_of_list.size(); i++) {
        cout << i + 1 << ". " << name_of_list[i] << endl;
    }

    cout << "\n0. Cancel / Return to Main Menu\n";

    int choice;
    cout << "\nSelect list to delete: ";
    cin >> choice;

    // --------------------------
    // USER CHOSE TO CANCEL
    // --------------------------
    if (choice == 0) {
        cout << "Returning to main menu...\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // --------------------------
    // INVALID NUMBER
    // --------------------------
    if (choice < 1 || choice > name_of_list.size()) {
        cout << "Invalid choice.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int index = choice - 1;

    // --------------------------
    // DELETE CONFIRMATION
    // --------------------------
    char confirm;
    cout << "Are you sure you want to delete \""
         << name_of_list[index] << "\"? (y/n): ";
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion cancelled.\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // --------------------------------------------
    // MANUAL DELETE (resize + assignment only)
    // --------------------------------------------
    vector<string> newNames;
    vector<vector<string>> newLists;

    for (int i = 0; i < name_of_list.size(); i++) {
        if (i != index) {

            // Add name
            int ni = newNames.size();
            newNames.resize(ni + 1);
            newNames[ni] = name_of_list[i];

            // Add item list
            int li = newLists.size();
            newLists.resize(li + 1);
            newLists[li] = list_of_lists[i];
        }
    }

    // Replace old content
    name_of_list = newNames;
    list_of_lists = newLists;

    cout << "\nList deleted successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {

    vector<string> name_of_list;               
    vector<vector<string>> list_of_lists;     

    int choice;

    
    while (true) {

        system("cls");

        cout << "==========================================\n";
        cout << "             Tally++ List Manager          \n";
        cout << "==========================================\n";
        cout << " Organize your tasks, reminders, and more!\n";
        cout << "==========================================\n\n";

        cout << "            MAIN MENU\n";
        cout << "------------------------------------------\n";
        cout << "1. Create a New List\n";
        cout << "2. View Lists and Items\n";
        cout << "3. Edit or Update an Existing List\n";
        cout << "4. Delete a List\n";
        cout << "5. Return / Exit Program\n";
        cout << "------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 5) {
            cout << "\nInvalid choice. Enter a number from 1 to 5.\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (choice) {
            case 1:
                createNewList(name_of_list, list_of_lists);
                break;

            case 2:
                viewLists(name_of_list, list_of_lists);
                break;

            case 3:
                editList(name_of_list, list_of_lists);
                break;

            case 4:
                deleteList(name_of_list, list_of_lists);
                break;

            case 5:
                cout << "\nExiting program...\n";
                return 0;
        }
    }

    return 0;
}