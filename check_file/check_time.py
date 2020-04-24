import sys

print(list(map(lambda x: float(x[1]) - float(x[0][:-1]), [lines.split("[Project1] ")[1].split()[1:] for lines in sys.stdin.readlines()])))
