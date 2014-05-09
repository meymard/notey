#!/bin/bash
echo "## Compile Model ##"
mkdir -p bin/Model
g++ -c -o bin/Model/Note.o Model/Note.cpp
echo "## Compile Controller ##"
mkdir -p bin/Controller
g++ -c -o bin/Controller/Note.o Controller/Note.cpp
g++ -c -o bin/Controller/DataSave.o Controller/DataSave.cpp
echo "## Compile View ##"
mkdir -p bin/View/Console
g++ -c -o bin/View/Console/Menu.o View/Console/Menu.cpp
echo "## Compile notes ##"
g++ -c -o bin/notey.o notey.cpp
echo "## Create bin ##"
g++ -o bin/notey bin/notey.o bin/Model/Note.o bin/Controller/Note.o  bin/Controller/DataSave.o bin/View/Console/Menu.o -lm -lsqlite3
