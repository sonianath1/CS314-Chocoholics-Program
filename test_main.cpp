#include "database.h"

// TESTING PROGRAM's MAIN, SHOULD BE COMPILED IN A SEPARATE PROGRAM THAN MAIN.CPP
int main()
{
    DatabaseTest test_db;
    cout << "SMOKE TESTING\n" 
         << "-------------\n" << endl;
    test_db.constructor_test();
    //test_db.destructor_test(); FAILS
    test_db.read_from_file_test();
    //test_db.add_member_test(); FAILS
    test_db.update_member_test();
    return 0;
}