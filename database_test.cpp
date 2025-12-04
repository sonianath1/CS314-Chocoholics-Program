#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#include "database.h"
using namespace std;


// Smoke test if each data member initialized properly
void DatabaseTest::constructor_test()
{
	Database test_db;
	cout << "\n---Constructor Test---\n";
	assert(test_db.members_size == 10);
	assert(test_db.providers_size == 10);
	assert(test_db.prov_dir_size == 10);
	assert(test_db.Members != nullptr);
	assert(test_db.Providers != nullptr);
	assert(test_db.ProviderDirectory != nullptr);
}

void DatabaseTest::read_from_file_test()
{
    cout << "\n---Read File Test---\n";
    load_member_test();
    load_provider_test();
    load_provider_directory_test();
    load_provided_service_test();
}


void DatabaseTest::write_to_file_test()
{
    cout << "\n---Write File Test---\n";
    write_member_test();
    write_provider_test();
    write_provider_directory_test();
    write_provided_service_test();
}

// --------------------------------------------------
// ---------------- MEMBER TESTS --------------------
// --------------------------------------------------


void DatabaseTest::load_member_test()
{
	cout << "\n---Load Members Test---" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;
    first_db.remove_all(first_db.Members, first_db.members_size);

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
    cout << "\n---Write Member Test---\n";
    Database test_db; 
    int status;

    cout << "Making clean database...\n";
    // delete the database
    test_db.remove_all(test_db.Members, test_db.members_size);

    cout << "Ensuring clean members.txt\n";
    // delete members.txt
    int pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "members.txt");
        perror("error deleting members.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        // it just needs to delete it if it exists
    }

    // replace members.txt with the original members.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "test_txt/members_1.txt", "members.txt", (char *) NULL);
        perror("error resetting members.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure test_txt/members_1.txt exists");
    }

    // loading information from members
    cout << "Loading data from members.txt\n";
    test_db.load_member_data();

    test_db.write_member_data();

    cout << "Comparing files...\n";
    // test if the baseline is correct
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("./test_scripts/write_entities.bash", "./test_scripts/write_entities.bash", "test_txt/members_1.txt", "members.txt", (char *) NULL);
        perror("error diffing members.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Expected output members.txt not matching expected members.txt");
    }

    // delete members_1.txt
    pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "-f", "members.txt", (char *) NULL);
        perror("error deleting members.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        assert(status == 0 && "Unable to restore members.txt");
    }

    // replace with the original members.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "original_txt/members.txt", "members.txt", (char *) NULL);
        perror("error resetting members.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure original_txt/members.txt exists");
    }
}

void DatabaseTest::add_member_test()
{
    cout << "\n---Add Member Test---" << endl;

    // info was already verified by the terminal
    Database test_db;
    Member test_member;
    address test_addr;
    string name = "TEST";
    test_addr.city = "Likely";
    test_addr.state = "CA";
    test_addr.street_addr = "123 Apple Dr.";
    test_addr.zip_code = 80459;
    int number = 900000002;
    string status = "Active";
    
    test_member.set_name(name);
    test_member.set_address(test_addr);
    test_member.set_number(number);
    test_member.set_status(status);

    // delete the database
    test_db.remove_all(test_db.Members, test_db.members_size);

    // remake the size
    test_db.members_size = 10;
    test_db.add_member(test_member);

    // ensure it was put into the correct place
    assert(test_db.Members[2] != nullptr && "Member isn't being put in the correct place");

    // ensure that duplicates aren't added 
    try
    {
        test_db.add_member(test_member);
    }
    catch(DuplicateEntity err)
    {
        cerr << err.msg;
    }
    
    
    assert(test_db.Members[2]->next == nullptr && "Duplicates aren't allowed in the database");
}

void DatabaseTest::update_member_test()
{
    cout << "\n---Update Member Test---\n";
    // info was already verified by the terminal
    Database test_db;
    Member test_member;
    address test_addr;
    string name = "TEST";
    test_addr.city = "Likely";
    test_addr.state = "CA";
    test_addr.street_addr = "123 Apple Dr.";
    test_addr.zip_code = 80459;
    int number = 900000002;
    string status = "Active";
    
    test_member.set_name(name);
    test_member.set_address(test_addr);
    test_member.set_number(number);
    test_member.set_status(status);

    // delete the database
    test_db.remove_all(test_db.Members, test_db.members_size);

    // remake the size
    test_db.members_size = 10;
    test_db.add_member(test_member);

    // populate the stream with premade inputs
    istringstream iss_name("1\nOTTER");
    istringstream iss_number("2\n900000003");
    istringstream iss_addr("3\n203 NE Corner Blvd\n\nColden\n\nWA\n\n53984");
    istringstream iss_stat("4\nInvalid Number");
    

    
    // update the member's name
    cin.rdbuf(iss_name.rdbuf());
    test_db.update_member(number);

    // update the member's address
    cin.rdbuf(iss_addr.rdbuf());
    test_db.update_member(number);

    // update the status of the member
    cin.rdbuf(iss_stat.rdbuf());
    test_db.update_member(number);
    
    // update the member's number
    cin.rdbuf(iss_number.rdbuf());
    test_db.update_member(number);


    assert(test_db.Members[2]->data.get_name() == "OTTER" && "Member wasn't updated properly");
    assert(test_db.Members[2]->data.get_address().city == "Colden" && "Member wasn't updated properly");
    assert(test_db.Members[2]->data.get_address().state == "WA" && "Member wasn't updated properly");
    assert(test_db.Members[2]->data.get_address().street_addr == "203 NE Corner Blvd" && "Member wasn't updated properly");
    assert(test_db.Members[2]->data.get_address().zip_code == 53984 && "Member wasn't updated properly");
    assert(test_db.Members[2]->data.get_number() == 900000003 && "Member wasn't updated properly");
    assert(test_db.Members[2]->data.get_status() == "Invalid Number" && "Member wasn't updated properly");
}

void DatabaseTest::delete_member_test()
{
    cout << "\n---Delete Member Test---\n";
    // info was already verified by the terminal
    Database test_db;
    Member test_member;
    address test_addr;
    string name = "TEST";
    test_addr.city = "Likely";
    test_addr.state = "CA";
    test_addr.street_addr = "123 Apple Dr.";
    test_addr.zip_code = 80459;
    int number = 900000002;
    string status = "Active";
    
    test_member.set_name(name);
    test_member.set_address(test_addr);
    test_member.set_number(number);
    test_member.set_status(status);

    // delete the database
    test_db.remove_all(test_db.Members, test_db.members_size);

    // remake the size
    test_db.members_size = 10;
    test_db.add_member(test_member);

    assert(test_db.Members[2] != nullptr && "Member isn't being put in the correct place");

    // delete the member
    test_db.delete_member(number);

    assert(test_db.Members[2] == nullptr && "Member wasn't deleted properly");

    // try to delete member that doesnt exist

    bool failed = false;
    try
    {
        test_db.delete_member(number);
    }
    catch(NoEntityFound err)
    {
        failed = true;
    }

    assert(failed == true && "Deleting non-existent member expected NoEntityFound exception thrown");
    
}

// ----------------------------------------------------
// ---------------- PROVIDER TESTS --------------------
// ----------------------------------------------------


void DatabaseTest::load_provider_test()
{
	cout << "\n---Load Providers Test---" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;
    first_db.remove_all(first_db.Providers, first_db.providers_size);

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
    cout << "\n---Write Provider Test---\n";
    Database test_db; 
    int status;

    cout << "Making clean database...\n";
    // delete the database
    test_db.remove_all(test_db.Providers, test_db.providers_size);

    cout << "Ensuring clean providers.txt\n";
    // delete providers.txt
    int pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "providers.txt");
        perror("error deleting providers_1.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        // it just needs to delete it if it exists
    }

    // replace providers.txt with the original providers.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "test_txt/providers_1.txt", "providers.txt", (char *) NULL);
        perror("error resetting providers.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure test_txt/providers_1.txt exists");
    }

    // loading information from providers
    cout << "Loading data from providers.txt\n";
    test_db.load_provider_data();

    test_db.write_provider_data();

    cout << "Comparing files...\n";
    // test if the baseline is correct
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("./test_scripts/write_entities.bash", "./test_scripts/write_entities.bash", "test_txt/providers_1.txt", "providers.txt", (char *) NULL);
        perror("error diffing providers.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Expected output providers.txt not matching expected providers.txt");
    }

    // delete providers_1.txt
    pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "-f", "providers.txt", (char *) NULL);
        perror("error deleting providers.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        assert(status == 0 && "Unable to restore providers.txt");
    }

    // replace with the original providers.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "original_txt/providers.txt", "providers.txt", (char *) NULL);
        perror("error resetting providers.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure original_txt/providers.txt exists");
    }
}

void DatabaseTest::add_provider_test()
{
    cout << "\n---Add Provider Test---" << endl;

    // info was already verified by the terminal
    Database test_db;
    Provider test_provider;
    address test_addr;
    string name = "TEST";
    test_addr.city = "Likely";
    test_addr.state = "CA";
    test_addr.street_addr = "123 Apple Dr.";
    test_addr.zip_code = 80459;
    int number = 700000002;
    int service = 100500;
    
    test_provider.set_name(name);
    test_provider.set_address(test_addr);
    test_provider.set_number(number);
    test_provider.add_service(service);

    // delete the database
    test_db.remove_all(test_db.Providers, test_db.providers_size);

    // remake the size
    test_db.providers_size = 10;
    test_db.add_provider(test_provider);

    // ensure it was put into the correct place
    assert(test_db.Providers[2] != nullptr && "Provider isn't being put in the correct place");

    // ensure that duplicates aren't added 
    try
    {
        test_db.add_provider(test_provider);
    }
    catch(DuplicateEntity err)
    {
        cerr << "Duplicate was found in Providers!\n";
    }
    
    assert(test_db.Providers[2]->next == nullptr && "Duplicates aren't allowed in the database");

}

void DatabaseTest::update_provider_test()
{
    cout << "\n---Update Provider Test---" << endl;

    // info was already verified by the terminal
    Database test_db;
    Provider test_provider;
    address test_addr;
    string name = "TEST";
    test_addr.city = "Likely";
    test_addr.state = "CA";
    test_addr.street_addr = "123 Apple Dr.";
    test_addr.zip_code = 80459;
    int number = 700000002;
    int service = 100500;
    
    test_provider.set_name(name);
    test_provider.set_address(test_addr);
    test_provider.set_number(number);
    test_provider.add_service(service);

    // delete the database
    test_db.remove_all(test_db.Members, test_db.members_size);

    // remake the size
    test_db.providers_size = 10;
    test_db.add_provider(test_provider);

    // populate the stream with premade inputs
    istringstream iss_name("1\nOTTER");
    istringstream iss_number("2\n700000003");
    istringstream iss_addr("3\n203 NE Corner Blvd\n\nColden\n\nWA\n\n53984");
    istringstream iss_service("4\n100400");
    
    // update the provider's name
    cin.rdbuf(iss_name.rdbuf());
    test_db.update_provider(number);

    // update the provider's address
    cin.rdbuf(iss_addr.rdbuf());
    test_db.update_provider(number);

    // update the services of the provider
    cin.rdbuf(iss_service.rdbuf());
    test_db.update_provider(number);

    // update the provider's number
    cin.rdbuf(iss_number.rdbuf());
    test_db.update_provider(number);


    assert(test_db.Providers[2]->data.get_name() == "OTTER" && "Provider wasn't updated properly");
    assert(test_db.Providers[2]->data.get_address().city == "Colden" && "Provider wasn't updated properly");
    assert(test_db.Providers[2]->data.get_address().state == "WA" && "Provider wasn't updated properly");

    assert(test_db.Providers[2]->data.get_address().street_addr == "203 NE Corner Blvd" && "Provider wasn't updated properly");
    assert(test_db.Providers[2]->data.get_address().zip_code == 53984 && "Provider wasn't updated properly");
    assert(test_db.Providers[2]->data.get_number() == 700000003 && "Provider wasn't updated properly");
    assert(test_db.Providers[2]->data.get_services()[1] == 100400 && "Provider wasn't updated properly");

}

void DatabaseTest::delete_provider_test()
{
    cout << "\n---Delete Provider Test---\n";
    // info was already verified by the terminal
    Database test_db;
    Member test_member;
    address test_addr;
    string name = "TEST";
    test_addr.city = "Likely";
    test_addr.state = "CA";
    test_addr.street_addr = "123 Apple Dr.";
    test_addr.zip_code = 80459;
    int number = 900000002;
    string status = "Active";
    
    test_member.set_name(name);
    test_member.set_address(test_addr);
    test_member.set_number(number);
    test_member.set_status(status);

    // delete the database
    test_db.remove_all(test_db.Members, test_db.members_size);

    // remake the size
    test_db.members_size = 10;
    test_db.add_member(test_member);

    assert(test_db.Members[2] != nullptr && "Member isn't being put in the correct place");

    // delete the member
    test_db.delete_member(number);

    assert(test_db.Members[2] == nullptr && "Member wasn't deleted properly");

    // try to delete member that doesnt exist

    bool failed = false;
    try
    {
        test_db.delete_member(number);
    }
    catch(NoEntityFound err)
    {
        failed = true;
    }

    assert(failed == true && "Deleting non-existent member expected NoEntityFound exception thrown");
    
}

// --------------------------------------------------------------
// ---------------- PROVIDER DIRECTORY TESTS --------------------
// --------------------------------------------------------------


void DatabaseTest::load_provider_directory_test()
{
	cout << "\n---Load Provider Directory Test---\n" << endl;
	cout << "\t\tCorrect File\n";
	Database first_db;
    first_db.remove_all(first_db.ProviderDirectory, first_db.prov_dir_size);

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
    cout << "\n---Write Provider Directory Test---\n";
    Database test_db; 
    int status;

    cout << "Making clean database...\n";
    // delete the database
    test_db.remove_all(test_db.ProviderDirectory, test_db.prov_dir_size);

    cout << "Ensuring clean providerdirectory.txt\n";
    // delete providerdirectory.txt
    int pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "providerdirectory.txt");
        perror("error deleting providerdirectory_1.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        // it just needs to delete it if it exists
    }

    // replace providerdirectory.txt with the original providerdirectory.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "test_txt/providerdirectory_1.txt", "providerdirectory.txt", (char *) NULL);
        perror("error resetting providerdirectory.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure test_txt/providerdirectory_1.txt exists");
    }

    // loading information from providerdirectory
    cout << "Loading data from providerdirectory.txt\n";
    test_db.load_provider_directory_data();

    test_db.write_provider_directory_data();

    cout << "Comparing files...\n";
    // test if the baseline is correct
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("./test_scripts/write_entities.bash", "./test_scripts/write_entities.bash", "test_txt/providerdirectory_1.txt", "providerdirectory.txt", (char *) NULL);
        perror("error diffing providerdirectory.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Expected output providerdirectory.txt not matching expected providerdirectory.txt");
    }

    // delete providerdirectory_1.txt
    pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "-f", "providerdirectory.txt", (char *) NULL);
        perror("error deleting providerdirectory.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        assert(status == 0 && "Unable to restore providerdirectory.txt");
    }

    // replace with the original providerdirectory.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "original_txt/providerdirectory.txt", "providerdirectory.txt", (char *) NULL);
        perror("error resetting providerdirectory.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure original_txt/providerdirectory.txt exists");
    }
}

void DatabaseTest::add_service_test()
{
    cout << "\n---Add Service Test---\n" << endl;

    // info was already verified by the terminal
    Database test_db;
    Service test_service;
    string name = "TEST";
    int service = 100502;
    float fee = 25.35;
    
    test_service.set_code(service);
    test_service.set_fee(fee);
    test_service.set_name(name);

    // delete the database
    test_db.remove_all(test_db.ProviderDirectory, test_db.prov_dir_size);

    // remake the size
    test_db.prov_dir_size = 10;
    test_db.add_service(test_service);

    // ensure it was put into the correct place
    assert(test_db.ProviderDirectory[2] != nullptr && "Service isn't being put in the correct place");

    // ensure that duplicates aren't added 
    try
    {
        test_db.add_service(test_service);
    }
    catch(DuplicateEntity err)
    {
        cerr << err.msg;
    }
    
    assert(test_db.ProviderDirectory[2]->next == nullptr && "Duplicates aren't allowed in the database");
}

void DatabaseTest::get_service_data_test()
{
    cout << "\n---Get Service Data Test---\n" << endl;
    Database test_db;

    // get service that exists
    Service the_service;
    Service empty_service;

    cout << "Getting Service from Database";
    test_db.get_service_data(100900, the_service);

    assert(the_service.get_name() == "Stress Management" && "Did not retrieve the correct service");

    // get service that doesnt exist
    try
    {
        test_db.get_service_data(494837, empty_service);
    }
    catch(NoEntityFound err)
    {
        cerr << err.msg << endl;
    }
    
    // try to overwrite a service
    test_db.get_service_data(100400, the_service);

    assert(the_service.get_name() == "Dietitian Consult" && "Did not correctly overwrite the_service");
}

// --------------------------------------------------------
// ---------------- WEEKLY REPORT TEST --------------------
// --------------------------------------------------------

void DatabaseTest::generate_weekly_report_test()
{
    cout << "\n---Generate Weekly Report Test---\n";
    Database test_db; 
    int status;

    // delete weekly_report.txt and EFT_report.txt
    int pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "weekly_report.txt");
        perror("error deleting weekly_report.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        // it just needs to delete it if it exists
    }

    pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "EFT_report.txt");
        perror("error deleting EFT_report.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        // it just needs to delete it if it exists
    }
    
    test_db.generate_weekly_report();
    // ensure eft report and weekly report get created

    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("./test_scripts/check_weekly_report.bash", "./test_scripts/check_weekly_report.bash", (char *) NULL);
        perror("error checking if report files exist");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Weekly Report or EFT report was not created");
    }
}

// -----------------------------------------------------------
// ---------------- PROVIDED SERVICE TEST --------------------
// -----------------------------------------------------------


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
    cout << "\n---Write Provided Service Test---\n";
    Database test_db; 
    int status;

    cout << "Making clean database...\n";

    // delete the database
    test_db.ProvidedServices.clear();

    cout << "Ensuring clean providedservices.txt\n";
    // delete providedservices.txt
    int pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "providedservices.txt");
        perror("error deleting providedservices_1.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        // it just needs to delete it if it exists
    }

    // replace providedservices.txt with the original providedservices.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "test_txt/providedservices_1.txt", "providedservices.txt", (char *) NULL);
        perror("error resetting providedservices.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure test_txt/providedservices_1.txt exists");
    }

    // loading information from providedservices
    cout << "Loading data from providedservices.txt\n";
    test_db.load_provided_service_data();

    test_db.write_provided_service_data();

    cout << "Comparing files...\n";
    // test if the baseline is correct
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("./test_scripts/write_entities.bash", "./test_scripts/write_entities.bash", "test_txt/providedservices_1.txt", "providedservices.txt", (char *) NULL);
        perror("error diffing providedservices.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Expected output providedservices.txt not matching expected providedservices.txt");
    }

    // delete providedservices_1.txt
    pid = fork();
    if (0 == pid)
    {
        status = execlp("rm", "rm", "-f", "providedservices.txt", (char *) NULL);
        perror("error deleting providedservices.txt");
        _exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        assert(status == 0 && "Unable to restore providedservices.txt");
    }

    // replace with the original providedservices.txt
    pid = fork();
    if (0 == pid)       /* Child Process */
    {
        status = execlp("cp", "cp", "-f", "original_txt/providedservices.txt", "providedservices.txt", (char *) NULL);
        perror("error resetting providedservices.txt");
        _exit(EXIT_FAILURE);
    }
    else                /* Parent Process */
    {
        wait(&status);
        assert(status == 0 && "Ensure original_txt/providedservices.txt exists");
    }
}

void DatabaseTest::record_provided_service_test()
{
    cout << "\n---Record Provided Service Test---\n";
    Database test_db;
    ProvidedService ps;

    ps.current_date_time = "11-14-2025 09:14:22";
    ps.service_data_time = "11-10-2025";
    ps.provider_number = 900123456;
    ps.member_number = 100400;

    test_db.record_provided_service(ps);

    assert(test_db.ProvidedServices.back().current_date_time == "11-14-2025 09:14:22" && "Did not properly record the provided service");
}

// ---------------------------------------------------
// ---------------- VERIFY TESTS --------------------
// ---------------------------------------------------

void DatabaseTest::verify_member_test()
{
    Database test_db;
    int validMember = 900887990;
    int invalidMember = 323;
    int suspendedMember = 900901234;

    cout << "\n---Verify member test---" << endl;
    
    cout << "The following tests should print 'Verified', 'Invalid Member', and 'Member Suspended', respectively." << endl; 
    assert(test_db.verify_member(validMember) == true);  // should return true
    assert(test_db.verify_member(invalidMember) == false);   // should return false
    assert(test_db.verify_member(suspendedMember) == false);   // should return false

    return;
}

void DatabaseTest::verify_provider_test()
{
    Database test_db;
    int validProvider = 700567890;
    int invalidProvider = 323;

    cout << "\n0---Verify provider test---" << endl;
    
    cout << "The following tests should print 'Verified' and 'Invalid Number', respectively." << endl; 
    assert(test_db.verify_provider(validProvider) == true);  // should return true
    assert(test_db.verify_provider(invalidProvider) == false);   // should return false

    return;
}

void DatabaseTest::verify_service_test()
{
    Database test_db;
    int validService = 100900;
    int invalidService = 323;

    cout << "\n---Verify service test---" << endl;
    
    cout << "The following tests should print 'Service: Stress Management' and 'Invalid Number', respectively." << endl; 
    assert(test_db.verify_provider(validService) == true);  // should return true
    assert(test_db.verify_provider(invalidService) == false);   // should return false

    return;
}

void DatabaseTest::hash_function_test()
{
	// tests that the hash function returns a hash between 0 and table_size (inclusive)
	// for normal and big numbers with each of the 3 tables
    	Database test_db;
	int normalNum = 12;
	int bigNum = 999999999;
	int hash = 0;

	cout << "\n---Hash function test---" << endl;

	hash = test_db.hash_function(normalNum, test_db.members_size); 
	assert(hash >= 0 && hash < test_db.members_size);
	hash = test_db.hash_function(bigNum, test_db.members_size); 
	assert(hash >= 0 && hash < test_db.members_size);

	hash = test_db.hash_function(normalNum, test_db.providers_size); 
	assert(hash >= 0 && hash < test_db.providers_size);
	hash = test_db.hash_function(bigNum, test_db.providers_size); 
	assert(hash >= 0 && hash < test_db.providers_size);

	hash = test_db.hash_function(normalNum, test_db.prov_dir_size); 
	assert(hash >= 0 && hash < test_db.prov_dir_size);
	hash = test_db.hash_function(bigNum, test_db.prov_dir_size); 
	assert(hash >= 0 && hash < test_db.prov_dir_size);

	return;
}

// ---------------------------------------------------
// ---------------- SERVICE TESTS --------------------
// ---------------------------------------------------

void ServiceTest::default_constructor_test()  
{
    Service test_service;
    cout << "\n---Service default constructor test---" << endl;
    assert(test_service.name == "");
    assert(test_service.number == 0);
    // assert(test_service.fee == 0.0);
    assert(abs(test_service.fee - 0.0) < 1e-9);   

    return;
}

void ServiceTest::constructor_test()
{
    float comparison = 45.99;
    Service test_service("Name", 700899, 45.99);
    cout << "\n---Service arg constructor test---" << endl;
    assert(test_service.name == "Name");
    assert(test_service.number == 700899);
    // Source for below: https://www.geeksforgeeks.org/dsa/problem-in-comparing-floating-point-numbers-and-how-to-compare-them-correctly/
    assert(abs(test_service.fee - comparison) < 0.0000000001);    // same idea as assert(test_service.fee == 45.99) but for floats
    return;
}

void ServiceTest::get_number_test()
{
    Service test_service("Name", 700899, 45.99);
    cout << "\n---Get number test---" << endl;
    assert(test_service.get_number() == 700899);
    return;
}

void ServiceTest::set_name_test()
{
    Service test_service;
    cout << "\n---Set service name test---" << endl;
    test_service.set_name("New-Name");
    assert(test_service.name == "New-Name");
    return;
}

void ServiceTest::set_fee_test()
{
    float comparison = 30.55;
    Service test_service;
    cout << "\n---Set service fee test---" << endl;
    test_service.set_fee(30.55);
    assert(abs(test_service.fee - comparison) < 1e-9);    
    return;
}

void ServiceTest::set_code_test()
{
    Service test_service;
    cout << "\n---Set service code test---" << endl;
    test_service.set_code(700233);
    assert(test_service.number == 700233);
    return;
}

void ServiceTest::get_name_test()
{
    Service test_service("Name", 700899, 45.99);
    cout << "\n---Get number test---" << endl;
    assert(test_service.get_name() == "Name");
    return;
}

void ServiceTest::get_fee_test()
{
    float comparison = 45.99;
    Service test_service("Name", 700899, 45.99);
    cout << "\n---Get fee test---" << endl;
    assert(abs(test_service.fee - comparison) < 0.0000000001);    
    return;
}

void ServiceTest::display_all_test()
{
    Service test_service("Name", 700862, 99.89);
    cout << "\n---Display all information test (Should display name 'Name', number 700862, and fee 99.89)---" << endl;
    test_service.display_all();
    return;
}
