/*******************************************************************************
Chocoholics CS314 Program: Database Interface
Names: Yollaine Brooks, 
Description of Program: 
*********************************************************************************/

#include <fstream>
#include "entities.h"
#include "node.h"
#include "error.h"

// Service Struct
// Holds data from the Provider directory
struct Service
{
	std::string name;	// name of the service (max size 20)
	int code;			// 6 digit code
	float fee;			// max of 999.99
};

// ProvidedService Struct
struct ProvidedService
{
	std::string current_date_time;	// current date and time
	std::string service_data_time;	// date and time service was provided
	int provider_number;			// provider number
	int member_number;				// member number
	int service_code;				// service code number
	std::string comments = "";		// optional comments
};

// EFTFile
// stores data sent as an EFT in the weekly report
struct EFTFile
{
	std::string provider_name;	// provider's name
	int provider_number;		// provider number
	int transfer_amount;		// fee to be transferred
};

// Database Class
class Database
{
	public:
		Database(int size_members = 10, int size_providers = 10, 
			     int size_prov_dir = 10);							// constructor
		~Database();												// destructor
		void load_data();											// load data from file
		void add_member(Member &);									// add member to the member table
		void update_member(int member_number);						// update specific member based on number
		void delete_member(int member_number);						// delete member based on number
		void add_provider(Provider &);								// add provider to the provider table
		void update_provider(int provider_number);					// update specific provider based on number
		void delete_provider(int provider_number);					// delete provider based on number
		void record_provided_service(ProvidedService &);			// insert provided service into table
		void get_service_data(int service_number, Service & copy);	// service to get from Providerdirectory
		void generate_weekly_report();								// create the manager's weekly report
        friend class DatabaseTest;                                  // friend database testing class

	private:
		void verify_member(int member_number);		// verify that a member exists
		void verify_provider(int provider_number);	// verify that a provider exists
		void verify_service(int service_number);	// verify that a service exists

		void hash_function(string & key_value);		// has function 
		node<Member> **Members;						// member hash table
		int members_size;							// size of member hash table

		node<Provider> **Providers;					// provider hash table
		int providers_size;							// size of provider hash table

		node<Service> **ProviderDirectory;			// provider directory hash table
		int prov_dir_size;							// size of provider directory hash table

		std::vector<ProvidedService> ProvidedServices;	// vector of provided services

};

class DatabaseTest
{
    public:
        void constructor_test();
        void load_data_test();
        void add_member_test();
        void update_member_test();
        void delete_member_test();
        void add_provider_test();
        void update_provider_test();
        void record_provided_service_test();
        void get_service_data_test();
        void generate_weekly_report_test();
};
