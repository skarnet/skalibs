it: EXPORT- .done

EXPORT-: gen-EXPORT
	exec ./gen-EXPORT > EXPORT-

.done: gen-Makefile
	./gen-Makefile > Makefile.real && make -f Makefile.real && : > .done
