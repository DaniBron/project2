#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;
const int MAX = 100;

/*  Method: is_number
    Return: --
    Elements: --
    Description: This method will check if the string is a constant or variavle.
 */
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
    string id, type, location = " "; 
    Node* next;
public:
    //constructor
    Node();
    //constructor
    Node(string key, string type, string location)
    {
        this->id = key;
        this->type = type;
        this->location = location;
        next = NULL;
    }
    //destructor 
    //~Node();
    void print()
    {
        cout << "Identifier's Name:" << id
            << "   Type:" << type
            << "   Location: " << location << endl;
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
    TableEntry()
    {
        //populates all the array with NULL.
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }
    //~TableEntry();

    bool insert(string id, string type, string location);
    bool deleteRecord(string id);
    bool modify(string id, string type);

    string find(string id);

    int hashf(string id);
};

// Function to insert an identifier 
bool TableEntry::insert(string id, string type, string location)
{
    int index = hashf(id);
    Node* p = new Node(id, type, location);

    if (head[index] == NULL) {
        head[index] = p;

        return true;
    }

    else {
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;

        start->next = p;

        return true;
    }

    return false;
}

// Function to delete an identifier
bool TableEntry::deleteRecord(string id)
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
}

// Function to modify an identifier 
bool TableEntry::modify(string id, string type)
{
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return "-1";

    while (start != NULL) {
        if (start->id == id) {
            start->type = type;
            return true;
        }
        start = start->next;
    }

    return false; // id not found 
}

// Function to find an identifier 
string TableEntry::find(string id)
{
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return "-1";

    while (start != NULL) {

        if (start->id == id) {
            start->print();
            return start->type;
        }

        start = start->next;
    }

    return "-1"; // not found 
}

int TableEntry::hashf(string id)
{
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++) {
        asciiSum = asciiSum + id[i];
    }

    return (asciiSum % 100);
}

/*  Method: main
    Return: --
    Elements: --
    Description: The main method will read input file called Plain.
                    The Plain file is our Plain program.
 */
int main()
{
    string token;
    string inputLine;
    string line;
    string location = "";
    string type = "";
    ifstream input;
    TableEntry st;
    char* tkn;
    int topDown = 99;
    int buttomUp = 0;
    int count = 0;

    input.open("C:/Users/97254/source/repos/Project2Dani__Josh/Plain.txt");
    cout << "Entered file Plain.txt\n";

    //check if was able to open input file
    if (!input.is_open())
    {
        cout << "Unable to open file!";

        return 0;
    }
    
    while (!input.eof())
    {
        bool endLine = false;
        getline(input, inputLine); //Get next line
        tkn = strtok((char*)inputLine.c_str(), " ,.-"); //Get token
        count = 0;
        while (!endLine)
        {
            token = tkn;
            //Every line begins with line number.
            //Then, count will be 0 and it will insert line number as token.
            if (count == 0)
            {
                type = 'L';
                location = to_string(buttomUp);
                buttomUp++;
                count++;
                st.insert(tkn, type, location);
                st.find(tkn);
            }

            //If token is not line number.
            //Line numbers after the first token are ignored.
            else
            {
                //Input variable for the first time.
                //Variables are not inserted in the symbol table anywhere else.
                if (token.compare("input") == 0)
                {
                    tkn = strtok(NULL, " ,.-"); //Go to next token
                    type = "V";
                    location = to_string(topDown);
                    topDown--;
                    st.insert(tkn, type, location);
                    st.find(tkn);
                }
                //If token is 'if' it identifies all constants
                //We are skipping comparaters 
                //Variables are identified but not added to the symbol tyble, because they are already there
                else if (token.compare("if") == 0)
                {
                    while (!(token.compare("goto") == 0))
                    {
                        tkn = strtok(NULL, " ,.-");
                        token = tkn;
                        if (is_number(tkn))
                        {
                            type = 'C';
                            location = to_string(topDown);
                            topDown--;
                            st.insert(tkn, type, location);
                            st.find(tkn);
                        }
                        /*else {
                            type = 'V';
                            location = to_string(topDown);
                            topDown--;
                            st.insert(tkn, type, location);
                            st.find(tkn);
                        }*/
                        tkn = strtok(NULL, " ,.-");
                        token = tkn;
                    }  
                }
                //Adds constants that are outputed
                //but not variables.
                //If outputing a viarable, it already in the symbol table.
                else if (token.compare("output") == 0)
                {
                    tkn = strtok(NULL, " ,.-");
                    if (is_number(tkn))
                    {
                        type = 'C';
                        location = to_string(topDown);
                        topDown--;
                        st.insert(tkn, type, location);
                        st.find(tkn);
                    }
                    /*else {
                        type = 'V';
                        location = to_string(topDown);
                        topDown--;
                        st.insert(tkn, type, location);
                        st.find(tkn);
                    }*/
                }
                //If token is "prog_end", it is terminates the program
                else if (token.compare("prog_end") == 0)
                {
                    return 0;
                }
                //Go to next line
                //Line numbers after are tokens
                else if (token.compare("goto") == 0)
                {
                    endLine = true;
                }
                //Go to next input line
                //Line numbers after are tokens
                else if (token.compare("comment") == 0)
                {
                    endLine = true;
                }
                //Identifies variables but only adds constants to the symbol table.
                //Loops until end of line to allow multipule opperaters on RHS.
                else if (token.compare("assign") == 0)
                {
                    tkn = strtok(NULL, " ,.-");
                    /*type = "V";
                    location = to_string(topDown);
                    topDown--;
                    st.insert(tkn, type, location);
                    st.find(tkn);*/
                    tkn = strtok(NULL, " ,.-");
                    while(tkn != NULL)
                    {
                        tkn = strtok(NULL, " ,.-");
                        if (is_number(tkn))
                        {
                            type = 'C';
                            location = to_string(topDown);
                            topDown--;
                            st.insert( tkn, type, location);
                            st.find(tkn);
                        }
                        /*else {
                            type = 'V';
                            location = to_string(topDown);
                            topDown--;
                            st.insert(tkn, type, location);
                            st.find(tkn);
                        }*/
                        tkn = strtok(NULL, " ,.-");
                    }
                }
                //Gets next token unless next token is null
                //If next token is null, go to next line.
                try
                {
                    tkn = strtok(NULL, " ,.-");
                    if (tkn == NULL)
                    {
                        endLine = true;
                    }
                    else
                        token = tkn;
                }
                catch (...)
                {
                    cout << "ERROR!!!!";
                }
            }

        }
    }
}
