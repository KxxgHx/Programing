import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class User {
    private int id;
    private String name;

    public User(int id, String name) {
        this.id = id;
        this.name = name;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (!(obj instanceof User))
            return false;
        User other = (User) obj;
        return this.id == other.id;
    }

    @Override
    public String toString() {
        return "User{id=" + id + ", name='" + name + "'}";
    }
}

public class HW_1_2 {
    public static void main(String[] args) {
        User u1 = new User(1, "A");
        User u2 = new User(1, "B");
        User u3 = new User(2, "C");
        User u4 = new User(3, "D");
        User u5 = new User(1, "E");

        // HashSet 테스트
        Set<User> set = new HashSet<>();
        set.add(u1);
        set.add(u2);
        set.add(u3);
        set.add(u4);
        set.add(u5);
        System.out.println("HashSet size (hashCode 미재정의): " + set.size());
        System.out.println(set);
        // HashMap 테스트
        Map<User, String> map = new HashMap<>();
        map.put(u1, "1st");
        map.put(u2, "2nd");
        map.put(u3, "3rd");
        map.put(u4, "4th");
        map.put(u5, "5th");
        System.out.println("HashMap size (hashCode 미재정의): " + map.size());
        System.out.println(map);
    }
}

