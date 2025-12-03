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
void provider_menu(Database & database)
{
    int menu_choice = 0;
    int provider_num;
    int member_num;

    //loop until valid number is entered
    do
    {
        //TODO add a loop to continuously get the provider number or fix exception handling
        provider_num = get_provider();        
        //database.verify_provider(provider_num);
        
    }while(!provider_num);

    //sub-menu loop
    do
    {
        cout << menu_text::provider_sub;
        menu_choice = get_integer("\n> ");
        switch (menu_choice)
        {
            case(provider_menu_options::check_in):
                //update loop once expection handling for member lookup is confirmed
                do
                {
                    member_num = get_member();
                    //database.verify_member(member_num);
                }while(!menu_choice);
                break;

            case(provider_menu_options::check_out):
                    member_num = get_member();
                    //database.verify_member(member_num);
                break;

            case(provider_menu_options::request_dir):
                cout << "request directory" << endl;
                break;
        }
    }while(menu_choice != provider_menu_options::quit);

    return;
}

//contains sub menus for the manager
void manager_menu(Database & database)
{
    int menu_choice = 0;

    do
    {
        cout << menu_text::manager_sub;
        menu_choice = get_integer("\n> ");

        switch (menu_choice)
        {
            case(manager_menu_options::request_summary):
                cout << "requesting summary";
                break;
            case(manager_menu_options::request_provider):
                cout << "requesting providers";
                break;
        }
    }while(menu_choice != manager_menu_options::quit);

    return;
}

//contains sub menus for the operator
void op_menu(Database & database)
{
    int menu_choice = 0;

    do
    {
        cout << menu_text::operator_sub;
        menu_choice = get_integer("\n> ");

        switch(menu_choice)
        {
            case(operator_menu_options::manage_members):
                op_sub_member(database);
                break;

            case(operator_menu_options::manage_providers):
                op_sub_provider(database);
                break;
        }
    }while(menu_choice != operator_menu_options::quit);

    return;
}

//contains sub-sub menu for the operator manage members
void op_sub_member(Database & database)
{
    int menu_choice = 0;

    do
    {
        cout << menu_text::operator_member;
        menu_choice = get_integer("\n> ");

        switch(menu_choice)
        {
            case(operator_menu_options::add):
                cout << "add";
                break;

            case(operator_menu_options::remove):
                cout << "remove";
                break;

            case(operator_menu_options::update):
                cout << "update";
                break;
        }
    }while(menu_choice != operator_menu_options::sub_quit);

    return;
}

//contains sub-sub menu for the operator manage providers
void op_sub_provider(Database & database)
{
    int menu_choice = 0;

    do
    {
        cout << menu_text::operator_provider;
        menu_choice = get_integer("\n> ");

        switch(menu_choice)
        {
            case(operator_menu_options::add):
                
                break;

            case(operator_menu_options::remove):
                cout << "remove";
                break;

            case(operator_menu_options::update):
                cout << "update";
                break;
        }
    }while(menu_choice != operator_menu_options::sub_quit);

    return;
}
