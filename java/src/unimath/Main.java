package unimath;

import unimath.algebra.Addition;
import unimath.algebra.Exponent;
import unimath.algebra.Subtraction;
import unimath.algebra.Term;
import unimath.model.Matrix44D;
import unimath.model.Vector3D;
import unimath.util.AlgoUtils;

public class Main {
    public static void main(String[] args) {

        System.out.println(Vector3D.fromAxisAngles(60, 45, 120));

        Matrix44D matA = new Matrix44D(new double[][]{{1d, 0d, 7d, 10d}, {0d, 1d}, {1d, 1d}});
        System.out.println(matA);

        Matrix44D matB = new Matrix44D(new double[][]{{8d, 6d, 2d}, {4d, 1d, 0d}});
        System.out.println(matB);

        Matrix44D matT = matB.getTransposed();
        System.out.println(matT);

        Matrix44D matC = new Matrix44D();
        matC.loadRotation(new Vector3D(3,5,6), 90);
        System.out.println(matC);

        System.out.println(AlgoUtils.gcd(16, 72));

        Term<Integer> term1 = new Term<>(3);
        Term<Integer> term2 = new Term<>(10);
        Addition<Integer> addition = new Addition<>(term1, term2);
        Addition<Integer> addition1 = new Addition<>(term1, addition);
        Subtraction<Integer> subtraction = new Subtraction<>(addition1, term2);
        Exponent<Integer> exponent = new Exponent<>(subtraction, new Term<>(2));
        System.out.println(addition.computeValue());
        System.out.println(addition);
        System.out.println(addition1.computeValue());
        System.out.println(subtraction.computeValue());
        System.out.println(exponent.computeValue());
        System.out.println(exponent);
    }
}
