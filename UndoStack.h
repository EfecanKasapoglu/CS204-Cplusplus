//
// Created by Efecan Kasapoglu on 28.03.2024.
//

#ifndef HW3_UNDOSTACK_H
#define HW3_UNDOSTACK_H
#include <iostream>
#include <string>

using namespace std;

struct StackNode // stack structure
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;
};

class UndoStack{
public:
    UndoStack(); // default constructor
    void push(char operation, string employee_name, string project_name ,int project_priority);//adds the new node
    void pop(char &operation, string &employee_name, string &project_name ,int &project_priority);// deletes the node
    bool isEmpty(); // checks if it is empty or not
    void clear();// deletes the nodes
private:
    StackNode* top;
};
#endif //HW3_UNDOSTACK_H
