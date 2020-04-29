import os
import sys
import numpy as np

file_name = os.listdir(sys.argv[1])
folder_1, folder_2 = sys.argv[1], sys.argv[2]

for name in file_name:
	if "dmesg" in name:
		dmesg1 = np.argsort(np.genfromtxt(os.path.join(folder_1, name), dtype = np.str, delimiter = " ")[:, 1])
		#stdout = np.argsort(np.genfromtxt(os.path.join(folder_1, name.split("dmesg")[0] + "stdout.txt"), dtype = np.str, delimiter = " ")[:, 0])
		dmesg2 = np.argsort(np.genfromtxt(os.path.join(folder_2, name), dtype = np.str, delimiter = " ")[:, 1])
		
		if np.any(dmesg1 != dmesg2):
			print("%s dmesg is different"%name)
			print(dmesg, dmesg1)

	if "stdout" in name:
		file1 = np.genfromtxt(os.path.join(folder_1, name), dtype = np.str, delimiter = " ")[:, 0]
		file2 = np.genfromtxt(os.path.join(folder_2, name), dtype = np.str, delimiter = " ")[:, 0]

		if np.any(file1 != file2):
			print("%s stdout is different"%name)

