#!bin/bash
source=/media/share/
target=./merge-target/home/

# SYNOPSIS
# for each file
#	if file exist in both
#		if checksum same
#			if source older
#				delete destination
#				move source to destination
#			if destination older
#				delete source
#		if checksum not same
#			do nothing
#	if file exists in source only
#		move source to destination
#	if file exists in destination only
#		do nothing


#
isFileExists () {
	if [ -f "$1" ];
	then
		echo 1
	else 
		echo 0
	fi
}

# move while creating parent dir if missing
move () {
	src="$1"
	des="$2"
	if [ $(isFileExists $des) == 0 ];
	then
		echo "making dir for $des"
		mkdir -p "$(dirname "$des")"
	fi
	mv "$src" "$des"
}


# for each file
find $source -type f | while read file
do
	srcFile=$file
	fileName=${file/"$source"}
	desFile=$target$fileName
	
	srcFileExists=$( isFileExists "$srcFile" )
	desFileExists=$( isFileExists "$desFile" )
	
	if [ $srcFileExists == 1 ] && [ ! -s "$srcFile" ];
	then
		echo "size zero -> deleting src ($fileName)" 
		rm "$srcFile"
		continue
	fi
	
	if [ $desFileExists == 1 ] && [ ! -s "$desFile" ];
	then
		echo "size zero -> deleting des ($fileName)" 
		rm "$desFile"
		continue
	fi


	# if file exist in both
	if [ $srcFileExists == 1 ] && [ $desFileExists == 1 ];
	then
		srcMd5=$(md5sum "$srcFile" | cut -d ' ' -f 1)
		desMd5=$(md5sum "$desFile" | cut -d ' ' -f 1)
		# if checksum same
		if [ "$srcMd5" == "$desMd5" ];
		then
			srcFileMDate=$(stat -c "%Y" "$srcFile")
			desFileMDate=$(stat -c "%Y" "$desFile")
			# if source older
			if [ $srcFileMDate -lt $desFileMDate ];
			then
				echo "same md5, src older -> overwriting des ($fileName)"
				mv -f "$srcFile" "$desFile"
			# if target older
			else
				echo "same md5, des older -> deleting src ($fileName)" 
				rm "$srcFile"
			fi
		# if checksum not same
		else
			# do nothing
			echo "diff md5 -> ignore ($fileName)" 
		fi
	fi

	# if file exists in source only
	if [ $srcFileExists == 1 ] && [ $desFileExists == 0 ];
	then
		echo "file in src only -> moving to des ($fileName)"
		move "$srcFile" "$desFile"
	fi

	# if file exists in destination only
	if [ $srcFileExists == 0 ] && [ $desFileExists == 1 ];
	then
		# do nothing
		echo "file in des only -> ignore ($fileName)"
	fi
	
	

done

# delete empty dirs
find "$source" -empty -type d -delete
