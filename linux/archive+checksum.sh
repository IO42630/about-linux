# Archves and Checksums
# -----------------------------------------------------------------------------------------------------------

# TAR
# combine multiple files into one



# Gzip
# compresses a file
gzip -d file.gz				# '-d' decompress

tar -xf file.tar.gz			# x	extract files
					# v	verbose
					# z	uncompress gz (g)
					# f	param will be file
tar -xf file.tar.xz


zip -r arc.zip <dir>			# compress 'dir' into 'archive.zip'
unzip arc.zip				# unarchive

iat file.img file.iso			# .img -> .iso

unrar x ./archive.rar
cat "xx..md5"	look at md5 (from main server)
md5sum "xx."		extract md5, compare by eye (from mirror)