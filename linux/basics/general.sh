# General 
# -----------------------------------------------------------------------------------------------------------
Ctrl+PgUp                # go on Tab left (Xfce4 terminal)
Ctrl+PgDn                # go on Tab right (Xfce4 terminal)

echo $SHELL                # print current shell, there are other shells besides /bin/bash

echo $$                    # print current process id
bash                    # create new child process
ps --ppid 'id'                # print child processes on 'id' , init has id=1
pwd                    # print working dir

ls -a                    # list all files, also those behind '.'
ls /foo                    # absolute path
ls foo                    # relative path
ls ~                    # home dir
ls .                     # current dir
ls ..                    # parent dir

man 'command'                # manual, within man use /foo to search and 'n' for next resut
echo 'a b' a\ b                # spaces can be protected with '' or \
dmsg                    # view logs




uname -a                # system information
dmesg                        # view logs

STDIN(0)                # data fed into the programm
STDOUT(1)                # output, defaults to terminal
STDERR(2)                # error, defaults to terminal

top                    # system monitor
ps aux                    # processes of current terminal or all with 'aux' option
ps aux | grep 'firefox'            # get info about firefox
kill 'PID'                # kill
kill -9 'PID'                # force kill
CTRL+ALT+F'console'            # go to console
CTRL+ALT+F7                # GUI console

sleep 5 &                # will sleep for 5 sec and return.

CTRL+Z                    # put process in background, will print '[1]+ stopped'
fg 1                    # bring process back in foreground

CTRL+R                    # reverse search: search command history


Ctrl+A                    # goto start of line
Ctrl+E                    # goto end of line
Ctrl+U                    # delete line contents before cursor
Ctrl+K                    # delete line contents after cursor



in command prompt $ indicates what type of shell is active. $ indicates bash (bourne again shell). # may indicate something else.