//===============================================
// methode 1
//===============================================
// std::pair est fondamentalement :

struct std::pair {
    std::string first;
    std::string second;
};

std::vector<std::pair<std::string, std::string>> header_data = get_png_header_data(file_contents);

for (unsigned int i = 0; i < header_data.size(); i++)
{
    std::cout << header_data[i].first;
}
