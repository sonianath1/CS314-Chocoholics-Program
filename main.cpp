/*******************************************************************************
Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks, 
Description of Program: 
*********************************************************************************/
<<<<<<< HEAD


#include "menus.h"
=======
#include <iostream>
#include "database.h"
using namespace std;



>>>>>>> 952f33e1fda166a360b052ea0ed8a5708c1776be

int main(void)
{
	Database test;
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       MEMBERS                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_members();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       PROVIDERS                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

    cout << "ChocoAn";

<<<<<<< HEAD
    int menu_choice = 0;

    do
    {
        cout << menu_text::main;
        menu_choice = get_integer("> ");
        switch (menu_choice)
        {
            case(main_menu::provider):
                cout << "will add provider"; 
                break;
            case(main_menu::manager):
                cout << "will add manager"; 
                break;
            case(main_menu::op):
                cout << "will add operator"; 
                break;
        }

    }while(menu_choice != main_menu::quit);
=======
	test.display_providers();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       DIRECTORY                    \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
>>>>>>> 952f33e1fda166a360b052ea0ed8a5708c1776be

	test.display_prov_dir();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "               RECORDED SERVICES                    \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_recorded_ser();

    test.generate_weekly_report();
    cout<<"Weekly report generated."<<endl;

	return 0;
}
