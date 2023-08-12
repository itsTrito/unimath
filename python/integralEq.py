from utils.var_taker import varf_input

# Notes integralEq.md


def integral(minimum: float, maximum: float, c: float) -> float:
    return (c*maximum) - (c * minimum)


mini: float = varf_input("min")
maxi = varf_input("max")
con = varf_input("const")

print(integral(mini, maxi, con))
