//
// Created by Efecan Kasapoglu on 28.03.2024.
//
#include <string>
#include "UndoStack.h"

using namespace std;

UndoStack::UndoStack() { //default constructoır
    top = nullptr;
}

void UndoStack::push(char operation, string employee_name, string project_name, int project_priority) { //pushes the new node
    StackNode* newStack; //creates the new node
    newStack= new StackNode;
    newStack->operation=operation; //sets the operation
    newStack->employee_name=employee_name; // sets the employee name
    newStack->project_name=project_name;// sets the project name
    newStack->project_priority=project_priority;//sets the project priority
    if(isEmpty()){// checks if the stack is empty
        top=newStack; // sets the top pointer to the new node
        newStack->next = NULL;// sets the next pointer of the new node to null
    }
    else{// if the stack is not empty
        newStack->next=top;// sets the next pointer of the new node to the current top
        top=newStack;// updates the top pointer to the new node
    }
}

void UndoStack::pop(char &operation, string &employee_name, string &project_name, int &project_priority) {// deletes the node
    if(isEmpty()){
        cout<<"Stack is empty."<<endl;
    }
    else{
        StackNode* temp = top; //creates the new node
        project_name = temp->project_name; //sets the project name
        operation = temp->operation;// sets the operation
        project_priority = temp->project_priority; // sets the priority
        employee_name = temp->employee_name; // sets the employee name
        top = temp->next; //updates the top pointer
        delete temp; // deletes the node
    }
}

bool UndoStack::isEmpty() { // checks if the stack is empty or not
    if(top== nullptr){ // this condition shows that the list is empty
        return true;
    }
    else{
        return false;
    }
}

void UndoStack::clear() { // deletes all node
    StackNode* temp;
    while(top!= nullptr){ // deletes all of the nodes until the list is empty
        temp=top;
        top=top->next;
        delete temp;
    }
}
