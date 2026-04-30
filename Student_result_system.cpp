#include <iostream>
#include <limits>
#include <cctype>
#include <string>
using namespace std;

#define SIZE 1000
#define MAX_MARKS 100
#define MIN_MARKS 0

// struct for stack
struct Action{
    string type;
    int id, marks;
};

Action StackArr[1000];
int top = -1;

//functions for stack operation
void push(Action a){
    if(top >= 999) return;
    StackArr[++top] = a;
}

bool isStackEmpty(){
    return top == -1;
}

Action pop(){
    return StackArr[top--];
}


// struct for student
struct Student{
    int id;
    string name;
    int marks;
};


// hashtable
Student* hashTable[SIZE] = {NULL};

int hashFunc (int id){
    return id % SIZE;
}

//searching using hash
Student* searchHash (int id){
    int index = hashFunc(id);
    int start = index;

    while(hashTable[index] != NULL){
        if(hashTable[index]->id == id){
            return hashTable[index];
        }

        index = (index + 1) % SIZE;
        if(index == start) break;
    }
    return NULL;
}

// duplicate checking of Id
bool isDuplicateID (int id){
    return searchHash(id) != NULL;
}

//inserting new student to the hashtable
void insertHash(Student *s){
    int index = hashFunc(s->id);

    while(hashTable[index] != NULL)
        index = (index + 1) % SIZE;

    hashTable[index] = s;
}


// delete from hash after making undo
void deleteHash(int id){
    int index = hashFunc(id);
    int start = index;

    while(hashTable[index] != NULL){
        if(hashTable[index]-> id == id){
            hashTable[index] = NULL;
            return;
        }

        index = (index + 1) % SIZE;
        if(index == start) break;
    }
}


//struct for binary search tree
struct Node{
    Student data;
    Node *left;
    Node *right;
};

Node* root = NULL;

Node* createNode(Student s){
    Node* n = new Node();
    n-> data = s;
    n-> left = n-> right = NULL;
    return n;
}


// insert node at Binary search tree
 Node* insertBST(Node* node, Student s){
    if(!node) return createNode(s);

    if(s.marks > node->data.marks)  node->left = insertBST(node->left, s);
    else  node->right = insertBST(node-> right, s);

    return node;
 }


 // Delete node
 Node* deleteBST (Node* node, int id){
    if(!node) return NULL;

    if(node->data.id == id){
        if(!node->left && !node->right){
            delete node;
            return NULL;
        }
        if(!node->left){
            Node* t= node->right;
            delete node;
            return t;
        }
        if(!node->right){
            Node* t= node->left;
            delete node;
            return t;
        }

    Node* successor = node->right;
    while(successor->left)
        successor = successor->left;

    node->data = successor->data;
    node->right = deleteBST(node->right, successor->data.id);

    return node;
    }

    node->left = deleteBST(node->left, id);
    node->right = deleteBST(node->right, id);

    return node;
 }


 //traversing bst to show the student information
  void inorder(Node* node){
    if(!node) return;

    inorder(node->left);
    cout << "ID: " << node->data.id << " | Name: " << node->data.name << " | Marks: " << node->data.marks << endl;
    inorder(node->right);
  }


// validation function

int getValidInt(string prompt){
    int value;
    while(true){
        cout << prompt;
        cin >> value;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Numbers only!" << endl;
        }else{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}



string getValidName(string prompt){
    string name;

    while(true){

        cout << prompt;
        getline(cin, name);
         if(name.empty()){
            cout << "Name cannot be empty" << endl;
            continue;
         }
         bool ok = true;
         for(char c: name){
            if(!isalpha(c) && c != ' ') ok = false;
         }
         if(ok) return name;

         cout << "only letters allowed" << endl;
    }
}


int getValidMarks(){
    int m;
    while(true){
        m = getValidInt("Enter Marks: ");
        if(m >= MIN_MARKS && m <= MAX_MARKS) return m;

        cout << "Marks must be 0 - 100" << endl;
    }
}


// operations

// addstudent
void addStudent(){
    Student* s = new Student();

    s->id = getValidInt("Enter ID: ");

    if(isDuplicateID(s->id)){
        cout << "Duplicate ID not allowed" << endl;
        delete s;
        return;
    }

    s->name = getValidName("Enter Name: ");
    s->marks = getValidMarks();

    insertHash(s);
    root = insertBST(root, *s);
    push({"ADD", s->id, s->marks});

    cout << "Student Added." << endl;
}

// search Student
void searchStudent(){
    int id  = getValidInt("Enter ID: ");

    Student* s = searchHash(id);

    if(s) cout << "Found : " << s->name << " | Marks: " << s->marks << endl;
    else cout << "Not Found" << endl;
}

// display marks
void displaySorted(){
    if(!root){
        cout << "No Data" << endl;
        return;
    }

    cout << endl << "sorted students" << endl;
    inorder(root);
}


// update marks
void updateMarks(){
    int id = getValidInt("Enter ID: ");
    Student* s= searchHash(id);

    if(!s){
        cout << "Not Found" << endl;
        return;
    }

    int oldMarks = s->marks;
    int newMarks = getValidMarks();

    push({"UPDATE", s->id, oldMarks});

    // removing  the old node
    root = deleteBST(root, s->id);   


    // updating the value
    s->marks = newMarks;     

    //add
    root = insertBST(root, *s); 

    cout << "Updated" << endl;
}

// undoing function
void undo(){
    if(isStackEmpty()){
        cout << "Nothing to undo" << endl;
        return;
    }

    Action a = pop();
    if(a.type == "UPDATE"){
        Student* s = searchHash(a.id);
    if(s){
        root = deleteBST(root, s->id);
        s->marks = a.marks;
        root = insertBST(root, *s);
    }
    
    cout << "Undo UPDATE successful" << endl;
    }else if(a.type == "ADD"){
        deleteHash(a.id);
        root = deleteBST(root, a.id);
        cout << "Undo ADD successful" << endl;
    }
}


int main(){
    int choice;

    while(true){
        cout << "\n==========STUDENT RESULT SYSTEM==========\n";
        cout << "1. Add\n2. Search\n3. Display\n4. Update\n5. Undo\n6. Exit\n";

        choice = getValidInt("Enter choice: ");

        switch(choice){
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: displaySorted(); break;
            case 4: updateMarks(); break;
            case 5: undo(); break;
            case 6:
                cout << "BYE\n";
                return 0;
            default: cout << "Invalid\n";
        }
    }
}
// adding other account
