
#include <unistd.h>     // getpid(), getcwd()
#include <sys/wait.h>   // wait()
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;


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

    return 0;
}