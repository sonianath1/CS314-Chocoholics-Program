/*******************************************************************************
Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks, 
Description of Program: 
*********************************************************************************/


#include "menus.h"
#include <iostream>
#include "database.h"
using namespace std;




int main(void)
{
	Database test;

    /*
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       MEMBERS                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_members();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       PROVIDERS                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

    */


    int menu_choice = 0;

    do
    {
        system("clear");
        cout << menu_text::welcome << endl;
        cout << menu_text::main;
        menu_choice = get_integer("\n> ");
        switch (menu_choice)
        {
            case(main_menu::provider):
                provider_menu(test);
                break;
            case(main_menu::manager):
                manager_menu(test);
                break;
            case(main_menu::op):
                op_menu(test);
                break;
        }

    }while(menu_choice != main_menu::quit);

    cout << menu_text::goodbye;
    /*
	test.display_providers();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       DIRECTORY                    \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_prov_dir();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "               RECORDED SERVICES                    \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_recorded_ser();

    test.generate_weekly_report();
    cout<<"Weekly report generated."<<endl;
    */

	return 0;
}
