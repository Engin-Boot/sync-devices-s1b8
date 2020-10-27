#include "MenuCLI.hpp"

script_map main_menu_mapping;
script_map edit_menu_mapping;

void DisplayChoices() {
	cout << "Select one of the following menu items!" << endl;
	cout << "1. Add new Patient" << endl;
	cout << "2. Edit patient info" << endl;
	cout << "3. Start Procedure" << endl;
	cout << "4. Print Patient Data" << endl;
    cout << "5. Exit" << endl;
	cout << "Your choice (1/2/3/4/5)? ";
}

void displayEditMenu()
{
    cout << "1. Edit Name" << endl;
    cout << "2. Edit Age" << endl;
    cout << "3. Edit Gender" << endl;
    cout << "4. Edit Procedure" << endl;
    cout << "5. Edit All" << endl;
    cout << "Your choice (1/2/3/4/5)? ";
}

void CallScriptCorrespondingToChoice(script_map& functions_map, int choice)
{
    auto iter = functions_map.find(choice);
    (*iter->second)();
}

void ExecuteMainMenuChoice(int choice)
{
    CallScriptCorrespondingToChoice(main_menu_mapping, choice);
}

void ExecuteEditMenuChoice(int choice)
{
    CallScriptCorrespondingToChoice(edit_menu_mapping, choice);
}

void mapMainMenuToFunctions()
{
    main_menu_mapping.emplace(1, &addNewPatient);
    main_menu_mapping.emplace(2, &editPatientInfo);
    main_menu_mapping.emplace(3, &startProcedure);
    main_menu_mapping.emplace(4, &printPatientInformation);
    main_menu_mapping.emplace(5, &exitApplication);
}

void mapEditMenuToFunctions()
{
    edit_menu_mapping.emplace(1, &editName);
    edit_menu_mapping.emplace(2, &editAge);
    edit_menu_mapping.emplace(3, &editGender);
    edit_menu_mapping.emplace(4, &editProcedure);
    edit_menu_mapping.emplace(5, &editAll);
}

int getUserChoice()
{
    int choice;
    cin >> choice;
    return choice;
}

void exitApplication()
{
    exit_application = 1;
}

void InitializeMainApplication()
{
    mapMainMenuToFunctions();
    mapEditMenuToFunctions();
}