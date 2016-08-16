//
//  regex_build.hpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/16.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#ifndef regex_build_hpp
#define regex_build_hpp
#include "symbol_md.hpp"
#include <regex>
#include <string>
#include <iostream>
enum regex_node{
    num=0,
    sharp,
    ref,
    pic_link,
    pic  ,
    ui
};
    bool regex_builder(const std::string &str,std::smatch &match ,regex_node node_type);


#endif /* regex_build_hpp */
