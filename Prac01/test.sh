
#!/bin/sh

# Create a new file
touch test.txt
# Check that the file exists
if [ -f test.txt ]; then
    echo "File exists"
else
    echo "File does not exist"
fi
# Delete the file
rmsf test.txt

# Run the script
./test.sh





