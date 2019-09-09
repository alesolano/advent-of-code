#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <utility> // std::pair

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
        
        // THIS CONDITION IS WRONG
        is_two = (n.n_twos != n.n_threes) and (n.n_twos > 0);
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
    
    uset_char chars1;
    uset_char chars2;
    std::pair<uset_char::iterator, bool> is_new_char_pair;
    
    // Linear O(m), m being the size of the string
    for (char& c : key)
    {
        // Average: constant
        is_new_char_pair = chars1.insert(c);
        if (!is_new_char_pair.second)
        {
            // Average: constant
            is_new_char_pair = chars2.insert(c);
            if (!is_new_char_pair.second)
            {
                n_result.n_threes += 1;
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
        // Linear O(n) where n is the number of lines
        while(ifile >> line)
        {
            update_n(n_result, check_repeated(line));
            std::cout << line << std::endl;
            std::cout << n_result.n_twos << " " << n_result.n_threes << std::endl;
        }
        ifile.close();
    }
    
    std::cout << "Checksum: " << n_result.get_checksum() << std::endl;

    return 0;
}

