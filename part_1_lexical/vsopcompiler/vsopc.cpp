#include <iostream>

int main(int argc, char** argv)
{
    if(argc != 3)
        std::cerr << "Program usage: ./vsopc -l <SOURCE-FILE>" << std::endl;

    std::string flag = argv[1];

    if(flag == "-l")
    {
        std::cout << "Lexer on " << argv[2] << std::endl;
    }

    return 0;
}