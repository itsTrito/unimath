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
    }
}
