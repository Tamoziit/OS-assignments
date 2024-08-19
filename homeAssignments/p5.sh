if [ $# -ne 1 ]
	then
		echo "Usage: $0 'expression'"
	else
		result=`echo "scale=4; $1" | bc`
		echo "Result = $result"
fi
