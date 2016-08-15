//
//  symbol_md.cpp
//  md_cpp
//
//  Created by 傅莘莘 on 16/8/11.
//  Copyright © 2016年 傅莘莘. All rights reserved.
//

#include "symbol_md.hpp"
void string_removespace(std::string &str){
  str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

std::vector<char >vec{'#','*','-','+','.','>','`','=','~','_'};
int blode_num=0;
std::string code_string;
std::string::iterator it;
std::string::iterator one_star=code_string.begin();
std::string::iterator tmp_it;
std::string ves;
int flag=0;
bool read_code(const  std::string& line){
    if(line=="```"){
        flag++;
        if(flag>1){
            flag=0;
        }
        return  true;
    }
    if(flag==1){
        if(line!="```"){
            ves+=line+"\n";
        }
          return true;
    }
    else {
        if(!ves.empty()){
            ves="<pre>\n"+ves+"</pre>\n";
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
    if(read_ref(str)){
        return;
    }
    if(read_code(str)){
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
        std::cout<<all_str<<std::endl;
    }

}
void common_sentence(std::string::iterator it){
    tmp_it=it;
    while(*it++){
        auto index=*std::find(vec.begin(), vec.end(), *it);
        if(index){
            break;
        }
    }
    std::string content_=std::string(tmp_it,it);
    std::cout<<"common "<<content_<<std::endl;
    it--;
//    std::cout<<"itititi"<<*(it+1)<<std::endl;
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
        std::regex pieces_pic("(https|http):[0-9a-zA-Z_/.]*.(jpg|jpeg|png)");
        std::string link_content;
        //是图片
        if(std::regex_match(suffix,match,pieces_pic)){
            link_content="<img src=\""+suffix+"\"/>";
            std::cout<<link_content<<std::endl;
        }
        //是网址
        else {
            link_content="<a href=\""+suffix+"\">" +filename+"</a>";
            std::cout<<link_content<<std::endl;
        }
    
    return true;
}

bool read_ui(const std::string &ul_string){
    //(!|-|\*)\s.*
    //    std::regex pieces_pic("((!|-|\\*))(\\s)(.*)");
    std::string filename;
    std::string suffix;
    std::regex pieces_regex("((!|-|\\*|\\+))(\\s.*)");
    std::smatch pieces_match;
    if (std::regex_match(ul_string, pieces_match, pieces_regex)) {
        suffix=pieces_match[3].str();
//        std::cout<<pieces_match[0].str()<<std::endl;
    
    //这一步在后续步骤中，不用取消空格
    string_removespace(suffix);
        suffix=read_all(suffix);
        //<li><p>heloop</p></li>
        
    suffix="<li>"+suffix+"</li>";
    auto index=suffix.find_first_of("<li>");
    suffix= suffix.substr(index);
    std::cout<<suffix<<std::endl;
    return  true;
}
    return  false;
}

bool read_sharp(const std::string &str){
    std::smatch match;
    std::regex pieces_pic("(#)+(.*)");
    // ####
    if(std::regex_match(str,match,pieces_pic)){
        std::string sharp_str=match[2].str();
        auto num=str.find_last_of("#")+1;
        string_removespace(sharp_str);
        sharp_str="<h"+std::to_string(num)+">"+sharp_str+"</h>";
        std::cout<<sharp_str<<std::endl;
        return true;
    }
    return  false;
}

bool read_ref(std::string &str){
    //>.*
    std::smatch match;
    std::regex pieces_pic(">.*");
    if(std::regex_match(str,match,pieces_pic)){
        
        std::string sharp_str=match.str();
        sharp_str.erase(sharp_str.begin());
        sharp_str="<blockquote><p>"+sharp_str+"</p></blockquote>";
        string_removespace(sharp_str);
        std::cout<<sharp_str<<std::endl;
        return  true;
    }
    return false;
}

bool read_pic_link(const std::string fname){
    //(.*)!?\[(.*)\]\(((.+))\)(.*)
    std::string filename;
    std::string suffix;
    std::string begin_;
    std::string end_;
    std::regex pieces_regex("(.*)!?\\[(.*)\\]\\(((.+))\\)(.*)");
    std::smatch pieces_match;
    if (std::regex_match(fname, pieces_match, pieces_regex)) {
        filename=pieces_match[1].str();
        suffix=pieces_match[2].str();
        //        std::cout<<pieces_match[1].str()<<std::endl;//前缀 可能以！开头
        begin_=pieces_match[1].str();
        //        std::cout<<pieces_match[2].str()<<std::endl;//名称
        filename=pieces_match[2].str();
        //        std::cout<<pieces_match[3].str()<<std::endl;//文件suffix
        suffix=pieces_match[3].str();
        //        std::cout<<pieces_match[5].str()<<std::endl;    //后缀
        end_=pieces_match[5].str();
    }
    else {
        return  false;
    }
    std::smatch match;
    std::regex pieces_pic("(https|http):[0-9a-zA-Z_/.]*.(jpg|jpeg|png)");
    std::string link_content;
    //是图片
    if(std::regex_match(suffix,match,pieces_pic)){
        link_content="<img src=\""+suffix+"\"/>";
        std::cout<<link_content<<std::endl;
        
    }
    //是网址
    else {
        link_content="<a href=\""+suffix+"\">" +filename+"</a>";
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
        //    else if(final_string.find_last_of("</p>")==final_string.length()-1){
        //        final_string+="</p>";
        //    }
        if(all_str.find_last_of("</p>")==all_str.length()-1){
            //            test=test.substr(0,test.length()-4)
            //            std::cout<<"hello--------"<<std::endl;
            all_str=all_str.substr(0,all_str.length()-4);
        }
        std::cout<<all_str;
    }
    if(end_!=""){
        std::string all_str= read_all(end_);
        if(!all_str.find_first_of("<p>")){
            all_str= all_str.substr(3);
        }
        //    else if(final_string.find_last_of("</p>")==final_string.length()-1){
        //        final_string+="</p>";
        //    }
//        auto i=all_str.find_last_of("</p>");
//        auto j=all_str.length()-1;
//        std::cout<<"i  "<<i<<"j   "<<j;
        if(all_str.find_last_of("</p>")==all_str.length()-1){
            //            test=test.substr(0,test.length()-4)
//            std::cout<<"hello--------"<<std::endl;
            all_str=all_str.substr(0,all_str.length()-4);
        }
        
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
//    std::cout<<begin_str<<std::endl;
   }
}
////最后归结为  下划  删除 高亮  普通字体 ```   ``  **    ** **    一起出现的情况
std::string read_all(std::string allstr){
    std::string final_string;
//    char specail[]={'*','_','~','=','`'};
    scanning_head(allstr,final_string);
    std::string::iterator sit=allstr.begin()-1;
    for(auto item=allstr.begin();item!=allstr.end();++item){
//        std::cout<<(*item)<<std::endl;
        switch (*item) {
            case '*':
//                std::cout<<"*"<<std::endl;
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
//                     std::cout<<tmp<<std::endl;
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
//                        alpha_common="<p>"+alpha_common+"</p>";
//                        std::cout<<alpha_common<<std::endl;
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
                    //                     std::cout<<tmp<<std::endl;
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
                        //                        alpha_common="<p>"+alpha_common+"</p>";
                        //                        std::cout<<alpha_common<<std::endl;
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
//                    std::cout<<tmp<<std::endl;
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
//                        alpha_common="<p>"+alpha_common+"</p>";
                        final_string+=alpha_common;
//                        std::cout<<alpha_common<<std::endl;
                    }
                    sit=allstr.begin()-1;
                }
                break;
            case '=':
//                std::cout<<"="<<std::endl;
                if(sit==allstr.begin()-1){
                    item+=2;
                    sit=item;
                }
                else {
                    std::string tmp(sit,item);
                    std::string alpha_common;
                     tmp="<mark>"+tmp+"</mark>";
                    final_string+=tmp;
//                    std::cout<<tmp<<std::endl;
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
//                        alpha_common="<p>"+alpha_common+"</p>";
                        final_string+=alpha_common;
//                        std::cout<<alpha_common<<std::endl;
                    }
                    sit=allstr.begin()-1;
                }
                break;
            case '`':
//                std::cout<<"`"<<std::endl;
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
//                    std::cout<<tmp<<std::endl;
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
//                        alpha_common="<p>"+alpha_common+"</p>";
                        final_string+=alpha_common;
//                        std::cout<<alpha_common<<std::endl;
                    }
                    sit=allstr.begin()-1;
                }
                break;
        }
        
        
    }
//    std::cout<<final_string<<std::endl;
    
//    if(final_string.find_first_of("<p>")){
//        final_string="<p>"+final_string;
//    }
//    else if(final_string.find_last_of("</p>")==final_string.length()-1){
//        final_string+="</p>";
//    }
    final_string="<p>"+final_string+"</p>";
//    std::cout<<final_string<<std::endl;
    return  final_string;
}
bool read_num(const std::string &str){
    //(\\d\.\\s)((.*)*)
    std::regex pieces_regex("(\\d\\.\\s)((.*)*)");
    std::smatch pieces_match;
    if (std::regex_match(str, pieces_match, pieces_regex)) {
        std::string suffix= pieces_match[2].str();
        suffix=read_all(suffix);
        suffix="1. "+suffix;
        //        auto index=suffix.find_first_of("<li>");
        //        suffix= suffix.substr(index);
        std::cout<<std:: endl;
        std::cout<<suffix<<"\n"<<std::endl;
        return  true;
    }
    return  false;
}



