# OS 2020 SPRING Project1
**B06902074 KeHongYing**

## Usage
```powersell
# Generate the Makefile
cmake .

# Compile
make

# Execute
sudo ./project_1 < <INPUT FILE>
```

## How to use the script
1. Run `sudo dmesg -c` to clean the log first.
2. Run the main code
```powershell
# For single test data
sudo ./project_1 < <INPUT FILE> > <OUTPUT FILE>

#For all test data
sudo python run.py <INPUT FILE DIRECTORY>
```
3. For single test data, you can run `dmesg | python check_time.py` to check each process running time.
4. For all output file(\*stdout.txt and \*dmesg.txt), you can run `python check_order.py <output> <ANSWER FILE DIRECTORY>` to check.
