#include <iostream>
#include <fstream>
#include "analyser.h"

void read_from_file(std::vector<std::string>& lines, const std::string& file);

void solution(const std::string& grammar_file, const std::string& words_file,
                        std::vector<std::string>& words, std::vector<std::string>& ans);

std::set<char> testing_first(const std::string& grammar_file, situation sit);
// in this function I am testing functions find_possible_words and FIRST
// Watch my_tests.cpp