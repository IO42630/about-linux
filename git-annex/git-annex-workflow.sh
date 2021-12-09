

# have one default repo as archive
git  init
git annex init
# copy all files
# edit .gitignore
# edit .gitattributes
git annex add
git commit

# have a thin repo as mirror (of the newest file)
git clone "target" .
git init
git annex init
git config annex.thin true
# edit .gitignore
# edit .gitattributes
git remote add pool "archive"
git annex sync
git annex get .

