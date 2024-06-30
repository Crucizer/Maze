#include <iostream>
#include <vector>
#include <tuple>
#include <random> 

using namespace std;

class Node {
   public:
        bool visited = false;
        int value = 0;
        int x;
        int y;
        int size;
        Node (int Nodey,int Nodex, int Size) {
            x = Nodex;
            y = Nodey;
            size = Size;
        }

        std::vector<std::tuple <int, int>> getNeighbors () {
            std::vector<std::tuple<int, int>> neighbors;
            std::tuple <int, int> temp;
            if (y > 0) {
            neighbors.push_back(std::make_tuple(y - 1,x));

            }
            if (x > 0) {
                neighbors.push_back(std::make_tuple(y, x-1));
            }
            if (x < size - 1) {
                neighbors.push_back(std::make_tuple(y, x+1));
            }
            if (y < size - 1) {
                neighbors.push_back(std::make_tuple(y + 1,x));
            }

            return neighbors;

        }
};

class Board {
    public:
        int size;
        std::vector < std::vector <Node>> maze; 

        // Constructor 
        Board(int Size) {
            size = Size;

            // making the board
            for (int i=0;i<size;i++) {
                std::vector <Node> row; // creating a row
                for (int j=0;j<size;j++) {
                    row.push_back(Node(i,j, size));
                }
                maze.push_back(row);
            }

            // making the borders
            // makeBorders();

        }

        // changes borders to value 1
        void makeBorders() {
            for(int i=0;i<size;i++) {
                for(int j=0;j<size;j++) {
                    if(i == 0 || j == 0 || i == size-1 || j == size -1) {
                        maze[i][j].value = 1;
                    }
                }
            }
        }


        // printing the board
        void printBoard() {
            for(int i=0;i<size;i++) {
                for(int j=0;j<size;j++) {
                    if (maze[i][j].value == 1
                    ){ 
                        std::cout << "# ";
                    }
                    else {
                        std::cout << ". ";
                    }
                }
                std::cout << '\n';
            }
        }

        void generateBoard() {
            // lets start from the first cell
            int nextX = 0;
            int nextY = 0;
            std::vector <std::tuple < int, int>> path;
            maze[nextY][nextX].visited = true;
            

            while (nextX != -1) {

                std::tuple <int, int> next = nextCell(maze[nextY][nextX]);

                nextX = get<1>(next);
                nextY = get<0>(next);

                path.push_back(std::make_tuple(nextY, nextX));
            }


            for(int i =0; i<path.size(); i++) {
                std::cout << get<0>(path[i]) << " " << get<1>(path[i]) << endl;
            }

        }

        std::tuple<int, int> nextCell (Node node) {
            std::vector<std::tuple <int, int> > neighbors = node.getNeighbors();

            bool flag = true;
            int randomIndex;
            while (flag) {
                if (neighbors.size() != 0){
                    randomIndex = getRandom(neighbors.size());

                    int neighborX = get<1>(neighbors[randomIndex]);
                    int neighborY = get<0>(neighbors[randomIndex]);

                    if (maze[neighborY][neighborX].visited == false){
                        flag = false;
                        maze[neighborY][neighborX].visited = true;
                        maze[neighborY][neighborX].value = 1;
                        std::cout << "Next Cell: " << neighborY << " " << neighborX << endl;
                        printBoard();
                        return std::make_tuple(neighborY, neighborX);
                    }
                    else { // visited cell, remove from neighbors 
                        neighbors.erase(neighbors.begin() + randomIndex);
                    }
                }
                else {
                    flag = false;
                    return std::make_tuple(-1,-1); // no empty neighbors
                }
            }
            
            return std::make_tuple(-1,-1); // no ensure a return statement

        }

        int getRandom(int max) {
            // get a random number
            std::random_device rd; // getting random seed from the os
            std::mt19937 gen(rd()); // using mersenne twister as the random number engine

            // defining a distribution
            std::uniform_int_distribution<> dist(0, max-1);
            int rand = dist(gen);

            return rand;
        }
};

int main () {

    Board board(10);
    board.generateBoard();
    board.printBoard();

    return 0;
}
