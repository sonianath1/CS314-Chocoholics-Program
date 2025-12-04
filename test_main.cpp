#include "database.h"

// TESTING PROGRAM's MAIN, SHOULD BE COMPILED IN A SEPARATE PROGRAM THAN MAIN.CPP
int main()
{    
    DatabaseTest test_db;
    ServiceTest test_service;
    
    cout << "SMOKE TESTING\n" 
         << "-------------\n" << endl;
    test_db.constructor_test();
    test_db.read_from_file_test();
    test_db.write_to_file_test();
    test_db.add_member_test();
    test_db.update_member_test();
    test_db.delete_member_test();
    test_db.add_provider_test();
    test_db.update_provider_test();
    test_db.delete_provider_test();
    
    
    cout << "SERVICE TESTING\n" 
         << "-------------\n" << endl;
    test_service.default_constructor_test();
    test_service.constructor_test();
    test_service.get_number_test();
    test_service.get_name_test();
    test_service.get_fee_test();
    test_service.set_name_test();
    test_service.set_code_test();
    test_service.set_fee_test();
    test_service.display_all_test();
    

    
    return 0;
}
