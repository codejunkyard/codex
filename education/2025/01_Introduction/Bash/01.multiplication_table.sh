# Create a 12x12 multiplication table
for i in {1..12}; do
  for j in {1..12}; do
    printf "%6d" $((i*j))
  done
  echo
done > 01_table.txt
cat 01_table.txt