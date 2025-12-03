#include "entities.h"
#include <assert.h>
using namespace std;

//-------------------------------------------------------- 
//------------------ Entity Test ------------------------- 
//-------------------------------------------------------- 

void EntityTest::constructor_test()
{
    Entity test_entity;
    assert(test_entity.get_name() == "");
    assert(test_entity.get_number() == 0);
    
    address &addr = test_entity.get_address();
    assert(addr.street_addr == "");
    assert(addr.city == "");
    assert(addr.state == "");
    assert(addr.zip_code == 0);  
}

void EntityTest::get_number_test()
{
    Entity test_entity;
    test_entity.set_number(123456);
    assert(test_entity.get_number() == 123456);
}

void EntityTest::get_name_test()
{
    Entity test_entity;
    test_entity.set_name("havana");
    assert(test_entity.get_name() == "havana");

}

void EntityTest::compare_number_test()
{
    Entity test_entity;
    test_entity.set_number(42);

    assert(test_entity.compare_number(42) == true);
    assert(test_entity.compare_number(99) == false);
}

void EntityTest::update_data()
{
    Entity original;
    original.set_name("Original");
    original.set_number(1);
    address orig_addr;
    orig_addr.street_addr = "625 jackson";
    orig_addr.city = "Portland";
    orig_addr.state = "OR";
    orig_addr.zip_code = 97201;
    original.set_address(orig_addr);

    Entity src;
    src.set_name("source");
    src.set_number(999);
    address src_addr;
    src_addr.street_addr = "111 pine";
    src_addr.city = "salt lake";
    src_addr.state = "UT";
    src_addr.zip_code = 78234;
    src.set_address(src_addr);

    original.update_data(src);

    assert(original.get_name() == "Source");
    assert(original.get_number() == 999);

    address &addr = original.get_address();
    assert(addr.street_addr == "111 pine");
    assert(addr.city == "salt lake");
    assert(addr.state == "UT");
    assert(addr.zip_code == 78234);

    

}

void EntityTest::set_name_test()
{
    Entity test_entity;
    test_entity.set_name("Maria");
    assert(test_entity.get_name() == "Maria");
}

void EntityTest::set_number_test()
{
    Entity test_entity;
    test_entity.set_number(314159);
    assert(test_entity.get_number() == 314159);

}

void EntityTest::get_address_test()
{
    Entity test_entity;

    address addr_in;
    addr_in.street_addr = "7453 foxfire st";
    addr_in.city = "Surprise";
    addr_in.state = "AZ";
    addr_in.zip_code = 85465;

    test_entity.set_address(addr_in);

    address &addr_out = test_entity.get_address();
    assert(addr_out.street_addr == "7453 foxfire st");
    assert(addr_out.city == "Surprise");
    assert(addr_out.state == "AZ");
    assert(addr_out.zip_code == 85465);


}

void EntityTest::display_all_test()
{
    Entity test_entity;
    test_entity.set_name("Display Entity");
    test_entity.set_number(777);

    address addr_in;
    addr_in.street_addr = "777 Display st";
    addr_in.city = "bananas";
    addr_in.state = "WA";
    addr_in.zip_code = 45245;
    test_entity.set_address(addr_in);

    test_entity.display_all();
}

//-------------------------------------------------------- 
//------------------ Member Test ------------------------- 
//-------------------------------------------------------- 

void MemberTest::constructor_test()
{
    Member test_mem;
    assert(test_mem.get_status() == "");    
}

void MemberTest::update_data_test()
{
    Member original;
    original.set_name("Original Member");
    original.set_number(111);
    address orig_addr;
    orig_addr.street_addr = "1 Member St";
    orig_addr.city = "Portland";
    orig_addr.state = "OR";
    orig_addr.zip_code = 97201;
    original.set_address(orig_addr);
    original.set_status("VALID");

    Member src;
    src.set_name("Source Member");
    src.set_number(222);
    address src_addr;
    src_addr.street_addr = "2 Other Ave";
    src_addr.city = "Seattle";
    src_addr.state = "WA";
    src_addr.zip_code = 98101;
    src.set_address(src_addr);
    src.set_status("SUSPENDED");

    original.update_data(src);


    assert(original.get_name() == "Source Member");
    assert(original.get_number() == 222);

    address &addr = original.get_address();
    assert(addr.street_addr == "2 Other Ave");
    assert(addr.city == "Seattle");
    assert(addr.state == "WA");
    assert(addr.zip_code == 98101);
    
    assert(original.get_status() == "SUSPENDED");
}

void MemberTest::set_status_test()
{
    Member test_mem;
    test_mem.set_status("VALID");
    assert(test_mem.get_status() == "VALID");

}

void MemberTest::get_status_test()
{
    Member test_mem;
    test_mem.set_status("SUSPENDED");
    assert(test_mem.get_status() == "SUSPENDED");

}

void MemberTest::display_all_test()
{

    Member test_mem;
    test_mem.set_name("Display Member");
    test_mem.set_number(333);
    address addr_in;
    addr_in.street_addr = "333 NE Way";
    addr_in.city = "Salem";
    addr_in.state = "OR";
    addr_in.zip_code = 97303;
    test_mem.set_address(addr_in);
    test_mem.set_status("VALID");

    test_mem.display_all();
}

//----------------------------------------------------------
//------------------ Provider Test ------------------------- 
//----------------------------------------------------------

void ProviderTest::constructor_test()
{
    Provider test_prov;

    vector<int> servs = test_prov.get_services();
    assert(servs.empty());
}

void ProviderTest::update_data_test()
{
    Provider original;
    original.set_name("Original Provider");
    original.set_number(444);
    address orig_addr;
    orig_addr.street_addr = "4 Provider Way";
    orig_addr.city = "Portland";
    orig_addr.state = "OR";
    orig_addr.zip_code = 97203;
    original.set_address(orig_addr);
    original.add_service(100001);
    original.add_service(100002);

    Provider src;
    src.set_name("Source Provider");
    src.set_number(555);
    address src_addr;
    src_addr.street_addr = "5 Other Way";
    src_addr.city = "Seattle";
    src_addr.state = "WA";
    src_addr.zip_code = 98102;
    src.set_address(src_addr);
    src.add_service(200001);
    src.add_service(200002);
    src.add_service(200003);

    original.update_data(src);

    
    assert(original.get_name() == "Source Provider");
    assert(original.get_number() == 555);

    address &addr = original.get_address();
    assert(addr.street_addr == "5 Other Way");
    assert(addr.city == "Seattle");
    assert(addr.state == "WA");
    assert(addr.zip_code == 98102);

    vector<int> servs = original.get_services();
    assert(servs.size() == 3);
    assert(servs[0] == 200001);
    assert(servs[1] == 200002);
    assert(servs[2] == 200003);
}


void ProviderTest::add_service_test()
{
    Provider test_prov;

    test_prov.add_service(700100);
    test_prov.add_service(700200);
    test_prov.add_service(700300);

    vector<int> servs = test_prov.get_services();
    assert(servs.size() == 3);
    assert(servs[0] == 700100);
    assert(servs[1] == 700200);
    assert(servs[2] == 700300);
}

void ProviderTest::get_services_test()
{
    Provider test_prov;

    test_prov.add_service(123456);
    test_prov.add_service(654321);

    vector<int> servs = test_prov.get_services();
    assert(servs.size() == 2);
    assert(servs[0] == 123456);
    assert(servs[1] == 654321);

}

void ProviderTest::clear_services_test()
{
    Provider test_prov;

    test_prov.add_service(111111);
    test_prov.add_service(222222);
    test_prov.add_service(333333);

    test_prov.clear_services();

    vector<int> servs = test_prov.get_services();
    assert(servs.empty());
}

void ProviderTest::display_all_test()
{
    Provider test_prov;

    test_prov.set_name("Display Provider");
    test_prov.set_number(999);
    address addr_in;
    addr_in.street_addr = "999 nw calle";
    addr_in.city = "Fresno";
    addr_in.state = "CA";
    addr_in.zip_code = 93661;
    test_prov.set_address(addr_in);

    test_prov.add_service(100001);
    test_prov.add_service(100002);
    
    test_prov.display_all();

}
