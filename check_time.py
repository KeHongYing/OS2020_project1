import sys
import numpy as np

print(line)
try:
	# for dmesg rediirect
	time_log = np.array([lines.split("[Project1] ")[1].split()[1:] for lines in line]).astype(np.float)
except:
	# for *_dmesg.txt
	time_log = np.array([lines.split("[Project1] ")[0].split()[1:] for lines in line]).astype(np.float)

time = list(map(lambda x: float(x[1]) - float(x[0]), time_log))
time_log -= np.min(time_log)

for i in range(len(time_log)):
	print(time_log[i], time[i])
