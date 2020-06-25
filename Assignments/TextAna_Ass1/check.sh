#!/bin/sh

if [ ! -d "out" ]
then
    echo "Creating out/ directory"
    mkdir "out"
fi

for text in data/*.txt
do
    num=$(basename "$text" .txt)

    echo "$text"
    
    # expected output
    sed -e '1,/\*\*\* START OF/ d' -e '/\*\*\* END OF/,$ d' < "$text" | tr 'A-Z' 'a-z' | tr -cs "a-z0-9\'-" "\n" | grep '..' | sed -f stop.sed | ./stem | sort | uniq -c | sort -k1nr -k2 | head -n 100 > out/"$num".exp
    
    # observed output
    ./tw 100 "$text" > out/"$num".out

    if ! diff "out/$num.exp" "out/$num.out" > /dev/null
    then
        echo "expected and observed differ for $text"
    fi
done
