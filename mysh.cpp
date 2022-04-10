//includes and namespace
#include <unistd.h>     
#include <sys/wait.h>  
#include <sys/types.h> 
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
#include <signal.h>
#include <algorithm>
#include <filesystem>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
using namespace std;

//function definition
int history(vector<string>& hist);
int replay(char*args[], vector<string>& hist);
int start(char*args[]);
int background(char*args[]);
int terminate(char*args[]);
int terminateall();
int repeat(char*args[], vector<string>& hist);
int dwelt(char*args[]);
int createFile(char*args[]);
int coppyFile(char*args[]);

//vector to store all the children pid for the terminateall function
vector<pid_t> children;
//stat for checking
struct stat sb;


int main(void){
    //create history vector
    vector<string> histv;
    //create base variables needed
    int i, success;
    bool loopcheck = true;
    string commandLine;
    char* command[10];
    cout << "#";

    //start the main loop that handles user input and tokenizing and starting the functions
    while(loopcheck){
        i= 0;
        //get user input
        
        getline(cin, commandLine);
        
        //push command on the history vector
        histv.push_back(commandLine);

        //copy string format to char* format bc it wasnt working befor
        char *cstr = new char[commandLine.length() + 1];
        strcpy(cstr, commandLine.c_str());
        char *token = strtok(cstr, " ");
        
        while(token != NULL){
            command[i++] = token;
            token = strtok(NULL, " ");
        }
        
        


        //find which command was typed and trigger accompanying function
        if(strcmp(command[0], "history") == 0){
            success = history(histv);
        }else if(strcmp(command[0], "byebye") == 0){
            loopcheck = false;
            success = 0;
            break;
        }else if(strcmp(command[0], "replay") == 0){
            success = replay(command, histv);
        }else if(strcmp(command[0], "start") == 0){
            success = start(command);
        }else if(strcmp(command[0], "background") == 0){
            success = background(command);
        }else if(strcmp(command[0], "terminate") == 0){
            success = terminate(command);
        }else if(strcmp(command[0], "terminateall") == 0){
            success = terminateall();
        }else if(strcmp(command[0], "repeat") == 0){
            success = repeat(command, histv);
        }else if(strcmp(command[0], "dwelt") == 0){
            success = dwelt(command);
        }
        if(success != 0){
            cout << "Your command failed, try running this shell with sudo";
        }
        cout << "#";
    }
    //save vector to history file
    std::ofstream output_file("mysh.history");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(histv.begin(), histv.end(), output_iterator);
    output_file.close();

    //end program
    exit(0);
    return 0;
}


int history(vector<string>& hist){
    //clear history if command is passed
    if(hist.back().find("-c") != string::npos){
        hist.clear();
        return 0;
    }
    //print out history vector contents
    for (int j = hist.size()-1; j>=0;j--){
        cout << hist.size()-(j+1) << ": " << hist[j] << endl;
    }
    //read from history file if it exists
    std::ifstream input_file("mysh.history");
    std::string content;
    std::vector<std::string> numbers;

    while(input_file >> content) 
        numbers.push_back(content);
    for(int i = numbers.size() - 1; i >= 0; i--)
        std::cout << numbers[i] << endl;

    //close file
    input_file.close();

    return 0;
}


int replay(char*args[], vector<string>& hist){
    //get proper position and make other varables set up
    int pos = (hist.size()-1)-(atoi(args[1])+1);
    int i = 0;
    char *cstrs = new char[hist[pos].length() + 1];
    strcpy(cstrs, hist[pos].c_str());
    char *tokens = strtok(cstrs, " ");
    char* rcommand[10];
    //tokenize again
    while(tokens != NULL){
        rcommand[i++] = tokens;
        tokens = strtok(NULL, " ");
    }
    //run proper command
    if(strcmp(rcommand[0], "history") == 0){
        history(hist);
    }else if(strcmp(rcommand[0], "start") == 0){
        start(rcommand);
    }else if(strcmp(rcommand[0], "background") == 0){
        background(rcommand);
    }else if(strcmp(rcommand[0], "terminate") == 0){
        terminate(rcommand);
    }else if(strcmp(rcommand[0], "terminateall") == 0){
        terminateall();
    }else if(strcmp(rcommand[0], "repeat") == 0){
        repeat(rcommand, hist);
    }else if(strcmp(rcommand[0], "dwelt") == 0){
        dwelt(rcommand);
    }
    return 0;
}

int start(char*args[]){
    //set up variables
    pid_t pid;
    pid = fork();
    //run the process
    if(pid < 0){
        cout << stderr<< "fork fail"<< endl;
        return 1;
    }else if(pid == 0){
        execvp(args[1], args);
    }else {
        pid = wait(NULL);
    }
    


    return 0;
}

int background(char*args[]){
    //make variables
    pid_t cpid;
    cpid = fork();
    //run process in background
    if(cpid < 0){
        cout << stderr<< "fork fail"<< endl;
        return 1;
    }else if(cpid == 0){
        cpid = execvp(args[1], args);
    }
    //add to child vector
    children.push_back(cpid);
    //print pid
    cout<<cpid<<endl;
    
    return 0;
}

int terminate(char*args[]){
    int val = 1;
    //send kill signal
    if(0==kill(atoi(args[1]), 0)){
        val = kill(atoi(args[1]), SIGKILL);
    }
    //remove terminated process from vector
    std::vector<pid_t>::iterator pid, el;
    pid = std::find(children.begin(), children.end(), atoi(args[1]));
    if(pid != children.end()) {
        children.erase(pid);
    }
    return val;
}

int terminateall(){
    //terminate all pids in child vector
    for(int i = 0; i < children.size();i++){
        kill(children[i], SIGKILL);
    }
    //clear bc all pids terminated
    children.clear();
    return 0;
}

int repeat(char*args[], vector<string>& hist){
    //variables
    int i = 0;
    char* argv[10];
    //pull out command to be repeated
    while(args[i] != NULL){
        argv[i-2] = args[i];
    }
    //run command the specified number of times
    if(strcmp(argv[0], "history") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            history(hist);
        }    
    }else if(strcmp(argv[0], "start") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            start(argv);
        }
    }else if(strcmp(argv[0], "background") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            background(argv);
        }
    }else if(strcmp(argv[0], "terminate") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            terminate(argv);
        }
    }else if(strcmp(argv[0], "terminateall") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            terminateall();
        }
    }
    return 0;
}

int dwelt(char*args[]){
    int file = 0;
    int direc = 0;
    std::ifstream f(args[1]);
    if(f.good())file++;
    if (stat(args[1], &sb) == 0 && S_ISDIR(sb.st_mode))direc++;
    if(direc > 0)cout << "Abode is." << endl;
    else if(file > 0)cout << "Dwelt indeed." << endl;
    else cout << "Dwelt not." << endl;
    return 0;
}

int createFile(char*args[]){
    std::ifstream f(args[1]);
    if(f.good()){
        cout << "Error: file already exists"<< endl;
        return 0;
    }
    std::ofstream output_file(args[1]);
    output_file << "Draft" << endl;
    output_file.close();
    return 0;
}

int coppyFile(char*args[]){
    return 0;
}