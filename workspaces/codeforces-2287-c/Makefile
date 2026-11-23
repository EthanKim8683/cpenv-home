%.o: %.cpp
	g++ -O2 -std=c++23 -Wall -Wextra -pedantic -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -o $@ $^
.PRECIOUS: %.o

%.out: %.o
	./$^

%.: %.o
	for u in $**n; do echo - $$u; ./$^ < $$u; done
