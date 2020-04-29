# OS 2020 SPRING Project1
**B06902074 KeHongYing**

## Environment
- OS: Ubuntu 16.04
- GCC version: 5.4.0
- cmake version: 3.5.1(minimum required: 2.8)
- python version: 3.5.2(for checking script, not necessary)

## Usage
```powershell
# Generate the Makefile
cmake .

# Compile
make

# Execute
sudo ./project_1 < <INPUT FILE>
```

## How to use the script
```powershell
# install the require package
sudo pip3 install -r requirement.txt

# clean the dmesg log
sudo dmesg -c

# For single test data
sudo ./project_1 < <INPUT FILE> > <OUTPUT FILE>

# For all test data, output will be save in output/
sudo python3 run.py <INPUT FILE DIRECTORY>

# To check each process time for sigle file
dmesg | grep Project1 python3 check_time.py

# Or
python3 check_time.py < <dmesg FILE>

# To check correctness, prepare a correct answer
python3 check_order.py <OUTPUT FILE DIRECTORY> <ANSWER FILE DIRECTORY>
```
