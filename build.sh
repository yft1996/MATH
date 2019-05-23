#!/usr/bin/env bash
echo -e "\033[44;33m\$\$\$\$\$\$\$\$\$\$\$\$$\$\$--发财线--\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\033[0m"
echo -e "\033[40;32m\$\$\$\$\$\$\$\$\$\$\$配置并编译MATH库...\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\033[0m"
echo -e "\033[44;33m\$\$\$\$\$\$\$\$\$\$\$\$$\$\$--发财线--\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\$\033[0m\n"
rm lib/*

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4