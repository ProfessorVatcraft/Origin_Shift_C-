#include <iostream>
#include <vector>
//Randomizer libraries
#include <ctime>
#include <cstdlib>
//Libraries for custom unicode characters
#include <io.h>
#include <fcntl.h>

using namespace std;

// Define Node
class Node {
public:
    int direction_x;
    int direction_y;
    Node(int x, int y) {
        direction_x = x;
        direction_y = y;
    }
};

// Define Maze
class Maze {
public:
    int height;
    int width;
    Node origin;
    vector<vector<Node>> mazeMap;
    //Initializing simple perfect maze
    Maze(int h, int w) : height(h), width(w), origin(0, 0) {
        mazeMap = vector<vector<Node>>(h, vector<Node>(w, Node(0, 0)));
        for (int i = 0; i < h; i++){
            for (int j = 0 ; j < w; j++){
                mazeMap[i][j].direction_x = 1;
                if (j == w - 1) {
                    mazeMap[i][j].direction_x = 0;
                    mazeMap[i][j].direction_y = -1;
                }
            }
        }
        mazeMap[h - 1][w - 1].direction_x = 0;
        mazeMap[h - 1][w - 1].direction_y = 0;
        srand(time(0));
    }
    //Origin initial coordinates
    int origin_pos_x = width - 1;
    int origin_pos_y = height - 1;
    //Origin shift
    void OriginShift (){
        //Choose X or Y axis
        bool direction = rand() % 2 == 0;

        if (direction) { //Shifting the Origin Node in the X axis
            //Check for out of bound
            if (origin_pos_x + 1 == width) {
                shiftLeft();
            }
            else if (origin_pos_x - 1 == -1) {
                shiftRight();
            }
            //Shift Origin Node either left or right
            else {
                bool shiftTo = rand() % 2 == 0;
                if (shiftTo){
                    shiftLeft();
                }
                else {
                    shiftRight();
                }
            }
        }
        else { //Shifting the Origin Node in the Y axis
            //Check for out of bound
            if (origin_pos_y + 1 == height){
                shiftUp();
            }
            else if (origin_pos_y - 1 == -1){
                shiftDown();
            }
            else {
                bool shiftTo = rand() % 2 == 0;
                if (shiftTo){
                    shiftUp();
                }
                else {
                    shiftDown();
                }
            }
        }
    }
    //Shifting directions
    void shiftRight(){
        mazeMap[origin_pos_y][origin_pos_x + 1] = mazeMap[origin_pos_y][origin_pos_x];
        mazeMap[origin_pos_y][origin_pos_x].direction_x = 1;
        origin_pos_x++;
    }
    void shiftLeft(){
        mazeMap[origin_pos_y][origin_pos_x - 1] = mazeMap[origin_pos_y][origin_pos_x];
        mazeMap[origin_pos_y][origin_pos_x].direction_x = -1;
        origin_pos_x--;
    }
    void shiftUp(){
        mazeMap[origin_pos_y - 1][origin_pos_x] = mazeMap[origin_pos_y][origin_pos_x];
        mazeMap[origin_pos_y][origin_pos_x].direction_y = 1;
        origin_pos_y--;
    }
    void shiftDown(){
        mazeMap[origin_pos_y + 1][origin_pos_x] = mazeMap[origin_pos_y][origin_pos_x];
        mazeMap[origin_pos_y][origin_pos_x].direction_y = -1;
        origin_pos_y++;
    }

    //Function to print the maze
    void printMaze() {
        //Define arrow characters
        _setmode(_fileno(stdout), _O_U16TEXT);
        const wchar_t R = L'\x2192';
        const wchar_t L = L'\x2190';
        const wchar_t U = L'\x2191';
        const wchar_t D = L'\x2193';
        const wchar_t Origin = L'\x00D8';
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (mazeMap[i][j].direction_x == -1){
                    wcout << ' ' << L << ' ' << 'o';
                }
                else {
                    if (mazeMap[i][j - 1].direction_x == 0 || mazeMap[i][j - 1].direction_x == -1){
                        wcout << "   ";
                    }
                    if (mazeMap[i][j].direction_x == 0 && mazeMap[i][j].direction_y == 0){
                        wcout << Origin;
                    }
                    else {
                        wcout << 'o';
                        if (mazeMap[i][j].direction_x == 1){
                            wcout << ' ' << R << ' ';
                        }
                    }
                }
            }
            wcout << endl;
            for (int k = 0; k < width; k++){
                if (mazeMap[i][k].direction_y == -1){
                    wcout << D << "   ";
                }
                else if (i < height - 1 && mazeMap[i + 1][k].direction_y == 1){
                    wcout << U << "   ";
                }
                else {
                    wcout << "    ";
                }
            }
            wcout << endl;
        }
    }
};

int main() {
    // Input handling
    int mazeSize;
    cout << "Enter maze size(size > 1): ";
    cin >> mazeSize;
    if (mazeSize < 2) {
        cout << "Invalid size!" << endl;
    }
    else {
        Maze myMaze(mazeSize, mazeSize);
        myMaze.printMaze();
        char iterate;
        wcout << "Press 'i' to iterate the maze 1 time" << endl;
        wcout << "Press 'f' to iterate the maze multiple times" << endl;
        wcout << "Press any other keys to end" << endl;
        do {
            cin >> iterate;
            if (iterate != 'i' && iterate != 'f') {
                break;
            }
            if (iterate == 'i'){
                myMaze.OriginShift();
                myMaze.printMaze();
            }
            else {
                for (int i = 1; i <= mazeSize * mazeSize * 10; i++){
                    myMaze.OriginShift();
                }
                myMaze.printMaze();
            }
        }while(iterate == 'i' || iterate == 'f');
    }
    return 0;
}
