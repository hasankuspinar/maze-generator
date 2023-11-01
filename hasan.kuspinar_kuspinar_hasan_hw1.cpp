#include <iostream>
#include "Stack.h"
#include <string>
#include <vector>
#include "Randgen.h"
#include <fstream>
using namespace std;
struct Cell
{
    int x;
    int y;
    bool right = 1;
    bool left = 1;
    bool up = 1;
    bool down = 1;
    bool visited = 0;
};

bool vector_find(int num, vector<int> & vector1) // a function that checks if the given num is in the vector or not
{
    if(!vector1.empty())
    {
        for (int i = 0; i < vector1.size(); i++)
        {
            if (num == vector1[i]) // checking if num is equal to the element in the ith index
            {
                return true;
            }
        }
    }
    return false;
}

void vector_initializer(vector<vector<Cell>> & mat1, int rows, int cols) //initializes the x and v values of the cells of the maze vector
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            mat1[i][j].x = j; //assigning the column value to the x of the cell
            mat1[i][j].y = i; //assigning the row value to the y of the cell
        }
    }
}

void recursive_reverse_stack_print(Stack<Cell> & stack1, ofstream & out_file) //prints the stack to the output file in the reverse order recursively
{
    if(!stack1.isEmpty())
    {
        Cell cell1 = stack1.topAndPop();

        recursive_reverse_stack_print(stack1, out_file);

        out_file << cell1.x << " " << cell1.y << endl;
    }
}

void path_finder(int ent_x, int ent_y, int ex_x, int ex_y, int m_id) //finding a path in the maze with the given maze id, entry and exit coordinates
{
    ifstream in_file;
    in_file.open("maze_" + to_string(m_id) + ".txt"); //opening the file that the info will be read from

    int rows, cols;
    string str;
    getline(in_file,str); //getting the first line of the file
    rows = stoi(str.substr(0, str.find(' '))); //getting the row size from the string
    cols = stoi(str.substr(str.find(' '))); //getting the column size from the string

    vector<vector<Cell>> mat(rows, vector<Cell>(cols)); //creating a matrix to store the maze data
    vector_initializer(mat, rows, cols); //initializing x and y values of the cells of the matrix

    while(getline(in_file, str)) //reading every line until there are not any lines left in the file to be read
    {
        int x = stoi(str.substr(str.find('x')+2, str.find(' ')-str.find('x')+2)); //getting the x value from the string
        int y = stoi(str.substr(str.find('y')+2, str.find('l')-(str.find('y')+2)-1)); //getting the y value from the string
        bool right = stoi(str.substr(str.find('r')+2,1)); //getting the right value from the string
        bool left = stoi(str.substr(str.find('l')+2,1)); //getting the left value from the string
        bool up = stoi(str.substr(str.find('u')+2,1)); //getting the up value from the string
        bool down = stoi(str.substr(str.find('d')+2,1)); //getting the down value from the string

        //assigning the values that are get from the file to the matrix
        mat[y][x].right = right;
        mat[y][x].left = left;
        mat[y][x].up = up;
        mat[y][x].down = down;
    }
    in_file.close(); //closing the file

    Stack<Cell> maze_Stack1; //creating the stack for the path
    maze_Stack1.push(mat[ent_y][ent_x]); //pushing the entry cell to the stack
    mat[ent_y][ent_x].visited = 1; //making the entry cell visited
    RandGen rnd;

    while(!(maze_Stack1.top().x == ex_x && maze_Stack1.top().y == ex_y))
    {
        bool no_new_cell_added = true;
        Cell curr = maze_Stack1.top();
        vector<int> nums; //a vector to keep track of the directions in order to not go in the same direction twice

        while(no_new_cell_added) // is true if no new cell has been visited (i.e. no new cell has been added to the stack)
        {
            int direction = rnd.RandInt(1, 4); // 1->right 2->left 3->up 4->down

            if (nums.size() < 4)// && !vector_find(direction, nums)) //checks if there are any directions that has not been tried yet
            {
                if (direction == 1) //right direction
                {
                    if (curr.right == 0) //checks if the right wall of the current is broken
                    {
                        if (mat[curr.y][curr.x + 1].visited == 0) //checks if the right cell of the current is visited
                        {
                            maze_Stack1.push(mat[curr.y][curr.x + 1]); //pushing the right cell into the stack
                            mat[curr.y][curr.x + 1].visited = 1; //making the right cell visited
                            no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                        }
                    }
                }
                else if (direction == 2) //left direction
                {
                    if (curr.left == 0) //checks if the left wall of the current is broken
                    {
                        if (mat[curr.y][curr.x - 1].visited == 0) //checks if the left cell of the current is visited
                        {
                            maze_Stack1.push(mat[curr.y][curr.x - 1]); //pushing the left cell into the stack
                            mat[curr.y][curr.x - 1].visited = 1; //making the left cell visited
                            no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                        }
                    }
                }
                else if (direction == 3) //up direction
                {
                    if (curr.up == 0) //checks if the up wall of the current is broken
                    {
                        if (mat[curr.y + 1][curr.x].visited == 0) //checks if the up cell of the current is visited
                        {
                            maze_Stack1.push(mat[curr.y + 1][curr.x]); //pushing the up cell into the stack
                            mat[curr.y + 1][curr.x].visited = 1; //making the up cell visited
                            no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                        }
                    }
                }
                else if (direction == 4) //down direction
                {
                    if (curr.down == 0) //checks if the down wall of the current is broken
                    {
                        if (mat[curr.y - 1][curr.x].visited == 0) //checks if the down cell of the current is visited
                        {
                            maze_Stack1.push(mat[curr.y - 1][curr.x]); //pushing the down cell into the stack
                            mat[curr.y - 1][curr.x].visited = 1; //making the down cell visited
                            no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                        }
                    }
                }
                if(!vector_find(direction, nums))
                {
                    nums.push_back(direction); //adding the current direction to the vector if it is not already in it
                }
            }
            else //if no_new_cell_added is still true after all the directions have been tried we make it false since there is nowhere to go from this cell,
                // and we need to pop this cell from the stack since all the directions have been tried, and we need to go back to the cell before and try again
            {
                maze_Stack1.pop();
                no_new_cell_added = false;
            }
        }
    }

    ofstream output_file; //creating the output file for the path to be written to
    output_file.open("maze_" + to_string(m_id) + "_path_" + to_string(ent_x) + "_" + to_string(ent_y) + "_" + to_string(ex_x) + "_" + to_string(ex_y) + ".txt");
    recursive_reverse_stack_print(maze_Stack1, output_file);
}

void print_matrix(ofstream & out_file, int rows, int cols, vector<vector<Cell>> mat) //prints the data of the maze to the output file
{
    out_file << rows << " " << cols << endl;


    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out_file << "x=" << mat[i][j].x << " y=" << mat[i][j].y << " l=" << mat[i][j].left << " r=" << mat[i][j].right << " u="
                        << mat[i][j].up << " d=" << mat[i][j].down << endl;
        }
    }


    out_file.close();
}

int main()
{
    int num_of_mazes, row, col;
    cout << "Enter the number of mazes: ";
    cin >> num_of_mazes;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> row >> col;

    //-------------------------------------------------------------
    //-------------------------------------------------------------
    //Maze generation

    for(int id = 1; id <= num_of_mazes; id++) //id = id of the maze
    {
        vector<vector<Cell>> maze_Matrix(row, vector<Cell>(col)); // creating the vector to store the maze cells
        vector_initializer(maze_Matrix, row, col);

        Stack<Cell> maze_Stack; //the stack to generate the maze

        RandGen rnd;

        maze_Stack.push(maze_Matrix[0][0]); //pushing 0,0 cell into the stack
        maze_Matrix[0][0].visited = 1; //making the 0,0 cell visited

        int visited_cell_count = 0; //keeping the count of visited cells to finish the loop when it reaches row*col-1 cells

        ofstream output_file;


        while(visited_cell_count < (row*col - 1))// the loop goes on until there are row*col-1 visited cells
        {
            bool no_new_cell_added = true;
            Cell curr = maze_Stack.top();
            vector<int> nums; //a vector to keep track of the directions

            while(no_new_cell_added) // is true if no new cell has been visited (i.e. no new cell has been added to the stack)
            {
                int direction = rnd.RandInt(1, 4); // 1->right 2->left 3->up 4->down

                if (nums.size() < 4)// && !vector_find(direction, nums)) //checks if there are any directions that has not been tried yet
                {
                    if (direction == 1) //right direction
                    {
                        if (curr.x + 1 <= col - 1) //checks if the right cell of the current is in the range
                        {
                            if (maze_Matrix[curr.y][curr.x + 1].visited == 0) //checks if the right cell of the current is visited
                            {
                                maze_Stack.push(maze_Matrix[curr.y][curr.x + 1]); //pushes the cell to the stack
                                maze_Matrix[curr.y][curr.x + 1].visited = 1; //makes the cell visited in the matrix
                                maze_Matrix[curr.y][curr.x + 1].left = 0; //breaks the left wall of the new cell
                                maze_Matrix[curr.y][curr.x].right = 0; //breaks the right wall of the current cell
                                no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                                visited_cell_count++;
                            }
                        }
                    }
                    else if (direction == 2) //left direction
                    {
                        if (curr.x - 1 >= 0) //checks if the left cell of the current is in the range
                        {
                            if (maze_Matrix[curr.y][curr.x - 1].visited == 0) //checks if the left cell of the current is visited
                            {
                                maze_Stack.push(maze_Matrix[curr.y][curr.x - 1]); //pushes the cell to the stack
                                maze_Matrix[curr.y][curr.x - 1].visited = 1; //makes the cell visited in the matrix
                                maze_Matrix[curr.y][curr.x - 1].right = 0; //breaks the right wall of the new cell
                                maze_Matrix[curr.y][curr.x].left = 0; //breaks the left wall of the current cell
                                no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                                visited_cell_count++;
                            }
                        }
                    }
                    else if (direction == 3) //up direction
                    {
                        if (curr.y + 1 <= row - 1) //checks if the up cell of the current is in the range
                        {
                            if (maze_Matrix[curr.y + 1][curr.x].visited == 0) //checks if the up cell of the current is visited
                            {
                                maze_Stack.push(maze_Matrix[curr.y + 1][curr.x]); //pushes the cell to the stack
                                maze_Matrix[curr.y + 1][curr.x].visited = 1; //makes the cell visited in the matrix
                                maze_Matrix[curr.y + 1][curr.x].down = 0; //breaks the down wall of the new cell
                                maze_Matrix[curr.y][curr.x].up = 0; //breaks the up wall of the current cell
                                no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                                visited_cell_count++;
                            }
                        }
                    }
                    else if (direction == 4) //down direction
                    {
                        if (curr.y - 1 >= 0) //checks if the down cell of the current is in the range
                        {
                            if (maze_Matrix[curr.y - 1][curr.x].visited == 0) //checks if the down cell of the current is visited
                            {
                                maze_Stack.push(maze_Matrix[curr.y - 1][curr.x]); //pushes the cell to the stack
                                maze_Matrix[curr.y - 1][curr.x].visited = 1; //makes the cell visited in the matrix
                                maze_Matrix[curr.y - 1][curr.x].up = 0; //breaks the up wall of the new cell
                                maze_Matrix[curr.y][curr.x].down = 0; //breaks the down wall of the current cell
                                no_new_cell_added = false; //making no_new_cell_added false since a cell has been added to the stack
                                visited_cell_count++;
                            }
                        }
                    }
                    if(!vector_find(direction, nums))
                    {
                        nums.push_back(direction); //adding the current direction to the vector if it is not already in it
                    }
                }
                else //if no_new_cell_added is still true after all the directions have been tried we make it false since there is nowhere to go from this cell,
                     // and we need to pop this cell from the stack since all the directions have been tried, and we need to go back to the cell before and try again
                {
                    maze_Stack.pop();
                    no_new_cell_added = false;
                }
            }
        }


        output_file.open("maze_" + to_string(id) + ".txt"); // opening the file to print the maze infos
        print_matrix(output_file,row, col, maze_Matrix);
    }

    int maze_id;
    cout << "Enter a maze ID between 1 to " << num_of_mazes << " inclusive to find a path: ";
    cin >> maze_id;
    int entry_x, entry_y, exit_x, exit_y;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entry_x >> entry_y;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exit_x >> exit_y;

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //Finding the path in the maze

    path_finder(entry_x, entry_y, exit_x, exit_y, maze_id);

    return 0;
}
