#compile
gcc -g -Wall -o bin/daemon src/daemon.c -lm
gcc -g -Wall -o bin/deusVult src/deusVult.c -lm

#start the daemon
./bin/deusVult -rmpipe
./bin/deusVult -mkpipe
./bin/daemon
./bin/deusVult -start


