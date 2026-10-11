%.o: %.cpp
	g++ -g -O2 -std=c++23 -fsanitize=undefined -Wall -Wextra -pedantic -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -D_GLIBCXX_DEBUG -o $@ $^
.PRECIOUS: %.o

%.out: %.o
	./$^

%.: %.o
	for u in $**n; do echo - $$u; ./$^ < $$u; done
