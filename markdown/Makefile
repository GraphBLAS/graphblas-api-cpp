TEX_SOURCES += $(wildcard *.tex)
MD_SOURCES += $(wildcard *.md)

graphblas.pdf: $(TEX_SOURCES) $(MD_SOURCES)
	pandoc -s \
	       --toc \
	       --top-level-division=chapter \
	       -H preamble.tex \
	       -B title.tex \
	       -V geometry:margin=1in \
	       -o graphblas.pdf \
	       intro.md \
	       --toc \
	       --toc-depth=2 \
	       -Vsecnumdepth=2 \
	       matrix.md \
	       vector.md \
	       index.md \
	       functional.md \
	       concepts.md

clean:
	rm -fv *.pdf *.html

