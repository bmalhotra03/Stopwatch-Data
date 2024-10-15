// Brij Malhotra
// hw1.cpp
// Purpose: Make a program that processes timing data produced by a stopwatch and shows stats 

#include <iostream>
#include "fileUtils.h"
#include <fstream>

using namespace std;

struct Stats{
    int numLaps = 0;
    int totalLaptime = 0;
    int maxLap = 0;
    int minLap = 0;
    int avgLap = 0;
    int * arrPtr = nullptr;

};

// Function prototypes

Stats readFile(char * filename);
char mainMenu();
void goodbyeMsg();
void listFiles(int argc, char *argv[]);
double avgAvg(Stats arr[], int numFiles);
long totTotal(Stats arr[], int numFiles);
void displayStats(Stats userChoice);

int main (int argc, char *argv[]) {
    
    int fileChoice = 0;
    char choice;

    Stats fileArr[6];       
    for (int i = 1; i < argc; i++){         // This code segment creates an array for each of the files in use 
        fileArr[i] = readFile(argv[i]);
    }


    while(choice != '5'){       // For menu choice 2 I could not figure out how to individually show the details by asking the user for
        choice = mainMenu();    // the filename and then moving onto to trigger the readFile function and then proceed to the displaystats function
        if(choice == '1'){
            listFiles(argc, argv);
            cout << endl << endl;
        }else if(choice == '2'){
            cout << " Which file would you like to see stats for? (Enter the number of the file): ";   
            cin >> fileChoice;
            while (fileChoice < 1 || fileChoice > argc - 1){    // -1 has been put because it counts the program execution as an argument 
                cout << " Please enter a number between 1 and " <<  argc - 1 <<  ". " << endl;
                cin >> fileChoice;
            }
            displayStats(fileArr[fileChoice]);    
        }else if(choice == '3'){
            cout << avgAvg(fileArr, argc) << " ms";
            cout << endl << endl;
        }else if(choice == '4'){
            cout << totTotal(fileArr, argc) << " ms";
            cout << endl << endl;            
        }else if(choice == '5'){
            goodbyeMsg();
            cout << endl << endl;
        }else{
            cout << "That is not a valid input. Please enter your choice again.";
            cout << endl << endl;
        }
    }
    return 0;
}

// Function declaration

Stats readFile(char * filename){        // This function reads in from the file into a dynamically stored array
    Stats fstats;
    ifstream input;

    input.open(filename);
    fstats.numLaps = readByte(input);
    fstats.arrPtr = new int[fstats.numLaps];

    for (int i = 0; i < fstats.numLaps; i++){
        fstats.arrPtr[i] = readInt(input);
        if (fstats.arrPtr[i] > fstats.maxLap) {
            fstats.maxLap = fstats.arrPtr[i];
        }
        if (fstats.minLap == 0 || fstats.arrPtr[i] < fstats.minLap) {
            fstats.minLap = fstats.arrPtr[i];
        }
        fstats.totalLaptime += fstats.arrPtr[i];
    }

    fstats.avgLap = fstats.totalLaptime / fstats.numLaps; 

    input.close();

    return fstats;
}

char mainMenu(){        // This function is the mainmenu for the program
    
    char choice;

    cout << endl;
    cout << "Menu for stopwatch data:" << endl << endl;
    cout << "1. List the names of the files that have been loaded." << endl;
    cout << "2. Stats for particular file" << endl;
    cout << "3. The average (mean) time of all averages of files" << endl;
    cout << "4. The total time (sum) of all laps across the files" << endl;
    cout << "5. Exit this program" << endl << endl;

    cout << "Please enter your choice: ";
    cin >> choice;
    cout << endl << endl;

    return choice;
}

void goodbyeMsg(){      // This function is the message given out when the user quits the program
    
    cout << endl;
    cout << "Hope the stats were satisfactory, goodbye. " << endl << endl;
}

void listFiles(int argc, char *argv[]){     // This function lists down the files being used for the program
    
    cout << "The number of files being used are: " << argc - 1 << endl;

    for (int i = 1; i < argc; i++){
        char *argument = argv[i];
        cout << "Argument " << i << ": " << argument << endl;
    }
}

void displayStats(Stats userChoice){        // This function displays the stats of the file

    cout << " The number of laps in this file are: " << userChoice.numLaps << endl;
    cout << " The maximum laptime in this file is: " << userChoice.maxLap << " ms" << endl;
    cout << " The minimum laptime in thie file is: " << userChoice.minLap << " ms" <<endl;
    cout << " The average of the laptimes in this file is: " << userChoice.avgLap << " ms" << endl;
    cout << " The sum of the laptimes in this file is: " << userChoice.totalLaptime << " ms" << endl;
}

double avgAvg(Stats arr[], int argc){       // This function displayes the average of the averages of all files

    double sumAvg = 0;
    double avgAverage = 0;

    for (int i = 0; i < argc; i++){
        sumAvg += arr[i].avgLap;
    }

    avgAverage = sumAvg / argc - 1;

    return avgAverage;
}

long totTotal(Stats arr[], int argc){     // This function displayes the total of the sum of laptimes of all files

    double sumTotal = 0;

    for (int i = 0; i < argc; i++){
        sumTotal += arr[i].totalLaptime;
    }

    return sumTotal;    
}

// Thank you for giving most of the important functions in class, it really helped