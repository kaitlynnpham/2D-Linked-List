/*
 Name: Kaitlynn_Pham, 5005989243, 1004, AS8
 Description: This program will create
 a 2d linked list that traverses in all 4
 directions. It will create a matrix
 consisting of 3 character strings that
 are randomly generated. One of it will be replaced
 by the word neo and must be traced.
 Input:  length and width of the matrix
 Output: prints the matrix and outputs if trace was
 successful
*/
#include <iostream>
using namespace std;
class Node
{
public:
    string data;
    Node *Left;
    Node *right;
    Node *up;
    Node *down;
    // constructor
    /*
Node: parameterized constructer
sets attributes and pointers to null
parameters: string s
return value: no return
*/
    Node(string s)
    {
        data = s;
        Left = nullptr;
        right = nullptr;
        up = nullptr;
        down = nullptr;
    }
};

class LinkedList
{
public:
    Node *head;

    // create random string
    /*
RNGString: creates a 3 character
string with random letters a-z
parameters: no parameters
return value: string
*/
    static string RNGString()
    {
        // random values lowercase a-z
        char letter1 = 'a' + rand() % 26;
        char letter2 = 'a' + rand() % 26;
        char letter3 = 'a' + rand() % 26;
        string word;
        word += letter1;
        word += letter2;
        word += letter3;
        return word;
    }
    /*
    LinkedList: constructor that creates
    the 2d linked list and takes in
    length and width for matrix
    parameters: int length, int width
    return value: no return
    */
    LinkedList(int length, int width)
    {
        // if arguments are zero, head is null
        if (length == 0 || width == 0)
        {
            head = nullptr;
        }
        else
        {
            // select random length and width for neo
            int length_neo = rand() % length;
            int width_neo = rand() % width;

            // tail pointer to add new nodes
            Node *tail = nullptr;
            // pointer to keep track of above row
            Node *head_above = nullptr;
            // track start of each row
            Node *head_row = nullptr;

            // create new current node
            Node *current = nullptr;
            // row
            for (int i = 0; i < length; i++)
            {

                for (int j = 0; j < width; j++)
                {
                    // create rand string for data
                    string rand_Data = RNGString();
                    // if at coordinates of neo
                    if (i == length_neo && j == width_neo)
                    {
                        current = new Node("neo");
                    }
                    else
                    {
                        current = new Node(rand_Data);
                    }
                    // first node
                    if (j == 0 && i == 0)
                    {
                        //set all pointers to current
                        head = current;
                        head_row = current;
                        tail = current;
                        head_above = current;
                    }
                    // first row of list
                    if (i == 0 && j > 0)
                    {
                        //set left and right pointers and tail to current
                        tail->right = current;
                        current->Left = tail;
                        tail = current;
                    }
                    // first column of list
                    if (i > 0 && j == 0)
                    {
                        //set up and down pointers in first col
                        head_row->down = current;
                        current->up = head_row;
                        current->Left = nullptr;
                        //make row above point to current
                        head_above = current;
                        tail = current;
                        //set head row to the right 
                        head_row = head_row->right;
                    }
                    // rest of matrix
                    if (i > 0 && j > 0)
                    {
                        //set all directions 
                        current->Left = tail;
                        tail->right = current;
                        current->up = head_row;
                        head_row->down = current;
                        //move row above to right 
                        head_row = head_row->right;

                        tail = current;
                    }
                }
                //reset the start of row to the pointer above
                head_row = head_above;
            }
        }
    }
    /*
    ~LinkedList: deconstructor, deallocate
    2d linked list
    parameters: no parameters
    return value: no return
    */
    ~LinkedList()
    {

        // go through each row and column and deallocate
        for (Node *row = head; row != nullptr;)
        {
            for (Node *col = row->right; col != nullptr;)
            {
                // check first row until null
                if (col->right != nullptr)
                {
                    //move col right and delete prev
                    col = col->right;
                    delete col->Left;
                }
                else
                {
                    //delete col pointer and set to null
                    delete col;
                    col = nullptr;
                }
                // check row until null
                if (row->down != nullptr)
                {
                    //move row down and delete row above
                    row = row->down;
                    delete row->up;
                }
                else
                {
                    //if next is null, delete current row
                    delete row;
                    row = nullptr;
                }
            }
        }
    }
/*
print: output the matrix 
parameters: no parameters
return value: no return 
*/
    void print()
    {
        //start at head
        Node *row_head = head;
        Node *current = row_head;
        while (row_head != nullptr)
        {   
            //at end of row, move down 
            if (current == nullptr)
            {
                current = row_head->down;
                row_head = row_head->down;
                cout << endl;
            }
            //move right 
            if (current != nullptr)
            {
                cout << current->data << " ";
                current = current->right;
            }
        }
    }
/*
RNGdirection: select a random
direction for trace to check 
parameters: Node *curr
return value: Node *newCurr
*/
    Node *RNGdirection(Node *curr)
    {
        Node *newCurr = nullptr;
        int direction = rand() % 4; // 0,1,2,3 (up,down,left,right)
        switch (direction)
        {
        case 0:
            std::cout << "u,"; // up
            newCurr = curr->up;
            break;
        case 1:
            std::cout << "d,"; // down
            newCurr = curr->down;
            break;
        case 2:
            std::cout << "l,"; // left
            newCurr = curr->Left;
            break;
        case 3:
            std::cout << "r,"; // right
            newCurr = curr->right;
            break;
        }
        if (!newCurr)
            return RNGdirection(curr);
        return newCurr;
    }
/*
traceTheCall: find neo using two different 
modes. The first mode will do a search
left to right. The second mode will randomly
search the list. It will display if it is
a success or not. 
parameters: int mode 
return value:  1 or 0 
*/
    int traceTheCall(int mode)
    {
        //check if empty
        if (head == nullptr)
        {
            cout << mode << ": Trace Failed." << endl;
            return 1;
        }
        //mode 0
        if (mode == 0)
        {
            //temp pointer variables
            Node *row = head;
            Node *current = row;
            //variables to get coordinates
            int j = 0;
            int count = 1;
            int i = 0;
    
            while (row != nullptr)
            {   //success
                if (current->data == "neo")
                {   //print coordinates 
                    cout << mode
                         << ": Trace Successful at Coordinates ("
                         << j << ", " << i << ") by "
                         << count << " Compares..." << endl;
                    return 0;
                }
                //move right
                current = current->right;
                i++;
                //move down a row
                if (current == nullptr)
                {   
                    row = row->down;
                    j++;
                    i = 0;
                    //set current pointer to the row moved down to
                    current = row;
                }

                count++;
            }

            cout << mode << ": Trace Failed." << endl;
            return 1;
        }
        //mode 1
        if (mode == 1)
        {
            Node *c = head;
            int i = 1;
            while (i < 10000)
            {  
                //success
                if (c->data == "neo")
                {
                    cout << endl;
                    cout << mode << ": Trace Successful by "
                         << i << " Compares..." << endl;
                    return 0;
                }
                //call random function for direction
                c = RNGdirection(c);
                i++;
            }
            cout << mode << ": Trace Failed." << endl;
            return 1;
        }
        //anything else 
        cout << mode << ": Unknown Trace Mode." << endl;
        return 1;
    }
};