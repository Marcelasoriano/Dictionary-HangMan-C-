/*
Author: Marcela Soriano Cornejo
Course: CSCI-136
Instructor: Genady Maryash
Assignment: Project1D
Hangman Project
*/

#include <iostream> // include input/output stream library
#include <fstream>  // include file stream library
#include <string>   // include string library

using namespace std; // use the standard namespace

const int g_MAX_WORDS = 1000; // define constant for max number of words
int g_word_count = 0;         // initialize word count to 0

string g_words[g_MAX_WORDS];       // declare global array for words
string g_definitions[g_MAX_WORDS]; // declare global array for definitions
string g_pos[g_MAX_WORDS];         // declare global array for parts of speech

/**
    @param :   The string with the `filename`
    @post  :   Reads the words, definitions
               pos into the global-arrays
               and set the value of `g_word_count`
               to the number of words read
*/

void readWords(string filename) // function definition to read words from file
{
    ifstream file(filename); // open the file for reading
    if (!file.is_open())     // check if the file was opened successfully
    {
        cout << "Error opening file " << filename << endl;
        return;
    }

    string line;                // declare string variable to store each line of file
    while (getline(file, line)) // read each line of file into the string variable
    {
        // tokenize the line at space
        int pos = line.find(" ");                 // find position of first space character
        string word = line.substr(0, pos);        // extract word from the line
        string definition = line.substr(pos + 1); // extract definition from the line

        // tokenize the definition at :
        pos = definition.find(":");                       // find position of colon character
        string po_speech = definition.substr(0, pos - 1); // extract part of speech from definition
        string def = definition.substr(pos + 2);          // extract definition text from definition string

        // remove next line character
           if (def.substr(def.length() - 2) == "ie")
        {
            def.replace(def.length() - 2, 2, "ies");
        }

        // add the word, pos, and definition to the arrays
        g_words[g_word_count] = word;      // add word to global array
        g_pos[g_word_count] = po_speech;   // add part of speech to global array
        g_definitions[g_word_count] = def; // add definition to global array

        // increase the word count
        g_word_count++;                  // increment word count
        if (g_word_count >= g_MAX_WORDS) // check if max word count has been reached
        {
            cout << "Too many words in the file" << endl;
            return;
        }
    }

    file.close(); // close the file
}
/**
    @param            :   The string with a query word
    @return           :   Integer index of the word in
                          `g_words` global-array. Returns
                          -1 if the word is not found
    @post             :   Find the index of given `word`
                          in the `g_words` array. Return -1
                          if word is not in the array
*/

int getIndex(string word)
{
    for (int i = 0; i < g_word_count; i++) // loop through all the words in g_words array
    {
        if (g_words[i] == word) // check if the word matches the query word
        {
            return i; // return the index of the word in the array
        }
    }
    return -1; // return -1 if the word is not found in the array
}

/**
    @param            :   The string with a query word
    @return           :   Return the string definition of
                          the word from  `g_definitions`
                          global-array. Return "NOT_FOUND" if
                          word doesn't exist in the dictionary
    @post             :   Find the definition of the given `word`
                          Return "NOT_FOUND" otherwise
*/

string getDefinition(string word)
{
    int index = getIndex(word); // get the index of the word in the array
    if (index == -1)            // if the word is not found in the array
    {
        return "NOT_FOUND"; // return "NOT_FOUND"
    }
    return g_definitions[index]; // return the definition of the word from g_definitions array
}

/**
    @param            :   The string with a query word
    @return           :   Return the string part-of-speech(pos)
                          from the `g_pos` global-array. Return
                          "NOT_FOUND" if the word doesn't exist
                          in the dictionary.
    @post             :   Find the pos of the given `word`
                          Return "NOT_FOUND" otherwise
*/

string getPOS(string word)
{
    int index = getIndex(word); // get the index of the word in the array
    if (index == -1)            // if the word is not found in the array
    {
        return "NOT_FOUND"; // return "NOT_FOUND"
    }
    return g_pos[index]; // return the part-of-speech of the word from g_pos array
}

/**
    @param            :   The string prefix of a word (the prefix
                          can be of any length)
    @return           :   Integer number of words found that starts
                          with the given `prefix`
    @post             :   Count the words that start with the given
                          `prefix`
*/

int countPrefix(string prefix)
{
    int count = 0;                         // initialize the count to 0
    for (int i = 0; i < g_word_count; i++) // loop through all the words in g_words array
    {
        if (g_words[i].find(prefix) == 0) // check if the word starts with the given prefix
        {
            count++; // increase the count if the word starts with the prefix
        }
    }
    return count; // return the count of the words that start with the prefix
}

int main()
{
    /*
    Task A Begins: Reads words from file and populates global arrays
     */
    readWords("dictionary.txt"); // reads the words from "dictionary.txt" file

    // prints the values of g_MAX_WORDS, the maximum number of words that can be stored
    cout << "g_MAX_WORDS: " << g_MAX_WORDS << endl
         << endl;

    // prints the number of words in g_word_count
    cout << "g_word_count: " << g_word_count << endl
         << endl;

    // prints the list of words in g_words array
    cout << "g_words: [";
    for (int i = 0; i < g_word_count; i++)
    {
        cout << "\"" << g_words[i] << "\""; // prints each word in double-quotes
        if (i < g_word_count - 1)
        {
            cout << ", "; // adds a comma after each word except the last one
        }
    }
    cout << "]" << endl
         << endl;

    // prints the list of parts of speech in g_pos array
    cout << "g_pos: [";
    for (int i = 0; i < g_word_count; i++)
    {
        cout << "\"" << g_pos[i] << "\""; // prints each part of speech in double-quotes
        if (i < g_word_count - 1)
        {
            cout << ", "; // adds a comma after each part of speech except the last one
        }
    }
    cout << "]" << endl
         << endl;

    // prints the list of definitions in g_definitions array
    cout << "g_definitions: [";
    for (int i = 0; i < g_word_count; i++)
    {
        if (i < g_word_count - 1)
        {
            cout << "\"" << g_definitions[i] << "\"," << endl; // prints each definition in double-quotes, separated by a comma and a new line
            continue;
        }
        cout << "\"" << g_definitions[i] << "\"" << endl; // prints the last definition without a comma
    }
    cout << "]" << endl
         << endl;

    /*
    Task A ends here
     */

    /*
    Task B Begins: Asks user for word search or prefix search
     */

    // asks the user to choose between word search, prefix search, or exit
    cout << "\n1. Word Search.\n2. Prefix Search.\n3. Exit." << endl;
    int choice;
    cout << "Choice> ";
    cin >> choice;

    // do-while loop to repeat the search until the user chooses to exit
    do
    {
        if (choice == 1) // if user chooses word search
        {
            // ask for word
            string word;
            cout << "Enter word: ";
            cin.ignore();
            getline(cin, word); // reads the word from user input, including spaces

            // finds the definition and part of speech of the word
            string foundDef = getDefinition(word);
            string foundPos = getPOS(word);

            cout << "\n\t====> Results <====:\n";
            // print the definition
            cout << "Definition ==> " << foundDef << endl;
            // print the part of speech
            cout << "Part of Speech ==> " << foundPos << endl;
        }
        else if (choice == 2) // if user chooses prefix search
        {
            // ask for prefix
            string prefix;
            cout << "Enter prefix: ";
            cin >> prefix; // reads the prefix from user input

            // counts the number of words that start with the prefix
            int count = countPrefix(prefix);
            // print the Count
            cout << "Prefix Count ==> " << count << endl;
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "\n\t*** Invalid choice ***" << endl;
        }
        // ask for word search or Prefix Search
        cout << "\n1. Word Search.\n2. Prefix Search.\n3. Exit." << endl;
        cout << "Choice> ";
        cin >> choice;
    } while (choice == 1 || choice == 2);

    return 0;
}

/**
    @param word       :   The string with a new word
    @param definition :   The string with the definition of the
                          new `word`
    @param pos        :   The string with the pos of the new `word`
    @return           :   return `true` if the word is
                          successfully added to the dictionary
                          return `false` if failed (word already
                          exists or dictionary is full)
    @post             :   Add the given `word`, `definition`, `pos`
                          to the end of the respective
                          global-arrays.
                          The word should not be added to the
                          global-arrays if it already exists 
                          or if the array reached maximum 
                          capacity(`g_MAX_WORDS`).
                          Update `g_word_count` if the word is
                          successfully added
*/

bool addWord(string word, string definition, string pos)
{
    if (g_word_count >= g_MAX_WORDS) // check if max word count has been reached
    {
        cout << "Dictionary is full" << endl;
        return false;
    }

    // check if the word already exists in the dictionary
    for (int i = 0; i < g_word_count; i++)
    {
        if (g_words[i] == word)
        {
            cout << "Word already exists in the dictionary" << endl;
            return false;
        }
    }

    // add the word, pos, and definition to the arrays
    g_words[g_word_count] = word;      // add word to global array
    g_pos[g_word_count] = pos;         // add part of speech to global array
    g_definitions[g_word_count] = definition; // add definition to global array

    // increase the word count
    g_word_count++;                  // increment word count

    return true;
}

/**
    @param word       :   The string with the word that is to
                          be edited
    @param definition :   The string with the new definition of 
                          the `word`
    @param pos        :   The string with the new pos of the `word`
    @return           :   return `true` if the word is successfully
                          edited, return `false` if the `word`
                          doesn't exist in the dictionary
    @post             :   Replace the given `word`'s  definition
                          and pos with the given `definition` and
                          `pos` (by modifying global-arrays
                          `g_definitions` and `g_pos`).
                          The modification will fail if the word
                          doesn't exist in the dictionary
*/
bool editWord(string word, string definition, string pos)
{
    int index = getIndex(word); // get the index of the word in the array
    if (index == -1)            // if the word is not found in the array
    {
        return false; // return false to indicate that the word was not edited
    }

    // modify the definition and pos of the word
    g_definitions[index] = definition;
    g_pos[index] = pos;

    return true; // return true to indicate that the word was successfully edited
}

/**
    @param            :   The string with the word that is to
                          be removed
    @return           :   return `true` if the word is successfully
                          removed from the dictionary return `false`
                          if the word doesn't exist in the dictionary
    @post             :   Remove the given `word`, `word`'s
                          definition and `word`'s pos from the
                          respective global-arrays if the word
                          exists.  
                          Update `g_word_count` if the word is
                          successfully removed
*/

bool removeWord(string word)
{
    int index = getIndex(word); // get the index of the word in the array
    if (index == -1)            // if the word is not found in the array
    {
        return false; // return false to indicate removal failed
    }

    // shift the elements to the left to overwrite the element to be removed
    for (int i = index; i < g_word_count - 1; i++)
    {
        g_words[i] = g_words[i + 1];                   // shift the word to the left
        g_definitions[i] = g_definitions[i + 1];       // shift the definition to the left
        g_pos[i] = g_pos[i + 1];                       // shift the part of speech to the left
    }

    // set the last element to empty strings
    g_words[g_word_count - 1] = "";          // set the last word to an empty string
    g_definitions[g_word_count - 1] = "";   // set the last definition to an empty string
    g_pos[g_word_count - 1] = "";           // set the last part of speech to an empty string

    g_word_count--; // decrease the word count

    return true; // return true to indicate removal succeeded
}
string maskWord(string word) {
    string masked_word(word.length(), '_');
    return masked_word;
}

int getTries(int difficulty) {
    switch (difficulty) {
        case 0:
            return 9;
        case 1:
            return 7;
        case 2:
            return 5;
        default:
            return 0;
    }
}

void printAttempts(int tries, int difficulty) {
    int total_tries;
    switch (difficulty) {
        case 0:
            total_tries = 9;
            break;
        case 1:
            total_tries = 7;
            break;
        case 2:
            total_tries = 5;
            break;
        default:
            total_tries = 0;
            break;
    }
    for (int i = 0; i < tries; i++) {
        cout << "O";
    }
    for (int i = tries; i < total_tries; i++) {
        cout << "X";
    }
}

bool revealLetter(string word, char letter, string &current) {
    bool found_letter = false;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == letter) {
            current[i] = letter;
            found_letter = true;
        }
    }
    return found_letter;
}
