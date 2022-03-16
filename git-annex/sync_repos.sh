#!/bin/sh

cd /media/home
git annex add . # 1. add the file (to thin repo)
git commit -m "adding new files in /media/home" # 2. commit the file
git annex sync --content # 3. pull content from all remotes

cd /pool/home
git annex add .
git commit -m "adding new files in /pool/home"
git annex sync --content