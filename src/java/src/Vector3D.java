import java.util.Collection;

/**
 * @author @Trit0
 * @since September 2022
 */

public class Vector3D {
    public double x = 0, y = 0, z = 0;

    public final static Vector3D zero = new Vector3D(0,0,0);
    public final static Vector3D identity = new Vector3D(1, 1, 1);
    public final static Vector3D left = new Vector3D(-1, 0, 0);
    public final static Vector3D right = new Vector3D(1, 0, 0);
    public final static Vector3D down = new Vector3D(0, -1, 0);
    public final static Vector3D up = new Vector3D(0, 1, 0);
    public final static Vector3D backward = new Vector3D(0, 0, -1);
    public final static Vector3D forward = new Vector3D(0, 0, 1);

    public Vector3D(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vector3D() {}

    public double getNorm() {
       return Math.sqrt((x * x) + (y * y) + (z * z));
    }

    public double getAngleDegree(Vector3D v) {
        double product = this.dotProduct(v);
        double norm = this.getNorm() * v.getNorm();
        double i = UnitUtils.degToRad(product) / UnitUtils.degToRad(norm);
        double c = i == 1d ? 0 : (i == -1d ? Math.PI : Math.acos(i));
        return UnitUtils.radToDeg(c);
    }

    // doubt
    public Vector3D getAngleVector(Vector3D v) {
        double angleX = x == v.x ? 0 : new Vector3D(x, 1, 1).getAngleDegree(new Vector3D(v.x, 1, 1));
        double angleY = y == v.y ? 0 : new Vector3D(1, y, 1).getAngleDegree(new Vector3D(1, v.y, 1));
        double angleZ = z == v.z ? 0 : new Vector3D(1, 1, z).getAngleDegree(new Vector3D(1, 1, v.z));
        return new Vector3D(angleX, angleY, angleZ);
    }

    public void normalize() {
        final double norm = this.getNorm();
        if (norm != 0) {
            x /= norm;
            y /= norm;
            z /= norm;
        }
    }

    public static Vector3D getNormalized(Vector3D v) {
        final double norm = v.getNorm();
        if (norm != 0) {
            v.x /= norm;
            v.y /= norm;
            v.z /= norm;
        }
        return v;
    }

    public boolean sameDirection(Vector3D v) {
        final Vector3D vn = getNormalized(v);
        final Vector3D tn = getNormalized(this);
        return vn.equals(tn);
    }

    public boolean equals(Vector3D v) {
        return (v.x == x) && (v.y == y) && (v.z == z);
    }

    public boolean notEquals(Vector3D v) {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }

    public Vector3D addition(Vector3D v) {
        return new Vector3D(x + v.x, y + v.y, z + v.z);
    }

    public void add(Vector3D v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    public Vector3D sum(Collection<Vector3D> vectors) {
        Vector3D vector3D = new Vector3D();
        for (Vector3D v : vectors) {
            vector3D.add(v);
        }
        return vector3D;
    }

    public Vector3D difference(Vector3D v) {
        return new Vector3D(x - v.x, y - v.y, z - v.z);
    }

    public void subtract(Vector3D v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    public Vector3D multiplyByScalar(double scalar) {
        return new Vector3D(x * scalar, y * scalar, z * scalar);
    }

    public Vector3D divideByScalar(double scalar) {
        return new Vector3D(x / scalar, y / scalar, z / scalar);
    }

    public Vector3D lerp(Vector3D destination, double t) {
        t = Math.min(Math.max(t, 0d), 1d);
        return (this.multiplyByScalar(-t)).addition(destination.multiplyByScalar(t));
    }

    public static Vector3D lerp(Vector3D p1, Vector3D p2, double t) {
        t = Math.min(Math.max(t, 0d), 1d);
        return (p1.multiplyByScalar(-t)).addition(p2.multiplyByScalar(t));
    }

    public double dotProduct(Vector3D v) {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    public Vector3D crossProduct(Vector3D v) {
        return new Vector3D((y * v.z) - (v.y * z), (z * v.x) - (v.z - x), (x * v.y) - (v.x * y));
    }

    public static double determinant(Vector3D v1, Vector3D v2, Vector3D v3) {
        return v1.dotProduct(v2.crossProduct(v3));
    }

    public static Vector3D fromAxisAngles(double xAngleDeg, double yAngleDeg, double zAngleDeg) {
        return new Vector3D(
                Math.cos(UnitUtils.degToRad(xAngleDeg)),
                Math.cos(UnitUtils.degToRad(yAngleDeg)),
                Math.cos(UnitUtils.degToRad(zAngleDeg))
        );
    }

    public boolean isUnitVector() {
        return getNorm() == 1;
    }

    @Override
    public String toString() {
        return "[ " + x + ", " + y + ", " + z + " ]";
    }
}
