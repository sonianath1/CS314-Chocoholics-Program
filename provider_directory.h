/*******************************************************************************
Chocoholics CS314 Program: Provider Directory Interface
Names: Yollaine Brooks, 
Description of Program: 
*********************************************************************************/

#include <string>
#include <vector>

// Service Struct
// Holds data from the Provider directory
struct service
{
	std::string name;	// name of the service (max size 20)
	int code;	// 6 digit code
	float fee;	// max of 999.99
};

class ProviderDirectory
{
	public:
		ProviderDirectory();	// constructor
		~ProviderDirectory();	// destructor
		void load_data();	// load data from file
		void get_service_data(service & copy);
	private:
		std::vector<service> services;

}
