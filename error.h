/*******************************************************************************
Chocoholics CS314 Program: Error Handling Interface
Names: Sonia Nath, Yollaine Brooks,
Description of Program:
*********************************************************************************/
#pragma once

// No entity found in the database
struct NoEntityFound
{
	string msg;
};

// No service found in the database
struct NoServiceFound
{
	string msg;
};

struct InvalidMenuOption
{
	string msg;
};

// error while parsing files into database
struct FileParseError
{
	string msg;
};
