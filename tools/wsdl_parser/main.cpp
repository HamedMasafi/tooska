#include <fstream>
#include <iostream>
#include <soap/class_generator.h>
#include <soap/wsdl_parser.h>
#include <string>
#include <vector>

using namespace std;
using namespace tooska::soap;

int main(int argc, char **argv)
{
    ifstream wsdl_file(argv[1]);

    if (argc != 2) {
        cout << "Invalid arguments count" << endl;
        return -1;
    }

    string wsdl_content;
    wsdl_file.seekg(0, std::ios::end);
    wsdl_content.reserve(wsdl_file.tellg());
    wsdl_file.seekg(0, std::ios::beg);

    wsdl_content.assign((std::istreambuf_iterator<char>(wsdl_file)),
                     std::istreambuf_iterator<char>());

    wsdl_parser parser;
    parser.set_content(wsdl_content);

    class_generator generator(&parser);
    generator.generate();

    return 0;
}
