class Group {
    public String[] str;
    public int length = 0;
    public Group(int ptr) {
        this.str = new String[ptr];
    }

    public void setMembers(String s) {
        if (length < str.length) {
            str[length++] = s;
        } else {
            System.out.println("Error: 그룹이 가득 찼습니다!");
        }
    }

    public String[] getMembers() {
        return str;
    }
}
public class HW_1_3 {
    public static void main(String[] args) {
        Group g = new Group(5);
        int i = 0;
        g.setMembers("Alpha");
        g.setMembers("Bravo");
        g.setMembers("Charlie");
        g.setMembers("Delta");
        g.setMembers("Echo");
        g.getMembers()[0] = "Alice";
        for (i = 0; i < 5; i++) {
            System.out.println(g.getMembers()[i]);
        }
    }
}