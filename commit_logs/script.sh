aaa="commitlog"
ls -d */ | while read line;
  do
    echo "./$line"
     name=$(echo "$(basename $line)$aaa" | tr "[:upper:]" "[:lower:]");
    cd ./$line;
    git log > ../$name;
    cd ..;
  done

