#!/bin/bash

function checkError {
    if [ $? -ne 0 ]
    then
        echo "Check error and restart make"
        exit 1
    fi
}

echo "## Compile Model ##"
mkdir -p bin/Model
g++ -c -o bin/Model/Note.o Model/Note.cpp
checkError

echo "## Compile Controller ##"
mkdir -p bin/Controller
g++ -c -o bin/Controller/Note.o Controller/Note.cpp
checkError
g++ -c -o bin/Controller/SqliteDataSave.o Controller/Sqlite/DataSave.cpp
checkError

echo "## Compile View ##"
mkdir -p bin/View/Console
g++ -c -o bin/View/Console/Menu.o View/Console/Menu.cpp
checkError

echo "## Compile notey ##"
g++ -c -o bin/notey.o notey.cpp
checkError

echo "## Create bin ##"
g++ -o bin/notey bin/notey.o bin/Model/Note.o bin/Controller/Note.o  bin/Controller/SqliteDataSave.o bin/View/Console/Menu.o -lm -lsqlite3
checkError
