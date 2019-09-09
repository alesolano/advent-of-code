#include <iostream>
#include <fstream>
#include <unordered_set>
#include <forward_list>
#include <utility>

int main()
{
    int last_freq = 0;
    
    std::forward_list<int> freqs;
    auto last_freq_i = freqs.insert_after(freqs.before_begin(), last_freq);
    
    std::unordered_set<int> seen_freqs;
    seen_freqs.insert(last_freq);
    
    std::pair<std::unordered_set<int>::iterator, bool> is_new_freq_pair;
    bool is_new_freq = true;

    int new_value;
    std::ifstream ifile("input.txt");
    
    // First reading
    if (ifile.is_open())
    {
        while(ifile >> new_value and is_new_freq)
        {
            last_freq += new_value;
            
            last_freq_i = freqs.insert_after(last_freq_i, last_freq);
            
            is_new_freq_pair = seen_freqs.insert(last_freq);
            is_new_freq = is_new_freq_pair.second;
        }

        ifile.close();
    }
    else std::cout << "Unable to read file.\n";
    
    std::cout << "Last frequency: " << last_freq << std::endl;
    
    // Parse until a frequency is repeated:
    auto freq_i = freqs.begin();
    while (is_new_freq)
    {
        ++freq_i;
        new_value = *freq_i + last_freq;
        
        last_freq_i = freqs.insert_after(last_freq_i, new_value);
        
        is_new_freq_pair = seen_freqs.insert(new_value);
        is_new_freq = is_new_freq_pair.second;
    }
    
    std::cout << "Result: " << new_value << std::endl;
    
    return 0;
}

