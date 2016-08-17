//
//  md_transform.hpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/16.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#ifndef md_transform_hpp
#define md_transform_hpp
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include "symbol_md.hpp"
#include "entended_feature.hpp"
void transform_md( std::string &line);
 void  trans_meaning(std::string &line);
void read_tohtml(std::string line_,std::string out_file);
#endif /* md_transform_hpp */
