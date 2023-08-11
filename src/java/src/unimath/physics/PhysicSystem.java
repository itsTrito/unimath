package unimath.physics;

import java.util.ArrayList;
import java.util.Arrays;

public class PhysicSystem {
    private final ArrayList<Strength> externalStrengths = new ArrayList<>();

    public PhysicSystem(Strength... strengths) {
        externalStrengths.addAll(Arrays.asList(strengths));
    }
}
