import java.util.Scanner;

public class HelloWorld{
    public static void  main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        int c = sc.nextInt();
        int d = sc.nextInt();
        System.out.format("%d %d %d %d", d, c, b, a);
    }
}