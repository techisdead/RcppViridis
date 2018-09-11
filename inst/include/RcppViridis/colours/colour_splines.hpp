// #ifndef RCPP_VIRIDIS_HEADERS_COLOURS_SPLINES_H
// #define RCPP_VIRIDIS_HEADERS_COLOURS_SPLINES_H
//
// #include <Rcpp>
// #include "RcppViridis/colours.hpp"
//
// namespace rcppviridis {
// namespace colour_splines {
//
//   inline void resolve_item(
//       Rcpp::NumericVector& x,
//       Rcpp::StringVector& hex_strings,
//       int& i, int& r, int& g, int& b, int& a,
//       double& this_x,
//       boost::math::cubic_b_spline< double >& spline_red,
//       boost::math::cubic_b_spline< double >& spline_green,
//       boost::math::cubic_b_spline< double >& spline_blue,
//       boost::math::cubic_b_spline< double >& spline_alpha,
//       std::string& na_colour) {
//
//     format_rgba_value(r, spline_red, this_x);
//     format_rgba_value(r, spline_green, this_x);
//     format_rgba_value(r, spline_blue, this_x);
//     format_rgba_value(r, spline_alpha, this_x);
//     hex_strings[i] = rcppviridis::convert::convert_rgb_to_hex(r, g, b, a);
//   }
//
//   inline void resolve_item(
//       Rcpp::NumericVector& x,
//       Rcpp::StringVector& hex_strings,
//       int& i, int& r, int& g, int& b, int& a,
//       double& this_x,
//       boost::math::cubic_b_spline< double >& spline_red,
//       boost::math::cubic_b_spline< double >& spline_green,
//       boost::math::cubic_b_spline< double >& spline_blue,
//       Rcpp::NumericVector& alpha,
//       std::string& na_colour) {
//
//     format_rgba_value(r, spline_red, this_x);
//     format_rgba_value(r, spline_green, this_x);
//     format_rgba_value(r, spline_blue, this_x);
//     format_rgba_value(r, alpha, i);
//     hex_strings[i] = rcppviridis::convert::convert_rgb_to_hex(r, g, b, a);
//   }
//
// } // namespace colour_splines
// } // namespace rcppviridis
//
//
// #endif
