from grapher import Grapher

g = Grapher(['2 * x', '1 - ((x^2)/factorial(2)) + (x^4)/factorial(4)'],
            lb=-3, ub=3, lol='lower center', title='Taylor Polynomial for cos(x)')
g.plot()
