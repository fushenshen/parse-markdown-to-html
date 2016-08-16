//
//  regex_build.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/16.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include "regex_build.hpp"
    bool regex_builder(const std::string &str,std::smatch &match ,regex_node node_type){
     if (node_type==regex_node::num) {
        
            std::regex pieces_regex("(\\d\\.\\s)((.*)*)");
            if (std::regex_match(str, match, pieces_regex)){
                return true;
            }
     }
     else if(regex_node::sharp==node_type){
            std::regex pieces_pic("(#)+(.*)");
            // ####
            if(std::regex_match(str,match,pieces_pic)){
                return  true;
            }
     }
     else if(regex_node::ref==node_type){
           std::regex pieces_pic(">.*");
            if(std::regex_match(str,match,pieces_pic)){
             return  true;
         }
    
     }
     else if(regex_node::pic_link==node_type){
           std::regex pieces_regex("(.*)!?\\[(.*)\\]\\(((.+))\\)(.*)");
         if(std::regex_match(str,match,pieces_regex)){
             return  true;
         }
     }
     else if(regex_node::pic==node_type){
          std::regex pieces_pic("(https|http):[0-9a-zA-Z_/.]*.(jpg|jpeg|png)");
         if(std::regex_match(str,match,pieces_pic)){
             return  true;
         }
     }
     else if(regex_node::ui==node_type){
          std::regex pieces_regex("((!|-|\\*|\\+))(\\s.*)");
          if(std::regex_match(str,match,pieces_regex)){
             return  true;
         }
     }
        return false;
}