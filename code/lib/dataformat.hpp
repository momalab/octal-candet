#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace dataformat
{

std::vector<std::vector<double>> map_data(
    const std::vector<std::string> & ids,
    const std::vector<std::vector<std::string>> & cn,
    const std::vector<std::vector<std::string>> & var,
    const std::vector<std::string> & cn_ft,
    const std::vector<std::string> & cn_var
);

} // dataformat
