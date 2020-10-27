#pragma once

#include <iostream>
#include <unordered_map>
#include "PatientWrapper.hpp"

using namespace std;

extern int exit_application; 

typedef void (*ScriptFunction)(void); // function pointer type
typedef unordered_map<int, ScriptFunction> script_map;

void DisplayChoices();
void displayEditMenu();
int getUserChoice();
void CallScriptCorrespondingToChoice(script_map& functions_map, int choice);
void ExecuteMainMenuChoice(int choice);
void ExecuteEditMenuChoice(int choice);
void InitializeMainApplication();
void mapMainMenuToFunctions();
void exitApplication();
