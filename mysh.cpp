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
int replay();
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

    bye();
    return 0;
}

//function to handle the history command
//parameter: boolean clear, if true will clear the history
//returns 1 if success and 0 if fail
int history(bool clear){

}

//function to close the terminal
//saves history and exits the program
void bye(){
    exit(0);
}

int replay(){

}

int start(string program, string param){

}

int background(string program, string param){

}

int terminate(int id){

}