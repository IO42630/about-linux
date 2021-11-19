# even with multi-arch and stuff
# need to purge configs
dpkg --purge --force-depends libssl1.0.0:i386
dpkg --purge --force-depends libssl1.0.0:amd64
# proceed to download & install stuff
gdebi libssl1.0.0_1.0.1t-1+deb8u5_i386.deb
wget -O skype-install.deb http://www.skype.com/go/getskype-linux-deb
gdebi skype-install.deb
