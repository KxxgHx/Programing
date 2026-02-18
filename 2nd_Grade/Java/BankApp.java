class Account {
    private int balance = 0;

    public void deposit(int a)
    {
        balance+=a;
    }
    public void withdraw(int a) {
        if (balance >= a)
            balance -= a;
        else
            System.out.println("잔액 부족!");
    }

    public int getBalance() {
        return balance;
    }
}

public class BankApp {
    public static void main(String[] args) {
        Account acc = new Account();
        acc.deposit(1000);
        acc.withdraw(300);
        System.out.println("잔액: " + acc.getBalance());
    }
}