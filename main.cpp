#include <iostream>
#include "src/ModuleSelector.h"

int main() {
    dataBase::TestDataBase testDataBase;
    testDataBase.make();
    ModuleSelector selector;
    selector.selectModule(testDataBase);
}
