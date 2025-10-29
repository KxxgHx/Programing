#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "CourseDB.h"
#include "User.h"

using namespace std;


//  '새 시간표 추천' 시 사용자가 입력한 조건들을 저장하는 구조체
struct NewTimetablePreferences {
    // 사용자가 선택한 구체적인 강의(분반) 목록
    
    vector<Lecture> desiredLectures;
    
    // 비선호 시간대 목록
    vector<TimeSlot> nonPreferredTimes;

    // 기타 조건들
    bool preferNoClassesOnFriday = false;
    bool avoidMorningClasses = false; // ex) 10시 이전 수업 회피
    //(추가 조건 구현)
};

/**
 * @brief '추가 강의 추천' 시 사용자가 입력한 조건들을 저장하는 구조체
 */
struct AddCoursePreferences {
    string desiredCourseName = ""; // 특정 과목명 (선택)
    string preferredField = "";  // 선호 분야 (예: "교양")
    //(추가 조건)
};

/*
    사용자 입력을 담당하는 관리자 클래스
    '사용자 조건입력 구현'의 메인 로직을 포함
 */
class InputManager {
public:
    /** 
     * 선수과목 확인
     * @param user 현재 사용자
     * @param lecture 선택하려는 강의
     * @return 사용자가 수강하겠다고 확인하면 true
     */
    bool confirmPrerequisites(User* user, const Lecture& lecture) {
        // 1. 개설 학과 비교 (제안서)
        if (user->department != lecture.department && lecture.department != Department::CORE_EDUCATION) {
            cout << "[알림] '" << lecture.courseName << "' 과목은 타과 전공입니다." << endl;
        }

        // 2. 선수과목 수강 확인 (제안서)
        if (!lecture.prerequisiteCourseIds.empty()) {
            cout << "[확인] '" << lecture.courseName << "' 과목을 수강하려면 다음 선수과목 이수가 권장됩니다:" << endl;
            for(const auto& prereqId : lecture.prerequisiteCourseIds) {
                cout << "  - " << prereqId << endl;
            }
            cout << "  이수하였거나 수강에 문제가 없습니까? (y/n): ";
            char response;
            cin >> response;
            cin.ignore(10000, '\n'); // 입력 버퍼 비우기
            if (response != 'y' && response != 'Y') {
                cout << "  -> 수강 목록에 추가하지 않습니다." << endl;
                return false;
            }
        }
        return true;
    }

    /**
     * '새 시간표 추천'을 위한 사용자 조건을 입력받음
     * @param user 현재 사용자
     * @param db 강의 데이터베이스
     * @return 사용자가 입력한 모든 조건을 담은 구조체
     */
    NewTimetablePreferences getNewTimetablePreferences(User* user, const CourseDB* db) {
        NewTimetablePreferences prefs;
        string courseName;

        cout << "\n--- [1] 새 시간표 추천 ---" << endl;
        cout << "원하는 과목명을 하나씩 입력하세요 (완료 시 'q' 입력):" << endl;

        while (true) {
            cout << ">> 과목명: ";
            getline(cin, courseName);
            if (courseName == "q") break;

            // CourseDB의 'findLecturesByName' (빠른 O(log N) 검색) 호출
            vector<Lecture> foundLectures = db->findLecturesByName(courseName);
            if (foundLectures.empty()) {
                cout << "  -> '" << courseName << "' 과목을 찾을 수 없습니다." << endl;
                continue;
            }

            // 1. 과목명에 해당하는 모든 분반(섹션)을 보여줌
            cout << "  -> '" << courseName << "' 과목으로 " << foundLectures.size() << "개의 분반이 검색되었습니다." << endl;
            for (size_t i = 0; i < foundLectures.size(); ++i) {
                cout << "  [분반 " << (i + 1) << "]" << endl;
                foundLectures[i].printInfo();
            }

            // 2. 사용자에게 분반 선택 요청 (여기서는 간단히 첫 번째 분반을 선택한다고 가정)
            // (실제 구현 시: 사용자에게 번호를 입력받아 선택)
            int choice = 1; // 예: 사용자가 1번 분반 선택
            cout << "  -> [분반 " << choice << "]을 선택합니다." << endl;
            
            const Lecture& selectedLecture = foundLectures[choice - 1];

            // 3. '과목 관리' - 선수과목 확인 등
            if (confirmPrerequisites(user, selectedLecture)) {
                prefs.desiredLectures.push_back(selectedLecture);
                cout << "  -> '" << selectedLecture.courseName << "' (분반 " << choice << ") 추가 완료." << endl;
            }
        }

        // 4. (제안서) 선호/비선호 조건 입력
        cout << "\n--- [2] 선호/비선호 조건 입력 ---" << endl;
        cout << "금요일 공강을 선호하십니까? (y/n): ";
        char response;
        cin >> response;
        if (response == 'y' || response == 'Y') {
            prefs.preferNoClassesOnFriday = true;
        }
        cin.ignore(10000, '\n'); // 버퍼 비우기

        // (비선호 시간대 등 추가 입력 로직...)
        
        cout << "--- 조건 입력 완료 ---" << endl;
        return prefs; // 이 prefs 객체가 '조건 관리자' 모듈로 전달됩니다.
    }

    /**
     * @brief '추가 강의 추천'을 위한 사용자 조건을 입력받습니다.
     * @param user 현재 사용자
     * @param db 강의 데이터베이스
     * @return 사용자가 입력한 조건을 담은 구조체
     */
    AddCoursePreferences getAddCoursePreferences(User* user, const CourseDB* db) {
        AddCoursePreferences prefs;
        string input;
        
        cout << "\n--- [3] 추가 강의 추천 (꿀강의 탐색기) ---" << endl;
        cout << "특정 과목명을 원하십니까? (없으면 Enter): ";
        getline(cin, input);
        if (!input.empty()) {
            prefs.desiredCourseName = input;
        }

        cout << "선호하는 분야가 있습니까? (예: 교양, 전공 / 없으면 Enter): ";
        getline(cin, input);
        if (!input.empty()) {
            prefs.preferredField = input;
        }

        // (기타 선호/비선호 조건 입력 로직)
        
        cout << "--- 조건 입력 완료 ---" << endl;
        return prefs;
    }
};

#endif
