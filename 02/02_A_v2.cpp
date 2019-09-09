#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility> // std::pair
#include <memory> // std::unique_ptr


struct NTwoThreePair
{
    int n_twos = 0;
    int n_threes = 0;
    
    int get_checksum()
    {
        return n_twos * n_threes;
    }
    
    void update(const std::pair<bool, bool>& is_two_three)
    {
        if (is_two_three.first)  n_twos += 1;
        if (is_two_three.second) n_threes += 1;
    }
};


std::pair<bool, bool> check_repeated(std::string& key)
{
    int n_twos = 0;
    int n_threes = 0;
    
    std::map<char, int> char_counter;
    std::pair<std::map<char, int>::iterator, int> is_new_char_pair;
    
    // Overall: worse than O(m), but not too much
    // Linear O(m), m being the size of the string
    for (char& c : key)
    {
        // Insert with average log complexity
        is_new_char_pair = char_counter.insert(std::pair<char, int>(c, 1));
        // If is not new, then is repeated more than once
        if (!is_new_char_pair.second)
        {
            // [] operator with log complexity
            int& count = is_new_char_pair.first->second;
            if (count == 1)
            {
                count = 2;
                n_twos += 1;
            }
            else if (count == 2)
            {
                count = 3;
                n_threes += 1;
                n_twos -= 1;
            }
            else if (count == 3)
                n_threes -= 1;
        }
    }
    
    std::pair<bool, bool> is_two_three{n_twos>0, n_threes>0};
    return is_two_three;
}


int main()
{
    NTwoThreePair n_result;
    
    std::ifstream ifile("input.txt");
    std::string line;
    if (ifile.is_open())
    {
        // Overall algorithm: worse than Linear O(n*m)
        // while: Linear O(n) where n is the number of lines
        while(ifile >> line)
        {
            // check_repeated: worse than linear O(m), m being the size of the line
            n_result.update(check_repeated(line));
        }
        ifile.close();
    }
    
    std::cout << "Checksum: " << n_result.get_checksum() << std::endl;

    return 0;
}

