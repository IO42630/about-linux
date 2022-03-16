# Network
# -----------------------------------------------------------------------------------------------------------

ping -c 3 'url'             # ping site 3 times
traceroute 'url'            # print list of stations to 'addr'
tracepath 'url'             # basic traceroute
mtr 'url'                   # gui tool, combines 'ping' and 'traceroute'
host "url or ip"            # dns lookup, returns ip or url
whois                       # full whois lookup

ifconfig
netstat -r                  # routing table
netstat -p                  # ?
netstat -s                  # ?

wget 'url'                  # copy site to home directory

ssh user@localhost -p 9430      # connect via secure shell

ferm -l /root/firewall-files/ferm-default.conf      # view firewall rules

rsync -urvtW /home/user/user-sync/ /home/user/deb35/home/user/

nmap -sn 192.168.44.*       # ping scan (from zenmap)



# Wireless Config
# -----------------------------------------------------------------------------------------------------------

/sbin/iw dev                # show wireless dev name
ip link set 'name' up       # put interface up
/sbin/iw 'name' link        # show status?
/sbin/iw 'iface' scan       # return the (wireless) networks the iface discovers

wpa_passphrase 'SSID' 'pwd' /etc/wpa_supplicant.conf      # create requierd .conf file
wpa_supplicant -B -i wlp7s0 -c /etc/wpa_supplicant.conf      # init wpa_supp, -B run in background, -i interface , -c config file.

iface wlp7s0 inet dhcp      # in /network/interfaces write so network-manager stops messing with the interface:

dhclient wlp7s0             # use dhcp , no /etc/network/interfaces required ;-)

nmcli                       # network manager cli
nmcli dev status            #