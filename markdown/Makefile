TEX_SOURCES += $(wildcard *.tex)
MD_SOURCES += $(wildcard *.md)

all: graphblas.pdf graphblas.html

graphblas.html: $(TEX_SOURCES) $(MD_SOURCES) Makefile
	#pandoc -s matrix.md -o matrix.html
	#pandoc -s vector.md -o vector.html
	#pandoc -s index.md -o index.html
	#pandoc -s functional.md  -o functional.html
	#pandoc -s plus.md  -o plus.html
	#pandoc -s multiplies.md  -o multiplies.html
	#pandoc -s minus.md  -o minus.html
	#pandoc -s divides.md  -o divides.html
	#pandoc -s max.md  -o max.html
	#pandoc -s min.md  -o min.html
	#pandoc -s concepts.md  -o concepts.html
	#pandoc -s type_traits.md  -o type_traits.html
	#pandoc -s ops_mxm.md -o ops_mxm.html
	pandoc -s \
				 --toc \
				 -o graphblas.html \
				 metadata.md \
				 intro.md \
				 --toc \
				 --toc-depth=2 \
				 -Vsecnumdepth=2 \
				 --metadata title="GraphBLAS C++ API" \
				 matrix.md \
				 vector.md \
				 index.md \
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
	       --toc \
	       --top-level-division=chapter \
	       -H preamble.tex \
	       -B title.tex \
	       -V geometry:margin=1in \
	       -o graphblas.pdf \
	       metadata.md \
	       intro.md \
	       --toc \
	       --toc-depth=2 \
	       -Vsecnumdepth=2 \
	       matrix.md \
	       vector.md \
	       index.md \
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

