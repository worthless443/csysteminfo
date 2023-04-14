### System info parser in plain c (no regex)

Get system info into a nice convinient string of information, without using regex to parse it. The parsing here is done "Manually" as the regex in libc has a lot of memory related problems. Used dynamic allocation only three times and made sure to not have a leaky memory.

### Goal 

rhis is written to get accurate information on system status and use it along with dwm status bar. Apart from that, one can get information directly from the CLI (and that's the safest way). 

### Limitations

This is just the beginning of the project, at present it only does two things but if I see things that I don't get easily with things like dwmstatus or other programs that modify the dwm status bar, I will keep adding it. Since functions make use of buffer and pointers to filter information, and it is done on the stack it has some bugs here and there, so not totally safe to use yet. 
### Compilation and Installation (Legecy)
```
cd csysteminfo
make
```
you will end up having `st` binary, that's the main binary. also a static `libmst.a`, that's the reusable library

### Compilation and Installation (Legecy)
```bash
./compile install
```
or if you want to enable optimizations (does weird things, not recommanded from me), do 
```bash
CMP_OPTMZ=<level> ./compile install
```
To enable debugging logs, run the commmand with 
```bash
DEBUG=<1|2|3|all> ./compile 
```

### Tests 
The tests check if the int associated with battery percentage is different than what the actual number is.

```bash
./test
```
