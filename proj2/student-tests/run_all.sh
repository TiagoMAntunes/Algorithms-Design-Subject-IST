for INPUT in $(ls *.in)
do
    FILENAME=$(echo $INPUT | cut -d '.' -f 1)
    echo "-------- RUNNING ${FILENAME} --------"
    ./proj < $FILENAME.in > $FILENAME.try
    diff $FILENAME.out $FILENAME.try
done