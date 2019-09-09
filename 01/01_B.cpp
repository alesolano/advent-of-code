#include <iostream>
#include <fstream>
#include <unordered_set>
#include <forward_list>
#include <utility> // std::pair
#include <memory> // std::unique_ptr

// Some aliases for convenience
using flist_int = std::forward_list<int>;
using uset_int = std::unordered_set<int>;

int main()
{
    int last_freq = 0;
    
    // Forward list to insert all frequencies at constant time
    std::unique_ptr<flist_int> freqs(new flist_int);
    // In a forward list, we need to track the iterator of the last element
    // to guarantee constant time insert
    auto last_freq_i = freqs->insert_after(freqs->before_begin(), last_freq);
    
    // Unordered set to find repeated frequencies at average constant time
    std::unique_ptr<uset_int> seen_freqs(new uset_int);
    seen_freqs->insert(last_freq);
    
    // Iterator for the set, containig a bool that says
    // if a frequency is new or repeated when we try to insert it
    std::pair<uset_int::iterator, bool> is_new_freq_pair;
    bool is_new_freq = true;

    // First reading
    std::ifstream ifile("input.txt");
    int new_value;
    if (ifile.is_open())
    {
        // Read each line as an integer (new_value)
        while(ifile >> new_value and is_new_freq)
        {
            last_freq += new_value;
            
            last_freq_i = freqs->insert_after(last_freq_i, last_freq);
            
            is_new_freq_pair = seen_freqs->insert(last_freq);
            // Second element of the pair checks if the frequency is repeated
            is_new_freq = is_new_freq_pair.second;
        }

        ifile.close();
    }
    else std::cout << "Unable to read file.\n";
    
    std::cout << "Last frequency: " << last_freq << std::endl;
    
    // Parse until a frequency is repeated:
    auto freq_i = freqs->begin();
    while (is_new_freq)
    {
        // Increase iterator
        // It won't ever reach the end since we are adding new frequencies each time
        ++freq_i;
        
        // This line is basically the whole algorithm
        new_value = *freq_i + last_freq;
        
        last_freq_i = freqs->insert_after(last_freq_i, new_value);
        
        is_new_freq_pair = seen_freqs->insert(new_value);
        is_new_freq = is_new_freq_pair.second;
    }
    
    std::cout << "Result: " << new_value << std::endl;
    
    return 0;
}

