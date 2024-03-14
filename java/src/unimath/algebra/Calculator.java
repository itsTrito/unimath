package unimath.algebra;

import java.util.Scanner;

public class Calculator {

    public void run() {
        Interpreter interpreter = new Interpreter();
        boolean running = true;
        Scanner scanner = new Scanner(System.in);
        while (running) {
            System.out.print(">> ");
            String input = scanner.nextLine();
            if (input.equals("exit")) {
                running = false;
            } else {
                try {
                    String value = interpreter.evaluate(input);
                    System.out.println(value);
                } catch (Exception e) {
                    System.out.println("Invalid expression");
                    System.out.println(e.toString());
                }
            }
        }
    }
}
