#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CppTrue_CFalse = true;
string type = "";
string nameFunction = "";
string nameFile = "";
string parameters = "";
string parametersDefValues = "";
bool mustDefaultValue = false; // If one, in C++, you must have all the next! So starting with the last one!

bool doesFileExists ( const std::string& name ) { // https://stackoverflow.com/questions/46292764/check-for-file-existence-in-c-without-creating-file
    if ( FILE *file = fopen ( name.c_str(), "r" ) ) {
        fclose ( file );
        return true;
    } else {
        return false;
    }
}

bool updateC_CPP() { // File detection.
    if ( doesFileExists ( "main.c" ) == true ) {
        CppTrue_CFalse = false;
        cout << "\"main.c\" found. Working on it." << endl;
    } else if ( doesFileExists ( "main.cpp" ) ==true ) {
        CppTrue_CFalse = true;
        cout << "\"main.cpp\" found. Working on it." << endl;
    } else {
        cerr << "Neither \"main.c\" nor \"main.cpp\" found!" << endl;
        exit ( EXIT_FAILURE );
    }
    return CppTrue_CFalse;
}

void intro() {
    cout << "This program will help You to add a function with a H file (header)." << endl;
}

string askParamDefVal(){
 cout << "Same, but _with default value_ (For example \"int a = 0, bool b = true, string HW = "" ... \")\n";
        getline ( cin, parametersDefValues );
    return parametersDefValues ;
    }

void askInformations() {
    cout << "What is the type of the new function? (For example void, int, bool...) ";
    getline ( cin, type );
    cout << "What is the name of the new function? (For example add, test1...) ";
    getline ( cin, nameFunction );
    cout << "What is the name of the _new_ file? (For example operations, AllTests...) ";
    cout << "(Nothing for same name as the function.) " << endl;
    getline ( cin, nameFile );
    if ( nameFile=="" ) {
        nameFile = nameFunction;
    }
    cout << nameFile << ".c";
    if ( CppTrue_CFalse==true ) {
        cout << "pp" ;
    }
    cout << " " << " and " << nameFile << ".h" << endl;
    cout << "What are the potential type and parameters of the function (separated with a \",\", _without default value_) (For example \"int a, bool b, string HW ...\" ) ";
    if ( CppTrue_CFalse==true ) {
        cout << "Parameters with optional default value at the end." << endl;
    }
    getline ( cin, parameters );
    if ( CppTrue_CFalse==true ) {
    parametersDefValues  = askParamDefVal();
    }
}




void YouMustDo() { // Ok.
    cout << "My job is done. Now, _You_ must work." << endl;
    cout << "You must update \"main.c" ;
    if ( CppTrue_CFalse==true ) {
        cout << "pp";
    }
    cout << "\" with, at the beginning:" << endl;
    cout << "#include \"" ;
    cout << nameFile ;
    cout << ".h\"" << endl;
    cout << "Then, You must write the function." << endl;
    cout << "Then, You can use the function." << endl;
    cout << "Bye!" << endl;
}

void iout ( string message = "",  int colorisationFin = 0, int colorisation1 = 1, int colorisation2 = 31 ) { // Ok.
    // 31 = RED.
    // 1 = bold.
    // 3 = italic.
    // 4 = underline.
    // 0 = normal.
    // 2 effects or color only.
    // 41 = red background...
    printf ( "\033[%dm", colorisation1 );
    printf ( "\033[%dm", colorisation2 );
    cout << message;  // http://www.cplusplus.com/forum/beginner/108474/
    printf ( "\033[%dm", colorisationFin );
}

void ierr ( string message = "",  int colorisationFin = 0, int colorisation1 = 1, int colorisation2 = 31 ) { // Ok.
    // 31 = RED.
    // 1 = bold.
    // 3 = italic.
    // 4 = underline.
    // 0 = normal.
    // 2 effects or color only.
    // 41 = red background...
    printf ( "\033[%dm", colorisation1 );
    printf ( "\033[%dm", colorisation2 );
    cerr << message;  // http://www.cplusplus.com/forum/beginner/108474/
    printf ( "\033[%dm", colorisationFin );
}

string toUp ( string a = "" ) { // OK. // https://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
    for ( unsigned int i = 0; i < a.length(); i++ ) {
        a[i] = toupper ( a[i] );
    }
    return a;
}

int main() {
    intro();
    CppTrue_CFalse = updateC_CPP();
    askInformations();
    string file = nameFile + ".h";
    ofstream monFlux ( file.c_str(), ios::app );
    if ( !monFlux ) {
        cerr << "ERROR: Impossible to open the file ";
        ierr ( file );
        cerr << " in append mode!" << endl;
        return 1;
    } else {
        monFlux << "#ifndef " << toUp(nameFile) << "_H_INCLUDED" << endl;
        monFlux << "#define " << toUp(nameFile) << "_H_INCLUDED" << endl << endl;
        monFlux << type << " " << nameFunction << "(" << parametersDefValues << ");" << endl << endl;
// int add(int a_local_add = 0, int b_local_add = 0);
// int diff(int a_local_diff = 0, int b_local_diff = 0);
        monFlux << "#endif //" << toUp(nameFile) << "_H_INCLUDED";

    }
       monFlux.close();
file = nameFile + ".c";
    if ( CppTrue_CFalse==true ) {
file = file + "pp" ;
    }
    ofstream monFlux2 ( file.c_str(), ios::app );
    if ( !monFlux2 ) {
        cerr << "ERROR: Impossible to open the file ";
        ierr ( file );
        cerr << " in append mode!" << endl;
        return 1;
    } else {
        monFlux2 << "#include \"" << nameFile << ".h\"" << endl;
        monFlux2 << type << " " << nameFunction << "(" << parameters << "){" << endl;
monFlux2 << "// ..." << endl;

if (type != "void")
{
    monFlux2 << "return ... ;" << endl;
}
monFlux2 << "}" << endl;

        /*
        int add(int a_local_add, int b_local_add)
{
    return a_local_add + b_local_add;
}

int diff(int a_local_diff, int b_local_diff)
{
    return a_local_diff - b_local_diff;
}
        */

        monFlux2.close();
    }




    YouMustDo();
    getline(cin, file); // Enter to quit?
    return 0;
}
