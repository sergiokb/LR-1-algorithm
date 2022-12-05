#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include "grammar.cpp"
#include "condition.cpp"
#include "analyser.cpp"


int main() {
    std::ifstream input("grammar.txt");
    if (!input.is_open()) std::cerr << "Can't open";
    std::vector<std::string> taken;
    std::string line;
    while (std::getline(input, line)) {
        taken.push_back(line);
    }
    input.close();
    Grammar grammar(taken);
    Analyser analyser(grammar);
    std::ifstream inword("word.txt");
    std::string word;
    while (inword >> word) {
        std::cout << analyser.parse(word) << std::endl;
    }
    return 0;
}