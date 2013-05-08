# This makefile is available under a
# Creative Commons Attribution-Share Alike license (CC BY-SA 2.0).
# http://creativecommons.org/licenses/by-sa/2.0/
# Copyright © 2012 Rodrigo Hausen
NAME=aula15
SVGS=$(wildcard images/*.svg)
IMGS=$(SVGS:.svg=.pdf)
include ../Makefile.inc

$(NAME).pdf: aula15-1.pdf aula15-2.pdf aula15-3.pdf aula15-4.pdf aula15-5.pdf aula15-6.pdf aula15-7.pdf aula15-8.pdf aula15-9.pdf
	pdftk $^ cat output $@

aula15-%.pdf: aula15-%.tif
	tiff2pdf $< > $@

clean:
	rm -f $(NAME).pdf aula15-*.pdf $(IMGS)

images/%.pdf: images/%.svg
	inkscape -z `pwd`/$< --export-pdf=`pwd`/$@

upload: $(NAME).pdf
	rm -rf tmp/
	mkdir tmp/
	mv $(NAME).pdf tmp/
	make clean
	echo 'cd $(DIRREPOS) \n mkdir $(NAME) \n cd $(NAME) \n put tmp/$(NAME).pdf \n put *.tex \n put *.sty \n put Makefile \n mkdir images \n cd images \n put images/* \n cd .. \n mkdir circuits \n cd circuits \n put circuits/* \n quit'|sftp $(HOSTREPOS)
	rm -rf tmp/
