#include <iostream>
#include "CourseDB.h"
#include "InputManager.h"
#include "User.h"

using namespace std;


int main() {
    //강의 데이터베이스 모듈 초기화(loadData, buildIndices 호출)
    CourseDB database;

    //사용자 로그인 기능이 구현했다고 치고 User 객체 생성
    User currentUser("2022203089", Department::SOFTWARE, 2);
    currentUser.printInfo();

    //사용자 조건 입력 모듈 초기화
    InputManager inputMgr;

    //새 시간표 추천
    NewTimetablePreferences newPrefs = inputMgr.getNewTimetablePreferences(&currentUser, &database);

    //조건 관리자 파트
    cout << "\n[시스템] '조건 관리자' 모듈로 다음 데이터를 전달합니다:" << endl;
    cout << "  - 희망 강의 수: " << newPrefs.desiredLectures.size() << "개" << endl;
    cout << "  - 금공 선호: " << (newPrefs.preferNoClassesOnFriday ? "Yes" : "No") << endl;
    //가중치 계산 및 이진트리 탐색 수행 파트


    //추가 강의 추천
    AddCoursePreferences addPrefs = inputMgr.getAddCoursePreferences(&currentUser, &database);

    //추가 강의 추천 알고리즘 파트
    cout << "\n[시스템] '추가 강의 추천' 모듈로 다음 데이터를 전달합니다:" << endl;
    cout << "  - 희망 과목명: " << (addPrefs.desiredCourseName.empty() ? "(없음)" : addPrefs.desiredCourseName) << endl;
    cout << "  - 선호 분야: " << (addPrefs.preferredField.empty() ? "(없음)" : addPrefs.preferredField) << endl;

    return 0;
}
