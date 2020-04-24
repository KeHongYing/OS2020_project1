import os
import sys
import numpy as np

file_name = os.listdir(sys.argv[1])
folder_1, folder_2 = sys.argv[1], sys.argv[2]

for name in file_name:
	if "stdout" in name:
		file1 = np.genfromtxt(os.path.join(folder_1, name), dtype = np.str, delimiter = " ")[:, 0]
		file2 = np.genfromtxt(os.path.join(folder_2, name), dtype = np.str, delimiter = " ")[:, 0]
		
		if np.any(file1 != file2):
			print("%s is different"%name)

