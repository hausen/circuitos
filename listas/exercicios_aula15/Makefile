# This makefile is available under a
# Creative Commons Attribution-Share Alike license (CC BY-SA 2.0).
# http://creativecommons.org/licenses/by-sa/2.0/
# Copyright © 2012 Rodrigo Hausen
NAME=exercicios_aula15
SVGS=$(wildcard images/*.svg)
TIFS=$(wildcard images/*.tif)
IMGS=$(SVGS:.svg=.pdf) $(TIFS:.tif=.PDF)
HOSTREPOS=repository
DIRREPOS=public_html/hausen/courses/circuitos/listas

$(NAME).pdf: $(NAME).tex $(IMGS)
	pdflatex $<
	@if egrep -q '^(.*Rerun .*|No file $(NAME)\.[^.]+\.)$$' $(NAME).log; then pdflatex $<; else echo "done"; fi

clean:
	rm -f $(NAME).pdf *.aux *.log *.nav *.out *.snm *.toc *.vrb $(NAME)-handout.pdf $(NAME)-handout.tif $(IMGS)

images/%.PDF: images/%.tif
	tiff2pdf $< > $@

images/%.pdf: images/%.svg
	inkscape -z `pwd`/$< --export-pdf=`pwd`/$@

upload: $(NAME).pdf
	rm -rf tmp/
	mkdir tmp/
	mv $(NAME).pdf tmp/
	make clean
	echo 'cd $(DIRREPOS) \n mkdir $(NAME) \n cd $(NAME) \n put tmp/$(NAME).pdf \n put *.tex \n put *.sty \n put Makefile \n mkdir images \n cd images \n put images/* \n cd .. \n mkdir circuits \n cd circuits \n put circuits/* \n quit'|sftp $(HOSTREPOS)
	rm -rf tmp/
