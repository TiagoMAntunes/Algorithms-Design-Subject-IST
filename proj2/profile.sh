make profile
./proj < $1
gprof ./proj | gprof2dot | dot -Tpng -o output.png
