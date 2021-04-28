find ./src -type f -name '*.cpp' | xargs clang-format -i
find ./include -type f -name '*.h' | xargs clang-format -i
#Windows breaks everything, just copy-paste into console