//
//  md_transform.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/16.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include "md_transform.hpp"
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
            //表头
//            if(read_form(line)){
//                if(!flag){
//                //  table \n thead\n tr\n  结束时  </tr>  </thead>
//                std::deque<std::string> dq_form= form_content(line);
//                line+="<table>\n<thead>\n<tr>\n";
//                for(auto str_tmp:dq_form){
//                    line+="<th>"+str_tmp+"</th>"+"\n";
//                }
//                line=line+"</tr>\n"+"</thead>\n\n<tbody>";
//                flag=flag+1;
//                }
//                else {
//                    std::deque<std::string>dq_form = form_content(line);
//                    if(!dq_form.empty()){
//                        line+="<tr>\n";
//                        for(auto str_tmp:dq_form){
//                            line+="<th>"+str_tmp+"</th>"+"\n";
//                        }
//                        line=line+"</tr>\n";
//                    }
//                }
//                continue;
//            }
//           //得到整个表格的line
//            flag=0;
//            line+="</tbody>\n</table>\n";
            analyze_sentence(line);
            
        }
        
    }
    dq.push_back(foot);
    std::cout<<foot<<std::endl;
}

void read_tohtml(std::string line_,std::string out_file){
    transform_md(line_);
    extern std::deque<std::string> dq;
    std::ofstream out(out_file);
    if (out.is_open()){
        for(auto &sq:dq){
            out << sq<<std::endl;
        }
    }
    out.close();

}