@echo off
echo Compiling...
g++ -Iinclude -Iinclude/DataStructures main.cpp src/Document.cpp src/Index.cpp src/SearchEngine.cpp src/Tokenizer.cpp src/SearchHistory.cpp src/UI.cpp src/InputValidation.cpp src/DataStructures/IndexNode.cpp src/DataStructures/LinkedList.cpp src/DataStructures/Queue.cpp src/DataStructures/Stack.cpp src/DataStructures/BST.cpp src/DataStructures/Array.cpp -o main.exe
if %ERRORLEVEL% EQU 0 (
    echo Build successful! Launching in new window...
    start "Mini Search Engine Pro" main.exe
) else (
    echo Build failed!
    pause
)
