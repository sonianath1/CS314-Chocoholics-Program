#include <iostream>
#include <cstdlib>
#include <ctime>
#include "database.h"
using namespace std;
/*******************************************************************************
  Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks,
Description of Program:
 *********************************************************************************/




/******************** SONIA SECTION ********************/



// Constructor with arguments
Database::Database(int size_members, int size_providers, int size_prov_dir)
{
	members_size = size_members;
	providers_size = size_providers;
	prov_dir_size = size_prov_dir;

	Members = new node<Member>*[members_size];
	Providers = new node<Provider>*[providers_size];	
	ProviderDirectory = new node<Service>*[prov_dir_size];

	for (int i = 0; i < members_size; ++i)
		Members[i] = nullptr;

	for (int i = 0; i < providers_size; ++i)
		Providers[i] = nullptr;

	for (int i = 0; i < prov_dir_size; ++i)
		ProviderDirectory[i] = nullptr;

	read_from_file();
	// vector for provided services is automattically intialized 
}



// Destructor
Database::~Database()
{
	write_to_file(); // adding new data / updated data into DB

	// templated remove all function in .h file
	remove_all(Members, members_size);
	remove_all(Providers, providers_size);
	remove_all(ProviderDirectory, prov_dir_size);

	ProvidedServices.clear();
}



void Database::read_from_file()
{
	bool mem, pro, dir, record;

	mem = load_member_data();
	pro = load_provider_data();
	dir = load_provider_directory_data();
	record = load_provided_service_data();

	if (!mem || !pro || !dir || !record)
		cerr << "\nerror." << endl;	
}



void Database::write_to_file()
{
	bool mem, pro, dir, record;

	mem = write_member_data();
	pro = write_provider_data();
	dir = write_provider_directory_data();
	record = write_provided_service_data();

	if (!mem || !pro || !dir || !record)
		cerr << "\nerror." << endl;	
}



/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     MEMBER DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/



// Loading data from database into hash 
// tables. This is done at the beginning of every program.
bool Database::load_member_data()
{
	ifstream file_in("members.txt");
	if (!file_in)
	{
		cerr << "\ncould not open file.\n";
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM MEMBER DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	Member to_add;
	string line;

	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		string name_tmp;
		int number_tmp;
		string street_add_tmp;
		string city_tmp;
		string state_tmp;
		int zip_code_tmp;
		string status_tmp;

		// number (1)
		getline(ss, temp, '|');
		number_tmp = stoi(temp);
		to_add.set_number(number_tmp);

		// name (2nd)
		getline(ss, name_tmp, '|');
		to_add.set_name(name_tmp);

		// street (3rd)
		getline(ss, street_add_tmp, '|');
		to_add.get_address().street_addr = street_add_tmp;

		// city (4th)
		getline(ss, city_tmp, '|');
		to_add.get_address().city = city_tmp;

		// state (5th)
		getline(ss, state_tmp, '|');
		to_add.get_address().state = state_tmp;

		// zip (6th)
		getline(ss, temp, '|');
		zip_code_tmp = stoi(temp);
		to_add.get_address().zip_code = zip_code_tmp;

		// status (7th, no delimtier)
		getline(ss, status_tmp);
		to_add.set_status(status_tmp);

		// insert
		add_member(to_add);
	}

	return true;
}



// maybe ill implement this recursive if i cared that much
bool Database::write_member_data()
{
	ofstream file_out("members.txt");
	if (!file_out) 
	{
		cerr << "\ncould not open file.\n" << endl;
		return false;
	}


	for (int i = 0; i < members_size; ++i)
	{
		node<Member>* current = Members[i];
		while (current)
		{
			Member& mem_out = current->data;
			file_out << mem_out.get_number() << "|"
				<< mem_out.get_name() << "|"
				<< mem_out.get_address().street_addr << "|"
				<< mem_out.get_address().city << "|"
				<< mem_out.get_address().state << "|"
				<< mem_out.get_address().zip_code << "|"
				<< mem_out.get_status() << "\n";

			current = current->next;
		}
	}
	return true;
}




// adding member to hash table
void Database::add_member(Member & to_add)
{	
	add_to_table(Members, members_size, to_add);
}



void Database::update_member(int member_number)
{
	Member* found = find(Members, members_size, member_number);

	if (!found) {
		cerr << "\nmember not found\n";
		return;
	}

	cout << "\nUpdating member " << found->get_number() << "...\n";

	// need to implement menu portion for finding out which part 
	// of the member the user wants to update.	
	// Options: name, number, address(street_addr, city, state, zip code), status
}



// deleting member from hash table & DB
void Database::delete_member(int member_number)
{
	bool result = find_and_remove(Members, members_size, member_number);
	if (result)
		cout << "\nMember " << member_number << " removed successfully." << endl;
	else
		cerr << "\nCould not find member " << member_number << endl;
}




/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     PROVIDER DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/




// loading in provider data from file
bool Database::load_provider_data()
{
	ifstream file_in("providers.txt");
	if (!file_in)
	{
		cerr << "could not open providers.txt\n";
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM PROVIDER DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	string line;
	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		Provider to_add;

		//provider number
		getline(ss, temp, '|');
		to_add.set_number(stoi(temp));

		// name
		getline(ss, temp, '|');
		to_add.set_name(temp);

		// street
		getline(ss, temp, '|');
		to_add.get_address().street_addr = temp;

		// city
		getline(ss, temp, '|');
		to_add.get_address().city = temp;

		// state
		getline(ss, temp, '|');
		to_add.get_address().state = temp;

		// zip
		getline(ss, temp, '|');
		to_add.get_address().zip_code = stoi(temp);

		// service list (comma)
		string services_tmp;
		getline(ss, services_tmp); // last field, no delimiter needed

		// clear old vector 
		to_add.clear_services();

		if (!services_tmp.empty())
		{
			stringstream _service(services_tmp);
			string code;

			while (getline(_service, code, ','))
			{
				if (!code.empty())
					to_add.add_service(stoi(code));
			}
		}

		// store into hash table
		add_provider(to_add);
	}

	return true;
}



bool Database::write_provider_data()
{
	ofstream file_out("providers.txt");
	if (!file_out) 
	{
		cerr << "\ncould not open file.\n" << endl;
		return false;
	}


	for (int i = 0; i < providers_size; ++i)
	{
		node<Provider>* current = Providers[i];
		while (current)
		{
			Provider& pro_out = current->data;
			file_out << pro_out.get_number() << "|"
				<< pro_out.get_name() << "|"
				<< pro_out.get_address().street_addr << "|"
				<< pro_out.get_address().city << "|"
				<< pro_out.get_address().state << "|"
				<< pro_out.get_address().zip_code << "|";

			// making sure that txt file does not have a last comma, instad newline
			const vector<int>& servs = pro_out.get_services();	
			int len = servs.size();

			for (int i = 0; i < len; ++i)
			{
				file_out << servs[i];
				if (i < len - 1)
					file_out << ",";	
			}	

			file_out << "\n";

			/*			
						(int value : services_provided)
						file_out << value << ","*/

			current = current->next;
		}
	}
	return true;
}




// adding provider data into hash table / DB
void Database::add_provider(Provider &to_add)
{
	add_to_table(Providers, providers_size, to_add);
}



// updating certain provider in hash table / DB
void Database::update_provider(int provider_number)
{
	int inputNum{0};
    string inputString{" "};
	
	Provider* found = find(Providers, providers_size, provider_number);

	if (!found) {
		cerr << "\nprovider not found\n";
		return;
	}

	cout << "\nUpdating provider " << found->get_number() << "...\n";

	// need to implement menu portion for finding out which part 
	// of the member the user wants to update.	
	// Options: name, number, address(street_addr, city, state, zip code), vector of services

	cout << "\nWhich section of this provider's information would you like to update?: " << endl;
        cout << "\t1. Name" << endl;
        cout << "\t2. Provider Number" << endl;
        cout << "\t3. Address" << endl;
        cout << "\t4. Services Offered" << endl;
        cout << "\nEnter the number corresponding to your choice: ";
        cin >> inputNum; cin.ignore(100, '\n');

        switch (inputNum)
        {
                case 1:
                        cout << "\nEnter the provider's full name: ";
                        cin >> inputString; cin.ignore(100, '\n');
                        found->set_name(inputString);
                        cout << "Provider name successfully updated." << endl;
                        break;

                case 2:
                        cout << "\nEnter the 9-digit provider number: ";
                        cin >> inputNum; cin.ignore(100, '\n');
                        found->set_number(inputNum);
                        cout << "Provider number successfully updated." << endl;
                        break;
			case 3:
                        cout << "\nWhich section of the provider's address would you like to update?:" << endl;
                        cout << "\t1. Street address" << endl;
                        cout << "\t2. City" << endl;
                        cout << "\t3. State" << endl;
                        cout << "\t4. Zip code" << endl;
                        cout << "\nEnter the number corresponding to your choice: ";
                        cin >> inputNum; cin.ignore(100, '\n');
                                if (inputNum == 1) {

                                }
                                else if (inputNum == 2) {

                                }
                                else if (inputNum == 3) {

                                }
                                else if (inputNum == 4) {

                                }
                        break;

                case 4:
                        cout << "Would you like to add or remove a service for this provider? (1 for add, 2 for remove): ";
                        cin >> inputNum; cin.ignore(100, '\n');
                        if (inputNum == 1) {
							cout << "Enter the name of the new service: ";
                                cin >> inputString; cin.ignore(100, '\n');

                                // enter into vector...
                        }
                        else if (inputNum == 2) {
                                /*  display all services
                                 *  ask which one to delete
                                 *  delete it  */
                        }
                        break;

                default:
                        // throw exception for bad input or ask to try inputting again?
                        break;
        }

        return;
}



// delete certain provider
void Database::delete_provider(int provider_number)
{
	bool result = find_and_remove(Providers, providers_size, provider_number);
	if (result)
		cout << "\nProvider " << provider_number << " removed successfully." << endl;
	else
		cerr << "\nCould not find provider " << provider_number << endl;
}



/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *	        PROVIDER DIRECTORY DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/



// loading in provider directory data into HT from DB
bool Database::load_provider_directory_data()
{
	ifstream file_in("providerdirectory.txt");
	if (!file_in)
	{
		cerr << "\ncould not open file." << endl;
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING PROVIDER DIRECTORY DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	string line;
	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		Service to_add;

		// service code
		getline(ss, temp, '|');
		to_add.set_code(stoi(temp));

		// service name
		getline(ss, temp, '|');
		to_add.set_name(temp);

		// fee
		getline(ss, temp, '|');
		to_add.set_fee(stof(temp));

		// insert into hash table
		add_service(to_add);
	}

	return true;
}



bool Database::write_provider_directory_data()
{
	ofstream file_out("providerdirectory.txt");
	if (!file_out)
	{
		cerr << "\ncould not open file.\n" << endl;
		return false;
	}


	for (int i = 0; i < prov_dir_size; ++i)
	{
		node<Service>* current = ProviderDirectory[i];
		while (current)
		{
			Service& dir_out = current->data;
			file_out << dir_out.get_number() << "|"
				<< dir_out.get_name() << "|"
				<< dir_out.get_fee() << "\n";

			current = current->next;
		}
	}

	return true;

}




// adding service data into hash table 
void Database::add_service(Service &to_add)
{
	add_to_table(ProviderDirectory, prov_dir_size, to_add);
}



// getting info about a service based on number 
void Database::get_service_data(int service_number, Service& copy)
{
	Service *found = find(ProviderDirectory, prov_dir_size, service_number);

	if (!found)
	{
		cerr << "\nservice not found.\n" << endl;
		return;
	}

	copy = *(found); // deference found to copy contents
}



/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *	        RECORDED SERVICES DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/



// Loading in past services data into HT  
bool Database::load_provided_service_data()
{
	ifstream file_in("providedservices.txt");
	if (!file_in)
	{
		cerr << "Could not open providedservices.txt\n";
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING PROVIDED SERVICES ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	string line;
	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		ProvidedService to_add;

		// current date/time
		getline(ss, to_add.current_date_time, '|');

		// service date/time
		getline(ss, to_add.service_data_time, '|');

		// provider number
		getline(ss, temp, '|');
		to_add.provider_number = stoi(temp);

		// member number
		getline(ss, temp, '|');
		to_add.member_number = stoi(temp);

		// service code
		getline(ss, temp, '|');
		to_add.service_code = stoi(temp);

		// comments (full rest of line)
		getline(ss, to_add.comments);

		ProvidedServices.push_back(to_add);
	}

	return true;
}


bool Database::write_provided_service_data()
{
	ofstream file_out("providedservices.txt");
	if (!file_out)
	{
		cerr << "\ncould not open file.\n" << endl;
		return false;
	}

	
	for (const ProvidedService &value : ProvidedServices)
	{
		file_out << value.current_date_time << "|"
			<< value.service_data_time << "|"
			<< value.provider_number << "|"
			<< value.member_number << "|"
			<< value.service_code << "|"
			<< value.comments << "\n";
	}	

	return true;
}


// Adding to the vector
void Database::record_provided_service(ProvidedService &to_add)
{
	ProvidedServices.push_back(to_add);
}



/******************** 
 * testing hash functions, display is not really needed for this
 * ********************/


void Database::display_members()
{
	display(Members,members_size);
}
void Database::display_providers()
{
	display(Providers,providers_size);

}
void Database::display_prov_dir()
{
	display(ProviderDirectory,prov_dir_size);
}


void Database::display_recorded_ser()
{
	for (const ProvidedService &value : ProvidedServices)
	{
		cout << "\nCurrent Date Time: " << value.current_date_time << endl;
		cout << "Service Data Time: " << value.service_data_time << endl;
		cout << "Provider Number: " << value.provider_number << endl;
		cout << "Member Number: " << value.member_number << endl;
		cout << "Service Code: " << value.service_code << endl;
		cout << "Comments: " << value.comments << endl << endl;
	}
}

/******************** SONIA SECTION ********************/










void Database::generate_weekly_report()
{
}

void Database::verify_member(int member_number)
{
	NoEntityFound invalidMember;   // variable to throw
        Member* toVerify = find(Members, members_size, member_number);

        try   // this needs to be caught somewhere
        {
                if (!toVerify)
                        throw invalidMember;      // cout << "\nInvalid Number" << endl;
                else if (toVerify->get_number() == member_number && toVerify->get_status() == "Validated")
                        cout << "\nVerified" << endl;
                else if (toVerify->get_number() == member_number && toVerify->get_status() == "Member Suspended")
                        cout << "\nMember Suspended" << endl;
        }
        catch(NoEntityFound invalidMemberNumber)
        {
                cout << "\nInvalid Number" << endl;
        }

        return;
}

void Database::verify_provider(int provider_number)
{
	NoEntityFound invalidProvider;   // variable to throw
        Provider* toVerify = find(Providers, providers_size, provider_number);

        try   // this needs to be caught somewhere
        {
                if (!toVerify)
                        throw invalidProvider;    // cout << "\nInvalid Number" << endl;
                else if (toVerify->get_number() == provider_number)
                        cout << "\nVerified" << endl;
        }
        catch(NoEntityFound invalidProviderNumber)
        {
                cout << "\nInvalid Number" << endl;
        }

        return;
}

void Database::verify_service(int service_number)
{
	NoServiceFound invalidService;   // variable to throw
        Service* toVerify = find(ProviderDirectory, prov_dir_size, service_number);

        try   // this needs to be caught somewhere
        {
                if (!toVerify)
                        throw invalidService;     // cout << "\nInvalid Number" << endl;
                else if (toVerify->get_number() == service_number)    // ?
                        cout << "\nVerified" << endl;                 // ?
        }
        catch(NoServiceFound invalidServiceNumber)
        {
                cout << "\nInvalid Number" << endl;
        }

        return;
}

// Yasmine
int Database::hash_function(int key_value, int table_size)     // have table_size be prime for better results
{
	// https://www.uoitc.edu.iq/images/documents/informatics-institute/Competitive_exam/DataStructures.pdf
	
	// I can double-check this function, but despite it's simplicity this is actually a good hash function 
	return key_value % table_size;
}
