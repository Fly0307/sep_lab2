#pragma once

#include <string>
#include <utility>
#include <iostream>

using std::string;

struct ListNode {
    string value;
    ListNode *next;
    ListNode():value(""),next(nullptr){};
    ListNode(const string v, ListNode *n):value(std::move(v)), next(n){}
};
/*向head_p后面添加以新的node节点，值为val*/
/*void list_add(ListNode **head_p, string val) {
    auto *t = new ListNode(std::move(val), *head_p);
    *head_p = t;
}*/
/*node顺序打印到结尾*/
/*void print_list(ListNode* node){
    while (node){
        std::cout<<node->value<<std::endl;
        node=node->next;
    }
}*/


class Buffer {
private:
    int currentLineNum{};
    // TO DO: add a List here for storing the input lines
    ListNode* head;

public:
    int maxLineNum{};
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx);

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
