/**
 * @author @Trit0
 * @since October 2022
 */
public class Matrix44D {
    public double[][] matrix = new double[4][4];

    public Matrix44D() {}

    public Matrix44D(double[][] tab) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (i < tab.length && j < tab[i].length) {
                    this.matrix[i][j] = tab[i][j];
                }
            }
        }
    }

    public Matrix44D(Matrix44D mat) {
        this.copy(mat);
    }

    public double[] getRow(int index) {
        if (index < matrix.length) {
            return matrix[index];
        }
        return new double[4];
    }

    public double[] getColumn(int index) {
        double[] colTab = new double[matrix[0].length];
        if (index < matrix[0].length) {
            for (int i = 0; i < colTab.length; i++) {
                colTab[i] = matrix[i][index];
            }
        }
        return colTab;
    }

    public double getAt(int rowIndex, int colIndex) {
        double[] row = getRow(rowIndex);
        if (colIndex < row.length) {
            return row[colIndex];
        }
        return 0d;
    }

    /**
     * Multiply two matrices.
     * Matrices are row-major, i.e., { { row0 }, { row1 }, ... }.
     * @param otherMatrix matrix to compose
     * @return The result matrix of the multiplication A x B
     */
    public Matrix44D composition(Matrix44D otherMatrix) {
        if (this.matrix[0].length != otherMatrix.matrix.length) {
            return new Matrix44D();
        }

        Matrix44D newMatrix = new Matrix44D();
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < otherMatrix.matrix[0].length; j++) {
                for (int k = 0; k < this.matrix.length; k++) {
                    newMatrix.matrix[i][j] += this.matrix[i][k] * otherMatrix.matrix[k][j];
                }
            }
        }
        return newMatrix;
    }

    public Vector3D vectorialProduct(Vector3D v) {
        Vector3D vector = new Vector3D(0, 0, 0);

        vector.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z;
        vector.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z;
        vector.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z;

        return vector;
    }

    public Matrix44D scalarProduct(double d) {
        Matrix44D newMatrix = new Matrix44D();
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < this.matrix[0].length; j++) {
                newMatrix.matrix[i][j] *= d;
            }
        }
        return newMatrix;
    }

    public void copy(Matrix44D mat) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                matrix[i][j] = mat.matrix[i][j];
            }
        }
    }

    public void transpose() {
        swap(0, 1, 1, 0);
        swap(0, 2, 2, 0);
        swap(0, 3, 3, 0);
        swap(1, 2, 2, 1);
        swap(1, 3, 3, 1);
        swap(2, 3, 3, 2);
    }

    public Matrix44D getTransposed() {
        Matrix44D mat = new Matrix44D(this);
        mat.transpose();
        return mat;
    }

    public void swap(int x1, int y1, int x2, int y2) {
        if (x1 < matrix.length && x2 < matrix.length && y1 < matrix[0].length && y2 < matrix[0].length) {
            double tmp = matrix[x1][y1];
            matrix[x1][y1] = matrix[x2][y2];
            matrix[x2][y2] = tmp;
        }
    }

    public void loadIdentity() {
        matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1d;
        matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[1][0] = matrix[1][2] = matrix[1][3] = matrix[2][0] = matrix[2][1] = matrix[2][3] = matrix[3][0] = matrix[3][1] = matrix[3][2] = 0d;
    }

    public void loadOrthogonal(double right, double bottom) {
        matrix[0][0] = 2d / right;
        matrix[1][1] = 2d / -bottom;
        matrix[2][2] = matrix[3][0] = -1d;
        matrix[3][1] = matrix[3][3] = 1d;
        matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[1][0] = matrix[1][2] = matrix[1][3] = matrix[2][0] = matrix[2][1] = matrix[2][3] = matrix[3][2] = 0d;
    }

    public void loadPerspective(double right, double top, double near, double far) {
        matrix[0][0] = near / right;
        matrix[1][1] = near / top;
        matrix[2][2] = -(far + near) / (far - near);
        matrix[2][3] = -1d;
        matrix[3][2] = (-2d * far * near) / (far - near);
        matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[1][0] = matrix[1][2] = matrix[1][3] = matrix[2][0] = matrix[2][1] = matrix[3][0] = matrix[3][1] = matrix[3][3] = 0d;
    }

    public void loadView(Vector3D front, Vector3D side, Vector3D top) {
        matrix[0][0] = side.x;
        matrix[1][0] = side.y;
        matrix[2][0] = side.z;

        matrix[0][1] = top.x;
        matrix[1][1] = top.y;
        matrix[2][1] = top.z;

        matrix[0][2] = -front.x;
        matrix[1][2] = -front.y;
        matrix[2][2] = -front.z;

        matrix[3][3] = 1d;
        matrix[0][3] = matrix[1][3] = matrix[2][3] = matrix[3][0] = matrix[3][1] = matrix[3][2] = 0d;
    }

    public void loadRotationX(double angleDeg) {
        matrix[0][0] = 1d;
        matrix[0][1] = matrix[0][2] = matrix[1][0] = matrix[2][0] = 0d;
        matrix[1][1] = Math.cos(angleDeg);
        matrix[1][2] = -Math.sin(angleDeg);
        matrix[2][1] = Math.sin(angleDeg);
        matrix[2][2] = Math.cos(angleDeg);
    }

    public void loadRotationY(double angleDeg) {
        matrix[0][0] = Math.cos(angleDeg);
        matrix[0][1] = matrix[1][0] = matrix[1][2] = matrix[2][1] = 0d;
        matrix[0][2] = Math.sin(angleDeg);
        matrix[1][1] = 1d;
        matrix[2][0] = -Math.sin(angleDeg);
        matrix[2][2] = Math.cos(angleDeg);
    }

    public void loadRotationZ(double angleDeg) {
        matrix[0][0] = Math.cos(angleDeg);
        matrix[0][1] = -Math.sin(angleDeg);
        matrix[0][2] = matrix[1][2] = matrix[2][0] = matrix[2][1] = 0d;
        matrix[1][0] = Math.sin(angleDeg);
        matrix[1][1] = Math.cos(angleDeg);
        matrix[2][2] = 1d;
    }

    public void loadRotation(Vector3D axis, double angleDeg) {
        axis.normalize();
        double c = Math.cos(angleDeg);
        double s = Math.sin(angleDeg);
        double ic = -c;

        matrix[0][0] = axis.x * axis.x * ic + c;
        matrix[1][1] = axis.y * axis.y * ic + c;
        matrix[2][2] = axis.z * axis.z * ic + c;

        matrix[0][1] = axis.x * axis.y * ic + axis.z * s;
        matrix[1][0] = axis.x * axis.y * ic - axis.z * s;

        matrix[0][2] = axis.x * axis.z * ic + axis.y * s;
        matrix[2][0] = axis.x * axis.z * ic - axis.y * s;

        matrix[1][2] = axis.y * axis.z * ic - axis.x * s;
        matrix[2][1] = axis.y * axis.z * ic + axis.x * s;

        matrix[0][3] = matrix[1][3] = matrix[2][3] = matrix[3][0] = matrix[3][1] = matrix[3][2] = matrix[3][3] = 0d;
    }

    public void loadScaling(double x, double y, double z) {
        matrix[0][0] = x;
        matrix[1][1] = y;
        matrix[2][2] = z;
        matrix[3][3] = 1d;
        matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[1][0] = matrix[1][2] = matrix[1][3] = matrix[2][0] = matrix[2][1] = matrix[2][3] = matrix[3][0] = matrix[3][1] = matrix[3][2] = 0d;
    }

    @Override
    public String toString() {
        StringBuilder value = new StringBuilder();
        for (double[] row : this.matrix) {
            value.append("[ ");
            for (double val : row) {
                value.append(val).append(" ");
            }
            value.append("]\n");
        }
        return value.toString();
    }
}
