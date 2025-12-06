#include "database.h"

// TESTING PROGRAM's MAIN, SHOULD BE COMPILED IN A SEPARATE PROGRAM THAN MAIN.CPP
int main()


{    

     DatabaseTest test_db;
     ServiceTest test_service;
     EntityTest test_entity;

     cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                     ENTITY TESTING                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n\n";
     test_entity.constructor_test();
     test_entity.get_number_test();
     test_entity.get_name_test();
     test_entity.compare_number_test();
     test_entity.update_data();
     test_entity.set_name_test();
     test_entity.set_number_test();
     test_entity.get_address_test();
     test_entity.display_all_test();

     cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                    SERVICE TESTING                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n\n";
     test_service.default_constructor_test();
     test_service.constructor_test();
     test_service.get_number_test();
     test_service.get_name_test();
     test_service.get_fee_test();
     test_service.set_name_test();
     test_service.set_code_test();
     test_service.set_fee_test();
     test_service.display_all_test();

     cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n";
	cout << "                   DATABASE TESTING                     \n";
	cout << "***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************\n\n";
     
     test_db.constructor_test();
     test_db.read_from_file_test();
     test_db.write_to_file_test();
     test_db.add_member_test();    
     test_db.update_member_test(); // fails before merging Yasmine branch
     test_db.delete_member_test();
     test_db.add_provider_test();  // fails before merging Yasmine branch
     test_db.update_provider_test(); // fails before merging Yasmine branch
     test_db.delete_provider_test();
     test_db.load_provider_directory_test();
     test_db.write_provider_directory_test();
     test_db.add_service_test();
     test_db.get_service_data_test();
     test_db.generate_weekly_report_test();

     // recorded services
     test_db.load_provided_service_test();
     test_db.write_provided_service_test();
     test_db.record_provided_service_test();

     test_db.verify_member_test();		// verify that a member exists
     test_db.verify_provider_test();	// verify that a provider exists
     test_db.verify_service_test();	// verify that a service exists
     test_db.hash_function_test();		// hash function 

     cout << "***************☆*: .｡. d(￣◇￣)b.｡.:*☆**************\n";
	cout << "          DATABASE TESTING COMPLETED SUCCESSFULLY    \n";
	cout << "***************☆*: .｡. d(￣◇￣)b .｡.:*☆**************\n";
     
     return 0;

}
