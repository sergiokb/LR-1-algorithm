#include "solution.h"

void read_from_file(std::vector<std::string>& lines, const std::string& file) {
    std::ifstream input(file);
    if (!input.is_open()) std::cerr << "Can't open " << file;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
    input.close();
}

void solution(const std::string& grammar_file, const std::string& words_file,
              std::vector<std::string>& words, std::vector<std::string>& ans) {
    std::vector<std::string> description_of_rules;
    read_from_file(description_of_rules, grammar_file);

    Grammar grammar(description_of_rules);
    Analyser analyser(grammar);

    if(!analyser.grammar_is_LR1) return;

    read_from_file(words, words_file);

    for(std::string& word: words) {
        ans.push_back(analyser.parse(word));
    }
}

std::set<char> testing_first(const std::string& grammar_file, situation sit) {
    std::vector<std::string> description_of_rules;
    read_from_file(description_of_rules, grammar_file);
    Grammar grammar(description_of_rules);
    Condition temp(grammar);
    std::set<char> possible_words;
    temp.find_possible_words(possible_words, sit);
    return possible_words;
}