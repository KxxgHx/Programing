import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

class User_Fix {
    private int userId;
    private String userName;

    public User_Fix(int userId, String userName) {
        this.userId = userId;
        this.userName = userName;
    }

    // equals를 id 기준으로만 재정의
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof User_Fix)) return false;
        User_Fix other = (User_Fix) obj;
        return this.userId == other.userId;
    }

    // hashCode도 userId 기준으로 재정의
    @Override
    public int hashCode() {
        return Objects.hash(userId);
    }

    @Override
    public String toString() {
        return "User{Id=" + userId + ", name='" + userName + "'}";
    }
}

public class HW_1_2_Fix {
    public static void main(String[] args) {
        User_Fix u1 = new User_Fix(1, "A");
        User_Fix u2 = new User_Fix(1, "B");
        User_Fix u3 = new User_Fix(2, "C");
        User_Fix u4 = new User_Fix(3, "D");
        User_Fix u5 = new User_Fix(1, "E");

        // HashSet 테스트
        Set<User_Fix> set = new HashSet<>();
        set.add(u1);
        set.add(u2);
        set.add(u3);
        set.add(u4);
        set.add(u5);
        System.out.println("HashSet size (hashCode 재정의): " + set.size());
        System.out.println(set);

        // HashMap 테스트
        Map<User_Fix, String> map = new HashMap<>();
        map.put(u1, "1st");
        map.put(u2, "2nd");
        map.put(u3, "3rd");
        map.put(u4, "4th");
        map.put(u5, "5th");
        System.out.println("HashMap size (hashCode 재정의): " + map.size());
        System.out.println(map);
    }
}
