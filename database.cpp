#include "database.h"
#include <iostream>
using namespace std
/*******************************************************************************
Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks,
Description of Program:
*********************************************************************************/

// Sonia
Database::Database(int size_members, int size_providers, int size_prov_dir)
{

}

//Sonia
Database::~Database()
{
}


// Sonia
void Database::load_data()
{
}

// Sonia
void Database::add_member(Member &)
{
}

// Sonia
void Database::update_member(int member_number)
{
}

//Sonia
void Database::delete_member(int member_number)
{
}

// Sonia
void Database::add_provider(Provider &)
{
}

//Sonia
void Database::update_provider(int provider_number)
{
}

//Sonia
void Database::delete_provider(int provider_number)
{
}

// Sonia
void Database::record_provided_service(ProvidedService &)
{
}

void Database::get_service_data(int service_number, service& copy)
{
}

//olga
void Database::generate_weekly_report()
{
    //seraches thorough the memebrs hash table
    Member* find_memeber(int num)
    {
        node<Member>* current = Members[i];
        while(current != NULL)
        {
            if(current->data.get_number() == num)
                return &current->data;
            current = current->next;
        }
    }
    return NULL;

    //FINDS TE PROVIDER BY NUMBER
    Provider* find_provider(int num)
    {
        node<Provider>* current = Providers[i];
        while(current != NULL)
        {
            if(current->data.get_number() == num)
                return &current->data;
            current = current->next;
        }
    }
    return NULL;

    //FIND serivce using code
    Service* find_service(int code);
    {
        for(int i = 0; i < prov_dir_size; i++)
        {
            node<SERVICE>* current = ProviderDirectory[i];
            while(current != NULL)
            {
                if(current->data.code == code)
                    return &current->data;
                current = current->next;
            }
        }
        return NULL;
    }
    
    //output file
    ofstream report("Weekly_report.txt")
    if(!report)
    {
        cout<<"Error:Couldn't create weekly_report.txt\n";
        return;
    }

    report<<"********** ChpcAn Weekly Report **********\n\n";

    //keep wit the total services we provides and total amount
    int total_services = 0;
    double total_fees = 0.0;
    
    vector<int> unique_members;

    vector<int> provider_ids;
    vector<double> provider_amounts;

    for(int i = 0; i < ProvidedServices.size(); i++)
    {
        ProvidedService ps = ProvidedServices[i];

        int member_num = ps.member_number;
        int provider_num = ps.provider_number;
        int service_code = ps.service_code;

        Member* mem = find_memebr(member_num);
        string memeber_name = "Unknown";
        if(mem != NULL)
            member_name = m->get_name();

        Provider* prov = find_provider(provide_num);
        string provider_name = "Unknown";
        if(prov != NULL)
            provider_name = prov->get_name();

        Service* serv = find_service(service_code);
        string service_name = "Unknown";
        double fee = 0.0;
        if(serv != NULL)
        {
            service_name = serv->name;
            fee = serv->fee;
        }

        //wrtinr into the report
        report <<"Service Date: "<<ps.service_data_time<<endl;
        report<<"Member: "<<memebr_num<<"-"<< member_name <<endl;
        report<<"Provider: "<<provider_num <<"-"<<provider_name<<endl;
        report<<"Service: "<<service_name<<endl;
        report<<"Fee: "<<fee<<" $ "<<endl;
        report<<"---------------------------------------------------------"<<endl;
    }
}

void Database::verify_member(int member_number)
{
}

void Database::verify_provider(int provider_number)
{
}

void Database::verify_service(int service_number)
{
}

void Database::hash_function(string &key_value)
{
}


