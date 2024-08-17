var=$1
while [ $var -le $2 ]
do
    flag1=0
    flag3=0

    # Check if even
    if [ $(($var % 2)) -eq 0 ]; then
        flag1=1
        if [ $var -eq 2 ]; then
            flag3=1
        fi
    fi

    # Check if prime (for odd numbers and 2)
    if [ $var -gt 2 ]; then
        c=0
        i=2
        while [ $i -le $(echo "sqrt($var)" | bc) ]
        do
            if [ $(($var % $i)) -eq 0 ]; then
                c=$(($c + 1))
                break
            fi
            i=$(($i + 1))
        done
        if [ $c -eq 0 ]; then
            flag3=1
        fi
    fi

    # Output the result
    if [ $flag1 -eq 1 ]; then
        if [ $flag3 -eq 1 ]; then
            echo "$var - Even & Prime"
        else
            echo "$var - Even"
        fi
    elif [ $flag3 -eq 1 ]; then
        echo "$var - Odd & Prime"
    else
        echo "$var - Odd"
    fi

    var=$(($var + 1))
done

