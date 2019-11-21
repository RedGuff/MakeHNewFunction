
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

OverwriteBakWihoutPrompt = true; // INI file?
string mainF = "main"; // main0 for tests, main for real.
string nameFile = "";
string parameters = "";
string parametersDefValues = "";
string exampleFunctionCPP = "";
string pp = ""; // "" for C, pp for C++.
string fileCBP = "file.cbp" ;
bool fileHCPPExists = false;


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
bool doesFileExists ( const std::string& name ) { // https://stackoverflow.com/questions/46292764/check-for-file-existence-in-c-without-creating-file
    if ( FILE *file = fopen ( name.c_str(), "r" ) ) {
        fclose ( file );
        return true;
    } else {
        return false;
    }
}

string deleteDefValues ( string parameters = "" ) { // Tests Ok.
    int parenthesis = 0;
    // Entrer dans une string est facilement détectable, mais pas sa sortie.
    bool inAString = false; // "," in a string or in a char. // Impossible to have "," or "=" in a name!
    char charJustBefore = ' ';
    string result = "";
    bool add = true;

    for ( int a=0; a<parameters.size(); a++ ) {
        if ( ( parameters[a] == '=' ) && ( inAString == false ) ) {
            add = false;
        } else if ( ( parameters[a] == ',' ) && ( inAString == false ) ) {
            add = true;
        } else if ( ( charJustBefore != '\\' ) && ( ( parameters[a] == '"' ) || ( parameters[a] == '\'' ) ) ) {
            inAString = !inAString;
        }

        if ( add == true ) {
            result = result + parameters[a];

            if ( parameters[a]=='(' ) {
                parenthesis++;
            }

            if ( parameters[a]==')' ) {
                parenthesis--;
            }

        }

        charJustBefore = parameters[a];
    }

    if ( parenthesis<0 ) {
        cerr << "Bad function! I miss " << -parenthesis << " \"(\" in the result!"<< endl;
    }

    while ( parenthesis>0 ) {
        parenthesis--;
        result = result + ")"; // Some can be deleted.
    }

    return result;
}

void intro() { // Tests Ok.
    cout << "   This program will help You to add a function with external files: a H file (header)..." << endl;
}
void updateC_CPP() { // File detection. // Tests Ok.
    if ( doesFileExists ( mainF + ".c" ) == true ) {
        pp=""; // No change.
        cout << "\"" << mainF << ".c\" found. Working on it." << endl;
    } else if ( doesFileExists ( mainF + ".cpp" ) ==true ) {
        pp = "pp";
        cout << "\"" << mainF << ".cpp\" found. Working on it." << endl;
    } else {
        cerr << "ERROR: Neither \"" << mainF << ".c\" nor \"" << mainF << ".cpp\" found!" << endl;
 cout << "ENTER to quit." << endl;
       getline(cin,mainF);
        exit ( EXIT_FAILURE );
    }
}

string DelLeftSpacesTabs ( string In = "" ) { // Tests Ok.
// "" ? // Tests ok, no need.
    while ( ( In[0]==' ' ) || ( In[0]=='\t' ) ) {
        In=In.substr ( 1 );
    }

    return In;
}

void askFile() { //
    exampleFunctionCPP = "void f(int a = 0, char b = 'z', char c = '\\\'', string d = \"Yes\", string compliment = \"she\\'s intelligent.\", string insult = \"He is \\\"special\\\"...\")";
    cout << "You can have several functions in a file. \nFor example \"AllTests.h\" and \"AllTests.c" ;
    cout << pp ;
    cout << "\" can have \"bool test1()\" and \"bool test2()\" functions." << endl;
    cout << "(I can\'t do it for You, today, but I hope I\'ll be able to do it, one day!)" << endl;

    cout << "What is the name of the _new_ file, without extention? "; // if old file: Update TODO!!!!!!!!!!
    getline ( cin, nameFile );
    nameFile = DelLeftSpacesTabs ( nameFile );
    string nameFileCPP =  nameFile +".c" + pp;
   // clog << "nameFileCPP: " << nameFileCPP << endl;
  //  clog << "(doesFileExists(nameFileCPP): " << doesFileExists ( nameFileCPP ) << endl;
    string nameFileH =  nameFile +".h";
   // clog << "nameFileH: " << nameFileH << endl;
  //  clog << "(doesFileExists(nameFileH): " << doesFileExists ( nameFileH ) << endl;

    if ( ( doesFileExists ( nameFileCPP ) ) || ( doesFileExists ( nameFileH ) ) ) {
        fileHCPPExists = true;
        cerr << "\"" << nameFileCPP << "\" or/and \"" << nameFileH << "\" detected !" << endl;
        cout << "I can\'t work with existing files, today, but I hope that I may do it, one day." << endl;
        cout << "ENTER to quit." << endl;
       getline(cin,mainF);
        exit ( EXIT_FAILURE );

    }

    cout << "\"" << nameFile << ".c" << pp << "\" and " << nameFile << ".h\" will be made." << endl;
}
void askFunction() {
    cout << "What is the type and the function, with the potential type and parameters ";

    if ( pp=="" ) {
        cout << "_without_ default value? (There is no default value in C.) \n";
        cout << "For example: " << deleteDefValues ( exampleFunctionCPP ) << endl;
    } else  {
        cout << "with optional default value at the end. \n";
        cout << "For example: " << exampleFunctionCPP << endl;
    }

    getline ( cin, parametersDefValues );
    parametersDefValues = DelLeftSpacesTabs ( parametersDefValues );
    parameters = deleteDefValues ( parametersDefValues );

    if ( pp=="" ) {
        parametersDefValues = parameters; // There is no default value in C.
    }
}


void copyFile ( string FileIn = "", string FileOut = "", bool OverwriteWithoutPrompt = false ) {
    ifstream fileI ( FileIn.c_str(), ios::in ); // Read
testExist:
    if ((!OverwriteWithoutPrompt) && (doesFileExists(FileOut)==true))
    {
        cout << "The file \"" << FileOut << "\" exists!" << endl;
    cout << "Try a new name, or ENTER to replace." << endl;
    string newName  = "";
    getline ( cin, newName );
    if (newName=="")
    {
        goto replaceFile;
    } else {
    FileOut = newName;
    goto testExist;
    }
    }
replaceFile:
    if ( !fileI ) {
        cerr << "Impossible to open " << FileIn << "!" << endl;
    } else {
        ofstream fileO ( FileOut.c_str() ); // Delete and append. ?

        if ( !fileO ) {
            cerr << "Impossible to open " << FileOut << "!" << endl;
        } else {
            string line = "";

            while ( getline ( fileI, line ) ) {
                fileO << line << endl; // append file.
            }
        }

        fileO.close();
        fileI.close();
    }

}


int copyStringBeginningFileOrBeforeTrigger ( string data = "", string FileIn = "", string FileOut = "", string trigger = "" ) { // Insert a string at the beginning of the file, or before a trigger. AS the names says: data first, file after.
    bool insertionDone = false;

    ifstream fileI ( FileIn.c_str(), ios::in ); // Open to read.

    if ( !fileI ) {
        cerr << "Impossible to open " << FileIn << "!" << endl;
    } else {
        //ofstream fileO ( FileOut.c_str(), ios::app ); // Open to append.
        ofstream fileO ( FileOut.c_str() ); // Del and Open to append.

        if ( !fileO ) {
            cerr << "Impossible to open " << FileOut << "!" << endl;
        } else {
            string line = "";

            while ( getline ( fileI, line ) ) {
                if ( ( insertionDone == false ) && ( ( trigger == "" ) || ( trigger == line ) ) ) { // and "there is a string to detect for insertion" (!="").
                    fileO << data ; // append file.
                    insertionDone = true;
                }

                fileO << line << endl; // append file.
            }
        }

        fileO.close();
        fileI.close();
    }

    return 0;
}

void insertStringBeginningFileOrBeforeTrigger ( string stringtoInsert, string fileToInsert, string trigger = "" ) {
    string tempFile = "main.bak"; // https://en.cppreference.com/w/cpp/io/c/tmpfile
    copyFile ( fileToInsert, tempFile, OverwriteBakWihoutPrompt );
    copyStringBeginningFileOrBeforeTrigger ( stringtoInsert, tempFile, fileToInsert, trigger );
}


void updateMain() {
    string stringtoInsert = "#include \"" + nameFile + ".h\"" + "\n";
    string fileToInsert = mainF + ".c" + pp;
    string trigger = "";
    insertStringBeginningFileOrBeforeTrigger ( stringtoInsert, fileToInsert, trigger );
}

void YouMustDo() { // Ok.
    cout << "My job is done. Now, _You_ must work." << endl;
    updateMain();
    cout << "You must explain the function in " << nameFile << ".h" << endl;
    cout << "You must write the function inside " << nameFile << ".c" << pp << endl;
    cout << "Then, You can use the function." << endl;
    cout << "Bye!" << endl;
}


void updateCBP() {
// quel fichier de quel dossier ?

    cout << "You must check " << fileCBP <<"!"<< endl;
    if (doesFileExists(fileCBP)==false)
    {
        cerr << "ERR: no existence of " << fileCBP << endl;
    }
    string trigger = "<Unit filename=\"main.cpp\" />";
    cout << "after \"<Unit filename=\"main.cpp\" />\", please check:" << endl;
    cout << "<Unit filename=\"" << nameFile << ".h\" />" << endl;
    string stringtoInsert = "<Unit filename=\"" + nameFile + ".h\" />";
    insertStringBeginningFileOrBeforeTrigger ( stringtoInsert, fileCBP, trigger );
    stringtoInsert = "<Unit filename=\"" + nameFile + ".c" + pp + "\" />";
    cout << "<Unit filename=\""<< nameFile << ".c" << pp << " />" << endl;
    insertStringBeginningFileOrBeforeTrigger ( stringtoInsert, fileCBP, trigger );
    /*
    		<Unit filename="main.cpp" />
    		<Unit filename="who.cpp" />
    		<Unit filename="who.h" />
    */

}

int main ( int argc, char* argv[] ) {
    //  cout << "TESTS:{" << endl;
    // cout << argc << endl;

    if ( argc>1 ) {

        for ( int argument=0; argument<argc ; argument++ ) { // to test normal.
cout << "argv[" << argument << "] = " << argv[argument] << endl;
            string argu = argv[argument];
            int finArg = ( argu ).size() - 4 ;
            string argTot = toUp ( argv[argument] ); // toup?

            if ( argTot.substr ( finArg ) ==".CBP" ) {   // .cbp ?
                fileCBP = argv[argument];
                    clog << "fileCBP: " << fileCBP << endl;
            }
        }

    } else {
        fileCBP = "XXX.cbp";
        cerr << ".cbp not found, working with pseudo-file " << fileCBP << " instead." << endl;
    }
if (doesFileExists(fileCBP)==false)
    {
        cerr << "ERR: no existence of " << fileCBP << endl;
    }

    // cout << "}" << endl; // End of tests.
    intro();
    updateC_CPP();
    askFile(); // Files.
    askFunction(); // Functions.
    string file = nameFile + ".h";
    ofstream monFlux ( file.c_str(), ios::app );

    if ( !monFlux ) {
        cerr << "ERROR: Impossible to open the file ";
        ierr ( file );
        cerr << " in append mode!" << endl;
        return 1;
    } else {
        monFlux << "#ifndef " << toUp ( nameFile ) << "_H_INCLUDED" << endl;
        monFlux << "#define " << toUp ( nameFile ) << "_H_INCLUDED" << endl << endl;
        monFlux << "/**" << endl;
        monFlux << "* \\brief Function that ..." << endl;
        monFlux << "* \\param ..." << endl;

        if ( parameters.substr ( 0,4 ) != "void" ) { // Spaces and tabulations are deleted the beginning.
            monFlux << "* \\return ..." << endl;
        }

        monFlux << "*/" << endl;
        // askFunction(); // ?
        monFlux << parametersDefValues << ";"<< endl << endl;
// int add(int a_local_add = 0, int b_local_add = 0);
// int diff(int a_local_diff = 0, int b_local_diff = 0);
        monFlux << "#endif //" << toUp ( nameFile ) << "_H_INCLUDED";
    }

    monFlux.close();
    file = nameFile + ".c" + pp ;
    ofstream monFlux2 ( file.c_str(), ios::app );

    if ( !monFlux2 ) {
        cerr << "ERROR: Impossible to open the file ";
        ierr ( file );
        cerr << " in append mode!" << endl;
        return 1;
    } else {
        monFlux2 << "#include \"" << nameFile << ".h\"" << endl << endl;
        monFlux2 <<  parameters << "{" << endl;
        monFlux2 << "// ..." << endl;

        if ( parameters.substr ( 0,4 ) != "void" ) { // Spaces and tabulations are deleted the beginning.
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
       clog << "fileCBP: " << fileCBP << endl;
    updateCBP();
    YouMustDo();
    getline ( cin, file ); // Enter to quit?
    return 0;
}
