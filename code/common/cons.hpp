#pragma once

#include <string>
#include <vector>

namespace cons
{

const char delimiter = ' ';
const char data_delimiter = '\t';
const double us = 1000000;
// const std::vector<unsigned long long> coprimes{65537, 114689};
const std::vector<unsigned long long> coprimes{1073872897};

const std::vector<std::string> cancerTypes{
    "Bladder", "Breast", "Bronchusandlung", "Cervixuteri", "Colon",
    "Corpusuteri", "Kidney", "Liverandintrahepaticbileducts", "Ovary",
    "Skin", "Stomach"
};

} // cons
