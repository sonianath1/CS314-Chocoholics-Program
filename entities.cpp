#include <iostream>
#include "entities.h"
using namespace std;


/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     ENTITY
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


Entity::Entity(): name(""), number(0), addr({"", "", "", 0}) {}


Entity::Entity(const string _name, const int _number, const address _addr): name(_name), number(_number), addr(_addr) {}

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

void Entity::update_data(const Entity& to_copy)
{
	name = to_copy.name;
	number = to_copy.number;
	addr = to_copy.addr;
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


Member::Member(): Entity(), status("") {}

Member::Member(const string _name, const int _number, const address _addr, const string _status): 
	Entity(_name, _number, _addr), status(_status) {}

void Member::display_all()
{
	Entity::display_all();
	cout << "Status: " << status << endl;
}

void Member::update_data(const Member & to_copy)
{
	Entity::update_data(to_copy);

	status = to_copy.status;
}



/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     PROVIDER
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


Provider::Provider(): Entity(), services_provided() {}

Provider::Provider(const string _name, const int _number, const address _addr, const std::vector<int> &_services):
			Entity(_name, _number, _addr), services_provided(_services){}

void Provider::display_all()
{
	Entity::display_all();
	cout << "Services provided: ";

	// making sure that txt file does not have a last comma, instad newline
	const vector<int>& servs = get_services();
	int len = servs.size();

	for (int i = 0; i < len; ++i)
	{
		cout << servs[i];
		if (i < len - 1)
			cout << ",";
	}

	cout << "\n";
}

void Provider::update_data(const Provider& to_copy)
{
	Entity::update_data(to_copy);

	services_provided = to_copy.services_provided;
}
