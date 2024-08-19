c=0
for file in [aeiouAEIOU]*; do
    # Check if there are any matches
    if [ -e "$file" ]; then
    	c=$((c + 1))
        echo "$file"
    fi
done

if [ $c -eq 0 ]
	then
		echo "No Files starting with vowels under pwd"
fi
