if [ -e "$1" ]
	then
		wc=$(wc -w < "$1")
		echo "Word count = $wc"
		cc=$(wc -c < "$1")
		echo "Character count = $cc"
		lc=$(wc -l < "$1")
		echo "Line count = $lc"
	else
		echo "File doesn't exist"
fi
