#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CppTrue_CFalse = true;
string mainF = "main0"; // main0 for tests, main for real.
string type = "";
string nameFunction = "";
string nameFile = "";
string parameters = "";
string parametersDefValues = "";
// bool mustDefaultValue = false; // If one, in C++, you must have all the next! So starting with the last one!
// if cpb, update cpb.

string deleteDefValues ( string parameters = "" ) {
    string result = "";
    bool add = true;
    for ( int a=0; a<parameters.size(); a++ ) {
        if ( parameters[a] == '=' ) {
add = false;
        } else if (parameters[a] == ',') {
add = true;
        }
        if (add == true){
result = result + parameters[a];
        }
    }
    return result;
}


bool doesFileExists ( const std::string& name ) { // https://stackoverflow.com/questions/46292764/check-for-file-existence-in-c-without-creating-file
    if ( FILE *file = fopen ( name.c_str(), "r" ) ) {
        fclose ( file );
        return true;
    } else {
        return false;
    }
}

bool updateC_CPP() { // File detection.
    if ( doesFileExists ( mainF + ".c" ) == true ) {
        CppTrue_CFalse = false;
        cout << "\"" << mainF << ".c\" found. Working on it." << endl;
          } else if ( doesFileExists (  mainF + ".cpp" ) ==true ) {
        CppTrue_CFalse = true;
        cout << "\"" << mainF << ".cpp\" found. Working on it." << endl;
    } else {
        cerr << "Neither \"" << mainF << ".c\" nor \"" << mainF << ".cpp\" found!" << endl;
        exit ( EXIT_FAILURE );
    }
    return CppTrue_CFalse;
}

void intro() {
    cout << "This program will help You to add a function with a H file (header)." << endl;
}


void askInformations() {
    cout << "What is the type of the new function? (For example void, int, bool...) ";
    getline ( cin, type );
    cout << "What is the name of the new function? (For example add, test1...) ";
    getline ( cin, nameFunction );
    cout << "What is the name of the _new_ file? (For example operations, AllTests...) "; // if old file: Update!!!!!!!!!!
    cout << "(Nothing for same name as the function.) ";
    getline ( cin, nameFile );
    if ( nameFile=="" ) {
        nameFile = nameFunction;
    }
    cout << "\"" << nameFile << ".c";
    if ( CppTrue_CFalse==true ) {
        cout << "pp" ;
    }
    cout << "\" and " << nameFile << ".h\" will be made." << endl;
    cout << "What are the potential type and parameters of the function (separated with a \",\" ";
      if ( CppTrue_CFalse==false )
      {

        cout << "_without default value._ \nThere is no default value in C.) \n(For example \"int a, bool b, string HW ...\" ) ";
      }
    else  {
        cout << "with optional default value at the end. \n(For example \"int a = 0, bool b = true, string HW = "" ... \") ";
    }
    getline ( cin, parametersDefValues );
    parameters = deleteDefValues(parametersDefValues);
    if ( CppTrue_CFalse==false ) {
parametersDefValues = parameters; // There is no default value in C.
    }
}




void YouMustDo() { // Ok.
    cout << "My job is done. Now, _You_ must work." << endl;
    cout << "You must update \"" << mainF << ".c" ; // Auto insert string in file.
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
