#ifndef RCPP_VIRIDIS_HEADERS_UTILS_H
#define RCPP_VIRIDIS_HEADERS_UTILS_H

#include <Rcpp.h>

namespace rcppviridis {
namespace utils {

  inline void replace_nas( Rcpp::IntegerVector& out, int na_value ) {
    int int_s = NA_INTEGER;
    std::replace( out.begin(), out.end(), na_value, int_s);
  }

  inline Rcpp::NumericVector resolve_string_vector( Rcpp::StringVector x ) {
    bool anyNa = Rcpp::any( is_na( x ));
    Rcpp::StringVector lvls = Rcpp::sort_unique( x );
    Rcpp::IntegerVector out = Rcpp::match( x, lvls );

    if ( anyNa ) {
      int na_value = Rcpp::max( out );
      rcppviridis::utils::replace_nas( out, na_value );
    }
    return Rcpp::as< Rcpp::NumericVector >( out );
  }

} // namespace utils
} // namespace rcppviridis


#endif
