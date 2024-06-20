for DIR in jp nl us;
do 
  for file in ./$DIR/*
  do
    tail -n 1 "$file" | wc -c | xargs -I {} truncate "$file" -s -{}
    echo "auth-user-pass $HOME/.config/vpnator/.pass" >> "$file"
  done
done
