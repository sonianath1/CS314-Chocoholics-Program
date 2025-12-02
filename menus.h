//menus.h


#include <string>
#include <iostream>

using namespace std;

//gets integer, validates that it's not empty
int get_integer(string prompt);

//calls get integer, validates that it's 9 numbers long
int get_number(string prompt);

//calls get_number for member
int get_member();


//calls get_number for provider
int get_provider();


namespace provider_menu
{
    const int check_in = 1;
    const int check_out = 2;
    const int request_dir = 3;
    const int quit = 4;
}

namespace manager_menu
{
    const int request_summary = 1;
    const int request_provider = 2;
    const int quit = 3;
}

namespace operator_menu
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
    const string main = "\nChoose your login\n1. Provider\n2. Manager\n3. Operator";
}
