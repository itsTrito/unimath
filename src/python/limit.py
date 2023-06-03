from typing import List
from models.point2d import Point2Df


def limits(points: List[Point2Df], limit: Point2Df):
    print(points)
    found = False
    i = 0
    if (limit.x == None):
        points.sort(key=lambda p: p.y)
        while not found and i < len(points):
            if points[i].y < limit.y:
                i += 1
            else:
                found = True
        before = points[:i]
        after = points[i:]
        if len(before) == 0 or len(after) == 0:
            return "Not in range"
        return round(before[len(before) - 1].x) if round(before[len(before) - 1].x) == round(after[0].x) else "No limit"
    else:
        points.sort(key=lambda p: p.x)
        while not found and i < len(points):
            if points[i].x < limit.x:
                i += 1
            else:
                found = True
        before = points[:i]
        after = points[i:]
        if len(before) == 0 or len(after) == 0:
            return "Not in range"
        return round(before[len(before) - 1].y) if round(before[len(before) - 1].y) == round(after[0].y) else "No limit"


def sLim(before: Point2Df, after: Point2Df, limit: Point2Df) -> Point2Df:
    dif = difference(before, after)
    if limit.x == None:
        difY = abs(before.y - limit.y)
        limit.x = (difY * dif.x) / dif.y
        return add(before, Point2Df(limit.x, difY))
    else:
        difX = abs(before.x - limit.x)
        limit.y = (difX * dif.y) / dif.x
        return add(before, Point2Df(difX, limit.y))


def difference(p1: Point2Df, p2: Point2Df) -> Point2Df:
    return Point2Df(abs(p1.x - p2.x), abs(p1.y - p2.y))


def add(p1: Point2Df, p2: Point2Df) -> Point2Df:
    return Point2Df(abs(p1.x + p2.x), abs(p1.y + p2.y))


# mList = [Point2Df(-8.1, -0.14), Point2Df(-8.01, -0.09), Point2Df(-7.999, -0.01), Point2Df(-8.001, -0.02),
#          Point2Df(-7.99, -0.07),
#          Point2Df(-7.9, -0.11)]
mList = [Point2Df(0.9, -7.11), Point2Df(0.99, -6.11), Point2Df(0.999, -6.01), Point2Df(1.001, -5.99),
         Point2Df(1.01, -5.89),
         Point2Df(1.1, -4.89)]
print(limits(mList, Point2Df(None, -6)))


# print(sLim(Point2Df(-7.9, -0.11), Point2Df(-8.1, -0.14), Point2Df(-8.0, None)))
