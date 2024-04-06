//
// Created by Efecan Kasapoglu on 28.03.2024.
//
#include <iostream>
#include <string>
#include "EmployeeProject2DLL.h"

using namespace std;

EmployeeProject2DLL::EmployeeProject2DLL() { //This is constructs and creates an empty object with no employee
    head = nullptr;
}
bool EmployeeProject2DLL :: isEmployeeAssignedToProject(string employee_name,string project_name){ //this function checks if the employee is assigned or not
    EmployeeNode* currentnode=head; // points the head
    while(currentnode!=nullptr){ //this loop goes until there is no employee
        if(currentnode->employee_name==employee_name){ // checks the employee name is matching
            ProjectNode* currentprojectnode= currentnode->head; //this part starts to look at projects
            while(currentprojectnode!=nullptr){//checks all the project
                if(currentprojectnode->project_name==project_name){ //checks if the project name is matching or not
                    return true; // if it matches turns true
                }
                else{
                    currentprojectnode=currentprojectnode->next; //otherwise looks at the next node
                }
            }
            return false;
        }
        else{
            currentnode=currentnode->down; // looks to the next employee
        }
    }
    return false;
}
bool EmployeeProject2DLL::updateProjectPriority(string employee_name, string project_name, int &project_priority) {//this function updates the priority
    EmployeeNode* CurrentEmployeeNode=head; // points the head of the employee
    while (CurrentEmployeeNode!=nullptr){//while loop looks for the wanted employee
        if (CurrentEmployeeNode->employee_name==employee_name){//checks if the employee matches with the node employees
            ProjectNode* CurrentProjectNode=CurrentEmployeeNode->head;//This points the employees projects
            while (CurrentProjectNode!=nullptr){//while loop looks for the wanted project
                if (CurrentProjectNode->project_name==project_name){//checks if the project matches with the wanted project
                    if (CurrentProjectNode->project_priority==project_priority){//if the project and the priority is the same
                        cout<<"The project priority is already the same as the new priority."<<endl;
                        return false;// returns false
                    }
                    else{
                        ProjectNode* tempNode=CurrentEmployeeNode->head;//creates temporary project node
                        while (tempNode!=nullptr){// checks if while it is null
                            if (tempNode!=CurrentProjectNode && tempNode->project_priority==project_priority){// this condition shows there is other project with the same priority
                                cout<<"The project priority has not been updated because there is another project with the same priority."<<endl;
                                return false;// returns false
                            }
                            tempNode=tempNode->next; // checks the next node
                        }
                        int oldPriority = CurrentProjectNode->project_priority; //this part updates the priority
                        CurrentProjectNode->project_priority = project_priority;
                        project_priority = oldPriority;
                        //this part adjust the projects priority position to the new priority
                        if (CurrentProjectNode->prev){
                            CurrentProjectNode->prev->next = CurrentProjectNode->next;
                        }
                        if (CurrentProjectNode->next) {
                            CurrentProjectNode->next->prev = CurrentProjectNode->prev;
                        }
                        if (CurrentProjectNode == CurrentEmployeeNode->head){
                            CurrentEmployeeNode->head = CurrentProjectNode->next;
                        }

                        ProjectNode* beforeNode = nullptr; // this represents the currents nodes previous node
                        ProjectNode* searchNode = CurrentEmployeeNode->head; // this is for searching the location for the new node
                        while (searchNode != nullptr && CurrentProjectNode->project_priority > searchNode->project_priority) { // this loop helps to find the correct location
                            beforeNode = searchNode;
                            searchNode = searchNode->next;
                        }
                        if (beforeNode == nullptr) { // this condition if it is the beginning node
                            CurrentProjectNode->next = CurrentEmployeeNode->head;
                            if (CurrentEmployeeNode->head != nullptr) CurrentEmployeeNode->head->prev = CurrentProjectNode;
                            CurrentEmployeeNode->head = CurrentProjectNode;
                            CurrentProjectNode->prev = nullptr;
                        }
                        else { //this is for not in the beginning
                            CurrentProjectNode->next = beforeNode->next;
                            if (beforeNode->next != nullptr) beforeNode->next->prev = CurrentProjectNode;
                            beforeNode->next = CurrentProjectNode;
                            CurrentProjectNode->prev = beforeNode;
                        }
                        return true; // returns true
                    }
                }
                CurrentProjectNode = CurrentProjectNode->next; // if it is not find look at the next node
            }
        }
        CurrentEmployeeNode = CurrentEmployeeNode->down; // if employee is  not found it looks at the other employee
    }
    return false; // returns false
}


bool EmployeeProject2DLL::assignEmployeeToProject(string employee_name, string project_name, int project_priority) { // this function assigns employee to a project
    EmployeeNode* CurrentEmployeeNode=head; //points the beginning of the employee node
    EmployeeNode* PreviousEmployeeNode=nullptr;

    while (CurrentEmployeeNode!=nullptr && CurrentEmployeeNode->employee_name < employee_name) {// this loop is for finding the correct position
        PreviousEmployeeNode=CurrentEmployeeNode;
        CurrentEmployeeNode=CurrentEmployeeNode->down;
    }
    if (CurrentEmployeeNode==nullptr||CurrentEmployeeNode->employee_name!=employee_name) {//if employee is not in the list, this part inserts the employee
        EmployeeNode* NewEmployeeNode=new EmployeeNode;
        NewEmployeeNode->employee_name=employee_name;
        NewEmployeeNode->head=nullptr;
        NewEmployeeNode->down=nullptr;

        if (PreviousEmployeeNode==nullptr) {
            NewEmployeeNode->down=head;
            head=NewEmployeeNode;
        } else {
            PreviousEmployeeNode->down=NewEmployeeNode;
            NewEmployeeNode->down=CurrentEmployeeNode;
        }
        CurrentEmployeeNode=NewEmployeeNode;
    }
    ProjectNode* CurrentProjectNode=CurrentEmployeeNode->head;// this is for the project node
    while (CurrentProjectNode!=nullptr) {//checks if the project exists
        if (CurrentProjectNode->project_name==project_name) {//if it is it gives error
            cout<<"The project has not been added because it is already assigned to the employee."<<endl;
            return false;
        }
        if (CurrentProjectNode->project_priority==project_priority) {//if there is another project with the same priority it gives error
            cout<<"The project has not been added because there is another project with the same priority."<<endl;
            return false;
        }
        CurrentProjectNode=CurrentProjectNode->next;//goes to the next node
    }
    ProjectNode* NewProjectNode=new ProjectNode;// this part inserts the new project
    NewProjectNode->project_name=project_name; // inserts the project name
    NewProjectNode->project_priority=project_priority;//inserts the project priority
    NewProjectNode->next=nullptr;
    if (CurrentEmployeeNode->head==nullptr || CurrentEmployeeNode->head->project_priority>project_priority){
        NewProjectNode->next=CurrentEmployeeNode->head;
        if (CurrentEmployeeNode->head!=nullptr) {
            CurrentEmployeeNode->head->prev=NewProjectNode;
        }
        CurrentEmployeeNode->head=NewProjectNode;
    }
    else {
        ProjectNode* PreviousProjectNode=CurrentEmployeeNode->head;
        while (PreviousProjectNode->next!=nullptr && PreviousProjectNode->next->project_priority<project_priority){// this part checks the correct location of the priority
            PreviousProjectNode=PreviousProjectNode->next;
        }
        NewProjectNode->next=PreviousProjectNode->next;
        if (PreviousProjectNode->next!=nullptr) {
            PreviousProjectNode->next->prev=NewProjectNode;
        }
        PreviousProjectNode->next=NewProjectNode;
        NewProjectNode->prev=PreviousProjectNode;
    }
    return true; //returns true
}

bool EmployeeProject2DLL::withdrawEmployeeFromProject(string employee_name, string project_name, int &project_priority) { // this function is for withdrawing the project
    EmployeeNode* CurrentEmployeeNode=head;//points the head of the employee node
    while (CurrentEmployeeNode!=nullptr){// checks the employees
        if (CurrentEmployeeNode->employee_name==employee_name){// this condition if it matches or not
            ProjectNode* CurrentProjectNode=CurrentEmployeeNode->head;// creates the project pointer
            ProjectNode* PreviousProjectNode=nullptr;
            while (CurrentProjectNode!=nullptr) { // checks the projects which is assigned to the employee
                if (CurrentProjectNode->project_name==project_name) { //this condition checks if the project names match
                    project_priority=CurrentProjectNode->project_priority;
                    if (PreviousProjectNode==nullptr) { // if it is in the beginning
                        CurrentEmployeeNode->head=CurrentProjectNode->next;
                    }
                    else {
                        PreviousProjectNode->next=CurrentProjectNode->next;
                    }
                    delete CurrentProjectNode; // deletes the node
                    if (CurrentEmployeeNode->head==nullptr) { //this condition checks if the employee has no more projects assigned
                        if (CurrentEmployeeNode==head) {
                            head=CurrentEmployeeNode->down;
                        }
                        else {// this part finds the previous employee node and removes the current employee node from the list
                            EmployeeNode* TemporaryEmployeeNode=head;
                            while (TemporaryEmployeeNode!=nullptr && TemporaryEmployeeNode->down!=CurrentEmployeeNode) {
                                TemporaryEmployeeNode=TemporaryEmployeeNode->down;
                            }
                            if (TemporaryEmployeeNode!=nullptr) {
                                TemporaryEmployeeNode->down=CurrentEmployeeNode->down;
                            }
                        }
                        delete CurrentEmployeeNode; // deletes the node
                    }
                    return true; // returns true
                }
                PreviousProjectNode=CurrentProjectNode;
                CurrentProjectNode=CurrentProjectNode->next;// moves to the next project
            }
        }
        CurrentEmployeeNode=CurrentEmployeeNode->down; // moves to the next employee
    }
    return false; // returns false
}
void EmployeeProject2DLL::printTheEntireList(){ // this function prints the employees and the projects
    EmployeeNode* CurrentEmployeeNode=head; // this points the beginning of the employees
    if(CurrentEmployeeNode== nullptr){ // checks if the list is empty or not
        cout<<"The list is empty."<<endl;
    }
    else{
        while(CurrentEmployeeNode!= nullptr){//checks all the employees
            cout<<CurrentEmployeeNode->employee_name<<": "; // prints the employee name
            ProjectNode* CurrentProjectNode= CurrentEmployeeNode->head;
            while(CurrentProjectNode!=nullptr){ // this checks the employees projects
                cout<<"("<<CurrentProjectNode->project_name<<", "<<CurrentProjectNode->project_priority<<") ";// prints the project name and priority
                CurrentProjectNode=CurrentProjectNode->next;// goes to the next project
            }
            cout<<endl;
            CurrentEmployeeNode=CurrentEmployeeNode->down; // goes to the next employee
        }
    }
}
void EmployeeProject2DLL::printEmployeeProjects(string employee_name, int order){//this function prints the projects of the employee
    EmployeeNode* CurrentEmployeeNode=head;// point the beginning of the employee node
    if(CurrentEmployeeNode==nullptr){ // checks if the list is empty or not
        cout<<"There are no employees in the list."<<endl;
        return;
    }
    else{
        while(CurrentEmployeeNode!= nullptr&&CurrentEmployeeNode->employee_name!=employee_name){// this loop tries to find the employee if it exist
            CurrentEmployeeNode=CurrentEmployeeNode->down;
        }
        if(CurrentEmployeeNode== nullptr){ // if employee not in the list
            cout<<"The employee is not in the list."<<endl;
            return;
        }
        else{
            if(CurrentEmployeeNode->employee_name==employee_name){ // this condition if the employee matches
                ProjectNode* CurrentProjectNode= CurrentEmployeeNode->head;
                if(order==1){ // this is for ascending order
                    while(CurrentProjectNode!= nullptr){
                        cout<<"("<<CurrentProjectNode->project_name<<", "<<CurrentProjectNode->project_priority<<") ";
                        CurrentProjectNode=CurrentProjectNode->next;
                    }
                    cout<<endl;
                }
                else if (order==0) { // this is for descending order
                    CurrentProjectNode=CurrentEmployeeNode->head;
                    while (CurrentProjectNode->next!= nullptr) {
                        CurrentProjectNode = CurrentProjectNode->next;
                    }
                    while (CurrentProjectNode!=nullptr) {
                        cout<<"("<< CurrentProjectNode->project_name<<", "<<CurrentProjectNode->project_priority << ") ";
                        CurrentProjectNode=CurrentProjectNode->prev;
                    }
                    cout<<endl;
                }
                else{
                    cout<<"Invalid input."<<endl;
                }
            }
        }
    }
}
void EmployeeProject2DLL::undo(char operation, string employee_name, string project_name, int project_priority){

    if(operation=='a'){
            withdrawEmployeeFromProject(employee_name, project_name, project_priority);
            cout<<"Undoing the assignment of a project."<<endl;
        }
    else if(operation=='u'){
            updateProjectPriority(employee_name, project_name, project_priority);
            cout<<"Undoing the update of a project priority."<<endl;
    }
    else if(operation=='w'){
            assignEmployeeToProject(employee_name, project_name, project_priority);
            cout<<"Undoing the withdrawal of a project."<<endl;
        }

}
void EmployeeProject2DLL::clear(){ // this fonction deletes the employees and the projects
    EmployeeNode* CurrentEmployeeNode=head;
    while(CurrentEmployeeNode!=nullptr){ // this loop is for the employees
        ProjectNode* CurrentProjectNode=CurrentEmployeeNode->head;
        while(CurrentProjectNode!=nullptr){ // this loop is for the projects
            ProjectNode* NextProjectNode=CurrentProjectNode->next;
            delete CurrentProjectNode;// deletes the project
            CurrentProjectNode=NextProjectNode;
        }
        EmployeeNode* NextEmployeeNode=CurrentEmployeeNode->down;
        delete CurrentEmployeeNode; // deletes the employee
        CurrentEmployeeNode=NextEmployeeNode;
    }
}
