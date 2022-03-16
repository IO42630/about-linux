#!/bin/sh

git add 'foo' # files are added in unlocked state
git annex unlock # unlocks all files in path
git annex lock # locks files