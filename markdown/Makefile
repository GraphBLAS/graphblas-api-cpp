

all:
	pandoc -s \
         -H preamble.tex \
		     -V geometry:margin=1in \
	       -o matrix.pdf \
				 matrix.md \
				 index.md \

clean:
	rm -fv *.pdf
