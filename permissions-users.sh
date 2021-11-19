r = 4
w = 2
x = 1

owner group others
750

# Permissions , Users , Groups
# -----------------------------------------------------------------------------------------------------------


# 3 types of permissions: read write execute
# can be written as 3 chars or one number:

#read	write	execute		as 3 chars	as number
 0	0	0		---		0
 0	0	1		--x		1
 0	1	0		-w-		2
 0	1	1		-wx		3
 1	0	0		r--		4
 1	0	1		r-x		5
 1	1	0		rw-		6
 1	1	1		rwx		7

# 3 types of people: owner group others
owner can rwx, group can r-x, others can r-x
rwxr-xr-x 
755

ls -l <file>
drwxr-xr-x  5 user user   4096 Jun 26 23:22  ws
||||||||||- rwx permission of 'others', '-' if missing 
|||||||---- rwx permission of 'group' , '-' if missing
||||------- rwx permission of 'owner' , '-' if missing
|---------- 'd' if dir, '-' if file


chmod u+x hello.sh		# allows to modify single permission
chmod u-x hello.sh		
chmod 666 hello.sh		# quicker, but must overwrite all permissions



passwd					# change password

useradd					# system binary
useradd -m -d /foo			# '-m' create hoem dir in /foou
useradd -s /bin/bash			# specify the user's default shell
useradd -c 'foo'			# extra info about the user

userdel <name>				# delete user
groupdel <name>


adduser					# perl script using 'useradd'
addgroup --gid <ID> <group>		# create group, force gid=ID
adduser <user> <group>			# add user to group			

# switch from user1 to user2 with GUI
xhost +					# allow access to others, to be run in shell of user1
su - user2				# the '-' forces to source the '.bash_profile' of user2
$ export DISPLAY=:0.0			# after becoming user2, it may be necessary to set $DISPLAY variable.