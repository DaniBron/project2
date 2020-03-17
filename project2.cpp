#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
/*  Method: main
    Return: --
    Elements: --
    Description: The main method will read input file called Plain.
                    The Plain file is our Plain program.
 */
using namespace std;
const int MAX = 100; 

int main()
{
    char character;
    int size = 0;
    string token;
    string inputLine;
    string tName;
    ifstream input;
    TableEntry st; 

    input.open("INPUT FILE!");

    //check if was able to open input file
    if(!input.is_open())
    {
       cout << "Unable to open file!";

		return 0; 
    }

    //I took it from somewhere but this is checks only one token per line.
    //We need to change it to something that looks like the example of Plain.
    //Will keep it for now as a refernce, but MUST modifide for later use.
    do
    {
        getline(input , inputLine)

        //loop through file line by line
        for(int i=0; i < inputLine.size(); i++)
        {
            character = inputLine;

            // If a token is an operator or a Plain command,
            // it does not go into the symbol table
            if(character == '+' || character == '-' || character == '*' || character == '/' || character == 'Plain')
            {

            }

            //If a token is a line number, a variable, or a constant, it is placed in the symbol table.  
            else
            {
                st.insert();
            }
            
        }
        
    } while (!input.eof());
    
}

/*  Method: Node
    Return: --
    Elements: --
    Description: This will generate the array.
 */ 
class Node
{
    string id, type, scope; //Not sure about scope. lets keep it for now
    int location;
    int lineNum;
    Node* next;
public:
    //constructor
    Node()
    {
        next= NULL;
    }
    //constructor
    Node(string key, string value, string type, int lineNum)
    {
        this->id = key;
        this->scope = value;
        this->type = type;
        this->lineNum = lineNum;
        next = NULL;
    }
    //destructor 
    ~Node();
    friend class TableEntry;
};

/*  Method: TableEntry
    Return: --
    Elements: --
    Description: This will generate the array.
 */ 
class TableEntry 
{
    Node *head[MAX]; //allocates array of 100;
public:
    TableEntry ()
    {
        //populates all the array with NULL.
        for(int i=0; i <  MAX;  i++)
            head[i] = NULL;
    }
    ~TableEntry ();
    
    bool insert(string id, string scope, string type, int lineNum);
    bool deleteRecord(string id);
    bool modify(string id, string scope, string type, int lineNum);

    string find(string id);

    int hashf(string id);
};
 
// Function to insert an identifier 
bool TableEntry::insert (string id, string scope, string type, int lineNum)
{

}

// Function to delete an identifier
bool TableEntry::deleteRecord (string id)
{

}

// Function to modify an identifier 
bool TableEntry::modify (string id, string scope, string type, int lineNum)
{

}

// Function to find an identifier 
string TableEntry::find (string id)
{

}

int TableEntry::hashf (string id)
{

}

//Will keep the destructor for now. (We can delete it later)
//I dont think we'll use it
TableEntry ::~TableEntry ()
{
}

