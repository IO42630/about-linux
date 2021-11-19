# Input, Output, Pipes
# -----------------------------------------------------------------------------------------------------------
ls > list.txt				# write output to file
ls >> list.txt				# append instad of overwriting

ls 1> <file>				# write STDOUT to file, 1 can be omitted
ls 2> <file>				# write STDERR to file

ls > <file> 2>&1			# redirect STDOUT to 'file' and redirect STDERR to STDOUT, thus 'file' as well.

sort < list.txt				# input from file, output on screen
sort list.txt				# works just as fine, '<' usually not needed

sort < list.txt > sorted.txt		# input from file, output to file

ls | sort				# pipe, connects commands, print sorted output of ls

ls | head -n 2				# print the first 2 rows of 'ls'
tail -2 <file>				# same as head, note the alternative syntax
nl <file>				# cat but with numbered lines
wc <file>				# returns lines words chars
cut -f <field> -d <delimiter> <file>	# fetches column (field) form file
cut -f 1,3 -d ',' text.txt		# 'hello,this,is' -> 'hello is'

sed 's/search/replace/g' <file>		# stream editor, similar to 'rename' but mods contents instead
uniq <file>				# purge consequent dublicate lines
tac <file>				# cat but prints last line first
awk
diff