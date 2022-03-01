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
using namespace std;

//function definition
int history(vector<string>& hist);
int replay(char*args[], vector<string>& hist);
int start(char*args[]);
int background(char*args[]);
int terminate(char*args[]);
int terminateall();

vector<pid_t> children;

int main(void){
    //create history vector
    vector<string> histv;

    int i, success;
    bool loopcheck = true;
    string commandLine;
    char* command[10];
    cout << "#";
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
        }
        if(success != 0){
            cout << "Your command failed, try running this shell with sudo";
        }
        cout << "#";
    }
    
    std::ofstream output_file("mysh.history");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(histv.begin(), histv.end(), output_iterator);
    output_file.close();
    exit(0);
    return 0;
}


int history(vector<string>& hist){
    if(hist.back().find("-c") != string::npos){
        hist.clear();
        return 0;
    }

    for (int j = hist.size()-1; j>=0;j--){
        cout << hist.size()-(j+1) << ": " << hist[j] << endl;
    }

    std::ifstream input_file("mysh.history");
    std::string content;
    std::vector<std::string> numbers;

    while(input_file >> content) 
        numbers.push_back(content);
    for(int i = numbers.size() - 1; i >= 0; i--)
        std::cout << numbers[i] << endl;

    input_file.close();


    
    

    return 0;
}


int replay(char*args[], vector<string>& hist){
    int pos = (hist.size()-1)-(atoi(args[1])+1);
    int i = 0;
    char *cstrs = new char[hist[pos].length() + 1];
    strcpy(cstrs, hist[pos].c_str());
    char *tokens = strtok(cstrs, " ");
    char* rcommand[10];

    while(tokens != NULL){
        rcommand[i++] = tokens;
        tokens = strtok(NULL, " ");
    }
    
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
    }
    return 0;
}

int start(char*args[]){
    pid_t pid;
    pid = fork();

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
    pid_t cpid;
    cpid = fork();

    if(cpid < 0){
        cout << stderr<< "fork fail"<< endl;
        return 1;
    }else if(cpid == 0){
        cpid = execvp(args[1], args);
    }
    children.push_back(cpid);
    cout<<cpid<<endl;
    
    return 0;
}

int terminate(char*args[]){
    int val = 1;
    if(0==kill(atoi(args[1]), 0)){
        val = kill(atoi(args[1]), SIGKILL);
    }
    std::vector<pid_t>::iterator pid, el;
    pid = std::find(children.begin(), children.end(), atoi(args[1]));
    if(pid != children.end()) {
        children.erase(pid);
    }
    return val;
}

int terminateall(){
    for(int i = 0; i < children.size();i++){
        kill(children[i], SIGKILL);
    }
    children.clear();
    return 0;
}

int repeat(char*args[], vector<string>& hist){
    int pos = (hist.size()-1)-(atoi(args[1])+1);
    int i = 0;
    char *cstrs = new char[hist[pos].length() + 1];
    strcpy(cstrs, hist[pos].c_str());
    char *tokens = strtok(cstrs, " ");
    char* rcommand[10];

    while(tokens != NULL){
        rcommand[i++] = tokens;
        tokens = strtok(NULL, " ");
    }
    
    if(strcmp(rcommand[0], "history") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            history(hist);
        }    
    }else if(strcmp(rcommand[0], "start") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            start(rcommand);
        }
    }else if(strcmp(rcommand[0], "background") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            history(hist);
        }
    }else if(strcmp(rcommand[0], "terminate") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            terminate(rcommand);
        }
    }else if(strcmp(rcommand[0], "terminateall") == 0){
        for(int j = 0; j < atoi(args[1]); j++){
            terminateall();
        }
    }
    return 0;
}