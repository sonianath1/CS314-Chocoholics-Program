README

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Chocoholics Anonymous (ChocoAn) Data Processing Software

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Purpose:

    This software's purpose is to provide multiple different functionalities to Chocan users
and stakeholders. It support's operator, provider, and manager workflows. It allows for the 
management of members, providers, service directory, and weekly accounting reports. All while
maintaining a consistent database.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Installation:

1. Download Repository from https://github.com/sonianath1/CS314-Chocoholics-Program.git
2. Use command "make all" to make all the executables associated with this software.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Testing:

    There are multiple test files included in the test suite. The executable
Chocanprogramtest encompasses all of them. 

1. Run the command "./chocanprogramtest" to run the test suite

This will run all the tests that have been made for the software. If all the tests pass the following
message will be printed. If a test fails it aborts the program early.

***************☆*: .｡. d(￣◇￣)b .｡.:*☆**************
    DATABASE TESTING COMPLETED SUCCESSFULLY    
***************☆*: .｡. d(￣◇￣)b .｡.:*☆**************


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Running the software:

1. Run the command ./chocanprogram to run the software

This starts the overall program. A brief definition of each login is provided below.

Provider:
~~~~~~~~~
    Log into the provider portal requires a valid provider number, if no providers are saved in a
    providers.txt file, then a new provider must be added in order to log in. (see operator)

    Providers have the ability to check in a user to verify their status, check out a user to
    record the provided service, and request a provider directory be printed of services and their
    associated fees


Manager:
~~~~~~~~~
    Access to the manager portal is not restricted by a login.

    Managers have the ability to request a weekly summary of all the recorded services. It outputs to
    a .txt files titled weekly_reports.txt. If no services are recorded the file with be empty.

Operator:
~~~~~~~~~
    Access to the operator portal is not restricted by a login.
    
    Operators have the ability to add, remove, and update members and providers. In order to remove or
    update a member/provider you will need to look up the member or provider in the members.txt or providers.txt.

