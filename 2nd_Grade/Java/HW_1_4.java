class SecureFile {
    public void open() {
        System.out.println("인증 성공");
    }
}

class EvilFile extends SecureFile {
    @Override
    public void open() {
        System.out.println("인증 없이 파일 열기 성공");
    }
}

public class HW_1_4 {
    public static void main(String[] args) {
        new SecureFile().open();
        new EvilFile().open();
    }
}
