#!/bin/bash

# Change the directory if you want to clean up a specific directory
# cd /path/to/your/cpp/project/directory

# Remove the default a.out file if it exists
if [ -f "a.out" ]; then
    echo "Removing a.out"
    rm "a.out"
fi

# Remove any executable files without an extension
for file in *; do
    if [[ -f "$file" && ! "$file" =~ \. ]]; then
        echo "Removing $file"
        rm "$file"
    fi
done

# Remove all directories ending with .dSYM
for dir in *.dSYM; do
    if [ -d "$dir" ]; then
        echo "Removing $dir"
        rm -rf "$dir"
    fi
done

echo "Cleanup complete!"
