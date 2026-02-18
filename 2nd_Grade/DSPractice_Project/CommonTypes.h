#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <string>
#include <map>

// std 네임스페이스 사용
using namespace std;

//학과를 enum으로 구현(인융대 및 교양)
enum class Department {
    SOFTWARE,                   //소프트웨어학부
    Information_Convergence,    //정보융합학부
    Computer_Information,       //컴퓨터정보공학부
    CORE_EDUCATION,             //교양
    UNKNOWN //초기값
};

// 강의 요일 정의
enum class DayOfWeek {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    UNKNOWN
};

/*
 강의 시간 정보를 저장하는 구조체(과목 명, 시간대, 분야) 구현
 */
struct TimeSlot {
    DayOfWeek day;
    int startTime; // 9시 30분 -> 930 (숫자만 입력받도록 구현)
    int endTime;   // 10시 45분 -> 1045
    string location; // 강의실

    // 시간 충돌을 검사하는 헬퍼 함수
    bool overlapsWith(const TimeSlot& other) const {
        if (day != other.day) {
            return false;
        }
        // 시간 겹침 로직 (A.start <= B.end && B.start <= A.end)
        return (startTime <= other.endTime && other.startTime <= endTime);
    }

    // 시간 정보 문자열로 변환
    string toString() const {
        map<DayOfWeek, string> dayMap = {
            {DayOfWeek::MONDAY, "월"}, {DayOfWeek::TUESDAY, "화"}, {DayOfWeek::WEDNESDAY, "수"},
            {DayOfWeek::THURSDAY, "목"}, {DayOfWeek::FRIDAY, "금"}
        };
        return dayMap[day] + " " + to_string(startTime) + "-" + to_string(endTime) + " (" + location + ")";
    }
};

#endif
