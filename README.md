## Final Fantasy VII - Interactive Map

This is a simple interactive map for the Final Fantasy VII game, written in C++ with the use of the SFML framework.
   
The simple functionality it provides:
* Filtering by name: By typing anything you will filter the shown places.
* 5 different quadrants: you can access them by using the number keys from 1 to 5, and 0 to show all quadrants.

The start matrix
![](SCREENSHOT/astar_default_matrix.png)
   
The path with diagonal movement enabled
![](SCREENSHOT/astar_path_diag.png)
   
The path with diagonal movement disabled
![](SCREENSHOT/astar_path_nodiag.png)
   

To compile this project, open a terminal (or command prompt) in the project's directory, and run:
    
Windows:
```
build.bat
``` 
Linux:
```
./build.sh
```
This will create the executable **ffvii_map** (or **ffvii_map.exe** in Windows) inside the project's directory.