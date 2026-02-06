#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>


int main() {

    FILE* file = fopen("numbers.txt","r");

    char d[100];
    char str[100];
    char* result = (char*)malloc(1);
    result[0] = 0;

    fgets(d,100,file);
    d[strcspn(d, "\n")] = 0;

    while (fgets(str,100,file)) { 

        str[strcspn(str, "\n")] = 0;
        char* t = strtok(str,d);
        while (t) {

            result = (char*)realloc(result,strlen(result) + strlen(t) + (result[0]?2:1));
            strcat(result,t);
            strcat(result," ");
            t = strtok(NULL,d);

        }
    }
    fclose(file);

    if ( result[0] == 0 ) {
        std::cout << "your file no have a word";
        return 0;
    }
    std::cout << result << "\n";
    
    char* t = strtok(result," ");
    std::vector<size_t> num_result{};

    while (t) {
        num_result.push_back(atoi(t));
        t = strtok(NULL,d);
    }
    for ( int i{}; i < num_result.size();++i) {
        std::cout << num_result[i] << " ";
    }
}