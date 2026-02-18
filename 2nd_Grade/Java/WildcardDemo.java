class Stats1<T extends Number> {
    T[] nums;

    Stats1(T[] o) {
        nums = o;
    }

    double average() {
        double sum = 0.0;
        for (int i = 0; i < nums.length; i++) {
            sum += nums[i].doubleValue();
        }
        return sum / nums.length;
    }

    boolean isSameAvg(Stats1<?> ob) {
        if(average() == ob.average())
            return true;
        return false;
    }
}

public class WildcardDemo {
    public static void main(String[] args) {
        Integer[] inums = { 1, 2, 3, 4, 5 };
        Stats1<Integer> iob = new Stats1<Integer>(inums);
        double v = iob.average();
        System.out.println("iob average is " + v);

        Double[] dnums = { 1.1, 2.2, 3.3, 4.4, 5.5 };
        Stats1<Double> dob = new Stats1<Double>(dnums);
        double w = dob.average();
        System.out.println("dob average is " + w);
        
        System.out.print("Average of iob and dob ");
        if(iob.isSameAvg(dob))
            System.out.println("are the Same.");
        else
            System.out.println("differ.");
    }
}
