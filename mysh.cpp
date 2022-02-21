//includes and namespace
#include <unistd.h>     // getpid(), getcwd()
#include <sys/wait.h>   // wait()
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

//function definition
int history(bool clear);
void bye();
int replay(int number);
int start(string program, string param);
int background(string program, string param);
int terminate(int id);

int main(void){
    string commandLine;
    char* command[4];
    int i= 0;
    //get user input
    cout << "#";
    getline(cin, commandLine);
    
    //copy string format to char* format bc it wasnt working befor
    char *cstr = new char[commandLine.length() + 1];
    strcpy(cstr, commandLine.c_str());
    char *token = strtok(cstr, " ");
    
    while(token != NULL){
        command[i++] = token;
        token = strtok(NULL, " ");
    }
    
    if(strcmp(command[0], "history") == 0){
        history(command[1]);
    }else if(strcmp(command[0], "byebye") == 0){
        bye();
    }else if(strcmp(command[0], "replay") == 0){
        int j;
        sscanf(command[1], "%d", &j);
        replay(j);
    }else if(strcmp(command[0], "start") == 0){
        start(command[1], command[2]);
    }else if(strcmp(command[0], "background") == 0){
        background(command[1], command[2]);
    }else if(strcmp(command[0], "terminate") == 0){
        int j;
        sscanf(command[1], "%d", &j);
        terminate(j);
    }

    bye();
    return 0;
}

//function to handle the history command
//parameter: boolean clear, if true will clear the history
//returns 1 if success and 0 if fail
int history(bool clear){
    return 0;
}

//function to close the terminal
//saves history and exits the program
void bye(){

    cout << "goodbye\n";
    exit(0);
}

int replay(int number){
    return 0;
}

int start(string program, string param){
    return 0;
}

int background(string program, string param){
    return 0;
}

int terminate(int id){
    return 0;
}