# This makefile is available under a
# Creative Commons Attribution-Share Alike license (CC BY-SA 2.0).
# http://creativecommons.org/licenses/by-sa/2.0/
# Copyright © 2012 Rodrigo Hausen
NAME=aula2
SVGS=$(wildcard images/*.svg)
IMGS=$(SVGS:.svg=.pdf)
include ../Makefile.inc

$(NAME).pdf: $(NAME).tex $(IMGS)
	pdflatex $<

clean:
	rm -f $(NAME).pdf *.aux *.log *.nav *.out *.snm *.toc *.vrb $(NAME)-handout.pdf $(NAME)-handout.tif $(IMGS)

images/%.pdf: images/%.svg
	inkscape -z `pwd`/$< --export-pdf=`pwd`/$@

handout: $(NAME)-handout.pdf $(NAME)-handout.tif

$(NAME)-handout.pdf: $(NAME)-handout.tex
	pdflatex $<

$(NAME)-handout.tif: $(NAME)-handout.pdf
	gs -dNOPAUSE -sDEVICE=tiffg4 -sOutputFile=/tmp/tmp$(NAME)%02d.tiff -dBATCH -r600 $<
	tiffcp /tmp/tmp$(NAME)[0-9][0-9]*.tiff $@
	rm /tmp/tmp$(NAME)[0-9][0-9]*.tiff

upload: $(NAME).pdf
	rm -rf tmp/
	mkdir tmp/
	mv $(NAME).pdf tmp/
	make clean
	echo 'cd $(DIRREPOS) \n mkdir $(NAME) \n cd $(NAME) \n put tmp/$(NAME).pdf \n put *.tex \n put *.sty \n put Makefile \n mkdir images \n cd images \n put images/* \n cd .. \n quit'|sftp bmrepos
	rm -rf tmp/
