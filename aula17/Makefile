# This makefile is available under a
# Creative Commons Attribution-Share Alike license (CC BY-SA 2.0).
# http://creativecommons.org/licenses/by-sa/2.0/
# Copyright © 2014 Rodrigo Hausen
NAME=aula17
SVGS=$(wildcard images/*.svg)
IMGS=$(SVGS:.svg=.pdf)
JPGS=$(wildcard images/*.jpg)
JPEGS=$(wildcard images/*.jpeg)

$(NAME).pdf: $(NAME).tex $(IMGS) $(JPGS) $(JPEGS)
	@if [ -f $(NAME).nav ]; then \
		grep inserttotalframenumber $(NAME).nav |sed -e 's/[^0-9]//g' > $(NAME).framesbefore; \
	fi
	pdflatex $<
	@if [ -f $(NAME).nav ]; then \
		grep inserttotalframenumber $(NAME).nav |sed -e 's/[^0-9]//g' > $(NAME).framesafter; \
		diff -q $(NAME).framesbefore $(NAME).framesafter > /dev/null || pdflatex $< ; \
		rm -f $(NAME).framesbefore $(NAME).framesafter; \
	fi
	@grep -q -i '^latex warning:.*rerun' $(NAME).log && pdflatex $< || true
	@grep -q -i '^latex warning:.*rerun' $(NAME).log && pdflatex $< || true

$(NAME).tif: $(NAME).pdf
	convert -density 1200 -compress Group4 -dither FloydSteinberg -type bilevel -monochrome $< $@

clean:
	rm -f $(NAME).pdf *.aux *.log *.nav *.out *.snm *.toc *.vrb *.framesafter *.framesbefore $(NAME)-handout.pdf $(NAME)-handout.tif $(IMGS)

images/%.pdf: images/%.svg
	inkscape -z `pwd`/$< --export-pdf=`pwd`/$@

handout: $(NAME)-handout.pdf $(NAME)-handout.tif

$(NAME)-handout.pdf: $(NAME)-handout.tex
	pdflatex $<

$(NAME)-handout.tif: $(NAME)-handout.pdf
	gs -dNOPAUSE -sDEVICE=tiffg4 -sOutputFile=/tmp/tmp$(NAME)%02d.tiff -dBATCH -r600 $<
	tiffcp /tmp/tmp$(NAME)[0-9][0-9]*.tiff $@
	rm /tmp/tmp$(NAME)[0-9][0-9]*.tiff
