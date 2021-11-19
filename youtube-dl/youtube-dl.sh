

# show different formats aviable
youtube-dl -F https://www.youtube.com/watch?v=J2nbocJfXKk

# pick format
youtube-dl -f 140 https://www.youtube.com/playlist?list=UUSsz5GO1rQjzp1RND7QtEjg









## OPTIONS
# no appendix
--output "%(title)s.%(ext)s"
# limit rate 
-r 100K
# ignore errors
-i

youtube-dl -f 140 -i --output "%(title)s.%(ext)s"



## INSTALL / UPDATE
# remove the old version of youtube-dl
apt-get remove -y youtube-dl 

# download the latest version from the official website
wget https://yt-dl.org/latest/youtube-dl -O /usr/local/bin/youtube-dl

# change the permission of the downloaded file
chmod a+x /usr/local/bin/youtube-dl



apt-get remove -y youtube-dl &
wait; wget https://yt-dl.org/latest/youtube-dl -O /usr/local/bin/youtube-dl &
wait; chmod a+x /usr/local/bin/youtube-dl &
