#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

// Huffman Tree Node
struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// comparator for priority queue (this is a min heap)
struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

// generate the codes and store in the map recursively
void generateCodes(Node *root, const string &code, unordered_map<char, string> &huffmanCode)
{
    if (!root) return;

    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// free the memory used by the tree
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main()
{
    ifstream file_in("in.txt");
    if (!file_in.is_open())
    {
        cerr << "Error: unable to open the file" << endl;
        return 1;
    }

    ofstream file_out("out.txt");

    unordered_map<char, int> freq;
    string line, text;

    // read and normalize da text
    while (getline(file_in, line))
    {
        for (char c : line)
        {
            c = tolower(c);
            if (isalpha(c))
            {
                freq[c]++;
                text += c;
            }
        }
    }

    // priority queue for the tree
    priority_queue<Node *, vector<Node *>, Compare> pq;

    for (const auto &pair : freq)
    {
        pq.push(new Node(pair.first, pair.second));
    }

    // build the huffman tree
    while (pq.size() > 1)
    {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    Node *root = pq.top();

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (const auto &pair : huffmanCode)
    {
        cout << pair.first << ": " << pair.second << "\n";
    }

    // encode text
    string encodedText;
    for (char c : text)
    {
        encodedText += huffmanCode[c];
    }

    // output to file
    file_out << encodedText;

    // clean
    freeTree(root);
    file_in.close();
    file_out.close();

    return 0;
}
