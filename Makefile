#!/bin/sh
echo "## Compile Model ##"
mkdir -p bin/Model
STATUS=$(g++ -c -o bin/Model/Note.o Model/Note.cpp)
echo $STATUS
echo "## Compile Controller ##"
mkdir -p bin/Controller
STATUS=$(g++ -c -o bin/Controller/Note.o Controller/Note.cpp)
echo $STATUS
g++ -c -o bin/Controller/DataSave.o Controller/DataSave.cpp
echo $STATUS
echo "## Compile View ##"
mkdir -p bin/View/Console
g++ -c -o bin/View/Console/Menu.o View/Console/Menu.cpp
echo "## Compile notey ##"
g++ -c -o bin/notey.o notey.cpp
echo "## Create bin ##"
g++ -o bin/notey bin/notey.o bin/Model/Note.o bin/Controller/Note.o  bin/Controller/DataSave.o bin/View/Console/Menu.o -lm -lsqlite3
