#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
std::vector<std::string> RemNames(std::vector<std::string> in_vec);
std::vector<std::string> Counter(const std::vector<std::string>& vec_str, const std::string& argu_2); 
std::string CountHelp(const std::string& from_loop, const std::string& dna);
std::string MatchDNA(std::vector<std::vector<std::string>> people, const std::vector<std::string>& occur_count);
std::vector<std::string> MatchDNATempVec(std::vector<std::string> arg);
#endif