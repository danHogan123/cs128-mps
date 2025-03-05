#include "functions.hpp"
std::vector<std::string> RemNames(std::vector<std::string> in_vec){
  std::vector<std::string> ret_str;
  for (unsigned int i=1; i< in_vec.size(); ++i){
    ret_str.push_back(in_vec[i]);
  }
  return ret_str;
}
std::string CountHelp( const std::string& from_loop,  const std::string& dna){
     int count=0;
    int temp_count=0;
    for(unsigned int i=0; i<dna.length();++i){
        if(from_loop == dna.substr(i,from_loop.length())){
            temp_count++;
            i+=from_loop.length()-1;
        }
        else temp_count=0;
         if(temp_count>count){
                count=temp_count;
                }
    }
    return std::to_string(count);
}

std::vector<std::string> Counter(const std::vector<std::string>& vec_str, const std::string& argu_2){
  std::vector<std::string> occur_count;
for (unsigned int i=0; i<vec_str.size();++i){
 occur_count.push_back(CountHelp(vec_str[i],argu_2));
}
return occur_count;
}

std::vector<std::string> MatchDNATempVec(std::vector<std::string> arg){
 std::vector<std::string> ret_str;
  for (unsigned int i=1; i< arg.size(); ++i){
    ret_str.push_back(arg[i]);
  }
  return ret_str;
}


std::string MatchDNA(std::vector<std::vector<std::string>> people, const std::vector<std::string>& occur_count){
    std::string ret_str;
    int num_match =0;
    for(unsigned int i=0; i<people.size();++i){
    std::vector<std::string> temp_vec= MatchDNATempVec(people[i]);
if(occur_count==temp_vec){
    num_match++;
    ret_str = people[i][0];
}
}
if(num_match != 1){
   ret_str = "No Match";
}
return ret_str;
}
