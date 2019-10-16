rmdir .\build /s /q
mkdir build
cd build
cmake -DCMAKE_GENERATOR_PLATFORM=x64 -Dgtest_force_shared_crt=ON .. 
cd ..


