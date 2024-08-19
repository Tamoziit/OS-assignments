totalSize=0
echo "Non-directory files:"
for file in *
	do
		if [ -f "$file" ]
			then
				echo $file
				fileSize=$(wc -c < "$file")
				totalSize=$(($totalSize + $fileSize))
		fi
	done
	
echo "Total Size of Non-directory files = $totalSize"
		
