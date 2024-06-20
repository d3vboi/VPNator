#!/bin/bash

# Define the target directory
TARGET_DIR="$HOME/.config/vpnator"

# Create the directory if it doesn't exist
if [ ! -d "$TARGET_DIR" ]; then
    mkdir -p "$TARGET_DIR"
    echo "Created directory $TARGET_DIR"
else
    echo "Directory $TARGET_DIR already exists"
fi

# Create the .pass file with username and password if it doesn't exist
PASS_FILE="$TARGET_DIR/.pass"
if [ ! -f "$PASS_FILE" ]; then
    echo "Go to https://account.protonvpn.com/account and copy the OpenVPN username and password."
    echo "Enter OpenVPN username: "
    read username

    echo "Enter OpenVPN password (it will not be shown): "
    read -s password

    echo -e "$username\n$password" > "$PASS_FILE"
    echo "Created file $PASS_FILE"
else
    echo "File $PASS_FILE already exists"
fi

# Copy the directories jp/, nl/, and us/ to the target directory
for DIR in jp nl us; 
do
    if [ -d "./$DIR" ]; then
        cp -r "./$DIR" "$TARGET_DIR/"
        echo "Copied ./$DIR to $TARGET_DIR/"
    else
        echo "Directory ./$DIR does not exist"
    fi
done

# Run the compile.sh script
if [ -f "./compile.sh" ]; then
    chmod +x ./compile.sh
    ./compile.sh
    echo "Executed compile.sh"
else
    echo "compile.sh does not exist"
fi

# Move vpnator to /usr/bin/
if [ -f "./vpnator" ]; then
    sudo mv ./vpnator /usr/bin/
    echo "Moved vpnator to /usr/bin/"
else
    echo "vpnator does not exist"
fi
