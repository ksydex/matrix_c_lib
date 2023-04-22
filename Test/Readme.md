gcc -c library.c -o matrix.o                                                           
ar rcs libmatrix.a matrix.o                                                            
sudo cp libmatrix.a /usr/local/lib
Add to CMakeLists.txt - target_link_libraries(MatrixTest libmatrix.a)

Build with GCC:

gcc -o program main.c -L. libmatrix.a                                                  


