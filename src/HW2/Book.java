package src.HW2;

public class Book {
    private String isbn;
    private String title;
    private String author;
    private boolean isAvailable; // 대출 가능 여부

    public Book(String isbn, String title, String author) {
        this.isbn = isbn;
        this.title = title;
        this.author = author;
        this.isAvailable = true; // 초기에는 대출 가능
    }

    // Getter
    public String getIsbn() {
        return isbn;
    }

    public String getTitle() {
        return title;
    }

    public boolean isAvailable() {
        return isAvailable;
    }

    // Setter (대출 상태 변경을 위해 필요)
    public void setAvailable(boolean available) {
        isAvailable = available;
    }

    @Override
    public String toString() {
        return "ISBN: " + isbn + ", 제목: " + title + ", 저자: " + author + ", 상태: " + (isAvailable ? "대출 가능" : "대출 중");
    }
}