Exercises: cppp_exercises.pdf
Lecture: cppp_lecture.pdf

## Changes on 2017-09-11

## Lecture

* Remove motivation slides for multiple inheritance (previously: slides 156-158)
* Remove slide on multiple inheritance problems in "Template" part ("Containerproblem und Mehrfachvererbung", previously: slide 171)
* Introduce motivation slide for generic programming ("Generische Programmierung: Motivation", now: 168)
* Improve quality of slides (layout, explanations) in "Template" part
* Insert prepared slides from incubation section ("Beispiel: Template-Klasse Elevator<T>", "Der this-Zeiger", "Exkurs: Mehrfachvererbung in Java? (II)")

## Exercises

* Add hint regarding RGB565 export from Gimp to Ex. 27.

## Changes on 2017-09-07

## Exercises
* Improve documentation in sample solutions
* Improve code quality (remove static functions from headers, add missing includes,...)
* Ex. 25 "Joysticks": Use setCursor(0, 319); to set cursor to top-left corner

## Changes on 2017-09-06

### Lecture
* Bugfix: Shift operator fills with '1' with if shifted value is negative
* Improved explanations on slide 223 ("Bitoperationen – Bytes manipulieren")
* Bugfix on slide 223 ("Bitoperationen – Bytes manipulieren"): fix bit mask, b, b' of third example
* Layouting in C part

## Changes on 2017-09-04

### Lecture
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

### Lecture (cppp_lecture.pdf)
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