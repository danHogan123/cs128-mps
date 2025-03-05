#include "db_table.hpp"
#include "iostream"
#include "stdexcept"

// const unsigned int kRowGrowthRate = 2;
void DbTable::ResizeRow(){
  for (unsigned long i=0; i<rows_.size(); i++){
  void** temp = new void*[row_col_capacity_];
 for (unsigned long j=0; j<col_descs_.size(); j++)
temp[j] = rows_.at(i)[j];
 delete[] rows_.at(i);
 rows_.at(i) = temp;
    }
    }

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc){
    if(col_descs_.size() == row_col_capacity_){
      row_col_capacity_ = row_col_capacity_ * 2;
      ResizeRow();
    }
    col_descs_.push_back(col_desc);

    for (unsigned int i=0; i<rows_.size(); i++){

     if (col_desc.second == DataType::kString){
       rows_.at(i)[col_descs_.size()-1] = static_cast<void*>(new std::string(""));
    } else if (col_desc.second == DataType::kDouble){
       rows_.at(i)[col_descs_.size()-1] = static_cast<void*>(new double(0.0));
    } else{
      rows_.at(i)[col_descs_.size()-1] = static_cast<void*>(new int(0));
      }
     }
}

  void DbTable::DeleteColumnByIdx(unsigned int col_idx){
    if(col_idx > col_descs_.size()){
      throw std::out_of_range("");
    }
    if(col_descs_.size() == 1 && !rows_.empty()){
    throw std::runtime_error("");
      }

  for (unsigned int i=0; i<rows_.size(); i++){
    if (col_descs_.at(col_idx).second == DataType::kString){

    delete static_cast<std::string*>(rows_.at(i)[col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kDouble){

    delete static_cast<double*>(rows_.at(i)[col_idx]);
    } else { delete static_cast<int*>(rows_.at(i)[col_idx]);}

  for (unsigned long j=col_idx; j<col_descs_.size(); j++){
   rows_.at(i)[j] = rows_.at(i)[j+1]; }
      }



  auto place = col_descs_.begin() + col_idx;
    col_descs_.erase(place);
     }

     

  void DbTable::AddRow(const std::initializer_list<std::string>& col_data){
  if(col_data.size()!= col_descs_.size()){
    throw std::invalid_argument("");
  }
   rows_.insert({next_unique_id_, new void*[row_col_capacity_]});
    int it =0;

    for (const std::string& s : col_data) {
       

 if(col_descs_.at(it).second == DataType::kDouble){
rows_.at(next_unique_id_)[it] = static_cast<void*>(new double(std::stod(s)));
}
 else if(col_descs_.at(it).second == DataType::kString){
rows_.at(next_unique_id_)[it] = static_cast<void*>(new std::string(s));
 }
 else{rows_.at(next_unique_id_)[it] = static_cast<void*>(new int(std::stoi(s)));}
       
 it++;
    }
    next_unique_id_++;
  }

  
  void DbTable::DeleteRowById(unsigned int id){
    if(id >= next_unique_id_ || id < 0){
    throw std::invalid_argument ("");}

 for (unsigned long i=0; i<  col_descs_.size(); i++){

   if (col_descs_.at(i).second == DataType::kDouble){
 delete static_cast<double*>(rows_.at(id)[i]);
 }

   else if (col_descs_.at(i).second == DataType::kString){
delete static_cast<std::string*>(rows_.at(id)[i]);
}

   else{delete static_cast<int*>(rows_.at(id)[i]);}
    }


    delete[] rows_.at(id);
    rows_.erase(id);
   
  }

  DbTable::DbTable(const DbTable& rhs){
    //next_unique_id_ = rhs.next_unique_id_; 
  next_unique_id_ = rhs.next_unique_id_;

  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;

for( unsigned long i=0; i<rhs.rows_.size(); i++){
 void** t = new void*[rhs.col_descs_.size()];

  for ( unsigned long j=0; j< rhs.col_descs_.size();++j) {
      void* point = rhs.rows_.at(i)[j];
      
   if (rhs.col_descs_.at(j).second == DataType::kString){
   auto* st = new std::string(*(static_cast<std::string*>(point)));
      t[j] = static_cast<void*>(st);}

   else if (rhs.col_descs_.at(j).second == DataType::kDouble){   
    auto* dub = new double(*(static_cast<double*>(point)));
      t[j] = static_cast<void*>(dub);}

   else{
  auto* intp = new int(*(static_cast<int*>(point)));
  t[j] = static_cast<void*>(intp); }
        }
        rows_.insert({i, t});
       //  rows_.insert(std::pair<unsigned int, void**>{i, t});

    }
  }


void DbTable::OperatorHelper(){
for (unsigned long i=0; i<rows_.size(); i++) {

for (unsigned long j=0; j<col_descs_.size(); j++) {

if (col_descs_.at(j).second == DataType::kString){
   delete static_cast<std::string*>(rows_.at(i)[j]);}
else if (col_descs_.at(j).second == DataType::kDouble){
   delete static_cast<double*>(rows_.at(i)[j]);}
else {delete static_cast<int*>(rows_.at(i)[j]);}
        }

        delete[] rows_.at(i);
        col_descs_.clear();
        rows_.clear();
    }
}

  DbTable& DbTable::operator=(const DbTable& rhs){
    if(this == &rhs){ return *this;}
   OperatorHelper();
 next_unique_id_ = rhs.next_unique_id_;
    row_col_capacity_ = rhs.row_col_capacity_;
    col_descs_ = rhs.col_descs_;


for( unsigned long i=0; i<rhs.rows_.size(); i++){
 void** t = new void*[rhs.col_descs_.size()];
  for ( unsigned long j=0; j< rhs.col_descs_.size();++j) {
      void* point = rhs.rows_.at(i)[j];
   if (rhs.col_descs_.at(j).second == DataType::kString){
   auto* st = new std::string(*(static_cast<std::string*>(point)));
      t[j] = static_cast<void*>(st);
      }
   else if (rhs.col_descs_.at(j).second == DataType::kDouble){   
    auto* dub = new double(*(static_cast<double*>(point)));
      t[j] = static_cast<void*>(dub);
     }
   else{
  auto* intp = new int(*(static_cast<int*>(point)));
 t[j] = static_cast<void*>(intp);
  }
        }
       rows_.insert({i, t});
         //rows_.insert(std::pair<unsigned int, void**>{i, t});
    }
    return *this;
  }


  DbTable::~DbTable(){
for (unsigned  long i=0; i<rows_.size(); i++){

   for (unsigned long j=0; j<col_descs_.size(); j++){

if (col_descs_.at(j).second == DataType::kString){
  delete static_cast<std::string*>(rows_.at(i)[j]);
  }
else if(col_descs_.at(j).second == DataType::kDouble){
delete static_cast<double*>(rows_.at(i)[j]);}
else{ delete static_cast<int*>(rows_.at(i)[j]);
}
  }
        delete[] rows_.at(i);
    } 
    col_descs_.clear();
    rows_.clear();
  }


// void OsOperatorHelper(std::vector<std::pair<std::string, DataType>> vec_pr,){
//   for (unsigned long i=0; i<vec_pr.size() - 1; i++) {
//         name = vec_pr.at(i).first;
//         if (vec_pr.at(i).second == DataType::kString)
//             dt = "std::string";
//         else if (vec_pr.at(i).second == DataType::kDouble)
//             dt = "double";
//         else
//             dt = "int";
//         os << name << "(" << dt << "), ";
//     }
// }
  

 std::ostream& operator<<(std::ostream& os, const DbTable& table){
if(table.row_col_capacity_ ==2){
return os;
    }

    return os;

    
//  std::vector<std::pair<std::string, DataType>> vec_pr = table.col_descs_;
//     std::string name;
//     std::string dt;
//     //OsOperatorHelper(vec_pr,name,dt,os);
//     name = vec_pr.at(vec_pr.size() - 1).first;

// if (vec_pr.at(vec_pr.size() - 1).second == DataType::kString){
//      dt = "std::string";}
// else if (vec_pr.at(vec_pr.size() - 1).second == DataType::kDouble){
//    dt = "double";
//         }
// else{ dt = "int";}
//     os << name << "(" << dt << ")" << std::endl;

//     for (unsigned long i=0; i<table.rows_.size() - 1; i++) {
//         for (unsigned long j=0; j<vec_pr.size(); j++){
//         os << table.rows_.at(i)[j] << ", ";
//             }
//         os << std::endl;
//     }

//     for (unsigned long j=0; j<vec_pr.size() - 1; j++){
//         os << table.rows_.at(table.rows_.size() - 1)[j] << ", ";}

//     os << table.rows_.at(table.rows_.size() - 1)[vec_pr.size() - 1] << std::endl;
//     return os;



//     return os;
   }

