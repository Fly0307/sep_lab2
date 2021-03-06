#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TO DO: Implement destructor
    delete buffer;
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout <<buffer->currentLineNum<<":";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TO DO: finish cmdAppend.
    string value;
    while (true){
        getline(cin, value);
        if(value==".")
            break;
        buffer->appendLine(value);/*读一次写一次*/

    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if (firstLine) {
            /*std::cout<<buffer->currentLineNum<<std::endl;*/
            buffer->insertLine(text);
            firstLine = false;
        }  else {
           /* std::cout<<buffer->currentLineNum<<std::endl;*/
            buffer->appendLine(text);
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    cout << buffer->moveToLine(line) << endl;
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        /*文件名判定？*/
        // TO DO: call cmdWrite with proper arguments
        cmdWrite(cmd.substr(2));
        return;
    }
    // TO DO: handle special case "1,$n".
    if (cmd=="1,$n")
    {
        if(!buffer->maxLineNum){
            throw "Number range error";
            /*std::cout<<"Text is empty"<<std::endl;
            return;*/
        }
            /*throw "Text is empty";*/
            //buffer->print_list();//打印测试
        cmdNumber(1,buffer->maxLineNum);
        return;
    }

    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {
       /* if(start>end){
            throw "Number range error";
        }*/
        if (type == 'n') {
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            cmdDelete(start, end);
            return;
        }
    }
    throw "Bad/Unknown command";
}
