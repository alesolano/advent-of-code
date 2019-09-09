#include <iostream>
#include <fstream>

int main()
{
    int result = 0;
    
    int new_value;
    std::ifstream ifile("input_01_A.txt");
    
    if (ifile.is_open())
    {
        while(ifile >> new_value)
        {
            std::cout << new_value << " ";
            result += new_value;
        }
        std::cout << std::endl;

        ifile.close();
    }
    else std::cout << "Unable to read file.\n";
    
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}

