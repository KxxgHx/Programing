import java.util.ArrayList;
import java.util.List;

public class ArrayListDemo {
    public static void main(String[] args) {
        List<String> list = List.of("Grandeur", "Sonata", "Avante", "Genesis", "Soul");

        System.out.println(list.indexOf("Sonata"));
        System.out.println(list.contains("Santa Fe"));

        List<String> cars1 = new ArrayList<>(list);
        cars1.add("Santa Fe");
        cars1.removeIf(c -> c.startsWith("So"));
        cars1.replaceAll(s -> "New " + s);
        cars1.forEach(s -> System.out.print(s + " "));
        System.out.println();

        cars1.clear();
        System.out.println(cars1.isEmpty());
    }
}
