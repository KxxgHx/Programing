import java.util.Arrays;
import java.util.List;

public class ListDemo{
    public static void main(String[] args) {
        String[] animals1 = {"Deer","Tiger","Seal","Bear"};
        List<String> animals2 = Arrays.asList(animals1);
        animals2.set(1, "Parrot");
        //animals2.add(0,"Wolf"); (Compile Error)

        for(String s : animals2)
            System.out.print(s + ", ");
        System.out.println();

        String[] animals3 = animals2.toArray(new String[0]);
        for (int i = 0; i < animals3.length; i++) {
            System.out.print(animals3[i] + ", ");
        }
        System.out.println();
        List<String> car = List.of("Grandeur", "Sonata", "Avante", "Genesis");
        car.forEach(s -> System.out.print(s + " "));
        //car.set(1,"Santa Fe"); (Compile Error)
        //List<Object> objects = List.of("a",null); (Compile Error)
    }
}