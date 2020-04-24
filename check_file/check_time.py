import sys
import numpy as np

time_log = np.array([lines.split("[Project1] ")[1].split()[1:] for lines in sys.stdin.readlines()]).astype(np.float)
time = list(map(lambda x: float(x[1]) - float(x[0]), time_log))
time_log -= np.min(time_log)

for i in range(len(time_log)):
	print(time_log[i], time[i])
