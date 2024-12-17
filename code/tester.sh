# a.cpp -> code, naive.cpp -> naive solution, gen.cpp -> generator
g++ a.cpp -std=c++17 -O2 -o a.out
g++ naive.cpp -std=c++17 -O2 -o naive.out
g++ gen.cpp -std=c++17 -O2 -o gen.out
t=1000
for ((i = 1; i <= t; i++)); do
    printf "%s %d\r" "running on test" $i
    ./gen.out > test.txt
    ./a.out < test.txt > out.txt
    ./naive.out < test.txt > ans.txt
    diff -bBq out.txt ans.txt
    if [[ $? != 0 ]]; then
        echo wrong on test $i 
        echo input:
        cat test.txt
        echo output:
        cat out.txt
        echo answer:
        cat ans.txt
        exit
    fi
done
printf "all tests passed"
