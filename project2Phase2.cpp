#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
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
    const char* character;
    string token;
    string inputLine;
    string tName;
    ifstream input;
    TableEntry st; 
    char* tkn;
    string lineNum;
    string type = "";
    string location;

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
        getline(input , inputLine);

        //loop through file line by line
        for(int i=0 ; i < inputLine.length() ; i++)
        {
            int count=0;
            character = inputLine.c_str();
            tkn = strtok((char*) character, " ,.-"); //Split string into tokens
            //10 input x
            //10
            //input
            //x
            char* tokens[3];
            while (tkn != NULL)
            {
                if(count==0)
                {
                    lineNum = tkn;
                    type='L';
                    location = tkn;
                    st.insert(lineNum, type, location);
                    count++;
                }

                else
                {
                    if(tkn=="input")
                    {
                        tkn = strtok((char*) character , " ,.-");
                        type="V";
                        lineNum=tkn;
                        st.insert(lineNum, type, location);
                    }
                    else if(tkn=="if")
                    {

                    }
                    else if(tkn=="output")
                    {
                        tkn = strtok((char*) character , " ,.-");
                        if(is_number(tkn))
                        {
                            lineNum = tkn;
                            type='C';
                            st.insert(lineNum, type, location);
                        }
                        else{
                            lineNum = tkn;
                            type='V';
                            st.insert(lineNum, type, location);
                        }
                    }
                    else if(tkn == "prog_end")
                    {

                    }
                    else if(tkn == "comment")
                    {
                        
                    }
                    else
                    {
                        {/* code */}
                    }
                    
                }
                tkn = strtok(character , " ,.-");
            }
        }
        
        
    } while (!input.eof());
    
}

bool is_number(const std::string& s)
{
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}


/*  Class: Node
    Return: --
    Elements: --
    Description: This will generate the array.
 */ 
class Node
{
    string id, type, command; //Not sure about command. lets keep it for now
    int location;
    string lineNum;
    Node* next;
public:
    //constructor
    Node()
    {
        next= NULL;
    }
    //constructor
    Node(string lineNum, string key, /*string value,*/ string type)
    {
        this->id = key;
        //this->command = value;
        this->type = type;
        this->lineNum = lineNum;
        next = NULL;
    }
    //destructor 
    ~Node();
    void print() 
    { 
        cout << "Identifier's Name:" << id 
             << "\nType:" << type 
             << "\nCommand: " << command 
             << "\nLine Number: " << lineNum << endl; 
    } 
    friend class TableEntry;
};

/*  Method: TableEntry
    Return: --
    Elements: --
    Description: This will generate the array.
 */ 
class TableEntry 
{
    Node* head[MAX]; //allocates array of 100;
public:
    TableEntry ()
    {
        //populates all the array with NULL.
        for(int i=0; i <  MAX;  i++)
            head[i] = NULL;
    }
    ~TableEntry ();
    
    bool insert(string lineNum, string id, string type);
    bool deleteRecord(string id);
    bool modify(string lineNum, string id, string type);

    string find(string id);

    int hashf(string id);
};
 
// Function to insert an identifier 
bool TableEntry::insert(string lineNum, string id, string type)
{
    int index = hashf(id); 
    Node* p = new Node(lineNum, id, type); 
  
    if (head[index] == NULL) { 
        head[index] = p; 
        cout << "\n"
             << id << " inserted"; 
  
        return true; 
    } 
  
    else { 
        Node* start = head[index]; 
        while (start->next != NULL) 
            start = start->next; 
  
        start->next = p; 
        cout << "\n"
             << id << " inserted"; 
  
        return true; 
    } 
  
    return false; 
}

// Function to delete an identifier
bool TableEntry::deleteRecord (string id)
{
    int index = hashf(id); 
    Node* tmp = head[index]; 
    Node* par = head[index]; 
  
    // no identifier is present at that index 
    if (tmp == NULL) { 
        return false; 
    } 
    // only one identifier is present 
    if (tmp->id == id && tmp->next == NULL) { 
        tmp->next = NULL; 
        delete tmp; 
        return true; 
    } 
  
    while (tmp->id != id && tmp->next != NULL) { 
        par = tmp; 
        tmp = tmp->next; 
    } 
    if (tmp->id == id && tmp->next != NULL) { 
        par->next = tmp->next; 
        tmp->next = NULL; 
        delete tmp; 
        return true; 
    } 
  
    // delete at the end 
    else { 
        par->next = NULL; 
        tmp->next = NULL; 
        delete tmp; 
        return true; 
    } 
    return false;
    Node* tmp = head[index]; 
    Node* par = head[index]; 
  
    // no identifier is present at that index 
    if (tmp == NULL) { 
        return false; 
    } 
    // only one identifier is present 
    if (tmp->id == id && tmp->next == NULL) { 
        tmp->next = NULL; 
        delete tmp; 
        return true; 
    } 
  
    while (tmp->id != id && tmp->next != NULL) { 
        par = tmp; 
        tmp = tmp->next; 
    } 
    if (tmp->id == id && tmp->next != NULL) { 
        par->next = tmp->next; 
        tmp->next = NULL; 
        delete tmp; 
        return true; 
    } 
  
    // delete at the end 
    else { 
        par->next = NULL; 
        tmp->next = NULL; 
        delete tmp; 
        return true; 
    } 
    return false;
}

// Function to modify an identifier 
bool TableEntry::modify(string lineNum, string id, string type) 
{ 
    int index = hashf(id); 
    Node* start = head[index]; 
  
    if (start == NULL) 
        return "-1"; 
  
    while (start != NULL) { 
        if (start->id == id) { 
            //start->scope = s; 
            start->type = type; 
            start->lineNum = lineNum; 
            return true; 
        } 
        start = start->next; 
    } 
  
    return false; // id not found 
} 
