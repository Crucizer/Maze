#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// what functions should each node have? 

class Node {
   public:
        bool visited = false;
        int value = 0;
        int x;
        int y;
        int size = 6;
        Node (int Nodey,int Nodex) {
            x = Nodex;
            y = Nodey;
        }

        std::vector<std::tuple <int, int>> getNeighbors () {
            std::vector<std::tuple<int, int>> neighbors;
            std::tuple <int, int> temp;
            if (y>0) {
                neighbors.push_back(std::make_tuple(x,y-1));
            }
            if (x>0){
                neighbors.push_back(std::make_tuple(x-1, y));
            }
            if (x < size) {
                neighbors.push_back(std::make_tuple(x+1, y));
            }
            if (y < size) {
                neighbors.push_back(std::make_tuple(x, y+1));
            }

            return neighbors;

        }
};

int main () {

    // using a vector
    int size = 6;
    std::vector<std::vector<Node> > maze;

    for (int i=0;i<size;i++) {
        std::vector <Node> row; // creating a row
        for (int j=0;j<size;j++) {
            row.push_back(Node(i,j));
        }
        maze.push_back(row);
    }


    // Making borders for the maze
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            if(i == 0 || j == 0 || i == size-1 || j == size -1) {
                maze[i][j].value = 1;
            }
        }
    }

    // Printing the maze
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            if (maze[i][j].value == 1
            ){ 
                std::cout << "# ";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}
