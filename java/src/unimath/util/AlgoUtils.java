package unimath.util;

public class AlgoUtils {

    /**
     * Eucledian algorithm
     * @param a
     * @param b
     * @return Greatest common divisor
     */
    public static int gcd(int a, int b) {
        int r = a % b;
        int r2 = b;

        while (r > 0) {
            int tmp = r;
            r = r2 % r;
            r2 = tmp;
        }
        return r2;
    }
}
