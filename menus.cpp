//menus.cpp
//
//

#include "menus.h"

//gets integer, validates that it's not empty
int get_integer(string prompt)
{
    int num = 0;
    bool result = false;

    do
    {
        cout << prompt;
        cin >> num;
        cin.ignore(100, '\n');
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid number, please try again" << endl;
        }
        else
        {
            result = true;
        }
    }while(!result);

    return num;
}


//calls get integer, validates that it's 9 numbers long
int get_number(string prompt)
{
    bool result = false;
    int num = 0;
    do
    {
        num = get_integer(prompt);

        string conversion = to_string(num);

        if (conversion.length() == 9)
        {
            result = true;
        }
        else
        {
            cout << "Invalid number, please try again" << endl;
        }
    }while (!result);

    return num;
}


//calls get_number for member
int get_member()
{
    string prompt = "Enter member number: ";

    return get_number(prompt);
}

//calls get_number for provider
int get_provider()
{
    string prompt = "Enter provider number: ";
    
    return get_number(prompt);
}

//contains sub menus for the provider
int provider(Database & database)
{
    int menu_choice = 0;

    int provider_num;

    //loop until valid number is entered
    do
    {
        //TODO add a loop to continuously get the provider number or fix exception handling
        provider_num = get_provider();        
        
    }while(provider_num);

    //sub-menu loop
    do
    {
    
    }while(

    return 0;
}

//contains sub menus for the manager
int manager(Database & database)
{
    return 0;
}

//contains sub menus for the operator
int op(Database & database)
{
    return 0;
}
