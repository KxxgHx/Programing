#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include "CommonTypes.h"
#include "Lecture.h"

using namespace std;

// 로그인을 통해 생성되는 사용자 객체
class User {
public:
    string studentId; // 학번
    Department department; // 학과
    int grade;             // 학년
    list<Lecture> myTimetable; // 시간표 (Linked List)

    User(string id, Department dept, int g) : studentId(id), department(dept), grade(g) {}

    void printInfo() const {
        cout << "--- 사용자 정보 ---" << endl;
        cout << "학번: " << studentId << ", 학년: " << grade << endl;
        cout << "------------------" << endl;
    }
};

#endif