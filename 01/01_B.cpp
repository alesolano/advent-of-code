#include <iostream>
#include <fstream>
#include <unordered_set>
#include <utility>

int main()
{
    int result = 0;
    
    std::unordered_set<int> seen_freqs;
    seen_freqs.insert(result);
    
    std::pair<std::unordered_set<int>::iterator, bool> is_new_freq;
    
    int new_value;
    std::ifstream ifile("input.txt");
    
    if (ifile.is_open())
    {
        while(ifile >> new_value)
        {
            result += new_value;
            
            is_new_freq = seen_freqs.insert(result);
            if (is_new_freq.second) std::cout << result << " ";
            else break;
        }
        std::cout << std::endl;

        ifile.close();
    }
    else std::cout << "Unable to read file.\n";
    
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}

