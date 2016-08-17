//
//  main.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/11.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//
#include "symbol_md.hpp"
#include "entended_feature.hpp"
using namespace std;

int main(){
     std::string line_="/Users/fushenshen/Documents/test.md";
     std::string out_file="/Users/fushenshen/Documents/out.html";
     read_tohtml(line_, out_file);

}


