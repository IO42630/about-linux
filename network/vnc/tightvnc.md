#### Parameters
* "host" is `192.168.1.90`


### Setup Host
* might be a good idea to create dedicated user for vnc
    * i.e. `guest` so x-session of `user` won't be block the "vnc-x-session".
        * remember to set `useradd -s /bin/bash -m guest`
* install `tightvncviewer`
* run `/usr/bin/tightvncserver`
    * this will create an virtual instance `:1`...`:n` each time
    * they can be accessed by `192.168.1.90:1`
* change pwd if required `vncpasswd`
* kill if requred: `vncserver -kill :1`
* assuming user will be `/home/user/.vnc/startup

### Setup Client
* install `xtightvncviewer` on client
* `xtightvncviewer 192.168.1.90:1`


### Secure
* Host:
    * Start server local only
    * `/usr/bin/tightvncserver -localhost :1`
* Client: 
    * in Terminal A : `ssh user@192.168.1.90 -L 5901:localhost:5901` (for `:1`)
    * in Terminal B : `xtightvncviewer localhost:1`