#ifndef RCPP_VIRIDIS_HEADERS_COLOUR_HEX_H
#define RCPP_VIRIDIS_HEADERS_COLOUR_HEX_H

#include <iostream>
#include <string>
#include <sstream>

namespace rcppviridis {
namespace convert {

  std::string convert_rgb_to_hex( int num ) {
    std::string rgb;
    for (int i=(3*2) - 1; i>=0; i--) {
      rgb += "0123456789ABCDEF"[((num >> i*4) & 0xF)];
    }
    return rgb;
  }

  std::string convert_rgb_to_hex(int r, int g, int b) {
    int rgbNum = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
    return '#' + convert_rgb_to_hex( rgbNum );
  }

  int hex_element( std::string& hex, int pos ) {
    return std::stoul( hex.substr(pos, 2), nullptr, 16 );
  }

  Rcpp::StringVector convert_rgb_to_hex(Rcpp::NumericVector r, Rcpp::NumericVector g,
                                        Rcpp::NumericVector b) {
    int n = r.size();
    int i = 0;
    Rcpp::StringVector hex(n);
    for ( i = 0; i < n; i++ ) {
      hex[i] = convert_rgb_to_hex( r[i], g[i], b[i] );
    }
    return hex;
  }

  // TODO(3-character hex ("#0F0") and alpha channel)
  Rcpp::IntegerMatrix convert_hex_to_rgb( Rcpp::StringVector hex ) {
    int n = hex.size();
    Rcpp::IntegerMatrix rgb( n, 3 );
    int i = 0;
    int hasHash = 0;
    std::string this_hex;

    for (i = 0; i < n; i++) {
      this_hex = hex[i];
      if ( this_hex[0] == '#') {
        hasHash = 1;
      } else {
        hasHash = 0;
      }

      rgb(i, 0) = hex_element( this_hex, 0 + hasHash );
      rgb(i, 1) = hex_element( this_hex, 2 + hasHash );
      rgb(i, 2) = hex_element( this_hex, 4 + hasHash );
    }
    return rgb;
  }

} // namespace convert
} // namespace rcppviridis

#endif
