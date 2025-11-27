/*******************************************************************************
Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks, 
Description of Program: 
*********************************************************************************/


#include <iostream>
#include "database.h"
using namespace std;




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

	test.display_providers();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                       DIRECTORY                    \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_prov_dir();
	
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "               RECORDED SERVICES                    \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";

	test.display_recorded_ser();

	return 0;
}
