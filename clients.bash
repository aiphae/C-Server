for N in {1..100}
do
    ruby client.rb $((($N % 6) + 1)) &
done
wait