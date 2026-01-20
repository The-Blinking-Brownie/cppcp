clang++ -g -fno-omit-frame-pointer -include-pch bits/stdc++.h -DDETCHOCO_ENV "$name.cpp" -std=c++23 -Wno-vla-cxx-extension -o ".tmp/$name.out"
