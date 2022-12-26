### System info parser in plain c (no regex)

Get system info into a nice convinient string of information, without using regex to parse it. The parsing here is done "Manually" as the regex in libc has a lot of memory related problems. Used dynamic allocation only three times and made sure to not have a leaky memory.

### Goal 

This is written to get accurate information on system status and use it along with dwm status bar. Apart from that, one can get information directly from the CLI. 

### Limitations

This is just the beginning of the project, at present it only does two things but if I see things that I don't get easily with things like dwmstatus or other programs that modify the dwm status bar, I will keep adding it. Since functions make use of buffer and pointers to filter information, and it is done on the stack it has some bugs here and there, so not totally safe to use yet. 
