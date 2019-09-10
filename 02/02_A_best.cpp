/**

I love this approach. It's elegant, readable and eficient.
All the credit goes to Tristan Brindle (@tcbrindle) https://github.com/tcbrindle/advent_of_code_2018/blob/master/dec2/pt1.cpp

**/

#include <iostream>
#include <fstream>
#include <string>
#include <array>

void check_frequencies(const std::string& key, int& n_twos, int& n_threes)
{
    bool has_two = false;
    bool has_three = false;

    // Assuming keys do only contain lowcase letters (26)
    std::array<int, 26> freqs{}; // {} initializes the array to zero
    // O(m) where m is the size of the key
    for (const char& c : key)
        ++freqs[c - 'a']; // Elegant way of increasing the frequency of a letter
    
    // O(1): the loop is always repeated <= 26 times
    for (const auto& freq : freqs)
    {
        if (freq == 2 and !has_two)
        {
            ++n_twos;
            has_two = true;
        } else if (freq == 3 and !has_three)
        {
            ++n_threes;
            has_three = true;
        } 
        if (has_two and has_three) break;
    }
}

int main()
{
    int n_twos = 0;
    int n_threes = 0;
    
    std::ifstream ifile("input.txt");
    std::string line;
    if (ifile.is_open())
    {
        // Overall algorithm: O(n*m) where n is the number of lines and m the size of each line
        while(ifile >> line) // O(n)
            check_frequencies(line, n_twos, n_threes); // O(m)
        ifile.close();
    }
    
    std::cout << "Checksum: " << n_twos * n_threes << std::endl;

    return 0;
}

