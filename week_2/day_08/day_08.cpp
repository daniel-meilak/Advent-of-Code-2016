#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
void square(std::vector<std::vector<bool>> &screen, const int &a, const int &b);
void rotate_row(std::vector<std::vector<bool>> &screen, const int &a, const int &b);
void rotate_col(std::vector<std::vector<bool>> &screen, const int &a, const int &b);
void print_screen(const std::vector<std::vector<bool>> &screen);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "x", "y", "rotate", "=", "by"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    int width  = 50;
    int height =  6;

    // screen
    std::vector<std::vector<bool>> screen(height, std::vector<bool>(width,false));

    // work through input
    for (std::vector<std::string> line : input){

        if      (line[0] == "rect"  ){ square(screen, std::stoi(line[1]), std::stoi(line[2]));     }
        else if (line[0] == "row"   ){ rotate_row(screen, std::stoi(line[1]), std::stoi(line[2])); }
        else if (line[0] == "column"){ rotate_col(screen, std::stoi(line[1]), std::stoi(line[2])); }
        else { std::cout << "Error reading input" << std::endl; }
    }

    // count lit pixels
    int count = 0;
    for (size_t i=0; i<screen.size(); i++){
        for (size_t j=0; j<screen[0].size(); j++){
            if (screen[i][j]){ count++; }
        }
    }

    //int count = grid_count(screen,true);

    std::cout << "Answer (part 1): " << count << std::endl;
    
    // print screen for part 2
    std::cout << "Answer (part 2):" << std::endl;
    print_screen(screen);

    return 0;
}

// turns on square of size a*b at top left of screen
void square(std::vector<std::vector<bool>> &screen, const int &a, const int &b){

    for (int i=0; i<b; i++){
        for (int j=0; j<a; j++){
            screen[i][j] = true;
        }
    }
}

// rotate row A by B pixels
void rotate_row(std::vector<std::vector<bool>> &screen, const int &a, const int &b){

    // copy row
    std::vector<bool> copy = screen[a];

    size_t size = screen[a].size();
    for (size_t i=0; i<size; i++){
        screen[a][i] = copy[mod<int>(i-b,size)];
    }
}

// rotate column A by B pixels
void rotate_col(std::vector<std::vector<bool>> &screen, const int &a, const int &b){

    size_t size = screen.size();

    // copy column
    std::vector<bool> copy(size);
    for (size_t i=0; i<size; i++){ copy[i] = screen[i][a]; }

    for (size_t i=0; i<size; i++){
        screen[i][a] = copy[mod<int>(i-b,size)];
    } 
}

// print screen to terminal
void print_screen(const std::vector<std::vector<bool>> &screen){

    for (std::vector<bool> line : screen){
        for (bool pixel : line){
            if (pixel){ std::cout << '$'; }
            else { std::cout << ' '; }
        }
        std::cout << std::endl;
    }
}

