import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class HashSetDemo {
    public static void main(String[] args) {
        String[] fruits = { "Apple", "Banana", "Grape", "Watermelon" };
        Set<String> h1 = new HashSet<>();
        Set<String> h2 = new HashSet<>();

        for(String s : fruits)
            h1.add(s);
        
        System.out.println(h1);

        h1.add("Banana");
        h1.remove("Grape");
        h1.add(null);

        System.out.println(h1);
        System.out.println(h1.contains("Watermelon"));

        List<String> list = Arrays.asList(fruits);
        h2.addAll(list);
        System.out.println(h2);
    }
}
