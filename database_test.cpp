#include "database.h"
#include <assert.h>
using namespace std;

// Test if each data member initialized properly
void DatabaseTest::constructor_test()
{
    Database test_db;
    assert(test_db.members_size == 10);
    assert(test_db.providers_size == 10);
    assert(test_db.prov_dir_size == 10);
    assert(test_db.Members != nullptr);
    assert(test_db.Providers != nullptr);
    assert(test_db.ProviderDirectory != nullptr);
}

void DatabaseTest::read_from_file_test()
{
}

void DatabaseTest::write_to_file_test()
{
}

void DatabaseTest::load_member_test()
{
}

void DatabaseTest::write_member_test()
{
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

// service tests
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
