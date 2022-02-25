//includes and namespace
#include <unistd.h>     
#include <sys/wait.h>   
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

//function definition
int history(vector<string> hist);
int replay(int number);
int start(char* commands[]);
int background(char* commands[]);
int terminate(int id);
void writeToHist(char* commands[]);

int main(void){
    //create history vector
    vector<string> histv;

    int i;
    bool loopcheck = true;
    string commandLine;
    char* command[4];
    while(loopcheck){
        i= 0;
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
        //push command on the history vector
        histv.push_back(commandLine);
        
        

        //find which command was typed and trigger accompanying function
        if(strcmp(command[0], "history") == 0){
            if(i>=2){
                history(histv);
            }else{
                history(histv);
            }
        }else if(strcmp(command[0], "byebye") == 0){
            loopcheck = false;
        }else if(strcmp(command[0], "replay") == 0){
            if(i>=2){
                int j;
                sscanf(command[1], "%d", &j);
                replay(j);
            }else{
                cout << "A command number must be given";
            }
            
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
    
    std::ofstream output_file("history.mysh");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(histv.begin(), histv.end(), output_iterator);

    exit(0);
    return 0;
}

//function to handle the history command
//parameter: boolean clear, if true will clear the history
//returns 1 if success and 0 if fail
int history(vector<string> historyFile){
    cout << "history";
    return 0;
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