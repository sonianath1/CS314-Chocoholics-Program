/*******************************************************************************
Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks, 
Description of Program: 
*********************************************************************************/


#include "menus.h"

int main(void)
{

    cout << "ChocoAn";

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



	return 0;
}
