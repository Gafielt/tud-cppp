#!/bin/bash

export EXERCISES_ROOT=$(cd $(dirname $0); pwd)
echo $EXERCISES_ROOT
latexDirectory=$EXERCISES_ROOT/latex
solutionsDirectory=$EXERCISES_ROOT/solutions
templatesDirectory=$EXERCISES_ROOT/templates

for file in \
  $(find ${latexDirectory} -name "Makefile") \
  $(find ${solutionsDirectory}/* -name "Makefile") \
  $(find ${templatesDirectory}/* -name "Makefile");
do
  echo "---"
  echo "----------- $file ----------"
  echo "---"
  make -C $(dirname $file) $@
  if [ "$?" != "0" ];
  then
    echo "Execution of Makefile $file failed."
    exit 1;
  fi
done
