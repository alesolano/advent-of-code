#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Recursive function
// We split both ids in half and compare
// Once more than two characters differ: stop comparing
// So I think the worst case here is O(2*m) where m is the length of the id
//
//
// But inside there are 4 string::subst, which are linear with size...
// So that would mean 4*(m/2), then 4*(m/4), then 4*(m/8)...
// which is 4*sum([m/(2^i) for i in range(1, m)]) ???
// and that's an elementary geometric series: https://en.wikipedia.org/wiki/1/2_%2B_1/4_%2B_1/8_%2B_1/16_%2B_%E2%8B%AF
// so the complexity is O(1)!!
//
// So, yes, I think the worst case is O(2*m). Awesome
// I think the best case is O(m/2)
bool are_different(const std::string& id1, const std::string& id2, int& fails_count, std::string& diff_char)
{
    int len = id1.length();
    if (len > 1)
    {
        std::string id1_half1 = id1.substr(0, len/2);
        std::string id2_half1 = id2.substr(0, len/2);
        if ( are_different(id1_half1, id2_half1, fails_count, diff_char) ) return true;
        
        std::string id1_half2 = id1.substr(len/2, len);
        std::string id2_half2 = id2.substr(len/2, len);
        if ( are_different(id1_half2, id2_half2, fails_count, diff_char) ) return true;
    }
    else if (id1.compare(id2) != 0)
    {
        ++fails_count;
        diff_char = id1;
    }
    
    return fails_count > 1;
}


int main()
{
    std::string result;
    
    std::vector<std::string> ids;

    // Read file and populate vector;
    // I'm concerned about vector reallocation of memory...
    std::ifstream ifile("input.txt");
    std::string line;
    if (ifile.is_open())
    {
        while(ifile >> line)
            ids.push_back(line);
        ifile.close();
    }
    
    
    // Two for loops, but the second starts at value i 
    // So the complexity would be ~ O((n^2)/2) according to
    // https://cs.stackexchange.com/questions/57593/what-is-the-time-complexity-of-the-nested-loop-j-i-ldots-n-inside-i-1-ldot
    // And then our function is O(2*m)
    // So overall let's say it's O(m*n^2)
    bool break_flag = false;
    for (int i = 0; i < (ids.size() - 1); ++i)
    {
        for (int j = i+1; j < ids.size(); ++j)
        {
            int zero = 0;
            std::string diff_char = "";
            if (are_different(ids[i], ids[j], zero, diff_char)) continue;
            else
            {
                std::cout << ids[i] << " " << ids[j] << " " << diff_char << std::endl;
                
                size_t common_pos = ids[i].find(diff_char);
                result = ids[i].substr(0, common_pos) + ids[i].substr(common_pos+1, ids[i].length());
               
                break_flag = true;
                break;
            }
        }
        
        if (break_flag) break;
    }
    
    std::cout << result << std:: endl;

    return 0;
}

