#include "functions.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

// Your function definitions should go in this source file.
std::vector<std::string> uni_vec;

std::string MakeLower (std::string str){
    std::string n_str;
    for (unsigned int i=0;i<str.length();i++) {
        n_str += tolower(str.at(i));
     }
   return n_str;
    }


   std::string ChangePro(std::string str1){
        std::string alt_wrd;
        //loops lowercase word
for (unsigned int i=0; i<str1.length();i++){
    //all times when an 'a' appers
    

if(str1[i]=='a'){
    if (str1[i+1]=='i' || str1[i+1]=='e'){
     alt_wrd += "eye-";
      i++;
    }      else if (str1[i+1]=='o' || str1[i+1]=='u') {
     alt_wrd += "ow-";
      i++; 
     } else alt_wrd += "ah-";
     continue;
    } 

    //all times an 'e' appears
if(str1[i]=='e'){
    if (str1[i+1]=='i'){
     alt_wrd += "ay-";
     i++;
    } else if (str1[i+1]=='u'){
     alt_wrd += "eh-oo-";
     i++;
     } else if(str1[i+1]=='w'){
        alt_wrd += "ee-v";
        i++;
     } else alt_wrd += "eh-";
    continue;}

    //when 'i' appears
if(str1[i]=='i'){
    if(str1[i+1]=='u'){
alt_wrd += "ew";
i++;
    } else if(str1[i+1]=='w'){
        alt_wrd += "ee-v";
        i++;
     } else alt_wrd += "ee-";
    continue;
}

//checks 'o'
if(str1[i]=='o'){
    if(str1[i+1]=='i'){
alt_wrd += "oy-";
i++;
    } else if(str1[i+1]=='u'){
alt_wrd += "ow-";
i++;
    } else alt_wrd += "oh-";
    continue;
}
//for 'u'
if(str1[i]=='u'){
if (str1[i+1]=='i'){
    alt_wrd += "ooey-";
    i++;
} else alt_wrd += "oo-";
continue;
}
//finally for 'w'

alt_wrd += str1[i];
}
return alt_wrd;
    }

    std::string TakeOff(std::string str){
        std::string end_off;
          for (unsigned int i=0;i<str.length()-1;i++) {
            if((str.at(i)=='-') && (str.at(i+1)=='\'' || str.at(i+1)==' ')){
                continue;
            }
        end_off += str.at(i);
     }
     //end_off += str.at(str.length()-1);
   return end_off;

    }