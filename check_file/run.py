import os
import sys
import numpy as np

path = sys.argv[1]

if not os.path.exists("./output"):
	os.mkdir("./output")

for f in os.listdir(path):
	print(f)
	os.system("dmesg -c")
	filename = os.path.join(path, f)
	policy, num = f.split("_")[: 2]
	output_file = "%s_%s_stdout.txt"%(policy, num[:-4])
	dmesg_file = "%s_%s_dmesg.txt"%(policy, num[:-4])
	os.system("./project_1 < %s > %s"%(filename, os.path.join("output", output_file)))
	
	os.system("dmesg | grep Project1 > kernel_log")
	with open(os.path.join("output", dmesg_file), "w") as log_file:
		for i in np.genfromtxt("kernel_log", dtype = np.str, delimiter = "[Project1] ")[:, 1]:
			log_file.write("[Project1] " + i + "\n")
