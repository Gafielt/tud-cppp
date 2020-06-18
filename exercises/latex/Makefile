.PHONY: all combined publish copy-only-all clean

all: create-pdfs-split

combined: create-pdfs

create-pdfs:
	latexmk -pdf cppp_exercises.tex

create-pdfs-split:
	latexmk -pdf cppp_exercise_basics.tex
	latexmk -pdf cppp_exercise_memory.tex
	latexmk -pdf cppp_exercise_oo.tex
	latexmk -pdf cppp_exercise_advanced.tex
	latexmk -pdf cppp_exercise_c.tex
	latexmk -pdf cppp_exercise_elevator.tex
  
# Build and copy PDF files
publish: create-pdfs cp-only-all

# Copying pdfs to upper directory
cp-only-all: 
	cp cppp_exercise*.pdf ..

# cleaning compiled data except for PDF file
clean:
	@echo "Removing unnecessary compilation data..."
	find . -type f -name '*.aux' -delete
	find . -type f -name '*.log' -delete
	find . -type f -name '*.dvi' -delete
	find . -type f -name '*.lof' -delete
	find . -type f -name '*.lot' -delete
	find . -type f -name '*.toc' -delete
	find . -type f -name '*.out' -delete
	find . -type f -name '*.fls' -delete
	find . -type f -name '*.fdb_latexmk' -delete
	find . -type f -name '*.synctex.gz' -delete

# clean all created data (incl. PDF file)
clean_all: clean
	rm -f cppp_exercise*.pdf

