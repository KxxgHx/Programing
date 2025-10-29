package src.HW2;

public interface Loanable {
    // 회원 관리
    void addMember(Member member) throws LibraryException;
    Member findMember(String memberId) throws LibraryException;

    // 도서 관리
    void addBook(Book book) throws LibraryException;
    Book findBook(String isbn) throws LibraryException;

    // 대출 관리
    void borrowBook(String memberId, String isbn) throws LibraryException;
    void returnBook(String isbn) throws LibraryException;
}
