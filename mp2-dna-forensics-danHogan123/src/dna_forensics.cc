#include <iostream>
#include <fstream>
#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
std::vector<std::string> vec;
std::ifstream ifs{argv[1]};
//pulls first line, and turns breaks into a vector
for(std::string line; std::getline(ifs, line); line = ""){
  //std::cout << line << std::endl;
vec = utilities::GetSubstrs(line,',');
break;
  }
 std::vector<std::string> dna_seq = RemNames(vec);

 std::vector<std::string> dna_sequence_count = Counter(dna_seq,argv[2]);

 std::vector<std::vector<std::string>> verify_vec;
for(std::string line; std::getline(ifs, line); line = ""){
  
std::vector<std::string> temp_vec =(utilities::GetSubstrs(line,','));
verify_vec.push_back(temp_vec);
  }
std::cout << MatchDNA(verify_vec,dna_sequence_count) << std::endl;

  return 0;
}