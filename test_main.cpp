#include "database.h"

// TESTING PROGRAM's MAIN, SHOULD BE COMPILED IN A SEPARATE PROGRAM THAN MAIN.CPP
int main()
{
    DatabaseTest test_db;
    cout << "TEST SUITE --\n" 
         << "-------------\n" << endl;
    test_db.constructor_test();
    test_db.destructor_test();
    test_db.read_from_file_test();
    test_db.write_to_file_test();
    test_db.add_member_test();
    test_db.update_member_test();
    test_db.delete_member_test();
    test_db.add_provider_test();
    test_db.update_provider_test();
    test_db.delete_provider_test();
    return 0;
}