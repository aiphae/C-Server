for N in {1..250}
do
    ./client $((($N % 6) + 1)) &
done
wait