#include <iostream>
#include "entities.h"
using namespace std;


/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     ENTITY
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


Entity::Entity()
{
}

int Entity::get_number()
{
	return number;
}

string & Entity::get_name()
{
	return name;
}

bool Entity::compare_number(int number_to_compare)
{
	return false;
}

void Entity::update_data(Entity& to_copy)
{
}


void Entity::display_all()
{
	cout << "\nName: " << name << endl;
	cout << "Number: " << number << endl;
	cout << "Street Address: " << addr.street_addr << endl;
	cout << "City: " << addr.city << endl;
	cout << "State: " << addr.state << endl;
	cout << "Zip code: " << addr.zip_code << endl;
}


/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     MEMBER
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


Member::Member(): status("") {}

void Member::display_all()
{
	Entity::display_all();
	cout << "Status: " << status << endl;
}

void Member::update_data(Member & to_copy)
{
}



/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     PROVIDER
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


Provider::Provider()
{
}

void Provider::display_all()
{
	Entity::display_all();
	cout << "Services provided: ";
	for (int value : services_provided) 
		cout << value << ",";
	cout << "\n";	
}

void Provider::update_data(Provider& to_copy)
{
}
