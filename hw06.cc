/**
 *File: hw06.cc
 *Author: Mila Gmerek
 *Date: 3/30/2022
 *Brief: Program that processes orders for a car dealership.
 *
 */

#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

void displayMenu();
void displayOptions();
char modelSelection(char &model);
char isLowerCase(char &model);
char canceledOrder(char &model);

using namespace std;

int main()
{
    const int CHOICE_E = 10000; // constant price of model E
    const int CHOICE_L = 12000; // constant price of model L
    const int CHOICE_X = 18000; // constant price of model X
    int choice;
    int price;
    vector<string> order = {"Model: "};

    string orders = "NO MODEL SELECTED";
    char model;
    string option;
    string seperator = ", ";
    string optionChoice, nextOption;
    string answer;
    string removedOption;
    string newOption;
    string optionChoices = "Options: ";
    unsigned int location, location2, location3;

    cout << "Welcome to Bobcat Auto Dealership" << endl;
    do
    {
        displayMenu(); // call to function that displays the menu of options
        cin >> choice;

        if (choice == 1) // if user selects 1 then they are able to make a model selection
        {
            cout << orders << endl;
            cout << "Prices for models E, L, and X: "
                 << "$" << CHOICE_E << ", $" << CHOICE_L << ", $" << CHOICE_X << endl; // displays models and their prices
            modelSelection(model);                                                     // function that allows user to select their model
            orders.erase();                                                            // updates order
            orders += model;
            if (model == 'E') // assigns price to model
            {
                price = CHOICE_E;
            }
            if (model == 'L')
            {
                price = CHOICE_L;
            }
            if (model == 'X')
            {
                price = CHOICE_X;
            }
            orders += seperator;
            orders += to_string(price); // updates order with price
            order.push_back(orders);
            cout << order[0] << order[1] << endl;
            ifstream inStream;
            ofstream outStream;
            string fileName = "options.txt"; // opens file with the available options

            inStream.open(fileName);
            if (inStream.fail())
            {
                cout << "Error: file failed to open." << endl;
                exit(0);
            }
            while (getline(inStream, option, '!')) // reads until exclamation point at end of file
            {
                inStream >> option;
            }

            inStream.close();
        }
        if (choice == 2) // if user selects 2, then they are able to see available options
        {
            displayOptions();
        }
        if (choice == 3) // if user selects 3, they can add an option to their order
        {
            int count = 0;
            string answer;
            cout << "Enter an option you would like to add to your order: " << endl;
            getline(cin >> ws, optionChoice);
            location = option.find(optionChoice);
            if (location == string::npos)
            {
                cout << "Not a valid option." << endl;
                cout << "Please re-enter option." << endl;
                cin >> optionChoice;
            }
            orders += seperator;
            orders += optionChoices; // updates order with option selection
            orders += optionChoice;
            order.push_back(orders);
            cout << order[0] << order[2] << endl;
            count++;
            while (count < 6)
            {
                cout << "Would you like to add another option?" << endl;
                cin >> answer;
                if (answer == "no") // if user doesn't want to add another option, they are taken back to the menu
                {
                    cout << "No additional options will be added to your order." << endl;
                    count = 6;
                }
                if (answer == "yes") // if user would like to add another, it will be added to their order
                {
                    cout << "Enter another option to add to your order:" << endl;
                    getline(cin >> ws, nextOption);
                    location3 = option.find(nextOption);
                    if (location3 == string::npos) // if user enters an invalid option, they can re-enter their option choice
                    {
                        cout << "Not a valid option." << endl;
                        cin >> nextOption;
                    }
                    orders += seperator; // updates order with new option
                    orders += nextOption;
                    order.push_back(orders);
                    cout << orders << endl;
                }
            }
        }
        if (choice == 4) // if the user selects 4, they are able to remove an option from their order
        {
            cout << "Enter the option you would like to remove." << endl;
            getline(cin >> ws, removedOption);
            int length = removedOption.length();
            location2 = option.find(removedOption);
            if (location2 == string ::npos)
            {
                cout << "This option is not included in your order" << endl;
                cin >> removedOption;
            }
            orders.erase(18, length + 1); // erases selected option from the order
            cout << orders << endl;
        }
        if (choice == 5) // if the user selects 5, they are able to cancel their order
        {
            cout << "Order will be canceled." << endl;
            orders.erase(); // erases all previous selections
            orders.replace(0, orders.length(), "NO MODEL OR OPTIONS SELECTED");
            model = ' ';
            cout << orders << endl;
        }
        if (choice == 6) // if the user selects 6, the program will quit
        {
            cout << "Program will quit." << endl;
            exit(0);
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() // displays all choices
{
    cout << "Choose an option, 1-6:" << endl;
    cout << "Option 1: Select your model (E, L or X)" << endl;
    cout << "Option 2: Show available options" << endl;
    cout << "Option 3: Add an option to your order" << endl;
    cout << "Option 4: Remove an option from your order" << endl;
    cout << "Option 5: Cancel order" << endl;
    cout << "Option 6: Quit" << endl;
}

char modelSelection(char &model) // checks that entered model is valid even if entered as lower or uppercase
{
    bool choice = true;
    cout << "Select your choice of model: " << endl;
    cin >> model;
    isLowerCase(model);                               // if user enters lowercase, it won't matter
    if (model != 'E' && model != 'L' && model != 'X') // if it is not a valid model, they will re-enter
    {
        choice = false;
    }
    while (choice == false)
    {
        cout << "Select your choice of model: " << endl;
        cin >> model;
        isLowerCase(model);
        if (model == 'E' || model == 'L' || model == 'X')
        {
            choice = true;
        }
    }

    return model;
}
char isLowerCase(char &model) // checks lower and upper case user entered model selection 
{
    if (islower(model))
    {
        model = toupper(model);
    }

    return model;
}

void displayOptions() // displays all options the user can add to their order
{
    ifstream inStream;
    ofstream outStream;
    string fileName = "options.txt";
    string option;
    vector<string> options;

    inStream.open(fileName);
    if (inStream.fail())
    {
        cout << "Error: file failed to open." << endl;
        exit(0);
    }
    while (getline(inStream, option, '!'))
    {
        inStream >> option;
        options.push_back(option);
    }

    for (unsigned int i = 0; i < options.size(); i++)
    {
        cout << options[i] << endl;
    }
    inStream.close();
}

bool checkOption(string optionChoice, string option) // checks option for validity, even if lower or uppercase
{
    char currentCharacter;
    string selection;
    unsigned int location2;
    for (unsigned int i = 0; i < optionChoice.length(); i++)
    {
        if (islower(currentCharacter))
        {
            currentCharacter = toupper(currentCharacter);
            selection += currentCharacter;
        }
    }
    location2 = option.find(selection);
    if (location2 == string::npos)
    {
        return false;
    }
    return true;
}
