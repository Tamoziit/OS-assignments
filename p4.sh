# Check if two arguments (directories) are provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <OS1_directory> <OS2_directory>"
    exit 1
fi

OS1="$1"
OS2="$2"

# Check if both arguments are directories
if [ ! -d "$OS1" ] || [ ! -d "$OS2" ]; then
    echo "Both arguments must be directories."
    exit 1
fi

c=0
# Loop through each file in OS1
for file in "$OS1"/*; do
    filename=$(basename "$file")
    OS2_file="$OS2/$filename"

    # Check if the file exists in OS2 and is identical to the file in OS1
    if [ -e "$OS2_file" ] && cmp -s "$file" "$OS2_file"; then
        echo "Deleting identical file: $OS2_file"
        c=$(($c+1))
        rm "$OS2_file"
    fi
done

if [ $c -eq 0 ]
	then
		echo "No Identical files found"
fi

