#include <iostream>
#include <string>
using namespace std;
class Student {
private:
    string name;
    int id;
    float gpa;

public:
    Student() {
        name = "";
        id = 0;
        gpa = 0.0;
    }

    Student(string n, int i, float g) {
        name = n;
        id = i;
        gpa = g;
    }

    int getId() const {
        return id;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "GPA: " << gpa << endl;
    }
};
class Node {
public:
    Student data;
    Node* next;

    Node(Student s) : data(s), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(Student s) {
        Node* newNode = new Node(s);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Last Deleted Student:\n";
        top->data.display();
        Node* temp = top;
        top = top->next;
        delete temp;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = rear = nullptr;
    }

    void enqueue(Student s) {
        Node* newNode = new Node(s);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Serving Student:\n";
        front->data.display();
        Node* temp = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete temp;
    }
};

class StudentList {
private:
    Node* head;
    Stack deletedStack;
    Queue serviceQueue;

public:
    StudentList() {
        head = nullptr;
    }

    void addStudent(Student s) {
        Node* newNode = new Node(s);
        newNode->next = head;
        head = newNode;
        serviceQueue.enqueue(s);
        cout << "Student added successfully.\n";
    }

    void display() const {
        if (head == nullptr) {
            cout << "No students available.\n";
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            temp->data.display();
            cout << "-----------------\n";
            temp = temp->next;
        }
    }

    void searchStudent(int id) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data.getId() == id) {
                cout << "Student Found:\n";
                temp->data.display();
                return;
            }
            temp = temp->next;
        }
        cout << "Student not found.\n";
    }

    void deleteStudent(int id) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        if (head->data.getId() == id) {
            deletedStack.push(head->data);
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Student deleted.\n";
            return;
        }

        Node* prev = head;
        Node* curr = head->next;

        while (curr != nullptr && curr->data.getId() != id) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Student not found.\n";
        } else {
            deletedStack.push(curr->data);
            prev->next = curr->next;
            delete curr;
            cout << "Student deleted.\n";
        }
    }

    void showLastDeleted() {
        deletedStack.pop();
    }

    void serveStudent() {
        serviceQueue.dequeue();
    }
};

int main() {
    StudentList system;
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Search Student\n";
        cout << "5. Show Last Deleted Student (Stack)\n";
        cout << "6. Serve Student (Queue)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int id;
            float gpa;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter GPA: ";
            cin >> gpa;
            system.addStudent(Student(name, id, gpa));
        }
        else if (choice == 2)
            system.display();
        else if (choice == 3) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            system.deleteStudent(id);
        }
        else if (choice == 4) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            system.searchStudent(id);
        }
        else if (choice == 5)
            system.showLastDeleted();
        else if (choice == 6)
            system.serveStudent();
        else if (choice == 7)
            cout << "Exiting...\n";
        else
            cout << "Invalid choice.\n";

    } while (choice != 7);

    return 0;
}
