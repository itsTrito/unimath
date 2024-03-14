package unimath.algebra;

public class Parenthesis extends AlgebraUnit {

        private final AlgebraUnit a;

        public Parenthesis(AlgebraUnit a) {
            this.a = a;
        }

        @Override
        public String computeValue() {
            return a.computeValue();
        }

        @Override
        public String toString() {
            return String.format("(%s)", a.toString());
        }
}
