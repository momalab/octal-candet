#include "dataformat.hpp"

using namespace std;

namespace dataformat
{

vector<vector<double>> map_data(
    const vector<string> & ids,
    const vector<vector<string>> & cn,
    const vector<vector<string>> & var,
    const vector<string> & cn_ft,
    const vector<string> & var_ft
)
{
    auto nIds = ids.size();
    auto nCNs = cn_ft.size() - 1;
    auto nVars = var_ft.size();
    auto nFeatures = nCNs + nVars;

    // mapping the data for batch encryption - only data movement
    unordered_map< string, unordered_map< string,double > > cn_map;
    unordered_map< string, unordered_map< string,double > > var_map;
    vector<vector<double>> x( nIds, vector<double>( nFeatures, 0 ) );

    for ( size_t j=1; j < cn[0].size(); j++ ) // skip first column (not a person)
        for ( size_t i=1; i < cn.size(); i++ ) // skip first row (header)
            cn_map[ cn[0][j] ][ cn[i][0] ] = stod( cn[i][j] ); // cn_map[id][gene] = cn[i][j]
    for ( auto & row : var ) var_map[ row[0] ][ row[1] ] = stod( row[2] ); // var_map[id][gene]
    for ( size_t i=0; i < nIds; i++ )
    {
        for ( size_t j=0; j < nCNs ; j++ ) x[i][j     ] =  cn_map[ ids[i] ][  cn_ft[j+1] ];
        for ( size_t j=0; j < nVars; j++ ) x[i][j+nCNs] = var_map[ ids[i] ][ var_ft[j  ] ];
    }
    return x;
}

// vector<vector<double>> map_data(
//     const vector<string> & ids,
//     const vector<vector<string>> & cn,
//     const vector<vector<string>> & var,
//     const vector<string> & cn_ft,
//     const vector<string> & var_ft
// )
// {
//     auto nIds = ids.size();
//     auto nCNs = cn_ft.size() - 1;
//     auto nVars = var_ft.size();
//     auto nFeatures = nCNs + nVars;
//
//     // mapping the data for batch encryption - only data movement
//     unordered_map< string, unordered_map< string,double > > cn_map;
//     unordered_map< string, unordered_map< string,double > > v7_map;
//     unordered_map< string, unordered_map< string,double > > v8_map;
//     vector<vector<double>> x( 2*nIds, vector<double>( nFeatures, 0 ) );
//
//     for ( size_t j=1; j < cn[0].size(); j++ ) // skip first column (not a person)
//         for ( size_t i=1; i < cn.size(); i++ ) // skip first row (header)
//             cn_map[ cn[0][j] ][ cn[i][0] ] = stod( cn[i][j] ); // cn_map[id][gene] = cn[i][j]
//     for ( auto & row : var )
//     {
//         v7_map[ row[0] ][ row[1] ] = stod( row[2] ); // v7_map[id][gene]
//         v8_map[ row[0] ][ row[1] ] = stod( row[3] ); // v8_map[id][gene]
//     }
//     for ( size_t i=0; i < nIds; i++ )
//     {
//         for ( size_t j=0; j < nCNs; j++ ) x[2*i][j] = cn_map[ ids[i] ][ cn_ft[j+1] ];
//         for ( size_t j=0; j < nVars; j++ )
//         {
//             x[2*i  ][j+nCNs] = v7_map[ ids[i] ][ var_ft[j] ];
//             x[2*i+1][j+nCNs] = v8_map[ ids[i] ][ var_ft[j] ];
//         }
//     }
//     return x;
// }

} // dataformat
