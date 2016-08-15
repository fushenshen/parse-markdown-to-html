//
//  main.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/11.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include <fstream>
#include "symbol_md.hpp"
int main(){
    using namespace std ;
    string line;
    ifstream myfile ("/Users/fushenshen/Documents/test.md");
    cout<<head<<endl;
    if (myfile.is_open())
    {
        while( getline (myfile,line))
        {
            if(line==""){
                continue;
            }
            analyze_sentence(line);
        }
        
    }
    cout<<foot<<endl;
}


