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
    return '#' + convert_rgb_to_hex(rgbNum);
  }

  Rcpp::StringVector convert_rgb_to_hex(Rcpp::NumericVector r, Rcpp::NumericVector g, Rcpp::NumericVector b) {
    int n = r.size();
    int i = 0;
    Rcpp::StringVector hex(n);
    for ( i = 0; i < n; i++ ) {
      hex[i] = convert_rgb_to_hex(r[i], g[i], b[i]);
    }
    return hex;
  }

  Rcpp::IntegerVector convert_hex_to_rgb( std::string& hex) {

    int* rgb = new int[3];
    std::stringstream ss;
    std::string str;

    // Drop a hash if the value has one
    if (hex[0] == '#') {
      hex.erase(0,1);
    }

    int size = hex.size();
    int i = 0;

    for (i = 0; i < 3; i++) {
      // Determine 3 or 6 character format.
      if (size == 3) {
        str = std::string(2, hex[i]);
      } else if (size == 6) {
        str = hex.substr(i * 2, 2);
      } else {
        break;
      }

      ss << std::hex << str;
      ss >> rgb[i];
      ss.clear();
    }

    return Rcpp::IntegerVector::create( rgb[0], rgb[1], rgb[2] );
  }

  Rcpp::IntegerMatrix convert_hex_to_rgb( Rcpp::StringVector hex) {
    int n = hex.size();
    Rcpp::IntegerMatrix rgb(n, 3);
    int i = 0;
    std::string this_hex;
    for (i = 0; i < n; i++) {
      this_hex = hex[i];
      rgb(i, _) = convert_hex_to_rgb( this_hex );
    }
    return rgb;
  }

} // namespace convert
} // namespace rcppviridis

#endif
