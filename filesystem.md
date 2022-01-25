#### Directories
Acording to FHS (Filesystem Hierarchy Standard).

| | |
---|---
`/bin`   | basic binaries e.g. `ls` ,  , available in single-user-mode
`/boot`  | what os needs to boot, e.g. bootloaders
`/dev`   | devices (everything is a file)
`/etc`   | system-wide conf
`/home/<user>`    | home directory of the users
`/home/<user>/.conf`   | user dependant config files 
`/lib`   | libraries
`/lib32` | libraries
`/lib64` | libraries
`/media` | system mounted devices
`/mnt`   | user mounted devices
`/opt`   | manually installed software from vendors (e.g. drivers for printers) (also virtualbox)
`/proc`  | processes (everything is a file) for every process running, also `cat /proc/cpuinfo` for info about cpu. 
`/root`  | home dir of root (seprate to ensure it is not modified/deleted)
`/run`   | tempfs (runs in ram), used for proc that start early in bootproces for runtime info.
`/sbin`  | binaries `su` would use , available in single-user-mode
`/srv`   | service data, files to be accessed by clients of hosted server.
`/sys`   | tempfs (runs in ram), used to interact with kernel.
`/tmp`   | temp application data.
`/usr`   | user applications (unix system resource) , non-essential applications.
`/usr/bin`   | reserved for package managers
`/usr/sbin`  |
`/usr/lib`   |
`/usr/local/bin`  | typically compiled programs 
`/usr/local/sbin` |
`/usr/local/lib`  |
`/usr/share`      | larger apps
`/usr/src`        | kernel source & headers
`/var`            | files that expeced to grow
`/var/crash`      | info about crashes
`/var/log`        | logs


