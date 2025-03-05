#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map>

struct Relationship
{
  int rel_uin;
  std::string relation;
};


class IlliniBook {
public:

// helper
void WriteOut();
size_t CountHelper(std::vector<std::string>& rel_set) const;
//bool Match(int uin_1, int uin_2) const;


  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;


  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

private:

std::map<int,std::vector<Relationship>> graph_;

};



#endif
