#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "database.h"
using namespace std;


// Smoke test if each data member initialized properly
void DatabaseTest::constructor_test()
{
	Database test_db;
	cout << "Constructor Test\n";
	assert(test_db.members_size == 10);
	assert(test_db.providers_size == 10);
	assert(test_db.prov_dir_size == 10);
	assert(test_db.Members != nullptr);
	assert(test_db.Providers != nullptr);
	assert(test_db.ProviderDirectory != nullptr);
}

// Smoke test if each member is destructed properly
void DatabaseTest::destructor_test()
{
	Database test_db;
	cout << "Destructor Test\n";
	Database local_db;
	local_db.~Database();
	assert(test_db.members_size == 0 && "Size should be reset to 0");
	assert(test_db.providers_size == 0 && "Size should be reset to 0");
	assert(test_db.prov_dir_size == 0 && "Size should be reset to 0");
	assert(test_db.Members == nullptr && "Destructor expected to make all pointers nullptr");
	assert(test_db.Providers == nullptr && "Destructor expected to make all pointers nullptr");
	assert(test_db.ProviderDirectory == nullptr && "Destructor expected to make all pointers nullptr");
}

void DatabaseTest::read_from_file_test()
{
	cout << "Read File Test\n";
	load_member_test();
	load_provider_test();
	load_provider_directory_test();
	load_provider_directory_test();
}

void DatabaseTest::write_to_file_test()
{

}

void DatabaseTest::load_member_test()
{
	cout << "\tLoad Members Test" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;

	assert(first_db.load_member_data() && "Unable to load members.txt!");

	// create a child process that changes the name of members.txt to another name
	int status;
	pid_t pid;
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "members.txt", "gobbly.txt", (char *) NULL);
		perror("Unable to rename members.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
	cout << "\t\tIncorrect File\n";
	assert(first_db.load_member_data() == false && "Incorrect file read-in not returning false");

	// change back the name of members.txt
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "gobbly.txt", "members.txt", (char *) NULL);
		perror("Unable to rename members.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		int status = 0;
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
}

void DatabaseTest::write_member_test()
{
	cout << "\tWrite Member Test\n";
	// 1. check if it actually wrote out
	//      a new member needs to be added
	//      then write it out
	//      compare the current member.txt to the original file member.txt
	//      done by forking and exec'ing (run diff or cmp or something)
	//      then check the status. diff returns 0 on same, 1 on not the same
	//      we want diff to return that they're not the same, meaning the file was
	//      actually modified.
	// 2. check if it wrote out the correct stuff
	//      create text files that have the correct output to be written
	//      compare the written file to the correct one via diff
}

void DatabaseTest::add_member_test()
{

}

void DatabaseTest::update_member_test()
{

}

void DatabaseTest::delete_member_test()
{

}

void DatabaseTest::load_provider_test()
{
	cout << "\tLoad Providers Test" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;

	assert(first_db.load_provider_data() && "Unable to load providers.txt!");

	// create a child process that changes the name of providers.txt to another name
	int status;
	pid_t pid;
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "providers.txt", "gobbly.txt", (char *) NULL);
		perror("Unable to rename providers.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
	cout << "\t\tIncorrect File\n";
	assert(first_db.load_provider_data() == false && "Incorrect file read-in not returning false");

	// change back the name of providers.txt
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "gobbly.txt", "providers.txt", (char *) NULL);
		perror("Unable to rename providers.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		int status = 0;
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
}

void DatabaseTest::write_provider_test()
{
}

void DatabaseTest::add_provider_test()
{

}

void DatabaseTest::update_provider_test()
{

}

void DatabaseTest::delete_provider_test()
{
}

void DatabaseTest::load_provider_directory_test()
{
	cout << "\tLoad Provider Directory Test" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;

	assert(first_db.load_provider_directory_data() && "Unable to load providerdirectory.txt!");

	// create a child process that changes the name of providerdirectory.txt to another name
	int status;
	pid_t pid;
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "providerdirectory.txt", "gobbly.txt", (char *) NULL);
		perror("Unable to rename providerdirectory.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
	cout << "\t\tIncorrect File\n";
	assert(first_db.load_provider_directory_data() == false && "Incorrect file read-in not returning false");

	// change back the name of providerdirectory.txt
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "gobbly.txt", "providerdirectory.txt", (char *) NULL);
		perror("Unable to rename providerdirectory.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		int status = 0;
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
}

void DatabaseTest::write_provider_directory_test()
{
}

void DatabaseTest::add_service_test()
{

}

void DatabaseTest::get_service_data_test()
{

}

void DatabaseTest::generate_weekly_report_test()
{
}

void DatabaseTest::load_provided_service_test()
{
	cout << "\tLoad Provided Services Test" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;

	assert(first_db.load_provided_service_data() && "Unable to load providedservices.txt!");

	// create a child process that changes the name of providedservices.txt to another name
	int status;
	pid_t pid;
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "providedservices.txt", "gobbly.txt", (char *) NULL);
		perror("Unable to rename providedservices.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
	cout << "\t\tIncorrect File\n";
	assert(first_db.load_provided_service_data() == false && "Incorrect file read-in not returning false");

	// change back the name of providedservices.txt
	pid = fork();
	if (0 == pid)   /* Child process */
	{
		status = execlp("mv", "mv", "gobbly.txt", "providedservices.txt", (char *) NULL);
		perror("Unable to rename providedservices.txt to gobbly.txt");
		_exit(EXIT_FAILURE);
	}
	else            /* Parent process */
	{
		int status = 0;
		pid_t cpid = wait(&status);
		cerr << "pid: " << cpid << " status: " << status << endl;
	}
}

void DatabaseTest::write_provided_service_test()
{
}

void DatabaseTest::record_provided_service_test()
{

}

void DatabaseTest::verify_member_test()
{
}

void DatabaseTest::verify_provider_test()
{
}

void DatabaseTest::verify_service_test()
{
}

void DatabaseTest::hash_function_test()
{
}

void DatabaseTest::member_remove_all_test()
{

}
void DatabaseTest::member_add_to_table_test()
{

}
void DatabaseTest::member_remove_LLL_test()
{

}
void DatabaseTest::member_table_find_test()
{

}
void DatabaseTest::member_LLL_find_test()
{

}
void DatabaseTest::member_table_find_remove_test()
{

}
void DatabaseTest::member_LLL_find__remove_test()
{

}
void DatabaseTest::provider_remove_all_test()
{

}
void DatabaseTest::provider_add_to_table_test()
{

}
void DatabaseTest::provider_remove_LLL_test()
{

}
void DatabaseTest::provider_table_find_test()
{

}
void DatabaseTest::provider_LLL_find_test()
{

}
void DatabaseTest::provider_table_find_remove_test()
{

}
void DatabaseTest::provider_LLL_find__remove_test()
{

}
void DatabaseTest::provider_directory_remove_all_test()
{

}
void DatabaseTest::provider_directory_add_to_table_test()
{

}
void DatabaseTest::provider_directory_remove_LLL_test()
{

}
void DatabaseTest::provider_directory_table_find_test()
{

}
void DatabaseTest::provider_directory_LLL_find_test()
{

}
void DatabaseTest::provider_directory_table_find_remove_test()
{

}
void DatabaseTest::provider_directory_LLL_find__remove_test()
{

}

// ---------------------------------------------------
// ---------------- SERVICE TESTS --------------------
// ---------------------------------------------------

void ServiceTest::default_constructor_test()
{

}

void ServiceTest::constructor_test()
{

}

void ServiceTest::get_number_test()
{

}

void ServiceTest::set_name_test()
{

}

void ServiceTest::set_fee_test()
{

}

void ServiceTest::set_code_test()
{

}

void ServiceTest::get_name_test()
{

}

void ServiceTest::get_fee_test()
{

}

void ServiceTest::display_all_test()
{

}
