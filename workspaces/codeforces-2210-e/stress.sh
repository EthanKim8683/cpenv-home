make $1.o
for ((i = 1; ; ++i)); do
  echo try $i
  ./$1.o $i || break
done
echo fail $i
