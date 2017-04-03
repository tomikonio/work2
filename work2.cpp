#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>

/*
g++ -o shell *.cpp -std=c++11 -Wall -Wno-vla -pedantic -march=core2 -Os -pipe
-fstack-protector-all -g3 -Wl,-O,1,-z,combreloc
*/


int main(int argc, char** argv){
    char cwd[256];
    std::string input;
    std::cout << "Welcome to OS SHell!\n";
    int flag = 0;
    while(true){
        getcwd(cwd,sizeof(cwd));
        if (strcmp(cwd, getenv("HOME")) == 0){
            std::cout << "OS SHell: " << "~/" << ">";
        }
        else if(strstr(cwd, getenv("HOME"))){
            std::cout << "OS SHell: " << "~" << strrchr(cwd, '/') << ">";
        }
        else{
            std::cout << "OS SHell: " << cwd << ">";
        }
        std::getline(std::cin,input);
        //
        //
        std::istringstream iss(input);
        std::vector<std::string> tokens;
        copy(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            back_inserter(tokens));
        if(tokens[0].compare("cd") == 0){
            if(tokens.size() == 1){
                flag = chdir(getenv("HOME"));
            }
            else{
                flag = chdir(tokens[1].c_str());
                if (flag == -1){
                	perror("OS SHell: cd");
                }
            }
        }
        else if(tokens[0].compare("exit") == 0){
        	break;
        }
    }
    
    std::cout << "C Ya!\n";
    return 0;
}
