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
  folderName=$(dirname $file)
  echo "---"
  echo "----------- $file ----------"
  echo "---"
  
  make -C $folderName $@
  
  if [ "$?" != "0" ];
  then
    echo "Execution of Makefile $file failed."
    exit 1;
  fi
  
  case "$folderName" in
  *_tests)
      echo "Executing unit tests for $file"
      
      make -C $folderName run
      
      if [ "$?" != "0" ];
      then
        echo "Execution of unit tests failed for Makefile $file."
        exit 1;
      fi
      ;;
  *)
      ;;
  esac
  
  
done
