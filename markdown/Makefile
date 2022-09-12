TEX_SOURCES += $(wildcard *.tex)
MD_SOURCES += $(wildcard *.md)

all: graphblas.pdf graphblas.html

graphblas.html: $(TEX_SOURCES) $(MD_SOURCES) Makefile
	pandoc -s \
				 --toc \
				 -o graphblas.html \
				 metadata.md \
				 intro.md \
				 basic_concepts.md \
				 --toc \
				 --toc-depth=2 \
				 -Vsecnumdepth=2 \
				 --metadata title="GraphBLAS C++ API" \
				 matrix.md \
				 vector.md \
				 index.md \
				 hints.md \
				 functional.md \
				 plus.md \
				 multiplies.md \
				 minus.md \
				 divides.md \
				 max.md \
				 min.md \
				 utilities.md \
				 concepts.md \
				 type_traits.md \
				 matrix_traits.md \
				 algorithms.md \
				 multiply.md \
				 ewise_union.md \
				 ewise_intersection.md \
				 assign.md \
				 ops_mxm.md

graphblas.pdf: $(TEX_SOURCES) $(MD_SOURCES) Makefile
	pandoc -s \
	       --top-level-division=chapter \
	       -H preamble.tex \
	       -B title.tex \
	       -V geometry:margin=1in \
	       -o graphblas.pdf \
	       metadata.md \
	       intro.md \
	       basic_concepts.md \
	       --toc \
	       --toc-depth=2 \
	       -Vsecnumdepth=2 \
	       matrix.md \
	       vector.md \
	       index.md \
	       hints.md \
	       views.md \
	       functional.md \
	       plus.md \
	       multiplies.md \
	       minus.md \
	       divides.md \
	       max.md \
	       min.md \
	       utilities.md \
	       concepts.md \
	       type_traits.md \
	       matrix_traits.md \
	       algorithms.md \
	       multiply.md \
	       ewise_union.md \
	       ewise_intersection.md \
	       assign.md \
	       ops_mxm.md

clean:
	rm -fv *.pdf *.html

