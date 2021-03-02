find . -type f -name '*.cpp' | xargs clang-format -i
find . -type f -name '*.h' | xargs clang-format -i
#Windows breaks everything, just copy-paste into console