/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <utility> // std::pair
#include <memory> // std::unique_ptr

using uset_char = std::unordered_set<char>;

struct NTwoThreePair
{
    int n_twos = 0;
    int n_threes = 0;
    
    int get_checksum()
    {
        return n_twos * n_threes;
    }
};

struct IsTwoThreePair
{
    bool is_two = false;
    bool is_three = false;
    
    IsTwoThreePair(const NTwoThreePair& n)
    {
        is_three = n.n_threes > 0;
        is_two = n.n_twos > 0;
    }
};

void update_n(NTwoThreePair& n, const IsTwoThreePair& is)
{
    if (is.is_two)   n.n_twos += 1;
    if (is.is_three) n.n_threes += 1;
}

IsTwoThreePair check_repeated(std::string& key)
{
    NTwoThreePair n_result;
    
    std::unique_ptr<uset_char> chars1(new uset_char);
    std::unique_ptr<uset_char> chars2(new uset_char);
    std::unique_ptr<uset_char> chars3(new uset_char);
    std::pair<uset_char::iterator, bool> is_new_char_pair;
    
    // Linear O(m), m being the size of the string
    for (char& c : key)
    {
        // Insert with average constant complexity
        is_new_char_pair = chars1->insert(c);
        // If is not new, then is repeated more than once
        if (!is_new_char_pair.second)
        {
            // Insert with average constant complexity
            is_new_char_pair = chars2->insert(c);
            // If is not new, then is repeated more than twice
            if (!is_new_char_pair.second)
            {
                // Insert with average constant complexity
                is_new_char_pair = chars3->insert(c);
                // If is not new, then is repeated more than three times
                if (!is_new_char_pair.second) n_result.n_threes -= 1; // It was not a three!
                else
                {
                    n_result.n_threes += 1; // It's a three!
                    n_result.n_twos -= 1;   // It was not a two!
                }
            }
            else n_result.n_twos += 1;
        }
    }
    
    IsTwoThreePair is_result(n_result);
    return is_result;
}


int main()
{
    NTwoThreePair n_result;
    
    std::ifstream ifile("input.txt");
    std::string line;
    if (ifile.is_open())
    {
        // Overall algorithm: Linear O(n*m)
        // while: Linear O(n) where n is the number of lines
        while(ifile >> line)
        {
            // check_repeated: Linear O(m), m being the size of the line
            update_n(n_result, check_repeated(line));
        }
        ifile.close();
    }
    
    std::cout << "Checksum: " << n_result.get_checksum() << std::endl;

    return 0;
}

