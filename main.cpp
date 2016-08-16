//
//  main.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/11.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//
#include "md_transform.hpp"
//提高代码的高复用性
int main(){
    using namespace std ;
    //Users/fushenshen/Documents/test.md
     std::string line_="/Users/fushenshen/Documents/test.md";
     std::string out_file="/Users/fushenshen/Documents/out.html";
    read_tohtml(line_, out_file);
  
}


