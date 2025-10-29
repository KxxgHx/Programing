#ifndef COURSE_DB_H
#define COURSE_DB_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <fstream> // 파일 입출력 설계
#include "Lecture.h"

using namespace std;

/*
데이터베이스 개발 클래스
 - 데이터: Linked List
 - 검색 인덱스: map / multimap (Binary Search Tree)
 */
class CourseDB {
private:
    //모든 강의 원본 데이터를 저장(list)
    list<Lecture> allLectures; 

    //과목명으로 검색하기 위한 인덱스(multimap을 사용하여 이진 탐색 트리 구현)
    multimap<string, Lecture*> lecturesByName;

    //과목 코드로 빠르게 검색하기 위한 인덱스(map을 사용하여 이진 탐색 트리 구현)
    map<string, Lecture*> lectureById;

public:
    CourseDB() {
        // [웹 크롤링/파일 입출력 설계]
        // loadDataFromFile("courses.json");
        
        // (임시) 샘플 데이터 사용
        loadSampleData(); 

        // 데이터 로드 후, 검색 속도를 높이기 위해 인덱스를 구축
        buildIndices();
    }

    /**
     * @brief [웹 크롤링/파일 입출력 설계]
     * 광운대 홈페이지에서 추출한 데이터 파일(JSON, CSV 등)을 읽어 DB를 구축
     * @param filename 읽어올 파일 경로 (예: "courses.json")
     */
    void loadDataFromFile(const string& filename) {
        cout << "[DB] " << filename << " 에서 데이터를 로드합니다..." << endl;
        // --- [설계] ---
        // 1. (외부) Python 스크립트(requests, BeautifulSoup)가 광운대 홈페이지를 크롤링
        // 2. (외부) 스크립트가 'courses.json' 또는 'courses.csv' 파일 생성
        // 3. (C++) 이 함수에서 'filename'의 파일을 엽니다. (ifstream 사용)
        // 4. (C++) 파일 형식이 JSON이라면 'nlohmann/json' 같은 JSON 파서 라이브러리 사용
        // 5. (C++) 파일 형식이 CSV라면 'getline'과 'stringstream'으로 파싱
        // 6. 파싱한 데이터로 'Lecture' 객체를 생성하여 'allLectures' 리스트에 'push_back'
        // ---
        
        // (아래는 파일 입출력 예시가 아닌, 샘플 데이터 로드)
        loadSampleData();
    }


    // 샘플 데이터 로드 함수 (allLectures 리스트에 원본 데이터 추가)
    void loadSampleData() {
        Lecture l1("SOFT201", "자료구조실습", Department::SOFTWARE, 2, "전공필수", 3, "김교수", {"SOFT101"});
        l1.addTimeSlot(DayOfWeek::MONDAY, 1000, 1150, "SAEBIT-303");
        l1.addTimeSlot(DayOfWeek::WEDNESDAY, 1000, 1150, "SAEBIT-303");
        allLectures.push_back(l1); // 리스트에 추가

        Lecture l2("SOFT202", "객체지향프로그래밍", Department::SOFTWARE, 2, "전공필수", 3, "이교수", {"SOFT102"});
        l2.addTimeSlot(DayOfWeek::TUESDAY, 1300, 1450, "SAEBIT-204");
        l2.addTimeSlot(DayOfWeek::THURSDAY, 1300, 1450, "SAEBIT-204");
        allLectures.push_back(l2); // 리스트에 추가

        Lecture l3("SOFT302", "인공지능", Department::Information_Convergence, 1, "전공기초", 3, "박교수", {});
        l3.addTimeSlot(DayOfWeek::MONDAY, 900, 1050, "SAEBIT-204");
        allLectures.push_back(l3); // 리스트에 추가

        Lecture l4("CORE001", "미래사회와기술", Department::CORE_EDUCATION, 1, "공통교양", 2, "최교수", {});
        l4.addTimeSlot(DayOfWeek::FRIDAY, 1400, 1550, "ONLINE");
        allLectures.push_back(l4); // 리스트에 추가

        // (분반) 동일 과목, 다른 시간
        Lecture l5("SOFT201", "자료구조실습", Department::SOFTWARE, 2, "전공필수", 3, "김교수", {"SOFT101"});
        l5.addTimeSlot(DayOfWeek::TUESDAY, 900, 1050, "SAEBIT-302");
        l5.addTimeSlot(DayOfWeek::THURSDAY, 900, 1050, "SAEBIT-302");
        allLectures.push_back(l5); // 리스트에 추가
    }

    /*
        'allLectures' 리스트를 기반으로 검색용 'map'(이진탐색트리) 인덱스를 구축
    */
    void buildIndices() {
        lecturesByName.clear();
        lectureById.clear();

        /*
        'allLectures' (연결 리스트)를 순회(iterator)
        list는 push_back/push_front 외에 원소의 메모리 주소가 바뀌지 않으므로 포인터를 안전하게 저장 가능 및 인덱스로 사용
        */ 
        for (auto it = allLectures.begin(); it != allLectures.end(); ++it) {
            Lecture* lecturePtr = &(*it); // 리스트 내의 원본 객체 주소
            
            // 1. 과목명 인덱스(multimap)에 추가
            lecturesByName.insert({lecturePtr->courseName, lecturePtr});
            
            // 2. 과목ID 인덱스(map)에 추가
            lectureById.insert({lecturePtr->courseId, lecturePtr});
        }
    }


    /** 
     * 'lecturesByName' (multimap)을 사용한 빠른 검색
     * @param name 검색할 과목명 (예: "자료구조실습")
     * @return 해당 과목명의 모든 Lecture 객체 리스트
     */
    vector<Lecture> findLecturesByName(const string& name) const {
        vector<Lecture> found;
        
        // 'equal_range'는 multimap에서 일치하는 키의 범위를 O(log N)으로 찾습니다.
        auto range = lecturesByName.equal_range(name);
        
        // 찾은 범위(iterator 쌍)를 순회합니다.
        for (auto it = range.first; it != range.second; ++it) {
            found.push_back(*(it->second)); // 포인터가 가리키는 Lecture 객체를 복사하여 추가
        }
        
        return found;
    }

    /**
     * map을 사용한 빠른 검색
     * @param id 검색할 과목 ID (예: "SOFT201")
     * @return 해당 ID의 Lecture 객체 포인터 (없으면 nullptr)
     */
    const Lecture* getLectureById(const string& id) const {
        // 'find'는 map에서 O(log N)으로 키를 찾습니다.
        auto it = lectureById.find(id);
        if (it != lectureById.end()) {
            return it->second; // 찾은 경우, 저장된 포인터 반환
        }
        return nullptr;
    }
};

#endif
