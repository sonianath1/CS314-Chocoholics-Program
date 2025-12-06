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


//calls get integer, validates that it's the exact numbers long
int get_number(string prompt, size_t exact_digits)
{
    bool result = false;
    int num = 0;
    do
    {
        num = get_integer(prompt);

        string conversion = to_string(num);

        if (conversion.length() == exact_digits)
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

    return get_number(prompt, 9);
}

//calls get_number for provider
int get_provider()
{
    string prompt = "Enter provider number: ";
    
    return get_number(prompt, 9);
}

//gets a number that is less than a maximum number of digits
int get_zip (size_t max_digits, string prompt)
{
    int num = 0;
    bool result = false;

    do
    {
        num = get_integer(prompt);

        string conversion = to_string(num);

        if (conversion.length() > max_digits)
        {
            cout << "Invalid number, exeeds limit of " << max_digits << "characters. Please try again" << endl;
        }
        else
        {
            result = true;
        }
    }while (!result);

    return num;
}


//contains sub menus for the provider
void provider_menu(Database & database)
{
    int menu_choice = 0;
    int provider_num = 0;
    int member_num = 0;
    bool result = true;
    bool validated = false;

    //loop until valid number is entered
    do
    {
        system("clear");
        provider_num = get_provider();        
        result = database.verify_provider(provider_num);
        //user was not found in the database
        if (!result)
        {
            int choice = 0;
            
		    cout << "\nInvalid Number" << endl;
            cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
            choice = get_integer("\n> ");
            if (choice != 1)
            {
                break;
            }
        }
        else
        {
            validated = true;
        }
    
    }while(!result);

    

    //user chose not to try again
    if (!validated)
    {
        return;
    }
    //sub-menu loop

    continue_confirm();
    do
    {
        system("clear");
        cout << menu_text::provider_sub;
        menu_choice = get_integer("\n> ");
        switch (menu_choice)
        {
            //checking the user in
            case(provider_menu_options::check_in):
                system("clear");
                
                do
                {
                    member_num = get_member();
                    result = database.verify_member(member_num);
                    if (!result)
                    {
                        int choice = 0;
		                cout << "\nInvalid Number" << endl;
                        cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
                        choice = get_integer("\n> ");
                        if (choice != 1)
                        {
                            validated = false;
                            break;
                        }
                    }

                }while(!result);

                //user chose not to try again
                if (!validated)
                {
                    return;
                }

                continue_confirm();
                
                break;

            //checking the user out
            case(provider_menu_options::check_out):
                system("clear");

                service_input(database, provider_num); 

                continue_confirm();
                break;

            case(provider_menu_options::request_dir):
                system("clear");

                database.display_prov_dir();

                continue_confirm();
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
        system("clear");
        cout << menu_text::manager_sub;
        menu_choice = get_integer("\n> ");

        switch (menu_choice)
        {
            case(manager_menu_options::request_summary):
                system("clear");
                cout << "Requesting weekly summary...\n";
                database.generate_weekly_report();


                cout << "File outputed, view weekly_report.txt file" << endl;

                continue_confirm();

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
        system("clear");
        cout << menu_text::operator_sub;
        menu_choice = get_integer("\n> ");

        switch(menu_choice)
        {
            case(operator_menu_options::manage_members):
                system("clear");
                op_sub_member(database);
                break;

            case(operator_menu_options::manage_providers):
                system("clear");
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
    int member_num = 0;
    bool validated = false;
    bool result = false;

    do
    {
        system("clear");
        cout << menu_text::operator_member;
        menu_choice = get_integer("\n> ");

        switch(menu_choice)
        {
            case(operator_menu_options::add):
                system("clear");
                member_input(database);

                continue_confirm();
                break;

            case(operator_menu_options::remove):
                system("clear");
                do
                {
                    member_num = get_member();
                    result = database.verify_member(member_num);
                    if (!result)
                    {
                        int choice = 0;
		                cout << "\nInvalid Number" << endl;
                        cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
                        choice = get_integer("\n> ");
                        if (choice != 1)
                        {
                            validated = false;
                            break;
                        }
                    }
                    else
                    {
                        validated = true;
                    }

                }while(!result);

                if (validated)
                {
                    database.delete_member(member_num);
                }

                continue_confirm();
                break;

            case(operator_menu_options::update):
                do
                {
                    member_num = get_member();
                    result = database.verify_member(member_num);
                    if (!result)
                    {
                        int choice = 0;
		                cout << "\nInvalid Number" << endl;
                        cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
                        choice = get_integer("\n> ");
                        if (choice != 1)
                        {
                            validated = false;
                            break;
                        }
                    }
                    else
                    {
                        validated = true;
                    }

                }while(!result);


                if (validated)
                {
                    database.update_member(member_num);
                }

                continue_confirm();
                break;
        }
    }while(menu_choice != operator_menu_options::sub_quit);

    return;
}

//contains sub-sub menu for the operator manage providers
void op_sub_provider(Database & database)
{
    int menu_choice = 0;
    int provider_num = 0;
    bool validated = false;
    bool result = false;

    do
    {
        system("clear");
        cout << menu_text::operator_provider;
        menu_choice = get_integer("\n> ");

        switch(menu_choice)
        {
            case(operator_menu_options::add):
                system("clear");
                provider_input(database);
                
                continue_confirm();
                break;

            case(operator_menu_options::remove):
                
                do
                {
                    system("clear");
                    provider_num = get_provider();        
                    result = database.verify_provider(provider_num);
                    //user was not found in the database
                    if (!result)
                    {
                        int choice = 0;
                        
                        cout << "\nInvalid Number" << endl;
                        cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
                        choice = get_integer("\n> ");
                        if (choice != 1)
                        {
                            break;
                        }
                    }
                    else
                    {
                        validated = true;
                    }
                    
                }while(!result);


                if (validated)
                {
                    database.delete_provider(provider_num);
                }

                continue_confirm();
                break;

            case(operator_menu_options::update):

                do
                {
                    system("clear");
                    provider_num = get_provider();        
                    result = database.verify_provider(provider_num);
                    //user was not found in the database
                    if (!result)
                    {
                        int choice = 0;
                        
                        cout << "\nInvalid Number" << endl;
                        cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
                        choice = get_integer("\n> ");
                        if (choice != 1)
                        {
                            break;
                        }
                    }
                    else
                    {
                        validated = true;
                    }
                    
                }while(!result);


                if (validated)
                {
                    database.update_provider(provider_num);
                }

                continue_confirm();
                break;
        }
    }while(menu_choice != operator_menu_options::sub_quit);

    return;
}


//confirm function that allows viewer to still see screen before it is cleared
void continue_confirm()
{
    int confirm = 0;
    do
    {
        cout << "\nEnter 1 to continue";
        confirm = get_integer("\n> ");
        if (confirm != CONTINUE)
        {
            cout << "\nInvalid number" << endl;
        }
    }while(confirm != CONTINUE);

    return;
}

//get input for provider object and adds it to the database
void provider_input(Database & database)
{
    string temp_name;
    int temp_number;
    string temp_street;
    string temp_city;
    string temp_state;
    int temp_zip;

    vector <int> temp_services;

    temp_name = get_string(25, "Enter name of provider: ");

    temp_number = generate_provider_number(database);

    temp_street = get_string(25, "Enter street address: ");

    temp_city = get_string(14, "Enter city: ");

    temp_state = get_string(2, "Enter state abbreviation: ");

    temp_zip = get_zip(5, "Enter zip code: ");

    address temp_address = {temp_street, temp_city, temp_state, temp_zip};

    Provider temp_provider(temp_name, temp_number, temp_address, temp_services);

    database.add_provider(temp_provider);

    cout << "Provider has been assigned the number " << temp_number << endl;

    return;
}

//get input for member object
void member_input(Database & database)
{
    string temp_name;
    int temp_number;
    string temp_street;
    string temp_city;
    string temp_state;
    int temp_zip;

    string temp_status = "Active"; 

    temp_name = get_string(25, "Enter name of member: ");

    temp_number = generate_provider_number(database);

    temp_street = get_string(25, "Enter street address: ");

    temp_city = get_string(14, "Enter city: ");

    temp_state = get_string(2, "Enter state abbreviation: ");

    temp_zip = get_zip(5, "Enter zip code: ");

    address temp_address = {temp_street, temp_city, temp_state, temp_zip};

    Member temp_member(temp_name, temp_number, temp_address, temp_status);

    database.add_member(temp_member);

    cout << "Member has been assigned the number " << temp_number << endl;

    return;
}

//get input for the a provided service
void service_input(Database & database, int provider_num)
{
    string temp_current_time;
    string temp_service_date;
    int member_num;
    int service_num;
    string temp_comments;
    bool result;
    bool validated = true;
    int choice = 0;

    temp_current_time = get_string(19, "Enter current date (MM:DD:YYYY:HH:MM:SS): ");

    temp_service_date = get_string(19, "Enter date service was provided (MM:DD:YYYY:HH:MM:SS): ");
    
    do
    {
        member_num = get_member();
        result = database.verify_member(member_num);
        if (!result)
        {
		    cout << "\nInvalid Number" << endl;
            cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
            choice = get_integer("\n> ");
            if (choice != 1)
            {
                validated = false;
                break;
            }
        }

    }while(!result);

    //user chose not to try to enter a valid member number
    if (!validated)
    {
        return;
    }
    
    do
    {
        service_num = get_number("Enter Service Code Number: ", 6);
        result = database.verify_service(service_num);
        if (!result)
        {
		    cout << "\nInvalid Number" << endl;
            cout << "Would you like to try again? (enter 1 for yes, any other number for no)" << endl;
            choice = get_integer("\n> ");
            if (choice != 1)
            {
                validated = false;
                break;
            }
        }
        else
        {
            cout << "Is this the correct service? (enter 1 for yes, any other number for no)" << endl;
            choice = get_integer("\n> ");
            if (choice != 1)
            {
                result = false;
            }
        }

    }while(!result);

    //user chose not to try to enter a valid service code
    if (!validated)
    {
        return;
    }

    cout << "Would you like to add comments? (enter 1 for yes, any other number for no)" << endl;
    choice = get_integer("\n> ");

    //user wants to add comments
    if (choice == 1)
    {
        cout << "Enter comments about the provided service: ";
        getline(cin, temp_comments);
    }

    ProvidedService temp_services = {temp_current_time, temp_service_date, provider_num, member_num, service_num, temp_comments};

    database.record_provided_service(temp_services);

    cout << "Service recorded. Ask manager for the weekly report to see fee" << endl;
    return;
}

//gets input for string with max digit limit
string get_string(size_t max_digits, string prompt)
{
    string temp_string;

    do
    {
        cout << prompt;
        getline(cin, temp_string);

        if (temp_string.length() > max_digits)
        {
            cout << "Entry exeeds max digits of " << max_digits << ". Please try again" << endl;
        }

    }while(temp_string.length() > max_digits);

    return temp_string;
}

//generates member number making sure it is not duplicated
int generate_member_number(Database & database)
{

    bool result = false;
    int temp_num;
    do
    {
        temp_num = 100000000 + (rand() % 999999999);

        if (!database.verify_member(temp_num))
        {
            //found a number that isn't taken
            result = true;
        }

    }while(!result);

    return temp_num;
}

//generates provider number, making sure it is not duplicated
int generate_provider_number(Database & database)
{

    bool result = false;
    int temp_num;
    do
    {
        temp_num = 100000000 + (rand() % 999999999);

        if (!database.verify_provider(temp_num))
        {
            //found a number that isn't taken
            result = true;
        }

    }while(!result);

    return temp_num;
}
