#include <Rcpp.h>

#include "RcppViridis/colours/colours.hpp"

using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_num_value_hex( Rcpp::NumericVector x, std::string palette, std::string na_colour) {
  return rcppviridis::colours::colour_value_hex( x, palette, na_colour );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_colour_str_value_hex( Rcpp::StringVector x, std::string palette, std::string na_colour) {
  return rcppviridis::colours::colour_value_hex( x, palette, na_colour );
}


// [[Rcpp::export]]
Rcpp::IntegerMatrix rcpp_convert_hex_to_rgb( Rcpp::StringVector hex ) {
  return rcppviridis::convert::convert_hex_to_rgb( hex );
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_convert_rgb_to_hex(Rcpp::NumericVector r, Rcpp::NumericVector g, Rcpp::NumericVector b) {
  return rcppviridis::convert::convert_rgb_to_hex(r, g, b);
}
