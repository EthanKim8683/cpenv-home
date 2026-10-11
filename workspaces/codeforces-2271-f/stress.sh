make A.o
for((i=1;;i++));do
	echo "$i"
	./A.o "$i"
done
