package src.HW2;

import java.util.HashMap;
import java.util.Map;

public class LibraryManager implements Loanable {
    private Map<String, Member> members; // 회원 ID -> Member 객체
    private Map<String, Book> books;     // ISBN -> Book 객체
    private Map<String, String> currentLoans; // ISBN -> 회원 ID (대출 현황)

    public LibraryManager() {
        this.members = new HashMap<>();
        this.books = new HashMap<>();
        this.currentLoans = new HashMap<>();
    }

    // --- 회원 관리 ---

    @Override
    public void addMember(Member member) throws LibraryException {
        if (members.containsKey(member.getMemberId())) {
            throw new LibraryException("오류: 이미 존재하는 회원 ID입니다 - " + member.getMemberId());
        }
        members.put(member.getMemberId(), member);
        System.out.println("회원 등록 성공: " + member.getName());
    }

    @Override
    public Member findMember(String memberId) throws LibraryException {
        if (!members.containsKey(memberId)) {
            throw new LibraryException("오류: 존재하지 않는 회원 ID입니다 - " + memberId);
        }
        return members.get(memberId);
    }

    //도서 관리

    @Override
    public void addBook(Book book) throws LibraryException {
        if (books.containsKey(book.getIsbn())) {
            throw new LibraryException("오류: 이미 존재하는 도서 ISBN입니다 - " + book.getIsbn());
        }
        books.put(book.getIsbn(), book);
        System.out.println("도서 등록 성공: " + book.getTitle());
    }

    @Override
    public Book findBook(String isbn) throws LibraryException {
        if (!books.containsKey(isbn)) {
            throw new LibraryException("오류: 존재하지 않는 도서 ISBN입니다 - " + isbn);
        }
        return books.get(isbn);
    }

    //대출 관리

    @Override
    public void borrowBook(String memberId, String isbn) throws LibraryException {
        Member member = findMember(memberId); // 회원 존재 여부 확인 (예외 발생 가능)
        Book book = findBook(isbn);         // 도서 존재 여부 확인 (예외 발생 가능)

        if (!book.isAvailable()) {
            throw new LibraryException("오류: 해당 도서는 이미 대출 중입니다 - " + book.getTitle());
        }
        
        // 대출 처리
        book.setAvailable(false);
        currentLoans.put(isbn, memberId);
        System.out.println("대출 성공: " + member.getName() + "님이 '" + book.getTitle() + "'를 대출했습니다.");
    }

    @Override
    public void returnBook(String isbn) throws LibraryException {
        Book book = findBook(isbn); // 도서 존재 여부 확인

        if (book.isAvailable()) {
            throw new LibraryException("오류: 해당 도서는 대출 중이 아닙니다. 반납할 수 없습니다 - " + book.getTitle());
        }
        
        // 반납 처리
        book.setAvailable(true);
        currentLoans.remove(isbn);
        System.out.println("반납 성공: '" + book.getTitle() + "' 도서가 반납되었습니다.");
    }

    // 추가: 모든 도서 목록 출력 (테스트용)
    public void printAllBooks() {
        System.out.println("\n=== 전체 도서 목록 ===");
        if (books.isEmpty()) {
            System.out.println("등록된 도서가 없습니다.");
            return;
        }
        for (Book book : books.values()) {
            System.out.println(book);
        }
    }
}