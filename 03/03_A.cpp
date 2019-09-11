#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <memory>

using array2D = std::array<std::array<char, 1000>, 1000>;

int main()
{
    int n_collisions = 0;
    
    // TODO: How to initialize to zero?
    std::unique_ptr<array2D> matrix(new array2D);
    
    std::string id, at, position, dimensions;
    
    std::ifstream ifile("input.txt");
    if (ifile.is_open())
    {
        while(ifile >> id >> at >> position >> dimensions)
        {
            std::cout << id << " --- " << at << " --- " << position << " --- " << dimensions << "\n";
            
            size_t comma = position.find(",");
            int x = std::stoi(position.substr(0, comma));
            int y = std::stoi(position.substr(comma+1, position.length() - (comma+1) - 1));
            
            size_t cross = dimensions.find("x");
            int w = std::stoi(dimensions.substr(0, cross));
            int h = std::stoi(dimensions.substr(cross+1, position.length() - (cross+1)));
            
            std::cout << x << " " << y << " " << w << " " << h << std::endl;
            
            for (int row = x; row < x+w; ++row)
            {
                for (int col = h; h < y+h; ++col)
                {
                    continue;
                    //++matrix[row][col];
                    //if (matrix[row][col] == 2) ++n_collisions;
                }
            }
            
            
            // TODO: Remove this after tests
            break;
        }
        ifile.close();
    }

    return 0;
}

