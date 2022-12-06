#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include "grammar.cpp"
#include "situation.cpp"
#include "condition.cpp"
#include "analyser.cpp"

void read_from_file(std::vector<std::string>& lines, const std::string& file) {
    std::ifstream input(file);
    if (!input.is_open()) std::cerr << "Can't open";
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
    input.close();
}

int main() {
    std::vector<std::string> lines_of_rules;
    read_from_file(lines_of_rules, "grammar.txt");

    Grammar grammar(lines_of_rules);
    Analyser analyser(grammar);

    std::vector<std::string> words;
    read_from_file(words, "words.txt");

    for(std::string& word: words) {
        std::cout << analyser.parse(word) << '\n';
    }
    return 0;
}
