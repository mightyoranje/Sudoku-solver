#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <array>

using namespace std;
const int size = 9;
const int empty = 0;
array<int, 9> values{1,2,3,4,5,6,7,8,9};

int input(int sudoku[size][size]){
    int x;
    cout<< "how many cells do you want to fill: ";
    cin >> x;
    for(int t = 0 ; t<x; t++){
        int row,col,v;
        cout<<"which row: ";
        cin>>row;
        cout<<"which col: ";
        cin>>col;
        cout<<"what is the value: ";
        cin>>v;
        sudoku[row-1][col-1]=v;
    }
}

void gui(int sudoku[size][size]){
    string separator, text, padding;
    for (int i = 0; i < size; i++){
        text = "|";
        separator = " -";
        padding = "|";
        for (int j = 0; j < size; j++){
            string value = sudoku[i][j] == empty ? " " : to_string(sudoku[i][j]);
            text = text + "  " + value + "  |";
            separator = separator + "------";
            padding = padding + "     |";
            if (j % 3 == 2 && j != size - 1){
                text = text + "|";
                padding = padding + "|";
            }
        }
        if (i != 0 && i % 3 == 0){
            replace(separator.begin(), separator.end(), '-', '=');
        }
        cout << separator << endl;
        cout << padding << endl;
        cout << text << endl;
        cout << padding << endl;
        
    }
    cout << separator << endl;
}

bool isValid(int sudoku[size][size],int row, int col, int value){

    for(int c = 0; c <size ; c++){
        if(sudoku[row][c] == value) return false;
    }

    for(int r = 0; r<size ; r++){
        if(sudoku[r][col] == value) return false;
    }

    int srow = floor(row/3)*3;
    int scol = floor(col/3)*3;
    for(int r = srow; r < srow + 3; r++){
        for(int c = scol; c < scol + 3; c++ ){
            if(sudoku[r][c] == value) return false;
        }
    }
    return true;
}

bool isemptycell(int sudoku[size][size]){
    for(int i = 0 ; i <size ; i++){
        for(int j = 0 ; j < size ; j++){
            if(sudoku[i][j]==empty) return true;
        }
    }
    return false;
}

bool fill(int sudoku[size][size]){
    int row, col;
    for (int i = 0; i < size * size; i++){
        row = floor(i / size);
        col = i % size;
        if (sudoku[row][col] == empty){
            for (int j = 0; j < size; j++){
                if (isValid(sudoku, row, col, values[j])){
                    sudoku[row][col] = values[j];
                    if (!isemptycell(sudoku) || fill(sudoku)){
                        return true;
                    }
                }
            }
            break;
        }
    }
    sudoku[row][col] = empty;
    return false;
}

void make(int sudoku[size][size]){
    
    for(int i=0 ; i <size; i++){
        for(int j=0; j<size; j++){
            sudoku[i][j] = empty; 
        }
    }
}

int main(){
    
    int sudoku[size][size];

    make(sudoku);
    gui(sudoku);
    input(sudoku);
    gui(sudoku);
    int u;
    cout<<"do you want to solve this?(1=yes/0=no): ";
    cin>> u;
    if(u=1){
        fill(sudoku);
        gui(sudoku);
    }
    return 0;
}
