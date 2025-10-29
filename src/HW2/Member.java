package src.HW2;

public class Member {
    private String memberId;
    private String name;

    public Member(String memberId, String name) {
        this.memberId = memberId;
        this.name = name;
    }

    // Getter
    public String getMemberId() {
        return memberId;
    }

    public String getName() {
        return name;
    }

    // 필요한 경우 setter 추가 가능
    
    @Override
    public String toString() {
        return "회원ID: " + memberId + ", 이름: " + name;
    }
}

