#include <iostream>
#include <fstream>
#include <cstring>

namespace {
    int multiplicator;
}

int main(int argc, char** argv)
{
    std::ifstream file_in;

    if (argc >= 2 && (strcmp(argv[1], "-") != 0)) {
        if(argv[2] != nullptr)
        {
            multiplicator = (int)*argv[2] - 48;
        }
        else
        {
            multiplicator = 2;
        }
        file_in.open(argv[1]);
        if (file_in.is_open()) {
            std::cin.rdbuf(file_in.rdbuf());
            std::cerr << "Using " << argv[1] << "..." << std::endl;
        } else {
            std::cerr   << "Error: Cannot open '"
                        << argv[1] 
                        << "', using stdin (press CTRL-D for EOF)." 
                        << std::endl;
        }
    } else {
        std::cerr << "Using stdin (press CTRL-D for EOF)." << std::endl;
    }

    while (!std::cin.eof()) {

        std::string line;

        std::getline(std::cin, line);
        if (!line.empty()) {
            int val = atoi(line.c_str());
            std::cout << val * multiplicator << std::endl;
        }
    }

    if (file_in.is_open()) {
        file_in.close();
    }

    return 0;
}
