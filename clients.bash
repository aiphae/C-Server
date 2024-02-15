for N in {1..250}
do
    ruby client.rb $((($N % 6) + 1)) &
done
wait