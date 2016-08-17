//
//  symbol_md.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/11.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include "symbol_md.hpp"
std::deque<std::string> dq;
 void string_removespace(std::string &str){
  str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}
//bool is_form(std::string &str){
//    std::regex pieces_regex("<table>");
//    std::smatch match;
//    if (std::regex_match(str, match, pieces_regex)){
//        return true;
//    }
//    return  false;
//}
bool ref_complex(std::string &str){
    if(str.front()=='>'){
        auto string_final= read_all(std::string(str.begin()+1,str.end()));
        auto index=str.find_first_of ("#");
        if(index<str.length()){
            auto num_sharp=str.find_last_of("#")-index;
            string_final="<h"+std::to_string(num_sharp) +">"+string_final+"</h"+std::to_string(num_sharp)+">"+"\n</blockquote>";
            
        }
        else {
       string_final="<blockquote>\n"+string_final+"\n</blockquote>";
        }
        string_removespace(string_final);
        std::cout<<string_final<<std::endl;
        dq.push_back(string_final);
        return true;
    }
    else {
        return false;
    }
}
std::vector<char >vec{'#','*','-','+','.','>','`','=','~','_'};
int blode_num=0;
std::string code_string;
std::string num_string;
std::string ves;
int flag=0;
bool read_code(  std::string& line){
    if(line=="```"){
        flag++;
        if(flag>1){
            flag=0;
        }
        return  true;
    }
    if(flag==1){
        if(line!="```"){
            trans_meaning(line);
            ves+=line+"\n";
        }
          return true;
    }
    else {
        if(!ves.empty()){
            ves="<div><pre><code>\n"+ves+"</div></pre></code>\n\n";
            dq.push_back(ves);
            std::cout<<ves;
            ves.clear();
        }
        return  false;
    }
    return  false;
}
void analyze_sentence(std::string &str){
    if(read_num(str)){
        return;
    }
    if(read_ui(str)){
        return;
    }
  
    if(read_pic_link(str)){
        
        return;
    }
    if(ref_complex (str)){
        return;
    }
    if(  read_code(str)){
        return;
    }
    if(read_pic(str)){
        return;
    }
   
    if(read_sharp(str)){
        return;
    }
    else{
        std::string all_str=read_all(str);
        dq.push_back(all_str);
        std::cout<<all_str<<std::endl;
    }

}

bool read_pic(const std::string &fname){
    
        std::string filename;
        std::string suffix;
        std::smatch pieces_match;
        std::regex pieces_regex("!?\\[(.*)\\]\\(((.+))\\)");
        if (std::regex_match(fname, pieces_match, pieces_regex)) {
            filename=pieces_match[1].str();
            suffix=pieces_match[2].str();
        }
        else {
            return  false;
        }
        std::smatch match;

        std::string link_content;
        //是图片
    if(regex_builder(fname, match, regex_node::pic)){
            link_content="<img src=\""+suffix+"\"/>";
            dq.push_back(link_content);
            std::cout<<link_content<<std::endl;
        }
        //是网址
        else {
            link_content="<a href=\""+suffix+"\">" +filename+"</a>";
             dq.push_back(link_content);
            std::cout<<link_content<<std::endl;
        }
    
    return true;
}

bool read_ui(const std::string &ul_string){
    //(!|-|\*)\s.*
    //    std::regex pieces_pic("((!|-|\\*))(\\s)(.*)");
    std::string filename;
    std::string suffix;
    std::smatch pieces_match;
    if (regex_builder(ul_string, pieces_match, regex_node::ui)) {
        suffix=pieces_match[3].str();
    
    //这一步在后续步骤中，不用取消空格
    string_removespace(suffix);
        suffix=read_all(suffix);
        
    suffix="<li>"+suffix+"</li>";
    auto index=suffix.find_first_of("<li>");
    suffix= suffix.substr(index);
    dq.push_back(suffix);
    std::cout<<suffix<<std::endl;
    return  true;
}
    return  false;
}

bool read_sharp(const std::string &str){
    std::smatch match;
    if(regex_builder(str, match, regex_node::sharp)){
        std::string sharp_str=match[2].str();
        auto num=str.find_last_of("#")+1;
        string_removespace(sharp_str);
        sharp_str="<h"+std::to_string(num)+">"+sharp_str+"</h"+std::to_string(num)+">";
        dq.push_back(sharp_str);
        std::cout<<sharp_str<<std::endl;
        return true;
    }
    return  false;
}

bool read_pic_link(const std::string fname){
    //(.*)!?\[(.*)\]\(((.+))\)(.*)
    std::string filename;
    std::string suffix;
    std::string begin_;
    std::string end_;
    std::smatch pieces_match;
    if (regex_builder(fname, pieces_match, regex_node::pic_link)) {
        filename=pieces_match[1].str();
        suffix=pieces_match[2].str();
        begin_=pieces_match[1].str();
        filename=pieces_match[2].str();
        suffix=pieces_match[3].str();
        end_=pieces_match[5].str();
    }
    else {
        return  false;
    }
    std::smatch match;
    
    std::string link_content;
    //是图片
    if(regex_builder(suffix, match, regex_node::pic)){
        link_content="<img src=\""+suffix+"\"/>";
         dq.push_back(link_content);
        std::cout<<link_content<<std::endl;
        
    }
    //是网址
    else {
        link_content="<a href=\""+suffix+"\">" +filename+"</a>";
         dq.push_back(link_content);
        std::cout<<link_content;
    }
    if(*begin_.begin()=='!'){
        begin_.erase(begin_.begin());
    }
    if(begin_!=""){
        std::string all_str= read_all(begin_);
        if(!all_str.find_first_of("<p>")){
            all_str= all_str.substr(3);
        }
        if(all_str.find_last_of("</p>")==all_str.length()-1){
         
            all_str=all_str.substr(0,all_str.length()-4);
        }
        dq.push_back(all_str);
        std::cout<<all_str;
    }
    if(end_!=""){
        std::string all_str= read_all(end_);
        if(!all_str.find_first_of("<p>")){
            all_str= all_str.substr(3);
        }
       
        if(all_str.find_last_of("</p>")==all_str.length()-1){
      
            all_str=all_str.substr(0,all_str.length()-4);
        }
         dq.push_back(all_str);
        std::cout<<all_str<<std::endl;    }
    return true;
}

void scanning_head(const std::string& allstr,std::string &read){
    std::string begin_str;
    for(auto item=allstr.begin();item!=allstr.end();++item){
            auto index=*std::find(vec.begin(), vec.end(), *item);
                    if(index){
                                break;
                            }
                    else {
                        begin_str+=*item;
                    }
    }
    if(begin_str!=""){
        string_removespace(begin_str);
//        begin_str="<p>"+begin_str+"</p>";
        read+=begin_str;

   }
}
////最后归结为  下划  删除 高亮  普通字体 ```   ``  **    ** **    一起出现的情况
std::string read_all(std::string allstr){
    std::string final_string;
//    char specail[]={'*','_','~','=','`'};
   scanning_head(allstr,final_string);
    std::string::iterator sit=allstr.begin()-1;
    for(auto item=allstr.begin();item!=allstr.end();++item){

        switch (*item) {
            case '*':

                if(sit==allstr.begin()-1){
                    if(*(item+1)=='*'){
                        item+=2;
                    }
                    else {
                        item+=1;
                    }
                     sit=item;
                }
                else {
                    std::string tmp(sit,item);
                    std::string alpha_common;
                    if( item+1!=allstr.end()&&*(item+1)=='*'){
                        tmp="<strong>"+tmp+"</strong>";
                        item+=1;
                    }
                    else {
                        tmp="<i>"+tmp+"</i>";
                    }
                    final_string+=tmp;
                    if(*(item+1)){
                        auto index=*std::find(vec.begin(), vec.end(), *(item+1));
                        while(item!=allstr.end()-1){
                            if(index=='='||index=='*'||index=='`'||index=='_'||index=='~'){
                                break;
                            }
                            item+=1;
                            index=*std::find(vec.begin(), vec.end(), *(item+1));
                            alpha_common=alpha_common+* item;
                        }
                    }                    if(alpha_common!=""){

                        final_string+=alpha_common;
                    }
                     sit=allstr.begin()-1;
                }
                break;
                case '_':
                if(sit==allstr.begin()-1){
                    item+=1;
                    sit=item;
                }
                else {
                       std::string tmp(sit,item);
                        std::string alpha_common;
                        tmp="<i>"+tmp+"</i>";
                    
                    final_string+=tmp;
                    if(*(item+1)){
                        auto index=*std::find(vec.begin(), vec.end(), *(item+1));
                        while(item!=allstr.end()-1){
                            if(index=='='||index=='*'||index=='`'||index=='_'||index=='~'){
                                break;
                            }
                            item+=1;
                            index=*std::find(vec.begin(), vec.end(), *(item+1));
                            alpha_common=alpha_common+* item;
                        }
                    }                    if(alpha_common!=""){
                        
                        final_string+=alpha_common;
                    }
                       sit=allstr.begin()-1;
                }
                break;
            case '~':

                if(sit==allstr.begin()-1){
                    item+=2;
                    sit=item;
                }
                else {
                    
                    std::string tmp(sit,item);
                    std::string alpha_common;
                    tmp="<del>"+tmp+"</del>";
                    final_string+=tmp;

                    item++;
                    if(*(item+1)){
                        auto index=*std::find(vec.begin(), vec.end(), *(item+1));
                        while(item!=allstr.end()-1){
                            if(index=='='||index=='*'||index=='`'||index=='_'||index=='~'){
                                break;
                            }
                            item+=1;
                            index=*std::find(vec.begin(), vec.end(), *(item+1));
                            alpha_common=alpha_common+* item;
                        }
                    }
                    if(alpha_common!=""){

                        final_string+=alpha_common;

                    }
                    sit=allstr.begin()-1;
                }
                break;
            case '=':

                if(sit==allstr.begin()-1){
                    item+=2;
                    sit=item;
                }
                else {
                    std::string tmp(sit,item);
                    std::string alpha_common;
                     tmp="<mark>"+tmp+"</mark>";
                    final_string+=tmp;

                    item++;
                    if(*(item+1)){
                        auto index=*std::find(vec.begin(), vec.end(), *(item+1));
                        while(item!=allstr.end()-1){
                             if(index=='='||index=='*'||index=='`'||index=='_'||index=='~'){
                                break;
                            }
                            item+=1;
                            index=*std::find(vec.begin(), vec.end(), *(item+1));
                            alpha_common=alpha_common+* item;
                        }
                    }
                    if(alpha_common!=""){

                        final_string+=alpha_common;

                    }
                    sit=allstr.begin()-1;
                }
                break;
            case '`':

                if(sit==allstr.begin()-1){
                    if(*(item+2)=='`'){
                        item+=3;
                    }
                    else {
                        item+=1;
                    }
                    sit=item;
                }
                else {
                    std::string tmp(sit,item);
                    std::string alpha_common;
                    if( item+1!=allstr.end()&&*(item+2)=='`'){
                        item+=2;
                    }
                    tmp="<code>"+tmp+"</code>";
                    final_string+=tmp;

                    if(*(item+1)){
                        auto index=*std::find(vec.begin(), vec.end(), *(item+1));
                        while(item!=allstr.end()-1){
                            if(index=='='||index=='*'||index=='`'||index=='_'||index=='~'){
                                break;
                            }
                            item+=1;
                            index=*std::find(vec.begin(), vec.end(), *(item+1));
                            alpha_common=alpha_common+* item;
                        }
                    }
                    if(alpha_common!=""){

                        final_string+=alpha_common;

                    }
                    sit=allstr.begin()-1;
                }
                break;
        }
        
        
    }
    final_string="<p>"+final_string+"</p>";

    return  final_string;
}
bool read_num(const std::string &str){
    std::smatch pieces_match;
    if (regex_builder(str, pieces_match,regex_node::num)) {
        std::string suffix= pieces_match[2].str();
        suffix=read_all(suffix);
        if(num_string.empty()){
            num_string+="<li>"+suffix+"</li>";
            num_string="<ol>"+num_string;
        }else {
        num_string+="<li>" +suffix+"</li>"+"\n";
        }
            return  true;
    }
    else {
        if(!num_string.empty()){
            num_string+="</ol>";
            dq.push_back(num_string);
            num_string.clear();
        }
         return  false;
    }
}



