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
int replay(vector<string> hist);
int start(vector<string> hist);
int background(vector<string> hist);
int terminate(vector<string> hist);
void writeToHist(vector<string> hist);

int main(void){
    //create history vector
    vector<string> histv;

    int i, success;
    bool loopcheck = true;
    string commandLine;
    char* command[4];
    cout << "#";
    while(loopcheck){
        i= 0;
        //get user input
        
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
        
        for (auto ir = histv.rbegin(); ir != histv.rend(); ++ir)
        cout << *ir ;

        //find which command was typed and trigger accompanying function
        if(strcmp(command[0], "history") == 0){
            success = history(histv);
        }else if(strcmp(command[0], "byebye") == 0){
            loopcheck = false;
            success = 1;
            break;
        }else if(strcmp(command[0], "replay") == 0){
            success = replay(histv);
        }else if(strcmp(command[0], "start") == 0){
            success = start(histv);
        }else if(strcmp(command[0], "background") == 0){
            success = background(histv);
        }else if(strcmp(command[0], "terminate") == 0){
            success = terminate(histv);
        }
        if(success != 1){
            cout << "Your command failed, try running this shell with sudo";
        }
        cout << "\n#";
    }
    
    std::ofstream output_file("mysh.history");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(histv.begin(), histv.end(), output_iterator);
    output_file.close();
    exit(0);
    return 0;
}


int history(vector<string> hist){
    //variables
    char* command[4];
    char* cstr;
    int i= 0;
    //copy c++ string to char*
    
    strcpy(cstr, hist.back().c_str());
    char *token = strtok(cstr, " ");
    //tokenize 
    while(token != NULL){
        command[i++] = token;
        token = strtok(NULL, " ");
    }
    if(i>1){
        if(strcmp(command[1], "-c") == 0){
            hist.clear();
            return 1;
        }
    }
    int j = 0;
    for (auto ir = hist.rbegin(); ir != hist.rend(); ++ir)
        cout << *ir ;
    return 0;
}


int replay(vector<string> hist){
    cout << "replay";
    return 0;
}

int start(vector<string> hist){
    cout << "start";
    return 0;
}

int background(vector<string> hist){
    cout << "background";
    return 0;
}

int terminate(vector<string> hist){
    cout << "terminate";
    return 0;
}