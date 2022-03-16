#!/bin/sh

# have one default repo as archive
git  init
git annex init
# copy all files
# edit .gitignore
# edit .gitattributes
git annex add
git commit -m "foo"

# have a thin repo as mirror (of the newest file)
git clone "target" .
git init
git annex init
git config annex.thin true
# edit .gitignore
# edit .gitattributes
git remote add pool "archive"
git annex sync --content
git annex get .



# mount sshfs in windows
net use H: \\sshfs.r\user@192.168.1.122\media\home

# Troubleshooting
# broken links are fixe in a pre-commit hook, thus commiting helps sometimes