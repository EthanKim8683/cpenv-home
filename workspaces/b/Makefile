%.out:
	python $*.py

%.:
	for u in $**n; do echo - $$u; python $*.py < $$u; done
