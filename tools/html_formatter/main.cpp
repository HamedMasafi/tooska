#include <fstream>
#include <iostream>
#include <html/html_document.h>
#include <string>
#include <vector>
#include <core/string_helper.h>

using namespace std;
using namespace tooska::html;

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4) {
        cout << "Invalid arguments count" << endl;
        return -1;
    }

    ifstream html_file(argv[1]);
    string html_content;
    html_file.seekg(0, std::ios::end);
    html_content.reserve(html_file.tellg());
    html_file.seekg(0, std::ios::beg);

    html_content.assign((std::istreambuf_iterator<char>(html_file)),
                     std::istreambuf_iterator<char>());

    html_document doc;
    doc.set_text(html_content);

    std::ofstream out(argv[2]);

    if (argc == 4) {
        std::string type = argv[3];
        tooska::core::string_helper::tolower(type);
        if (type == "--compact" || type == "-c")
            out << doc.to_string(tooska::print_type::compact);
        else
            out << doc.to_string(tooska::print_type::formatted);
    } else {
        out << doc.to_string(tooska::print_type::formatted);
    }
    out.close();
    std::cout << doc.to_string();

    return 0;
}
