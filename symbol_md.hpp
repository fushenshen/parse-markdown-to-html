//
//  symbol_md.hpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/11.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#ifndef symbol_md_hpp
#define symbol_md_hpp
#include <iostream>
#include <regex>
#include<string>
#include <vector>
    const char head[]="<html><head><meta charset=""utf-8""><title>test</title></head><body>";
    const char foot[]="</body></html>";

void analyze_sentence(std::string &str);
void string_removespave(std::string &str);
bool read_pic(const std::string& str);
bool read_code( const std::string& line);
bool read_ui(const std::string &ul_string);
bool  read_sharp(const std::string &str);
bool read_ref( std::string &str);
bool read_pic_link(const std::string fname);
void scanning_head(const std::string& allstr,std::string &read);
std::string read_all(std::string);
bool read_num(const std::string &str);
#endif /* symbol_md_hpp */
