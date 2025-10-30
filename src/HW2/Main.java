package src.HW2;

import java.util.Scanner;

public class Main {
    private static LibraryManager manager = new LibraryManager();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        setupInitialData();
        
        System.out.println("=========================================");
        System.out.println("         도서 대출 시스템        ");
        System.out.println("=========================================");

        boolean running = true;
        while (running) {
            printMenu();
            System.out.print(" 메뉴 선택 (1-6): ");
            String choice = scanner.nextLine();

            try {
                switch (choice) {
                    case "1":
                        addBookInterface();
                        break;
                    case "2":
                        addMemberInterface();
                        break;
                    case "3":
                        borrowBookInterface();
                        break;
                    case "4":
                        returnBookInterface();
                        break;
                    case "5":
                        manager.printAllBooks(); // LibraryManager에 구현된 도서 목록 출력 사용
                        break;
                    case "6":
                        running = false;
                        System.out.println("시스템을 종료합니다. 감사합니다!");
                        break;
                    default:
                        System.out.println(" 잘못된 메뉴 선택입니다. 1부터 6 사이의 숫자를 입력해주세요.");
                }
            } catch (Exception e) {
                System.err.println("\n 시스템 오류 발생: " + e.getMessage());
            }
            if(running) System.out.println("\n-----------------------------------------\n");
        }
        scanner.close();
    }

// 테스트 용이를 위한 초기 데이터
    private static void setupInitialData() {
        try {
            manager.addMember(new Member("M001", "강현서"));
            manager.addMember(new Member("M002", "강한결"));
            manager.addBook(new Book("B1001", "자바 프로그래밍", "저자A"));
            manager.addBook(new Book("B1002", "알고리즘 개론", "저자B"));
            manager.addBook(new Book("B1003", "데이터베이스 기초", "저자C"));
        } catch (LibraryException e) {
            // 초기 데이터 설정 중복 무시
        }
    }

    private static void printMenu() {
        System.out.println("\n----- 기능 목록 -----");
        System.out.println("1. 도서 등록");
        System.out.println("2. 회원 등록");
        System.out.println("3. 도서 대출");
        System.out.println("4. 도서 반납");
        System.out.println("5. 전체 도서 목록 보기");
        System.out.println("6. 시스템 종료");
        System.out.println("---------------------");
    }

    
    //도서 등록 기능 인터페이스
    
    private static void addBookInterface() {
        System.out.println("\n--- 도서 등록 ---");
        System.out.print("ISBN 입력: ");
        String isbn = scanner.nextLine();
        System.out.print("제목 입력: ");
        String title = scanner.nextLine();
        System.out.print("저자 입력: ");
        String author = scanner.nextLine();

        try {
            manager.addBook(new Book(isbn, title, author));
        } catch (LibraryException e) {
            System.err.println(" 도서 등록 실패: " + e.getMessage());
        }
    }

    
    //회원 등록 기능 인터페이스
     
    private static void addMemberInterface() {
        System.out.println("\n--- 회원 등록 ---");
        System.out.print("회원 ID 입력: ");
        String memberId = scanner.nextLine();
        System.out.print("이름 입력: ");
        String name = scanner.nextLine();

        try {
            manager.addMember(new Member(memberId, name));
        } catch (LibraryException e) {
            System.err.println(" 회원 등록 실패: " + e.getMessage());
        }
    }

    
    //도서 대출 기능 인터페이스
    
    private static void borrowBookInterface() {
        System.out.println("\n--- 도서 대출 ---");
        System.out.print("회원 ID 입력: ");
        String memberId = scanner.nextLine();
        System.out.print("대출할 도서 ISBN 입력: ");
        String isbn = scanner.nextLine();

        try {
            manager.borrowBook(memberId, isbn);
        } catch (LibraryException e) {
            System.err.println(" 도서 대출 실패: " + e.getMessage());
        }
    }

    
    //도서 반납 기능 인터페이스
    
    private static void returnBookInterface() {
        System.out.println("\n--- 도서 반납 ---");
        System.out.print("반납할 도서 ISBN 입력: ");
        String isbn = scanner.nextLine();

        try {
            manager.returnBook(isbn);
        } catch (LibraryException e) {
            System.err.println(" 도서 반납 실패: " + e.getMessage());
        }
    }
}