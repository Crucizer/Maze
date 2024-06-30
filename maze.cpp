#include <iostream>
#include <vector>
#include <tuple>
#include <random> 
#include <stack>

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
        std::stack < std::tuple <int, int>> stacky;
        std::vector <std::tuple <int, int>> path;
        std::vector < std::vector <int>> board;


        // Constructor 
        Board(int Size) {
            size = Size;

            // making the maze
            for (int i=0;i<size;i++) {
                std::vector <Node> row; // creating a row
                for (int j=0;j<size;j++) {
                    row.push_back(Node(i,j, size));
                }
                maze.push_back(row);
            }

            // making the printable board
            for (int i=0;i<size*2;i++) {
                std::vector <int> row; // creating a row
                for (int j=0;j<size*2;j++) {
                    row.push_back(0);
                }
                board.push_back(row);
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

        void printBoard() {
        for (int i = 0; i < size * 2 - 1; i++) {
            for (int j = 0; j < size * 2 - 1; j++) {
                if (board[i][j] == 1) {
                    std::cout << "# ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << '\n';
            }
        }

        void markPath() {
            for (size_t i = 0; i < path.size() - 1; ++i) {
                int y1 = get<0>(path[i]);
                int x1 = get<1>(path[i]);
                int y2 = get<0>(path[i + 1]);
                int x2 = get<1>(path[i + 1]);

                board[y1 * 2][x1 * 2] = 1;
                board[y2 * 2][x2 * 2] = 1;

                if (x1 == x2) {
                    board[y1 * 2 + (y2 - y1)][x1 * 2] = 1;
                } else if (y1 == y2) {
                    board[y1 * 2][x1 * 2 + (x2 - x1)] = 1;
                }
        }
    }

        void generateBoard() {
            // Starts the dfs from top
            dfs_iter(0,0);

        }

        void dfs_iter (int startY, int startX) {
            stacky.push(make_tuple(startY, startX));
            
            while (!stacky.empty()) {
                int y = get<0>(stacky.top());
                int x = get<1>(stacky.top());
                stacky.pop();

                if (!maze[y][x].visited) {
                    // std:: cout << y<< " " <<x << endl;
                    path.push_back(make_tuple(y,x));
                    maze[y][x].visited = true;
                    maze[y][x].value = 1;

                    // adding neigbors to the stack
                    std::random_device rd; // getting random seed from the os
                    std::mt19937 g(rd()); // using mersenne twister as the random number engine

                    vector <tuple <int, int>> neighbors = maze[y][x].getNeighbors();
                    std::shuffle(neighbors.begin(), neighbors.end(), g);

                    for (const auto& neighbor: neighbors) {
                        int neighborY = get<0>(neighbor);
                        int neighborX = get<1>(neighbor);

                        if(!maze[neighborY][neighborX].visited) {
                            stacky.push(make_tuple(neighborY, neighborX));
                        }
                    }
                }

            }
            markPath();
        }
        
};

int main () {

    Board board(15);
    board.generateBoard();
    board.printBoard();

    return 0;
}
