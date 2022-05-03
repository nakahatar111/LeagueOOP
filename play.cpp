#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <unistd.h> 
#include <math.h>
#include <vector>
#include <regex>
#include <string>
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[])
{
    string inputfilename;
    int opt;
    while((opt = getopt(argc, argv, "i:s:d:t:")) != -1)
    {
        switch(opt)
        {
            case 'i':
                cout << "this is the filename " << optarg << endl;
                inputfilename = optarg;
                break;
            case 's':
                cout << "this is player1 name " << optarg << endl;
                break;
            case 'd':
                cout << "this is player 2 name " << optarg << endl;
                break;
            case 't':
                cout << "this is the team name to be compared " << optarg << endl;
                break;
        }
    }
    if(inputfilename.empty()){ // check for emtpy input 
        cout << "Need an input file" << endl;
        return -1;
    }
    ifstream myInputFile;
    string line;
    myInputFile.open(inputfilename);

    if(myInputFile.is_open())
    {
        //do_Read()
        //read in the file function
        myInputFile.close();
    }

}   