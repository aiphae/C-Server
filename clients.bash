for N in {1..500}
do
    ruby client.rb $((($N % 6) + 1)) &
done
wait