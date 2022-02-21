//includes and namespace
#include <unistd.h>     // getpid(), getcwd()
#include <sys/wait.h>   // wait()
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

//function definition
int history(bool clear, fstream& historyFile);
void bye(fstream& historyFile);
int replay(int number);
int start(char* commands[]);
int background(char* commands[]);
int terminate(int id);
void writeToHist(char* commands[]);

int main(void){
    //open file
    string filename = "history.txt";
    std::fstream historyFile;
    historyFile.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

    string commandLine;
    char* command[4];
    while(true){
        int i= 0;
        //get user input
        cout << "\n#";
        getline(cin, commandLine);
        
        //copy string format to char* format bc it wasnt working befor
        char *cstr = new char[commandLine.length() + 1];
        strcpy(cstr, commandLine.c_str());
        char *token = strtok(cstr, " ");
        
        while(token != NULL){
            command[i++] = token;
            token = strtok(NULL, " ");
        }
        //save to history
        for(int j = 0;j <= i; j++){
            historyFile << command[j];
        }
        historyFile << endl;

        //find which command was typed and trigger accompanying function
        if(strcmp(command[0], "history") == 0){
            if(command[1] == "-c"){
                history(true, historyFile);
            }else{
                history(false, historyFile);
            }
        }else if(strcmp(command[0], "byebye") == 0){
            bye(historyFile);
        }else if(strcmp(command[0], "replay") == 0){
            int j;
            sscanf(command[1], "%d", &j);
            replay(j);
        }else if(strcmp(command[0], "start") == 0){
            start(command);
        }else if(strcmp(command[0], "background") == 0){
            background(command);
        }else if(strcmp(command[0], "terminate") == 0){
            int j;
            sscanf(command[1], "%d", &j);
            terminate(j);
        }
    }
    

    bye(historyFile);
    return 0;
}

//function to handle the history command
//parameter: boolean clear, if true will clear the history
//returns 1 if success and 0 if fail
int history(bool clear, fstream& historyFile){
    cout << "history";
    return 0;
}

//function to close the terminal
//saves history and exits the program
void bye(fstream& historyFile){
    historyFile.close();
    exit(0);
}

int replay(int number){
    cout << "replay";
    return 0;
}

int start(char* commands[]){
    cout << "start";
    return 0;
}

int background(char* commands[]){
    cout << "background";
    return 0;
}

int terminate(int id){
    cout << "terminate";
    return 0;
}