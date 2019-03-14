FILE=$1

for INPUT in $(ls *.in)
do
    $FILE < $INPUT > $INPUT.res
    diff -q $INPUT.res $INPUT.out
done
