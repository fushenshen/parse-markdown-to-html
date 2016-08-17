//
//  md_transform.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/16.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include "md_transform.hpp"
extern std::deque<std::string> dq;
void  trans_meaning(std::string &line){
    for(auto it=line.begin();
        it!=line.end();
        ++it){
        if(*it=='<'){
            line.replace(it, it+1, "&lt;");
        }
        else if(*it=='>'){
         line.replace(it, it+1, "&gt;");
        }
    }
    

}
void transform_md( std::string &line){
    std::ifstream myfile (line);
    extern std::deque<std::string> dq;
    dq.push_back(head);
    std::string form_str;
    extern const int arr_num;
    int  flag=0;
    
    if (myfile.is_open())
    {
        
        while( getline (myfile,line))
        {
            
            if(line==""){
                continue;
            }
//            if(!line.find_first_of(" ")||!line.find_first_of("\t")){
//                continue;
//            }

            if(read_form(line)){
                if(!flag){
                form_str.clear();
                std::deque<std::string> dq_form= form_content(line);
               form_str+="<table>\n<thead>\n<tr>\n";
                for(auto str_tmp:dq_form){
                    string_removespace(str_tmp);
                    form_str+="<th>"+str_tmp+"</th>"+"\n";
//
                }
               
                form_str=form_str+"</tr>\n"+"</thead>\n\n<tbody>\n";
//                std::cout<<form_str<<std::endl;
                flag=flag+1;
                }
                else {
                    std::deque<std::string>dq_form = form_content(line);
                    if(!dq_form.empty()){
                       form_str+="<tr>\n";
                        for(auto str_tmp:dq_form){
                           form_str+="<td>"+str_tmp+"</td>"+"\n";
                        }
                       form_str=form_str+"</tr>\n";
                    }
                }
            
                continue;
            }
           
           //得到整个表格的line
            if(flag==1){
                flag=0;
                form_str+="</tbody>\n</table>\n";
                dq.push_back(form_str);
            }

            analyze_sentence(line);
            
        }
        
    }
    dq.push_back(foot);
    
}

void read_tohtml(std::string line_,std::string out_file){
    transform_md(line_);
    std::ofstream out(out_file);
    if (out.is_open()){
        for(auto &sq:dq){
            out << sq<<std::endl;
        }
    }
    out.close();

}