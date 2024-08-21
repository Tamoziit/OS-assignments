USER_NAME=`whoami`

# Get the current hour in 24-hour format
HOUR=$(date +%H)

# Determine the appropriate greeting based on the time of day
if [ $HOUR -ge 0 ] && [ $HOUR -lt 12 ] 
	then
    	GREETING="Good Morning"
elif [ $HOUR -ge 12 ] && [ $HOUR -lt 18 ]
	then
	    GREETING="Good Afternoon"
else
    GREETING="Good Evening"
fi

# Get the current date and time
CURRENT_DATE_TIME=$(date +%c)

# Get the process ID of the terminal
TERMINAL_PID=$$

# Print the greeting along with user's name, current date & time, and terminal process ID
echo "$GREETING, $USER_NAME!"
echo "Current date and time: $CURRENT_DATE_TIME"
echo "Your terminal process ID: $TERMINAL_PID"

