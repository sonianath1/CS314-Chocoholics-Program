#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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

	if (Members)
		delete [] Members;
	if (Providers)
		delete [] Providers;
	if (ProviderDirectory)
		delete [] ProviderDirectory;

	Members = nullptr;
	Providers = nullptr;
	ProviderDirectory = nullptr;
	members_size = 0;
	prov_dir_size = 0;
	providers_size = 0;

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

	// cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM MEMBER DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

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
	int index = hash_function(member_number, members_size);
	Member* found = find(Members, member_number, index);
	int inputNum{0};
	string inputString{" "};
	address newAddress;

	if (!found) {
		cerr << "\nmember not found\n";
		return;
	}

	cout << "\nUpdating member " << found->get_number() << "...\n";

	// need to implement menu portion for finding out which part 
	// of the member the user wants to update.	
	// Options: name, number, address(street_addr, city, state, zip code), status

	cout << "\nWhich section of this member's information would you like to update?: " << endl;
	cout << "\t1. Name" << endl;
	cout << "\t2. Member Number" << endl;
	cout << "\t3. Address" << endl;
	cout << "\t4. Member Status" << endl;
	cout << "\nEnter the number corresponding to your choice: ";
	cin >> inputNum; cin.ignore(100, '\n');

	switch (inputNum)
	{
		case 1:
			cout << "\nEnter the member's full name: ";
			cin >> inputString; cin.ignore(100, '\n');
			found->set_name(inputString);
			cout << "Member name successfully updated." << endl;
			break;

		case 2:
			cout << "\nEnter the 9-digit member number: ";
			cin >> inputNum; cin.ignore(100, '\n');
			found->set_number(inputNum);
			cout << "Provider number successfully updated." << endl;
			break;

		case 3:
			cout << "Enter the street address: ";
			cin >> newAddress.street_addr; cin.ignore(100, '\n');
			cout << "Enter the city: ";
			cin >> newAddress.city; cin.ignore(100, '\n');
			cout << "Enter the state: ";
			cin >> newAddress.state; cin.ignore(100, '\n');
			cout << "Enter the zip code: ";
			cin >> newAddress.zip_code; cin.ignore(100, '\n');
			found->set_address(newAddress);
			cout << "Provider address successfully updated." << endl;
			break;

		case 4:
			cout << "\nEnter the member status (Choose 'Validated', 'Invalid Number', or 'Member Suspended'): ";
			cin >> inputString; cin.ignore(100, '\n');
			found->set_status(inputString);
			cout << "Member status successfully updated." << endl;
			break;
	}

}



// deleting member from hash table & DB
void Database::delete_member(int member_number)
{
	int index = hash_function(member_number, members_size);
	bool result = find_and_remove(Members, member_number, index);
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

	// cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM PROVIDER DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

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
	address newAddress;

	int index = hash_function(provider_number, providers_size);	
	Provider* found = find(Providers, provider_number, index);

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
		case 3:  // which way should i do it?
			/*cout << "\nWhich section of the provider's address would you like to update?:" << endl;
			  cout << "\t1. Street address" << endl;
			  cout << "\t2. City" << endl;
			  cout << "\t3. State" << endl;
			  cout << "\t4. Zip code" << endl;
			  cout << "\nEnter the number corresponding to your choice: ";
			  cin >> inputNum; cin.ignore(100, '\n');
			  if (inputNum == 1) {
			  cout << "Enter the street address: ";
			  cin >> inputString; cin.ignore(100, '\n');

			  }
			  else if (inputNum == 2) {

			  }
			  else if (inputNum == 3) {

			  }
			  else if (inputNum == 4) {

			  }*/
			cout << "Enter the street address: ";
			cin >> newAddress.street_addr; cin.ignore(100, '\n');
			cout << "Enter the city: ";
			cin >> newAddress.city; cin.ignore(100, '\n');
			cout << "Enter the state: ";
			cin >> newAddress.state; cin.ignore(100, '\n');
			cout << "Enter the zip code: ";
			cin >> newAddress.zip_code; cin.ignore(100, '\n');
			found->set_address(newAddress);
			cout << "Provider address successfully updated." << endl;
			break;

		case 4:   // what kind of service goes here
			cout << "Would you like to add or remove a service for this provider? (1 for add, 2 for remove): ";
			cin >> inputNum; cin.ignore(100, '\n');
			if (inputNum == 1) {

				// enter into vector (?)
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
	int index = hash_function(provider_number, providers_size);
	bool result = find_and_remove(Providers, provider_number, index);
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

	// cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING PROVIDER DIRECTORY DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

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
	int index = hash_function(service_number, prov_dir_size);
	Service *found = find(ProviderDirectory, service_number, index);

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

	// cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING PROVIDED SERVICES ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

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
	//will hold all service data from prodiver directory test fule
	vector<int> service_codes;
	vector<string>service_names;
	vector<double>service_fees;

	//open the provder dictor
	ifstream provider_directory_file("providerdirectory.txt");
	if(!provider_directory_file)
	{
		cout<<"Couldn't open provider dictory text file"<<endl;
	}
	else
	{
		cout<<"Loading data ...."<<endl;
		string input_line;
		//readinf each line until the last one
		while(getline(provider_directory_file, input_line))
		{
			//skip od the no lines
			if(input_line.empty())
				continue;

			stringstream line_stream(input_line);
			string temp;

			int code{0};
			string name;
			double fee{0.0};

			//service code
			if(!getline(line_stream,temp, '|'))
				continue;
			code = stoi(temp);

			//sercue name
			if(!getline(line_stream, name, '|'))
				continue;

			//fee
			if(!getline(line_stream, temp, '|'))
				continue;
			fee = atof(temp.c_str());

			//will store the parsed calues into the vectors
			service_codes.push_back(code);
			service_names.push_back(name);
			service_fees.push_back(fee);

		}
		provider_directory_file.close();
	}




	//open output file
	ofstream report("weekly_report.txt");
	if(!report)
	{
		cout<<"Error:Couldn't create weekly_report.txt"<<endl;

		return;
	}

	report<<"********** ChpcAn Weekly Report **********"<<endl;
	cout<<"             --------------------                "<<endl<<endl;


	//keep wit the total services we provides and total amount
	int total_services = 0;
	double total_fees = 0.0;

	vector<int> unique_member_numbers; //specifically for the unique memebrs
	vector<int> provider_ids;
	vector<double> provider_totals;

	//itelearate though each servuce tht was provided
	for(int i = 0; i < (int)ProvidedServices.size(); i++)
	{
		ProvidedService current_service = ProvidedServices[i];

		int member_number = current_service.member_number;
		int provider_number = current_service.provider_number;
		int service_code = current_service.service_code;

		//lookup member suing fin()
		int m_index = hash_function(member_number, members_size);
		Member* mem = Database::find(Members, member_number, m_index);
		string member_name = "Unknown";
		if(mem != NULL)
			member_name = mem->get_name();


		//looup provider usinf same find()
		int p_index = hash_function(provider_number, providers_size);
		Provider* prov = Database::find(Providers, provider_number, p_index);
		string provider_name = "Unknown";
		if(prov != NULL)
			provider_name = prov->get_name();


		//loopup service


		string service_name = "Unknown";
		double fee = 0.0;

		for(int s = 0; s < (int)service_codes.size(); ++s)
		{
			if(service_codes[s] == service_code)
			{
				service_name = service_names[s];
				fee = service_fees[s];
				break;
			}
		}



		//wrtinr into the report
		report <<"Service Date: "<<current_service.service_data_time<<endl;
		report <<"Member: "<<member_number<<"-"<< member_name <<endl;
		report <<"Provider: "<<provider_number <<"-"<<provider_name<<endl;
		report <<"Service: "<<service_code<< "-" <<service_name<<endl;
		report <<"Fee: "<<fee<<" $ "<<endl;

		if(!current_service.comments.empty())
			report<<"Comments: "<< current_service.comments<<endl;

		report<<"---------------------------------------------------------"<<endl;

		//update overall totals
		total_services ++;
		total_fees += fee;


		//back to unique memebrs
		bool unique = false;

		for(int j = 0; j <(int)unique_member_numbers.size(); ++j)
		{
			if(unique_member_numbers[j] == member_number)
			{
				unique = true;
				break;
			}
		}
		if(!unique)
		{
			unique_member_numbers.push_back(member_number);
		}

		int provider_index = -1;

		for(int k = 0; k < (int)provider_ids.size(); ++k)
		{
			if(provider_ids[k] == provider_number)
			{
				provider_index = k;
				break;
			}
		}
		if(provider_index == -1)
		{
			provider_ids.push_back(provider_number);
			provider_totals.push_back(fee);
		}
		else
		{
			provider_totals[provider_index] += fee;
		}

	}

	//sdisplay the overal summary total section
	report <<"\n";
	report <<"Total Number of services : "<< total_services<<endl;
	report <<"Unique Members served    : "<< unique_member_numbers.size()<<endl;
	report <<"Total Fees for the week  : "<< total_fees<< "$"<<endl<<endl;
	report <<"  EFT Summary per provider"<<endl;
	report <<"--------------------------------------------------------------------------------"<<endl;


	//goes thorufh each provider who provided the service
	for(int i = 0; i <(int)provider_ids.size(); ++i)
	{
		int provider_number = provider_ids[i];
		double total_amount = provider_totals[i];

		int p_index = hash_function(provider_number, providers_size);
		Provider *provider_ptr = find(Providers, provider_number, p_index);
		string provider_name = "unknown";

		if(provider_ptr != NULL)
		{
			provider_name = provider_ptr->get_name();
		}

		report <<"Provider: "<< provider_number<<", "<<provider_name<<endl;
		report <<"Total Amount: "<<total_amount<<"$"<<endl;

	}
	report <<"End of the weekly report"<<endl<<endl;

	report.close();

}




void Database::verify_member(int member_number)
{
	NoEntityFound invalidMember;   // variable to throw
	int index = hash_function(member_number, members_size);
	Member* toVerify = find(Members, member_number, index);

	try   // this needs to be caught somewhere; can be caught in find(), ask Sonia
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
	NoEntityFound invalidProvider;   // variable to thro
	int index = hash_function(provider_number, providers_size);
	Provider* toVerify = find(Providers, provider_number, index);

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
	int index = hash_function(service_number, prov_dir_size);
	Service* toVerify = find(ProviderDirectory, service_number, index);

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
	// ^ for reference on hash functions 

	// Despite it's simplicity this is actually a good hash function 
	return key_value % table_size;
}
