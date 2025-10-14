import java.util.HashMap;
import java.util.Map;

public class HashMap1Demo {
    public static void main(String[] args) {
        Map<String, Integer> map = Map.of("Apple", 5, "Banana", 3, "Grape", 10, "Strawberry", 1);

        Map<String, Integer> fruits = new HashMap<>(map);
        System.out.println("# of fruit types: " + fruits.size());
        fruits.remove("Banana");
        System.out.println("# of fruit types: " + fruits.size());
        fruits.put("Mango", 2);
        System.out.println("After adding Mango: " + fruits);

        fruits.clear();
        System.out.println("# of fruit types: " + fruits.size());
    }
}
