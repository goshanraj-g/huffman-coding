#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
    string line;

    // getline(input_stream, string_variable)
    while (getline(file_in, line))
    {
        cout << line << "\n";
    }

    file_in.close();
    file_out.close();

    return 0;
}