#!/bin/sh













# Filters
# -----------------------------------------------------------------------------------------------------------

grep 'regex' <file>			# full text file search
grep -e					# extended grep
grep -e -n 'foo' <file>			
grep -c					# number of lines that match

# File Operations, File System
# -----------------------------------------------------------------------------------------------------------

file <file>				# return file type, these are determied by header(?), not extension
					# generally everything in linux is a file

cat <file>				# view file contents
cat 'source' >> 'target'		# appends contents of source file to target file

less <file>				# minimal editor, quit with 'q'

touch					# create file
mkdir –pv 'foo/bar'			# will create bar with parent directory foo as needed (-p) and be verbose

rm –d					# remove directory (-d)
rm –r					# remove recursive (includes –d)

cp [opt] <src> <dst>			# copy
cp –r					# recursive, thus dir with contentes

mv [opt] <src> <dst>			# can be used to rename files, dir can be renamed too,
					# however this will not overwrite the dst,
					# and instead place src into dst dir.

mv 'Sy & Unknown'*.m4a 'Sy & Unknown'	# use RexEx, this one moves all m4a files in basedir to target dir.

rename 's/FIND/REPLACE/FLAGS' <file>	# rename
rename 's/  / /' *.mp3			# replace all '  ' with ' ' in all .mp3 files

find <dir>				# returns list of file in <dir>
find <dir> -name <name> -delete		# seek and destroy, finds file with <name> in <dir> and deletes them
find <dir> -name "*.tif" -size -160K -delete 	# delete all .tif files smaller than 160K


jmtpfs -l				# list android devices
jmtpfs -device=2,10 /media/s4mini	# mound android device

mount /dev/sda1 /media/foo

# 2078 is the port, there will be a login thereafter
mount -t davfs https://hos107.unaxus.net:2078 /home/unaxus/
mount -t cifs //192.168.10.1/time /media/time/ -opasswd=qed[4as],sec=ntlm
mount -t hfsplus -o ro,offset=409640 /dev/sda2 /media/apple
mount_afp afp://user:qed[4as]@192.168.10.1/time /media/time


sshfs -p 9430 user@178.83.29.111:/ /home/user/deb35
sshfs user@192.168.44.2:/ /media/mba	# current setup for mounting macbook via ethernet.

ln -s <origin_dir> <link_dir>		# create alia
# 2078 is the port, there will be a login thereafters






	






# X Server , Mouse, Keyboard, Display, Audio
# -----------------------------------------------------------------------------------------------------------


xset m 5 1 		 		# mouse speed (xset what speed accel)

xkbset bell sticky -twokey latchlock feedback led stickybeep	# sticky keys

xrandr --newmode "1920x1080_60.00"  173.00  1920 2048 2248 2576  1080 1083 1088 1120 -hsync +vsync
xrandr --addmode VBOX0 1920x1080_60.00#!/bin/sh
xrandr --output DVI-0 --left-of VGA-0





screen					# start terminal multplexer (multiple windows)
ctrl+a then |				# split vertically (after running screen cmd)
ctrl+a then S				# split horizontaly
ctrl+a then Q				# un-split
ctrl+a then tab				# goto next split
ctrl+a then c				# start session in new split
ctrl+a then space			# next terminal
ctrl+a then backspace 			# prev terminal
ctrl+a then <n>				# goto n-th terminal




# OSX
# -----------------------------------------------------------------------------------------------------------

chflags hidden ~/Documents/
sudo fuse-ext2 -o force /dev/disk2s1 /Volumes/hello/

cp -R FaceTime.app ./clutter/
sudo rm -Rf FaceTime.app/


















# Wildcards
# -----------------------------------------------------------------------------------------------------------

# similar to regex but different in how it uses symbols

*		# zero or more chars
?		# single char
[]		# range of chars
a[p]*.???	# matches apple.jpg



