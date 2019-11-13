#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CppTrue_CFalse = true;
string type = "";
string nameFunction = "";
string nameFile = "";
string parameters = "";

bool updateC_CPP()
{
    return true;
}

void intro()
{
    cout << "This program will help You to add a function with a H file (header)." << endl;
}

void askInformations()
{
    cout << "What is the type of the new function? (For example void, int, bool...)";
    getline ( cin, type );
    cout << "What is the name of the new function? (For example add, test1...)";
    getline ( cin, nameFunction );
    cout << "What is the name of the _new_ file? (For example operations, AllTests...)";
    cout << "(Nothing for same name as the function.)" << endl;
    getline ( cin, nameFile );

    if ( nameFile=="" )
        {
        nameFile = nameFunction;
        }

    cout << "What are the potential type and parameters of the function (separated with a \",\", _without default value_) (For example int a, bool b, string HW... )";
    cout << "CPP : parameters with optional default value at the end." << endl;
    getline ( cin, parameters );
// if "cpp": with potential default values of each parameters;

}

void YouMustDo()
{
    cout << "My job is done. Now, You must work." << endl;
    cout << "You must update main.c or main.cpp with, at the beginning:" << endl;
    cout << "..." << endl;
}

int main()
{
    intro();
    CppTrue_CFalse = updateC_CPP();
    askInformations();

    YouMustDo();
    return 0;
}
