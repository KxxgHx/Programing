#ifndef LECTURE_H
#define LECTURE_H

#include <iostream>
#include <string>
#include <vector>
#include "CommonTypes.h" // 공통 타입 포함

// std 네임스페이스 사용
using namespace std;

/*
  Lecture(강의) 클래스
 */
class Lecture {
public:
    string courseId;       // 과목 코드
    string courseName;     // 과목명
    Department department; // 개설 학과
    int targetGrade;       // 대상 학년
    string field;          // 이수 구분
    int credits;           // 학점
    string professor;      // 교수명
    vector<TimeSlot> timeSlots; // 강의 시간(주 1회인지 2회인지)
    vector<string> prerequisiteCourseIds; // 선수과목 ID 리스트

    Lecture(string id, string name, Department dept, int grade, string f, int c, string prof, vector<string> prereqs)
        : courseId(id), courseName(name), department(dept), targetGrade(grade), field(f), credits(c), professor(prof), prerequisiteCourseIds(prereqs) {}

    void addTimeSlot(DayOfWeek day, int start, int end, string loc) {
        timeSlots.push_back({day, start, end, loc});
    }

    // 강의 정보 출력
    void printInfo() const {
        cout << "  [" << courseId << "] " << courseName << " (" << professor << ", " << credits << "학점)" << endl;
        for (const auto& ts : timeSlots) {
            cout << "    - " << ts.toString() << endl;
        }
    }
};

#endif
