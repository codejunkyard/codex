# Create a folder
mkdir 07_folder

# Create 5 text files inside the folder
for i in {1..5}; do
  echo "This is file $i" > 07_folder/file$i.txt
done

# List the files
ls 07_folder