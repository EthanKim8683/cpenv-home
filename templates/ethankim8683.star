files = {
    "sol.cpp": """#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  //
}""",
    "Makefile": """INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \\
		-DETHANKIM8683 \\
		-DU=U \\
		-D_GLIBCXX_DEBUG \\
		-O0 \\
		-g \\
		-std=c++20 \\
		-isystem/opt/homebrew/include \\
		-L/opt/homebrew/lib \\

outputs/%.txt: inputs/%.txt sol
	mkdir -p outputs
	./sol < $< > $@
	cat $@

test: $(OUTPUTS)

clean:
	rm -f sol
	rm -rf outputs

force_test:
	$(MAKE) clean
	$(MAKE) test""",
}
for i, sample in enumerate(problem["samples"]):
    files["inputs/%d.txt" % (i + 1)] = sample["input"]
