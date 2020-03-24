#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
/*  Method: main
    Return: --
    Elements: --
    Description: The main method will read input file called Plain.
                    The Plain file is our Plain program.
 */
using namespace std;
const int MAX = 100;

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
    string id, type, location, lineNum = " "; //Not sure about command. lets keep it for now
    //string location = "";
    //string lineNum = "";
    Node* next;
public:
    //constructor
    Node();
    //constructor
    Node(string lineNum, string key, /*string value,*/ string type, string location)
    {
        this->id = key;
        //this->command = value;
        this->type = type;
        this->lineNum = lineNum;
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

    bool insert(string lineNum, string id, string type, string location);
    bool deleteRecord(string id);
    bool modify(string lineNum, string id, string type);

    string find(string id);

    int hashf(string id);
};

// Function to insert an identifier 
bool TableEntry::insert(string lineNum, string id, string type, string location)
{
    int index = hashf(id);
    Node* p = new Node(lineNum, id, type, location);

    if (head[index] == NULL) {
        head[index] = p;
        /*cout << "\n"
            << id << " inserted";*/

        return true;
    }

    else {
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;

        start->next = p;
        /*cout << "\n"
            << id << " inserted";*/

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


int main()
{
    char character;
    string token;
    string inputLine;
    string line;
    string tName;
    ifstream input;
    TableEntry st;
    string constLineNum;
    //string input;
    char* tkn;
    string lineNum;
    int topDown = 99;
    int buttomUp = 0;
    
    
    const int MAX_TOKENS_PER_LINE = 20;
    const int MAX_CHARS_PER_LINE = 512;
    int count = 0;

    input.open("C:/Users/97254/Plain/Plain.txt");
    cout << "Entered file Plain.txt\n";

    //check if was able to open input file
    if (!input.is_open())
    {
        cout << "Unable to open file!";

        return 0;
    }

    //I took it from somewhere but this is checks only one token per line.
    //We need to change it to something that looks like the example of Plain.
    //Will keep it for now as a refernce, but MUST modifide for later use.
    
    while (!input.eof())
    {
        bool endLine = false;
        getline(input, inputLine);
        tkn = strtok((char*)inputLine.c_str(), " ,.-");
        count = 0;
        while (!endLine)
        {
            token = tkn;
            string location = "";
            string type = "";
            if (count == 0)
            {
                lineNum = tkn;
                constLineNum = tkn;
                type = 'L';
                location = to_string(buttomUp);
                buttomUp++;
                //cout << "Line Number: ";
                //cout << lineNum;
                count++;
                st.insert(lineNum, tkn, type, location);
                st.find(tkn);
            }

            else
            {
                if (token.compare("input") == 0)
                {
                    tkn = strtok(NULL, " ,.-");
                    type = "V";
                    lineNum = constLineNum;
                    location = to_string(topDown);
                    topDown--;
                    st.insert(lineNum, tkn, type, location);
                    st.find(tkn);
                }
                else if (tkn == "if")
                {

                }
                else if (token.compare("output") == 0)
                {
                    tkn = strtok(NULL, " ,.-");
                    if (is_number(tkn))
                    {
                        lineNum = tkn;
                        type = 'C';
                        location = to_string(topDown);
                        topDown--;
                        st.insert(lineNum, tkn, type, location);
                        st.find(tkn);
                    }
                    else {
                        lineNum = tkn;
                        type = 'V';
                        location = to_string(topDown);
                        topDown--;
                        st.insert(lineNum, tkn, type, location);
                        st.find(tkn);
                    }
                }
                else if (token.compare("prog_end") == 0)
                {
                    return 0;
                }
                else if (token.compare("goto") == 0)
                {
                    endLine = true;
                }
                else if (token.compare("comment") == 0)
                {
                    endLine = true;
                }
                else if (token.compare("assign") == 0)
                {
                    tkn = strtok(NULL, " ,.-");
                    type = "V";
                    lineNum = constLineNum;
                    location = to_string(topDown);
                    topDown--;
                    st.insert(lineNum, tkn, type, location);
                    st.find(tkn);
                    tkn = strtok(NULL, " ,.-");
                    while(tkn != NULL)
                    {
                        tkn = strtok(NULL, " ,.-");
                        if (is_number(tkn))
                        {
                            lineNum = tkn;
                            type = 'C';
                            location = to_string(topDown);
                            topDown--;
                            st.insert(lineNum, tkn, type, location);
                            st.find(tkn);
                        }
                        else {
                            lineNum = tkn;
                            type = 'V';
                            location = to_string(topDown);
                            topDown--;
                            st.insert(lineNum, tkn, type, location);
                            st.find(tkn);
                        }
                        tkn = strtok(NULL, " ,.-");
                    }
                }
                /*else
                {
                    tkn = strtok((char*)inputLine.c_str(), " ,.-");
                }*/
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
                    //cout << "ERROR!!!!";
                }
            }

        } //while (!input.eof());
    }
}

//constructor

//inline Node::Node()
//{
//    next = NULL;
//}
