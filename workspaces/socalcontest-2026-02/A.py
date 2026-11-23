"""
would we ever want to do op 2 when A is the max? not unless we have no op
3's left. A would always be greater if operated on when it was not the max

would we ever want to do op 1 when A is not the max? never. it would always
be optimal to have done it when it was the max (B would be greater) or when
it becomes the max (A would be greater)

so when A is the max, we can do op 1 or op 3, and when B is the max, we can
do op 2 or op 4

would we ever want to do an op 1 before an op 4 if A becomes the max in the
end? no because we could double B's contribution as well if we did if after
the op 4

we should do all the op 4's in the beginning because B's contribution to A
would be greater
"""

import math

O1, O2, O3, O4 = map(int, input().split())


def solve(a0, b0, o1, o2, o3, o4):
    if o1 < 0 or o2 < 0 or o3 < 0 or o4 < 0:
        return 0
    a, b = a0, b0
    while True:
        if a > b:
            if o3 >= 1:
                b += a
                o3 -= 1
            elif o2 >= 1:
                a += b
                o2 -= 1
            elif o1 >= 1:
                a += a
                o1 -= 1
            else:
                break
        else:
            if o4 >= 1:
                b += b
                o4 -= 1
            elif o2 >= 1:
                a += b
                o2 -= 1
            else:
                break
    return a


print(
    f"{
        math.log(
            max(
                solve(2, 1, O1 - 1, O2, O3, O4),
                solve(2, 1, O1, O2 - 1, O3, O4),
                solve(1, 2, O1, O2, O3 - 1, O4),
                solve(1, 2, O1, O2, O3, O4 - 1),
                solve(1, 2, O4, O3, O2, O1 - 1),
                solve(1, 2, O4, O3, O2 - 1, O1),
                solve(2, 1, O4, O3 - 1, O2, O1),
                solve(2, 1, O4 - 1, O3, O2, O1),
            ),
        ):.10f}"
)
print(
    max(
        solve(2, 1, O1 - 1, O2, O3, O4),
        solve(2, 1, O1, O2 - 1, O3, O4),
        solve(1, 2, O1, O2, O3 - 1, O4),
        solve(1, 2, O1, O2, O3, O4 - 1),
        solve(1, 2, O4, O3, O2, O1 - 1),
        solve(1, 2, O4, O3, O2 - 1, O1),
        solve(2, 1, O4, O3 - 1, O2, O1),
        solve(2, 1, O4 - 1, O3, O2, O1),
    )
)
