//menus.h


#include <string>
#include <iostream>
#include "database.h"

using namespace std;

//gets integer, validates that it's not empty
int get_integer(string prompt);

//calls get integer, validates that it's 9 numbers long
int get_number(string prompt);

//calls get_number for member
int get_member();


//calls get_number for provider
int get_provider();

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
    const int request_provider = 2;
    const int quit = 3;
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


namespace menu_text
{
    const string main = "\nChoose your login\n\t1. Provider\n\t2. Manager\n\t3. Operator\n\t4. Quit";
    const string provider_sub = "\nWelcome to the Provider Portal!\n\t1. Check-in User\n\t2. Check-out user\
        \n\t3. Request Provider Directory\n\t4. Log out";
    const string manager_sub = "\nWelcome to the Manager Portal!\n\t1.Request weekly summary of services\
        \n\t2. Request summary of one provider\n\t3. Log out";
    const string operator_sub = "\nWelcome to the Operator Portal!\n\t1.Manage Members\n\t2. Manage Providers\n\t3. Log out";
    const string operator_member = "\nManage Member Options:\n\t1. Add new member\n\t2. Delete member\n\t3. Update member\
        \n\t4. Go back";
    const string operator_provider = R"(
Manage Provider Options:
    1. Add new provider
    2. Delete provider
    3. Update provider
    4. Go back)";

    const string goodbye = "Thank you!";
}
