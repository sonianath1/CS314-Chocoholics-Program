#include "database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
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
    //will hold all service data from prodiver directory test fule
    vector<int> service_codes;
    vector<string>service_name;
    vector<double>service_fees;

    //open the provder dictor
    ifstream provider_directory_file("providerdirectory.txt");
    if(!provider_directory_file)
    {
        cout<<"Couldn't open provider dictory text file"<<endl;
    }
    else
    {
        cout<<"Loading data ...."<<endl;
        string input_line;
        //readinf each line until the last one
        while(getline(provider_directory_file, input_line))
        {
            //skip od the no lines
            if(input_line.empty())
                continue;

            stringstream line_stream(input_line);
            string temp;

            int code{0};
            string name;
            double fee{0.0};

            //service code
            if(!getline(line_stream,temp, '|'))
                continue;
            code = stoi(temp);
            
            //sercue name
            if(!getline(line_stream, name, '|'))
                continue;

            //fee
            if(!getline(line_stream, temp, '|'))
                continue;
            fee = atof(temp.c_str());

            //will store the parsed calues into the vectors
            service_codes.push_back(code);
            service_name.push_back(name);
            service_fees.push_back(fee);

        }
        provider_directory_file.close();
    }




    //open output file
    ofstream report("weekly_report.txt");
    if(!report)
    {
        cout<<"Error:Couldn't create weekly_report.txt"<<endl;
        
        return;
    }

    report<<"********** ChpcAn Weekly Report **********"<<endl;
    cout<<"             --------------------                "<<endl<<endl;


    //keep wit the total services we provides and total amount
    int total_services = 0;
    double total_fees = 0.0;
    
    vector<int> unique_member_numbers; //specifically for the unique memebrs
    vector<int> provider_ids;
    vector<double> provider_totals;

    //itelearate though each servuce tht was provided
    for(int i = 0; i < (int)ProvidedServices.size(); i++)
    {
        ProvidedService current_service = ProvidedServices[i];

        int member_number = current_service.member_number;
        int provider_number = current_service.provider_number;
        int service_code = current_service.service_code;

        //lookup member suing fin()
        Member* mem = Database::find(Members, members_size, member_number);
        string member_name = "Unknown";
        if(mem != NULL)
            member_name = mem->get_name();


        //looup provider usinf same find()
        Provider* prov = Database::find(Providers, providers_size, provider_number);
        string provider_name = "Unknown";
        if(prov != NULL)
            provider_name = prov->get_name();


        //loopup service
        
        string serv = "Unknown";
        double fee = 0.0;
        
        for(int s = 0; s < (int)service_codes.size(); ++s)
        {
            if(service_codes[s] == service_code)
            {
                serv = service_name[s];
                fee = service_fees[s];
                break;
            }
        }



        //wrtinr into the report
        report <<"Service Date: "<<current_service.service_data_time<<endl;
        report<<"Member: "<<member_number<<"-"<< member_name <<endl;
        report<<"Provider: "<<provider_number <<"-"<<provider_name<<endl;
        report<<"Service: "<<service_code<<"-"<<service_name<<endl;
        report<<"Fee: "<<fee<<" $ "<<endl;

        if(!current_service.comments.empty())
            report<<"Comments: "<< current_service.comments<<endl;

        report<<"---------------------------------------------------------"<<endl;

        //update overall totals
        total_services ++;
        total_fees += fee;


        //back to unique memebrs
        bool unique = false;

        for(int j = 0; j <(int)unique_member_numbers.size(); ++j)
        {
            if(unique_member_numbers[j] == member_number)
            {
                unique = true;
                break;
            }
        }
        if(!unique)
        {
            unique_member_numbers.push_back(member_number);
        }

        int provider_index = -1;

        for(int k = 0; k < (int)provider_ids.size(); ++k)
        {
            if(provider_ids[k] == provider_number)
            {
                provider_index = k;
                break;
            }
        }
        if(provider_index == -1)
        {
            provider_ids.push_back(provider_number);
            provider_totals.push_back(fee);
        }
        else
        {
            provider_totals[provider_index] += fee;
        }

    }

    //sdisplay the overal summary total section
    report <<"\n";
    report <<"Total Number of services : "<< total_services<<endl;
    report <<"Unique Members served    : "<< unique_member_numbers.size()<<endl;
    report <<"Total Fees for the week  : "<< total_fees<< "$"<<endl<<endl;
    report <<"  EFT Summary per provider"<<endl;
    report <<"--------------------------------------------------------------------------------"<<endl;


    //goes thorufh each provider who provided the service
    for(int i = 0; i <(int)provider_ids.size(); ++i)
    {
        int provider_number = provider_ids[i];
        double total_amount = provider_totals[i];


        Provider *provider_ptr = find(Providers, providers_size, provider_number);
        string provider_name = "unknown";
        
        if(provider_ptr != NULL)
        {
            provider_name = provider_ptr->get_name();
        }

        report <<"Provider: "<< provider_number<<", "<<provider_name<<endl;
        report <<"Total Amount: "<<total_amount<<"$"<<endl;
        
    }
    report <<"End of the weekly report"<<endl<<endl;

    report.close();

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


