1. Exercises: cppp_exercises.pdf
2. Slides: cppp_lecture.pdf

## Changes on 2018-08-24

### Slides

* p. 73: Clarify that int *iP; is a definition.
* p. 77: Fix formatting of pointer type: int* -> int *
* p.119: Destroying floor [1] -> Destroying floor [0]
* p.158: HiWi -> StudentAssistant

### Exercises
* Ex 2.3: Deklaration -> Definition
* Ex 3.1: Deklaration -> Schnittstelle
* Ex 18.1: Deklaration -> Definition

## Changes on 2018-08-23

### Slides

* p.45: Bugfix in "declaration vs. definition": "int x;"  is always a definition. Exception: global variables prefixed with "extern".
        Added links to cppreference.com that contain the full information.
* p.50: building -> hbi
        Building.h -> Building.hpp
* p.62: Insert missing do keyword in do-while loops
* p.80: Bugfix 'int *j = &i;' violates const correctness (invalid conversion from const int* to int).

### Exercises

* Add archive containing project templates in *exercises/tools/codelite*
  * See readme file for instructions on how to enable the templates in Codelite

## Changes on 2018-08-21

### Exercises
* Fix bug in sample solution for basic exercise
  * PR: https://github.com/Echtzeitsysteme/tud-cppp/pull/100
  * Issue: https://github.com/Echtzeitsysteme/tud-cppp/issues/99

## Changes in December 2017

### Slides
* Heavy restructuring
  * Move '[Exkurs]' slides into separate section
  * Remove outdated, non-helpful slides entirely
  * Move 'Einführung in (Embedded) C' in front of 'Fortgeschrittene Themen' to allow for getting started with the µC faster 

## Changes in November 2017

### Slides
* Remove instructions regarding old hardware
* Move "Memory-mapped I/O" in front of "volatile"
* Remove old "ancestry" of programming languages
* Remove comparison of SVN and Git
* Remove advanced usages of preprocessor

## Changes on 2017-09-21

## Slides
* Insert slide 110 ("Exceptions")
* Remove (hidden) slide 135 (Summary of memory mgmt section)
* Bugfix on slide 222: Logical "XOR" not equivalent to '!=' if operands may have arbitrary values

## Exercises
* Add Maze project (2017/mcProjects/Maze). See also README.md therein.
* 19: Proper instructions for creating iterators for the custom Array class
* 20.1: Fix typo "Projekt" -> "Project"
* 21.3: Fix type "Hello Welt" -> "Hello World"
* 21.3: Change zero-byte replacement character from '_' to '+'
* 21.6: Clarification of meaning of "IMP" and "BIIMP"

## Changes on 2017-09-20

## Slides

* Slide 218: Fix title
* Slide 223: Bugfixes in second and third part (0x03 -> 0x07 and b' = 0100 0000 for "Determine status of 6th bit")
* Slide 228: "RAM" -> "Adressraum"

## Exercises

* Ex. 20.1: Need to set "Executable to Run/Debug" to "$(ProjectPath)/main.exe" and "Working Directory" to "$(ProjectPath)"
* Ex. 20.10/20.11: Missing '%' in wildcard rules
* Ex. 21.3: "buffer[5]" -> "buffer[strlen(buffer)]" or "buffer[7]"


## Changes on 2017-09-19

### Exercises
* Ex. 12 (sample solution): Contrary to the comment in the sample solution, it is possible to catch the same exception type by value and by (const) reference at the same time. The compiler should issue a warning in this case
* Ex. 17: The RHS parameter of the function passed to 'reduce' may now have an arbitray type
  * Instead of only 'double' 
* Ex. 21.3: Improve structure and fix bug due to the heap being zero by default.

## Changes on 2017-09-18

### Slides
* Minor layout improvements in OO part (slides 136-166)
* Fix typos on slides 165 und 166

## Changes on 2017-09-15

### Slides
* Bugfixes in "Call by x" slides 95 + 100-103: Use proper constructor of Floor that takes std::string and int
* Get rid of several artefacts in PDF export ('orange blocks')
* Add ref. to https://www.onlinegdb.com/ (Appears to more mature than cpp.sh)

### Exercises

* Ex. 7 ("Verkettete Listen"): Elaborate more on exceptions and behavior of delete[]
* Ex. 22.3 ("LED bunt blinken lasssen"): Add listing that explains how to configure I/O in a generic way
* Ex. 22,23: Use defines in introductory C exercises instead of pointer variables
* Ex. 24 ("Display ansteuern"): Hint to font map and on how to write umlauts 


## Changes on 2017-09-14

### Slides
* Bugfix on slide 30 ("Header und Implementierungs-Dateien"): The shown code is a class definition (not declaration)

## Changes on 2017-09-11

### Slides

* Remove motivation slides for multiple inheritance (previously: slides 156-158)
* Remove slide on multiple inheritance problems in "Template" part ("Containerproblem und Mehrfachvererbung", previously: slide 171)
* Introduce motivation slide for generic programming ("Generische Programmierung: Motivation", now: 168)
* Improve quality of slides (layout, explanations) in "Template" part
* Insert prepared slides from incubation section ("Beispiel: Template-Klasse Elevator<T>", "Der this-Zeiger", "Exkurs: Mehrfachvererbung in Java? (II)")

### Exercises

* Add hint regarding RGB565 export from Gimp to Ex. 27.

## Changes on 2017-09-07

### Exercises
* Improve documentation in sample solutions
* Improve code quality (remove static functions from headers, add missing includes,...)
* Ex. 25 "Joysticks": Use setCursor(0, 319); to set cursor to top-left corner

## Changes on 2017-09-06

### Slides
* Bugfix: Shift operator fills with '1' with if shifted value is negative
* Improved explanations on slide 223 ("Bitoperationen – Bytes manipulieren")
* Bugfix on slide 223 ("Bitoperationen – Bytes manipulieren"): fix bit mask, b, b' of third example
* Layouting in C part

## Changes on 2017-09-04

### Slides
* Hide slides 156-158: motivating example is not very helpful
* Bugfix slide 162: "h.getName()" --> "h->getName()"
* Bugfix slide 159: ":Mitarbeiter" --> ":Employee"
* Bugfix slide 175: "Template-Instantiierung" --> "Template-Spezialisierung"
* Mark slide 167 ("Mehrfachvererbung in Java (I)") as "Exkurs"
* Slide 126: Add note about default constructor behavior of "std::shard_ptr"
* Incubation:
  * Append slide that illustrates multi inheritance issues with "default" in Java 1.8 (to be inserted after s. 167)
  * Append slide for this pointer (to be inserted after s. 75)
  * Append slide with Elevator<T> (to be inserted after s. 175)
* Layouting: slide 75, 169-182

### Exercises
* Bugfix in ListIterator exercise ("Aufgabe 7.5"):
  * List::end() should return the iterator that is equal to the result of invoking "operator++" on the list iterator that points to the end of the list

## Changes on 2017-09-01

### Slides (cppp_lecture.pdf)
* Bugfix slide 104 ("Assignment-Operator (I)"):
  * operator= should have the return type "[ClassName] &" and the return value "*this"
  * Also fixed in all remaining slides
* Extension on slide 108 ("Compiler-generierte Methoden: C++"):
  * Add explanation of "= default" as complement to "= delete"
  * Add link for further reading
* Slide 42: minor typographic improvements
* Layout improvements in "OO" section (slide 135-167)

## Changes on 2017-08-31

### Exercises
* Bugfix Ex. 20: Fix project setup instructions
* Improved layout in Makefile exercise (kill blank pages)
* Bugfix Ex. 2.2: printFigure(Direction d) --> printFigure(int n) 
