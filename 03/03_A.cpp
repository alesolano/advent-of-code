#include <iostream>
#include <fstream>
#include <string>
#include <array>


int main()
{
    int n_collisions = 0;
    
    // Constant time access. Initialized to zero. Heap allocated.
    std::array<std::array<char, 1000>, 1000> matrix{};

    std::string id, at, position, dimensions;

    std::ifstream ifile("input.txt");
    if (ifile.is_open())
    {
        while(ifile >> id >> at >> position >> dimensions)
        { 
            size_t comma = position.find(",");
            int x = std::stoi(position.substr(0, comma));
            int y = std::stoi(position.substr(comma+1, position.length() - (comma+1) - 1));
            
            size_t cross = dimensions.find("x");
            int w = std::stoi(dimensions.substr(0, cross));
            int h = std::stoi(dimensions.substr(cross+1, position.length() - (cross+1)));
            
            for (int row = x; row < x+w; ++row)
            {
                for (int col = y; col < y+h; ++col)
                {
                    ++matrix[row][col];
                    if (matrix[row][col] == 2) ++n_collisions;
                }
            }
            
        }
        ifile.close();
    }

    std::cout << n_collisions << std::endl;

    return 0;
}

