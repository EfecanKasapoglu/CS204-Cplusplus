//
// Created by Efecan Kasapoglu on 28.03.2024.
//

#ifndef HW3_EMPLOYEEPROJECT2DLL_H
#define HW3_EMPLOYEEPROJECT2DLL_H


#include <iostream>
#include <string>

using namespace std;

struct ProjectNode // project structure
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;
};
struct EmployeeNode //  employee structure
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;
};
class EmployeeProject2DLL{
private:
    EmployeeNode* head;
public:
    EmployeeProject2DLL(); // default constructor
    bool isEmployeeAssignedToProject(string employee_name,string project_name); // checking the employee if it is assigned to the project
    bool updateProjectPriority(string employee_name,string project_name, int &project_priority); // updating the project
    bool assignEmployeeToProject(string employee_name, string project_name, int project_priority); // assigning employee to the project
    bool withdrawEmployeeFromProject(string employee_name, string project_name, int &project_priority); // withdrawing the project
    void printTheEntireList(); // prints the list
    void printEmployeeProjects(string employee_name, int order);//prints the employees project
    void undo(char operation, string employee_name, string project_name, int project_priority);// undo the operation
    void clear(); // clears the nodes
};
#endif //HW3_EMPLOYEEPROJECT2DLL_H
