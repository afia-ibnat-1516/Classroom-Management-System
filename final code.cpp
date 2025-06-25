#include<iostream>
#include<cstring>
using namespace std;
#define MAX_STUDENTS 100
#define MAX_SCHEDULES 5
// Define schedule structure
struct Schedule {
    char day[20];
    char time[20];
    char course[50];
    char instructor[50];
};
// Define student structure
struct Student {
    char name[50];
    char email[20];
    int mobile;
    char id[10];
    Schedule schedules[MAX_SCHEDULES];
    int scheduleCount;
};
// Define node structure for linked list implementation
struct Node {
    Student data;
    Node* next;
};
// Function prototypes
void addStudentLinkedList(Node*& head, int& count);
void displayStudentsLinkedList(Node* head);
void addScheduleLinkedList(Node* head);
void displaySchedulesLinkedList(Node* head);
void deleteStudentLinkedList(Node*& head);
void deleteScheduleLinkedList(Node* head);
int main() {
    Node* headLinkedList = nullptr;
    int countLinkedList = 0, choice;
    cout << "...........INTERNATIONAL ISLAMIC UNIVERSITY CHATTOGRAM............\n\n";
    cout << "\n\t____Faculty of Science And Engineering____\n\n";
    cout << "\n\t\t____Department of CSE____\n\n";
    cout << "\n\tHOME PAGE";
    cout << "\n=========================\n\n";
    do {
        cout << "\nClassroom Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Add Schedule" << endl;
        cout << "4. Display Schedules" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Delete Schedule" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudentLinkedList(headLinkedList, countLinkedList);
                break;
            case 2:
                displayStudentsLinkedList(headLinkedList);
                break;
            case 3:
                addScheduleLinkedList(headLinkedList);
                break;
            case 4:
                displaySchedulesLinkedList(headLinkedList);
                break;
            case 5:
                deleteStudentLinkedList(headLinkedList);
                break;
            case 6:
                deleteScheduleLinkedList(headLinkedList);
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    // Clean up allocated memory for linked list nodes
    Node* current = headLinkedList;
    Node* temp;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
// Linked list functions
void addStudentLinkedList(Node*& head, int& count) {
    Node* newNode = new Node;
    if (newNode == nullptr) {
        cout << "Memory allocation failed." << endl;
        return;
    }
    cout << "Enter student name: ";
    cin.ignore(); // Ignore newline character in buffer
    cin.getline(newNode->data.name, 50);
    cout << "Enter student email: ";
    cin >> newNode->data.email;
    cout << "Enter student mobile: ";
    cin >> newNode->data.mobile;
    cout << "Enter student id: ";
    cin >> newNode->data.id;
    newNode->data.scheduleCount = 0; // Initialize schedule count
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    count++;
    cout << "Student added successfully to linked list." << endl;
}
void displayStudentsLinkedList(Node* head) {
    if (head == nullptr) {
        cout << "No students in the linked list." << endl;
        return;
    }
    cout << "\n";
    cout << "|==============================|" << endl;
    cout << "|    CLASSROOM STUDENTS        |" << endl;
    cout << "|==============================|" << endl;
    cout << "\n";
    Node* temp = head;
    while (temp != nullptr) {
        cout << "Name: " << temp->data.name << endl;
        cout << "Email: " << temp->data.email << endl;
        cout << "Mobile: " << temp->data.mobile << endl;
        cout << "ID: " << temp->data.id << endl;
        cout << "==============================" << endl;
        temp = temp->next;
    }
    cout << "\n";
}
void addScheduleLinkedList(Node* head) {
    char studentId[10];
    cout << "Enter student ID: ";
    cin >> studentId;
    Node* current = head;
    while (current != nullptr) {
        if (strcmp(current->data.id, studentId) == 0) {
            if (current->data.scheduleCount >= MAX_SCHEDULES) {
                cout << "Maximum number of schedules reached for this student." << endl;
                return;
            }
            Schedule newSchedule;
            cout << "Enter class day: ";
            cin >> newSchedule.day;
            cout << "Enter class time: ";
            cin >> newSchedule.time;
            cout << "Enter course name: ";
            cin >> newSchedule.course;
            cout << "Enter instructor name: ";
            cin >> newSchedule.instructor;
            current->data.schedules[current->data.scheduleCount] = newSchedule;
            current->data.scheduleCount++;
            cout << "Schedule added successfully." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Student with ID " << studentId << " not found." << endl;
}
void displaySchedulesLinkedList(Node* head) {
    char studentId[10];
    cout << "Enter student ID: ";
    cin >> studentId;
    Node* current = head;
    while (current != nullptr) {
        if (strcmp(current->data.id, studentId) == 0) {
            if (current->data.scheduleCount == 0) {
                cout << "No schedules found for this student." << endl;
                return;
            }
            cout << "\nSchedules for student " << current->data.name << ":" << endl;
            for (int i = 0; i < current->data.scheduleCount; i++) {
                cout << "Day: " << current->data.schedules[i].day << endl;
                cout << "Time: " << current->data.schedules[i].time << endl;
                cout << "Course: " << current->data.schedules[i].course << endl;
                cout << "Instructor: " << current->data.schedules[i].instructor << endl;
                cout << "==============================" << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Student with ID " << studentId << " not found." << endl;
}
void deleteStudentLinkedList(Node*& head) {
    char studentId[10];
    cout << "Enter student ID to delete: ";
    cin >> studentId;
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (strcmp(current->data.id, studentId) == 0) {
            if (prev == nullptr) {
                // If the student to be deleted is the head node
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Student with ID " << studentId << " deleted successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Student with ID " << studentId << " not found." << endl;
}
void deleteScheduleLinkedList(Node* head) {
    char studentId[10];
    cout << "Enter student ID: ";
    cin >> studentId;
    Node* current = head;
    while (current != nullptr) {
        if (strcmp(current->data.id, studentId) == 0) {
            if (current->data.scheduleCount == 0) {
                cout << "No schedules found for this student." << endl;
                return;
            }
            int scheduleIndex;
            cout << "Enter the index of the schedule to delete (0 to " << current->data.scheduleCount - 1 << "): ";
            cin >> scheduleIndex;
            if (scheduleIndex < 0 || scheduleIndex >= current->data.scheduleCount) {
                cout << "Invalid schedule index." << endl;
                return;
            }
            for (int i = scheduleIndex; i < current->data.scheduleCount - 1; i++) {
                current->data.schedules[i] = current->data.schedules[i + 1];
            }
            current->data.scheduleCount--;
            cout << "Schedule at index " << scheduleIndex << " deleted for student with ID " << studentId << endl;
            return;
        }
        current = current->next;
    }
    cout << "Student with ID " << studentId << " not found." << endl;
}
