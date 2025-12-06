//menus.h


#include <string>
#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include "database.h"

using namespace std;

//gets integer, validates that it's not empty
int get_integer(string prompt);

//calls get integer, validates that it is an exact numbers long
int get_number(string prompt, size_t exact_digits);

//calls get_number for member
int get_member();

//calls get_number for provider
int get_provider();

//gets a number that is less than a maximum number of digits
int get_zip (size_t max_digits, string prompt);

//contains sub menus for the provider
void provider_menu(Database & database);

//contains sub menus for the manager
void manager_menu(Database & database);

//contains sub menus for the operator
void op_menu(Database & database);

//contains sub-sub menu for the operator manage members
void op_sub_member(Database & database);

//contains sub-sub menu for the operator manage providers
void op_sub_provider(Database & database);

//confirm function that allows viewer to still see screen before it is cleared
void continue_confirm();

//get input for provider object
void provider_input(Database & database);

//get input for member object
void member_input(Database & database);

//get input for the a provided service
void service_input(Database & database, int provider_num);

//gets input for string with max digit limit
string get_string(size_t max_digits, string prompt);

//generates member number making sure it is not duplicated
int generate_member_number(Database & database);

//generates provider number, making sure it is not duplicated
int generate_provider_number(Database & database);

namespace provider_menu_options
{
    const int check_in = 1;
    const int check_out = 2;
    const int request_dir = 3;
    const int quit = 4;
}

namespace manager_menu_options
{
    const int request_summary = 1;
    const int quit = 2;
}

namespace operator_menu_options
{
    const int manage_members = 1;
    const int manage_providers = 2;
    const int quit = 3;

    const int add = 1;
    const int remove = 2;
    const int update = 3;
    const int sub_quit = 4;
}

namespace main_menu
{
    const int provider = 1;
    const int manager = 2;
    const int op = 3;
    const int quit = 4;
}

const int CONTINUE = 1;


namespace menu_text
{
    const string main = R"(
Choose your login
    1. Provider
    2. Manager
    3. Operator
    4. Exit)";

    const string provider_sub = R"(
Welcome to the Provider Portal!
    1. Check-in user
    2. Check-out user
    3. Request Provider Directory
    4. Log out)";

    const string manager_sub = R"(Welcome to the Manager Portal!
    1. Request weekly summary of services
    2. Log out)";

    const string operator_sub = R"(Welcome to the Operator Portal!
    1. Manage Members
    2. Manage Providers
    3. Log out)";

    const string operator_member = R"(Manage Member Options:
    1. Add new member
    2. Delete member
    3. Update member
    4. Go back)";

    const string operator_provider = R"(Manage Provider Options:
    1. Add new provider
    2. Delete provider
    3. Update provider
    4. Go back)";

    const string welcome = R"(Welcome to the Chocoholics Anonymous Data Processor!

Chocoholics Anonymous (ChocAn) is an organization dedicated to helping 
people addicted to chocolate in all its glorious forms. This software
manages all data given by members and providers, and allows for managers
and operators to view and edit the data.)";

    const string goodbye = "Thank you!\n";
}
