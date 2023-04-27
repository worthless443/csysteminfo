csysteminfo
-----------
### System info parser in plain c (no regex)

Get very essential system info into a nice convinient string of information, without using regex to parse it. The parsing here is done "Manually" as the regex in libc has a lot of memory related problems and bugs. As much as I would like to not use dynamic allocations, larger parts of the code didn't help me but got nessitise dynamic allocation, I have tried my best,however, to avoid leaks but bugs in either this program or external libraries make leaks still possible.

### Goal 

this is written solely as a wrapper and parser to system commands or files that hold info about the system and transforming it into easily readable format. To get accurate information on system status, many of the dark bugs needs to be avoided. At the early stages that we are as of now, this can't do a lot, it can so about do very basic things which was intended primarily for my personal usage for viewing system details easily.

## Limitations
it can do,
* parse battery data and show percentage and charging information
* parse memory usage data in MiBs 
* Show most recent processes being run

## Compilation and Installation 
Make sure you have `CC` set to `clang` in config.mk. Using GCC causes nasty bugs in the program. 
```
cd csysteminfo
make
```
you will end up having `st` binary, that's the main binary. also a static `libmst.a`, that's the reusable library

## Running
```
./st -a # show everthing
./st -<b|m|p> --poff <number of recent processes>
```
## Compilation and Installation (Legecy)
```bash
./utils/compile install
```
or if you want to enable optimizations (does weird things, not recommanded from me), do 
```bash
CMP_OPTMZ=<level> ./utils/compile install
```
To enable debugging logs, run the commmand with 
```bash
DEBUG=<1|2|3|all> ./utils/compile 
```

