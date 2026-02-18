class Group_Fixed {
    private String[] str;   // 내부 데이터는 은닉
    private int length = 0;

    public Group_Fixed(int size) {
        this.str = new String[size];
    }

    public void setMembers(String s) {
        if (length < str.length) {
            str[length++] = s;
        } else {
            System.out.println("Error: 그룹이 가득 찼습니다!");
        }
    }

    // 방어적 복사 적용: 배열의 복사본을 반환
    public String[] getMembers() {
        String[] copy = new String[length];  // 현재까지 저장된 만큼만 복사
        for (int i = 0; i < length; i++) {
            copy[i] = str[i];
        }
        return copy;
    }

    public int getLength() {
        return length;
    }
}

public class HW_1_3_Fixed {
    public static void main(String[] args) {
        Group_Fixed g = new Group_Fixed(5);
        g.setMembers("Alpha");
        g.setMembers("Bravo");
        g.setMembers("Charlie");
        g.setMembers("Delta");
        g.setMembers("Echo");

        // 이제 아래 문장은 내부 데이터에 영향을 주지 않음
        String[] members = g.getMembers();
        members[0] = "Alice";

        // 원본 데이터는 보호됨
        for (int i = 0; i < g.getLength(); i++) {
            System.out.println(g.getMembers()[i]);
        }
    }
}
