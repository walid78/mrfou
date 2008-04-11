NAME=rapport
VIEWER=evince

all : $(NAME).pdf

$(NAME).pdf : $(NAME).dvi
	dvipdf $(NAME).dvi

$(NAME).ps : $(NAME).dvi
	dvips $(NAME).dvi

$(NAME).dvi :
	make clean
	latex $(NAME)
	latex $(NAME)

clean :
	make cleanps
	rm -f 	$(NAME).ps

cleanps :
	make cleandvi
	rm -f 	*.dvi

cleandvi : 
	rm -f 	*~ *# *.aux *.log *.bbl *.bbg *.blg *.toc *.out

cleantotal :
	make clean
	rm -f $(NAME).pdf

show : 
	make
	make clean
	$(VIEWER) $(NAME).pdf