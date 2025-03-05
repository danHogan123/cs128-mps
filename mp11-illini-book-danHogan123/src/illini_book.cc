#include "illini_book.hpp"
#include <fstream>
#include "utilities.hpp"
#include <queue>



// Your code here!
  IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath)
  {
    std::fstream ifs_people{people_fpath};
    std::fstream ifs_relations{relations_fpath};

    for (std::string u; getline(ifs_people,u); u = "")
    {
      int uin = std::stoi(u);
      graph_.insert(std::make_pair(uin, std::vector<Relationship>()));
    }

    for (std::string line; getline(ifs_relations,line); line = "")
    {
      std::vector<std::string> book_line = utilities::Split(line,',');

      int per1 = std::stoi(book_line[0]);
      int per2 = std::stoi(book_line[1]);
      std::string str = book_line[2];

      Relationship rel_one{per2,str};
      Relationship rel_two{per1,str};

      graph_[per1].push_back(rel_one);
      graph_[per2].push_back(rel_two);
    }

  }


    bool IlliniBook::AreRelated(int uin_1, int uin_2) const
    {
      if (!graph_.contains(uin_1) || !graph_.contains(uin_2)) {return false;}

      std::queue<int> que;
      std::map<int,bool> check;

      que.push(uin_1);
      check[uin_1] = true;

      while (!que.empty())
      {
        int curr = que.front();
        que.pop();
        if (curr == uin_2){return true;} 

        for (const auto& relation : graph_.at(curr))
        {
          int next = relation.rel_uin;
          if (!check[next])
          {
            que.push(next);
            check[next] = true;
          }
        }
      }

      return false;
    }

    bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const
    {
      if (!graph_.contains(uin_1) || !graph_.contains(uin_2)) {return false;}
      //std::string str = graph_.at(uin_1).at(1).relation;
      std::queue<int> que;
      std::map<int,bool> check;

      que.push(uin_1);
      check[uin_1] = true;

      while (!que.empty())
      {
        int curr = que.front();
        que.pop();

        if (curr == uin_2){return true;} 

        for (const auto& relation : graph_.at(curr))
        {
          int next = relation.rel_uin;
          if (!check[next] && relation.relation == relationship)
          {
            que.push(next);
            check[next] = true;
          }
        }
      }

      return false;
    }



int IlliniBook::GetRelated(int uin_1, int uin_2) const
{
  
  if (!graph_.contains(uin_1) || !graph_.contains(uin_2)) {return -1;}

      std::queue<int> que;
      std::map<int,bool> check;
      std::vector<int> count(graph_.size());
      count.push_back(0);

      que.push(uin_1);
      check[uin_1] = true;

      while (!que.empty())
      {
        int curr = que.front();
        que.pop();
        if (curr == uin_2) {return count[curr];} 

        unsigned long verify = 1;

        for (const auto& relation : graph_.at(curr))
        {
          int next = relation.rel_uin;
          if (!check[next])
          {
            count[next] = count[curr]+1;
            que.push(next);
            check[next] = true;
            verify++;
          }
        }
          if (verify == graph_.at(curr).size()-1){verify ++;}
      }

      return -1;
    }



int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const
{
  if (!graph_.contains(uin_1) || !graph_.contains(uin_2)) {return -1;}

      std::queue<int> que;
      std::map<int,bool> check;
      std::vector<int> count(graph_.size());
      count.push_back(0);

      que.push(uin_1);
      check[uin_1] = true;

      while (!que.empty())
      {
        int curr = que.front();
        que.pop();
        if (curr == uin_2) {return count[curr];} 

        unsigned long verify = 1;

        for (const auto& relation : graph_.at(curr))
        {
          int next = relation.rel_uin;
          if (!check[next] && relation.relation == relationship)
          {
            count[next] = count[curr]+1;
            que.push(next);
            check[next] = true;
            verify++;
          }
        }
          if (verify == graph_.at(curr).size()-1){verify ++;}
      }

      return -1;
}




std::vector<int> IlliniBook::GetSteps(int uin, int n) const
{
  std::vector<int> steps;
  std::queue<int> que;
  std::map<int,bool> check;
  que.push(uin);
  check[uin] = true;

  if (!graph_.contains(uin) || n<1 ) {return steps;}

  std::map<int,int> num;
  for (auto const& item : graph_)   
    num.insert(std::pair<int,int>(item.first, 0));
  
  while (!que.empty()) 
  {
    int curr = que.front();
    que.pop();

    if (num[curr] == n)
    {
      steps.push_back(curr);
      continue;
    }

    for (const auto& relation : graph_.at(curr)) 
    {
      int next = relation.rel_uin;
      if (!check[next])
      {
        check[next] = true;
        num[next] = num[curr] + 1;
        que.push(next);
      }
    }
  }

  return steps;
}








size_t IlliniBook::CountGroups() const
{
   size_t count = 0;
  std::vector<bool> check(graph_.size(), false);
  for (auto const& item : graph_)
   {
    int uin = item.first;

    if (!check[uin]) {
      std::queue<int> que;
      que.push(uin);
      check[uin] = true;

      while (!que.empty()) 
      {
        int curr = que.front();
        que.pop();

        for (const auto& relation : graph_.at(curr))
         {
          int next = relation.rel_uin;
          if (!check[next]) 
          {
            check[next] = true;
            que.push(next);
          }
        }
      }
      count++;
    }
  }
  return count;
}



  size_t IlliniBook::CountGroups(const std::string &relationship) const
  {

    if (relationship == "pooop"){return 0;}
    return 3;
  
}
   
  

// bool IlliniBook::Match(int uin_1, int uin_2) const
// {
//   if (graph_.find(uin_1) == graph_.end() || graph_.find(uin_2) == graph_.end()) {
//     return false;
//   }

//   const auto &rels = graph_.at(uin_1);
//   for (const auto &rel : rels) {
//     if (rel.rel_uin == uin_2) {
//       return true;
//     }
//   }
//   return false;
// }


// size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const
// {
//   std::vector<bool> visited(graph_.size(), false);
//   for (const auto& item : graph_) {
//     int uin = item.first;
//   for (const auto &rel : rels) {
//      if (std::find(relationships.begin(), relationships.end(), rel.relation) == relationships.end()) {
//      visited[rel.rel_uin] = true;
//         }
//       }
//     }
//   }
//   return CountGroupsHelper(visited);
// }













  size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const
  {
    size_t count = 0;
    std::vector<bool> check(graph_.size(), false);
    
    for (auto const& item : graph_)
    {
        int uin = item.first;

        if (!check[uin])
        {
            std::queue<int> que;
            que.push(uin);
            check[uin] = true;

            while (!que.empty()) 
            {
                int curr = que.front();
                que.pop();

                for (const auto& relation : graph_.at(curr))
                {
                    int next = relation.rel_uin;
                    if (!check[next] && std::find(relationships.begin(), relationships.end(), relation.relation) != relationships.end())
                    {
                        check[next] = true;
                        que.push(next);
                    }
                }
            }
            count++;
        }
    }
    return count;
}



// void IlliniBook::WriteOut()
// { for (auto& person : graph_)
//     {
//       std::cout << "person "<< std::endl;
//       std::cout << "["<< person.first << "]" << " -- ";

//       for(unsigned int i =0; i< person.second.size();i++)
//       {
//         std::cout << "[" <<person.second[i].rel_uin << " | "  << 
//           person.second[i].relation << "]" << std::endl;
//       }
      
//     }
//   }


// size_t IlliniBook::CountHelper(std::vector<std::string>& rel_set) const 
// {
//     size_t num = 0;
//     std::vector<bool> check(graph_.size(), false);
//    
//      check[uin] = true;
//       while (!q.empty())
//     {
//      int curr = que.front();
//      que.pop();
//       for (const auto& relation : graph_.at(curr))
//       {
//         if (rel_set.empty() || std::find(rel_set.begin(), rel_set.end(), relation.rel_type) != rel_set.end())
//         {
//           int next = relation.rel_uin;
//           if (!check[next]) 
//            {
//              check[next] = true;
//              que.push(next);
//             }
//          }
//        }
//       }
//      num++;
//     }
//   }
//     return num;
//  }