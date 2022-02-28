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
using namespace std;

//function definition
int history(vector<string>& hist);
int replay(vector<string> hist);
int start(char*args[]);
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
            success = 1;
            break;
        }else if(strcmp(command[0], "replay") == 0){
            success = replay(histv);
        }else if(strcmp(command[0], "start") == 0){
            success = start(command);
        }else if(strcmp(command[0], "background") == 0){
            success = background(histv);
        }else if(strcmp(command[0], "terminate") == 0){
            success = terminate(histv);
        }
        if(success != 1){
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
    //variables
    if(hist.back().find("-c") != string::npos){
        hist.clear();
        return 1;
    }
    for (int j = hist.size()-1; j>=0;j--){
        cout << hist.size()-(j+1) << ": " << hist[j] << endl;
    }

    return 1;
}


int replay(vector<string> hist){
    cout << "replay"<< endl;
    return 1;
}

int start(char*args[]){
    pid_t cpid;
    cpid = fork();

    if(cpid < 0){
        cout << stderr<< "fork fail"<< endl;
        return 1;
    }else if(cpid == 0){
        execvp(args[1], args);
    }else {
        cpid = wait(NULL);
    }
    


    return 1;
}

int background(vector<string> hist){
    cout << "background"<< endl;
    return 1;
}

int terminate(vector<string> hist){
    cout << "terminate"<< endl;
    return 1;
}