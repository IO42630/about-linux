# Java
# -----------------------------------------------------------------------------------------------------------

java Prog > text.txt		# redirects terminal output to .txt
java Prog < text.txt		# uses .txt as input
java Prog1 | Prog2		# uses output from Prog1 as input Prog2


update-alternatives --config java	# list all jdk's, also set default JDK

tar -zxf /home/user/jdk-8u45-linux-x64.tar.gz -C /usr/lib/jvm					# unpack new JDK
update-alternatives --install /usr/bin/java java /usr/lib/jvm/jdk1.8.0_45/bin/java 9000		# install new JDK
update-alternatives --install /usr/bin/javac javac /usr/lib/jvm/jdk1.8.0_45/bin/javac 9000	# install new JDK