//this homework is done by Efecan Kasapoglu, 31038
// Created in 10.03.2023
// last edit time 17.03.2023

#include <string>
#include <fstream> // for opening file
#include <iostream>

using namespace std;

struct NodeLike // structure was given in the hw file
{
    string subject;
    string object;
    NodeLike *next;
};
struct NodeTaken// structure was given in the hw file
{
    string name;
    NodeTaken *next;
};
void printingLikes(NodeLike* headLikes) { // this function prints the nodes in likes
    NodeLike* temporary=headLikes; //creates a temporary pointer
    cout<<"Likes list: ";
    while(temporary!=nullptr){ // if temporary pointer is not empty it prints
        cout<<"("<<temporary->subject<<", "<<temporary->object <<") ";
        temporary=temporary->next; // it takes the temporary pointer to the next node
    }
}
void printingTaken(NodeTaken* headTaken) {// this function prints the nodes in taken
    NodeTaken* temporary=headTaken;//creates a temporary pointer
    cout<<"Taken list: ";
    while(temporary!= nullptr){// if temporary pointer is not empty it prints
        cout<<temporary->name<<" ";
        temporary=temporary->next;// it takes the temporary pointer to the next node
    }
}
// |_|_| -> |_|_|  |_|_|  |_|_|
void insertingLikeInOrder(NodeLike*& head, string& object, string& subject){ // this function adds nodes in the like nodes
    NodeLike* temporary=new NodeLike; // creates a temporary pointer
    temporary->object=object;
    temporary->subject=subject;
    temporary->next=nullptr;
    if(head==nullptr){ // if the list is empty
        head=temporary;
    }
    else{
        NodeLike* current=head;
        NodeLike* previous=nullptr;

        while(current!=nullptr && current->subject!=subject){ // this goes to the node if there is a same subject node or the end
            previous=current;
            current=current->next;
        }
        if(current!=nullptr && current->subject==subject){ //this condition look if there is an node with the same subject
            if(current->next==nullptr || current->next->subject!=subject){ // if there is a only one node with the same subject
                temporary->next=current->next;
                current->next=temporary;
            }
            else{
                while(current->next!=nullptr && current->next->subject==subject){ // this checks if there is a 2 or more nodes with the same subject
                    current=current->next;
                }
                temporary->next=current->next;
                current->next=temporary;
            }
        }
        else{
            previous->next=temporary;
        }
    }
}
void insertingTaken(NodeTaken* & head,string & name){// this function adds nodes in the taken nodes
    NodeTaken* temporary= new NodeTaken;
    temporary->name=name;
    temporary->next=nullptr;
    if (head==nullptr || name<head->name) { //this checks 2 condition. First it is empty, second the alphabetic order
        temporary->next=head;
        head = temporary;
    } else {
        NodeTaken* current=head;
        while (current->next!=nullptr && name>current->next->name) { // this takes the current pointer to the next step, not the end. it checks the alphabetic order
            current=current->next;
        }
        temporary->next=current->next;
        current->next=temporary;
    }
}

void DeleteAllLike(NodeLike*& Head){// this function deletes all the Likes nodes in the list
    NodeLike* current=Head;
    if (Head!=nullptr){//this continues until the list is empty
        Head=Head->next; // it moves to the next node
        delete current;
    }
    else{
    }
}
void DeleteAllTaken(NodeTaken*& Head){ // this function deletes all the taken nodes in the list
    while(Head!=nullptr){//this loop continues until the list is empty
        NodeTaken* current=Head;
        Head=Head->next;// it moves to the next node
        delete current;
    }
}
void deletingEachLike(NodeLike*& Head, string name){ // this function is used to delete node added to the like list. It deletes all nodes with the same object or subject with the name
    while (Head!=nullptr && (Head->object==name || Head->subject==name)){ // this checks if the list is empty and checks there is a subject and object matching
        NodeLike* temp=Head;
        Head=Head->next;
        delete temp;
    }
    if (Head!=nullptr){ // checks the current node is empty or not
       NodeLike* current=Head->next;
       NodeLike* previousnode=Head;
       while (current!=nullptr){ // while it is not in the end
          if (current->object==name || current->subject==name){ // checks if the object or subject matches with name
             previousnode->next=current->next;
             delete current; // deletes the current node
                current=previousnode->next;
            }
          else{// this works when there is not a match
              previousnode=current;
              current=current->next;
          }
       }
    }
}
void deletingLikeMatch(NodeLike*& head, string subject, string object){ // this function deletes the match
    if (head!=nullptr){ // checks if it is empty or not
        if (head->object==object && head->subject==subject){ //this checks the beginning node matches or not
            NodeLike* temp=head;
            head=head->next;
            delete temp; // this deletes the temp node
            return;
        }
        NodeLike* current=head->next;
        NodeLike* previousnode=head;
        while (current != nullptr){ // this condition continues while current node is not at the end
            if (current->object==object && current->subject==subject){ //checks if there is a match
                previousnode->next=current->next;
                delete current;
                return;
            }
            previousnode=current;
            current=current->next;
        }
    }
}
bool controlNodeLike(NodeLike*& head,string& object, string& subject){ //this function checks if there is already same like node or not
    NodeLike* current = head;
    while(current!=nullptr){  // it continues to the end
        if (current->object == object && current->subject == subject) {// this part shows there is a same node
            return true;
         }
        current = current->next;
    }
    return false;
}
bool controlMathcing(NodeLike*& head,string& object, string& subject){  // this bool function checks there is a match or not
    NodeLike* current = head;
    while(current!=nullptr){ //this checks the nodes to the end
        if (current->object == subject && current->subject == object) { // this checks the matching
            return true;
        }
        current = current->next;
    }
    return false;
}
bool TakenCheck(NodeTaken*& head, string name){ // this function checks the taken part, if it is already taken or not.
    NodeTaken* current=head;
    while(current!=nullptr){// this loop checks the nodes to the enc
        if(current->name==name){// this part shows there is a matching
            return true;
        }
        current=current->next;
    }
    return false;
}
int main() {
    string fileName,line, object, subject;
    int linenumber=0;
    cout<<"Please enter the file name: "; // taking the file name
    cin>>fileName;

    ifstream input;
    input.open(fileName.c_str());//opening the file
    while ( input.fail()){ // if it fails to open the file
        cout<<endl;
        cout<<"Could not open the file. Please enter a valid file name: "; // printing that it is failed and taking the file again
        cin>>fileName;
        input.open(fileName.c_str()); //opening the file again

    }
    NodeLike* HeadLikes=nullptr;
    NodeTaken* HeadTaken=nullptr;

    while(getline(input,line)){  // this while loop reads line by line.gets the line
        linenumber++;
        int spacefind=line.find(" " ); // this find the first space
        int spacefinder2=line.rfind(" "); // finds the second space
        subject=line.substr(0,spacefind); // takes the subject in the line string
        object = line.substr(spacefinder2+1); // takes the object in the line string
        cout<<endl;
        cout<<"Read line number ("<<linenumber<<"): "<<line<<endl; // this shows how many line number readed
        if(linenumber==1){ // if it is the first line
            insertingLikeInOrder(HeadLikes, object, subject); // directly inserts the likes in likes list, because there is no condition
            cout<<subject<<" likes "<<object<<" relation has been added to the likes list."<<endl;
            printingLikes(HeadLikes); // prints the likes list
            cout<<endl;
            printingTaken(HeadTaken); // prints the taken list
            cout<<endl;
        }
        else{
            if (controlNodeLike(HeadLikes,object,subject)){// checks if there is a same like or not
                cout<<subject<<" likes "<<object<<" relation already exists in the likes list, so it is not added to it."<<endl;
                printingLikes(HeadLikes); //prints likes list
                cout<<endl;
                printingTaken(HeadTaken);//prints taken list
                cout<<endl;
            }
            else if(controlMathcing(HeadLikes,object,subject)){ // this part checks if there is a match or not
                deletingLikeMatch(HeadLikes,object,subject); //deletes the matching in the like list
                deletingEachLike(HeadLikes,object); // deletes the other object likes in the list
                deletingEachLike(HeadLikes,subject); // deletes the other subject likes in the list
                insertingTaken(HeadTaken,subject); // inserts subject to the taken list
                insertingTaken(HeadTaken,object); // inserts object to the taken list
                cout<<"Match found: "<<subject<<" likes "<<object<<" and "<<object<<" likes "<<subject<<"."<<endl;
                cout<<"Added to taken list: "<<subject<<endl;
                cout<<"Added to taken list: "<<object<<endl;
                cout<<"Any node that has "<<subject<<" or "<<object<<" or both in it is removed from the likes list."<<endl;
                printingLikes(HeadLikes); // prints current likes list
                cout<<endl;
                printingTaken(HeadTaken); // prints current taken list
                cout<<endl;
            }
            else if(TakenCheck(HeadTaken,object)||TakenCheck(HeadTaken,subject)){// checks the taken list, if it already exists in the taken list, it prints message
                cout<<"Either "<<subject<<" or "<<object<<" or both is/are already taken, so the like relation is not added."<<endl;
                printingLikes(HeadLikes);// prints current likes list
                cout<<endl;
                printingTaken(HeadTaken);// prints current taken list
                cout<<endl;
            }
            else{
                insertingLikeInOrder(HeadLikes, object, subject); // inserts the like in the likes list
                cout<<subject<<" likes "<<object<<" relation has been added to the likes list."<<endl;
                printingLikes(HeadLikes);// prints current likes list
                cout<<endl;
                printingTaken(HeadTaken);// prints current taken list
                cout<<endl;
            }
        }
    }
    DeleteAllTaken(HeadTaken); // deletes all the taken nodes
    DeleteAllLike(HeadLikes); // deletes all the like nodes
    input.close(); //closes the file
    cout<<endl;
    cout<<"Lists are deleted and the program ends successfully.";
    return 0;
}
