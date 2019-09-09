#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


struct IsTwoThree
{
    int isTwo = 0;
    int isThree = 0;
};


IsTwoThree count_chars(const std::string& s)
{
    IsTwoThree pair;
    // Overall loop: Quadratic O(m^2) where m is the size of s
    // Liner O(m)
    for (auto& c: s)
    {
        // Linear O(m)
        int count = std::count(s.begin(), s.end(), c);
        if (count == 2) pair.isTwo = 1;
        if (count == 3) pair.isThree = 1;
        if (pair.isTwo==1 and pair.isThree==1) break;
    }
    return pair;
}


int main()
{
    auto ifile = std::ifstream("input.txt");

    std::string line;
    int n_twos = 0;
    int n_threes = 0;

    // Overall algorithm: O(n*m^2) where n is the number of lines and m the size of each line
    // Liner O(n)
    while(ifile >> line)
    {
        IsTwoThree pair = count_chars(line);
        n_twos += pair.isTwo;
        n_threes += pair.isThree;
    }

    std::cout << "Checksum: " << n_twos * n_threes << std::endl;
    
    return 0;
}

