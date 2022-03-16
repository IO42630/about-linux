Add `/home/user/.local/share/applications/idea.desktop`
with:

    [Desktop Entry]
    Version=1.0
    Type=Application
    Name=IDEA
    Icon=/home/user/app/idea/bin/idea.svg
    Exec="/home/user/app/idea/bin/idea.sh" %f
    Categories=Development;IDE;
    Terminal=false

Alternatively place in `/usr/share/applications` to show for all users.