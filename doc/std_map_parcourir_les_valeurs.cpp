//===============================================
// methode 1
//===============================================
map<string, int>::iterator it;

for (it = symbolTable.begin(); it != symbolTable.end(); it++)
{
    std::cout << it->first    // string (key)
              << ':'
              << it->second   // string's value 
              << std::endl;
}

//===============================================
// methode 2
//===============================================
// Avec C++11
for (auto const& x : symbolTable)
{
    std::cout << x.first  // string (key)
              << ':' 
              << x.second // string's value 
              << std::endl;
}

//===============================================
// methode 3
//===============================================
// Avec C++17
for (auto const& [key, val] : symbolTable)
{
    std::cout << key        // string (key)
              << ':'  
              << val        // string's value
              << std::endl;
}
