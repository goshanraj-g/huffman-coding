#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

// defining the huffman tree node
struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// comparator for min heap
struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq; // smallest freq comes first ( min heap )
    }
};

int main()
{
    // input stream in.txt
    ifstream file_in("in.txt");
    if (!file_in.is_open())
    {
        cerr << "Error: unable to open the file" << endl;
        return 1;
    }

    // output stream out.txt
    ofstream file_out("out.txt");
    unordered_map<char, int> freq;
    string line;

    // getline(input_stream, string_variable)
    // using
    while (getline(file_in, line))
    {
        for (char c : line) // for char in the line
        {
            c = tolower(c);
            if (isalpha(c))
            {
                freq[c]++;
            }
        }
        cout << line << "\n";
    }

    cout << "Hashmap" << endl;
    for (const auto &pair : freq)
    {
        cout << "Key: " << pair.first << ": " << pair.second << "\n";
    }

    file_in.close();
    file_out.close();

    return 0;
}