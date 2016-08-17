//
//  entended_feature.hpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/17.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#ifndef entended_feature_hpp
#define entended_feature_hpp
#include <deque>
#include <string>
#include <regex>
const int arr_num=40;
enum align_lrc{
    left_=1,
    right_=2,
};
bool   read_form(std::string form_line,int &form_cow,int (&align_num)[arr_num]);
bool   read_form(std::string form_line);
std::deque<std::string> form_content(std::string form);
#endif /* entended_feature_hpp */
