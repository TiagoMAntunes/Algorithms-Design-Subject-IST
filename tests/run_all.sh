FILE=$1

for INPUT in $(ls *.txt)
do
    $FILE < $INPUT > $INPUT.res
    diff -q -b $INPUT.res $INPUT.expected
done
