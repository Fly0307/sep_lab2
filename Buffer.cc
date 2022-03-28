#include <fstream>
#include <iostream>
#include "Buffer.h"

//TO DO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    this->currentLineNum=0;
    this->currentLineNum=0;
    head= new ListNode();
}

Buffer::~Buffer() {
    ListNode *tmp;
    while (head){
        tmp=head;
        head=head->next;
        delete tmp;
    }
}
/*
 * 将所有行写入文件并打印写入文件的字节数。
 * 如果未指定文件名，则打印错误。 当前地址不变。*/
void Buffer::writeToFile(const string &filename) const {
    std::fstream file(filename,std::ios::app);
    ListNode *tmp=head;
    unsigned long length=0;
    if(!file.is_open()){
        std::cout<<"can not open this file"<<std::endl;
        return;
    }
    tmp=tmp->next;
    while (tmp){
        file<<tmp->value<<'\n';
        length+=tmp->value.length()+1;/*结尾换行符*/
        tmp=tmp->next;
    }
    file.seekg (0, std::ios::end);
    file.close();
    std::cout<<length<<" byte(s) written"<<std::endl;
}

void Buffer::showLines(int from, int to) {
    if(from>to){
        throw "Number range error";
    }

    if(from<0||to>maxLineNum) {
        throw "Line number out of range";
        /*std::cout<<"? Bad/Unknown command"<<std::endl;
        return;*/
    }
    ListNode* tmp=head;
    for(int i=0;i<from;++i){
        tmp=tmp->next;
    }

    for(from; from <= to; from++){
        std::cout<<from<<"\t"<<tmp->value<<std::endl;
        tmp=tmp->next;
    }
    currentLineNum=to;

}

void Buffer::deleteLines(int from, int to){
    if(from>to){
        throw "Delete range error";
    }
    if(from<0||to>maxLineNum) {
        throw "Line number out of range";
    }
    ListNode *tmp=head;
    for(int i=0;i<from-1;++i){
        tmp=tmp->next;
    }
    ListNode *tmp_1,*tmp_2=tmp;
    tmp=tmp->next;
    for(int i=from;i<=to;++i){
        tmp_1=tmp->next;
        delete tmp;
        tmp=tmp_1;
    }
    tmp_2->next=tmp_1;
    if(from==1){
        this->currentLineNum=1;/*由0改为1*/
        //printf("currentLine: %d\n",this->currentLineNum);
    }else {
        this->currentLineNum = from;          /*删除最后一行后的新地址*/
        //printf("currentLine:%d\n",this->currentLineNum);
    }
    this->maxLineNum-=(to-from+1);/*重置最大行*/
    //printf("max:%d\n",this->maxLineNum);
}
/*插入1行,将指定文本插入到当前行之前。*/
void Buffer::insertLine(const string &text){
    ListNode *tmp=head;
    if(currentLineNum==0)
        currentLineNum=1;
    for(int i=0;i<currentLineNum-1;++i){
        tmp=tmp->next;
    }
    tmp->next=new ListNode(text,tmp->next);
    maxLineNum++;
    //printf("maxLineNuw:%d",this->maxLineNum);

}
/*追加1行,将指定文本插入到当前行之后*/
void Buffer::appendLine(const string &text){
    ListNode *tmp=head;
    for(int i=0;i<currentLineNum;++i){
        tmp=tmp->next;
    }
    tmp->next=new ListNode(text,tmp->next);
    maxLineNum++;
    currentLineNum++;
}

const string &Buffer::moveToLine(int idx){/*返回string*/
    if(idx>maxLineNum)
        throw "Line number out of range";
    ListNode *tmp=head;
    for(int i=0;i<idx;++i){
        tmp=tmp->next;
    }
    currentLineNum=idx;
    return tmp->value;
}
