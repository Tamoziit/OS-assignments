if test -a $1
	then
    	echo "Last modification time of $1: $(date -r "$1")"
	else
    	echo "File $1 does not exist."
fi

