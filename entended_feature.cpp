//
//  entended_feature.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/17.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include "entended_feature.hpp"

bool   read_form(std::string form_line){
    if(!form_line.size()){
        return false;
    }
    if(form_line.front()=='|'&&form_line.size()==1){
//        form_cow+=1;
        return true;
    }
//    if(form_line.front()=='|'){
//        form_cow+=1;
//    }
    return read_form(std::string(form_line.begin()+1,form_line.end()));
}

bool   read_form(std::string form_line,int &form_cow,int (&align_num)[arr_num]){
    if(!form_line.size()){
        return false;
    }
    if(form_line.front()=='|'&&form_line.size()==1){
        form_cow+=1;
        return true;
    }
    if(form_line.front()=='|'){
        form_cow+=1;
    }
    if(form_line.front()==':'){
        if(*(form_line.begin()+1)=='|'){
            align_num[form_cow]+=right_;
        }
        else {
            align_num[form_cow]+=left_;
        }
        if(align_num[form_cow]>2){
            align_num[form_cow]=2;
        }
    }
    
    return read_form(std::string(form_line.begin()+1,form_line.end()),form_cow,align_num);
}

std::deque<std::string> form_content(std::string form){
    std::deque<std::string> f_dq;
    //(\|:?)(.+)(:?\|)  ((\\|:?)(.+)(:?\\|))+
    std::smatch match;
    std::regex pieces_regex("[^-:|]+");
    while(std::regex_search(form, match, pieces_regex)){
        f_dq.push_back(match.str());
        form = match.suffix();
    }
    return f_dq;
}




