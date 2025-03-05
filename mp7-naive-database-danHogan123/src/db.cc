#include "db.hpp"


 void Database::CreateTable(const std::string& table_name){ 
    tables_.insert(std::pair<std::string,DbTable*>(table_name,new DbTable()));
    }

  //void Database::DropTable(const std::string& table_name){
    void Database::DropTable(const std::string& table_name){
    if (!tables_.contains(table_name))
      throw std::invalid_argument("No table with given name");
    if(tables_.contains(table_name)){
      delete tables_.at(table_name);
      tables_.erase(table_name);
    }
  }
    
  
  DbTable& Database::GetTable(const std::string& table_name){
    return *tables_[table_name];
  }

  Database::Database(const Database& rhs){
  //    if(!rhs.tables_==DbTable){
  //     tables_.*DbTable = nullptr;
  //    return;
  //  }
if(rhs.tables_.empty()){
   return;
}
//erase map data
   for (auto& [key, value] : tables_) {
    if(tables_.contains(key)) {
    delete tables_.at(key);
      tables_.erase(key);}
   }
   tables_.clear();
//copy data into tables_


   for (auto const& [key, value] : rhs.tables_) { 
     tables_.insert(std::pair<std::string,DbTable*>(key,value));
   }
  }

  Database& Database::operator=(const Database& rhs){
    if(rhs.tables_.empty()){
      return *this;
    }
    for (auto& [key, value] : tables_) {
      if(tables_.contains(key)){
      delete tables_.at(key);
      tables_.erase(key);}
    }
    tables_.clear();

for (auto const& [key, value] : rhs.tables_) { 
     tables_.insert(std::pair<std::string,DbTable*>(key,value));
   }

    return *this;
  }
//     tables_= rhs.tables_;
//     return *this;
//   }
  Database::~Database(){
    for(auto [k, v] : tables_){
      if(tables_.contains(k)){
      delete tables_.at(k);
       tables_.erase(k);}
      //if (*v.col_descs_.at(j).second == DataType::kString)
     //  v->~DbTable();
    }
    tables_.clear();
 }
  std::ostream& operator<<(std::ostream& os, const Database& db){
  
 for (auto const& [key, value] : db.tables_) { 
     os << key    << ':'    << value    << std::endl;
   }
    
return os;
    
  }