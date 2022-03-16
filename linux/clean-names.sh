#!/usr/bin/env bash

IFS=$'\n'

symbols=( "#" "%" "&" "=" "," " " )

for symbol in "${symbols[@]}"; do
    for f in $(find "$1" | grep -e "$symbol"); do
        echo "$f"
        target="s:$symbol:_:g"
        target="$(echo "$f" | sed -e "$target")"
        mv "$f" "$target"
    done
done

# special escape for :
for f in $(find "$1" | grep -e ":"); do
    echo "$f"
    target="s:\::_:g"
    target="$(echo "$f" | sed -e "$target")"
    mv "$f" "$target"
done
