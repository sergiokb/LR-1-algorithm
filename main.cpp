#include <iostream>
#include <fstream>
#include "src/analyser.h"

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
    std::vector<std::string> description_of_rules;
    read_from_file(description_of_rules, "grammar.txt");

    Grammar grammar(description_of_rules);
    Analyser analyser(grammar);

    std::vector<std::string> words;
    read_from_file(words, "words.txt");

    for(std::string& word: words) {
        std::cout << word << " - "<< analyser.parse(word) << '\n';
    }
    return 0;
}
