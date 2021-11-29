TEX_SOURCES += $(wildcard *.tex)
MD_SOURCES += $(wildcard *.md)

graphblas.pdf: $(TEX_SOURCES) $(MD_SOURCES)
	pandoc -s \
	       --toc \
	       -B title.tex \
	       -H preamble.tex \
	       -V geometry:margin=1in \
	       -o graphblas.pdf \
	       intro.md \
	       --toc \
	       --toc-depth=2 \
	       -Vsecnumdepth=2 \
	       matrix.md \
	       index.md \
	       concepts.md

clean:
	rm -fv *.pdf *.html

