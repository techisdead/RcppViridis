#ifndef RCPP_VIRIDIS_HEADERS_COLOURS_HEX_H
#define RCPP_VIRIDIS_HEADERS_COLOURS_HEX_H

#include <Rcpp.h>
#include "RcppViridis/colours.hpp"
#include "RcppViridis/utils/utils.hpp"


// if matrix palette.ncol() == 4
// - ignore alpha argument
// - alpha column gets splined

// ALPHA in [0,255] and assigned to each x
// if matrix palette.ncol() == 3 && alpha.length() > 1
// - alpha vector gets rescaled to [0,255], but NOT splined

// if matrix palette.ncol() == 3 && alpha.length() == 1; use single alpha constant
// - alpha must be in [0,255], but NOT splined

// if string palette && alpha.length() == 1; use single alpha constant
// - alpha must be in range [0,255], but NOT splined

// if string palette && alpha.length() == x.length()
// - alpha vector gets rescaled to [0,255], but NOT splined


namespace rcppviridis {
namespace colours_hex {

  // if palette is a string; it's using in-built palettes; nothing to do
  // if palette is function or vectors, force rescaling
  inline void format_rgba_value(int& val, boost::math::cubic_b_spline< double >& spline, double& this_x) {
    val = round( spline( this_x ) * 255);
  }

  inline void format_rgba_value(int& val, Rcpp::NumericVector& vals, int& i) {
    val = vals[i];
  }

  inline void resolve_item(
      Rcpp::NumericVector& x,
      Rcpp::StringVector& hex_strings,
      int& i, int& r, int& g, int& b, int& a,
      double& this_x,
      boost::math::cubic_b_spline< double >& spline_red,
      boost::math::cubic_b_spline< double >& spline_green,
      boost::math::cubic_b_spline< double >& spline_blue,
      boost::math::cubic_b_spline< double >& spline_alpha,
      std::string& na_colour) {

      format_rgba_value(r, spline_red, this_x);
      format_rgba_value(r, spline_green, this_x);
      format_rgba_value(r, spline_blue, this_x);
      format_rgba_value(r, spline_alpha, this_x);
      hex_strings[i] = rcppviridis::convert::convert_rgb_to_hex(r, g, b, a);
  }

  inline void resolve_item(
      Rcpp::NumericVector& x,
      Rcpp::StringVector& hex_strings,
      int& i, int& r, int& g, int& b, int& a,
      double& this_x,
      boost::math::cubic_b_spline< double >& spline_red,
      boost::math::cubic_b_spline< double >& spline_green,
      boost::math::cubic_b_spline< double >& spline_blue,
      Rcpp::NumericVector& alpha,
      std::string& na_colour) {

      format_rgba_value(r, spline_red, this_x);
      format_rgba_value(r, spline_green, this_x);
      format_rgba_value(r, spline_blue, this_x);
      format_rgba_value(r, alpha, i);
      hex_strings[i] = rcppviridis::convert::convert_rgb_to_hex(r, g, b, a);
  }

  inline Rcpp::StringVector colour_values_to_hex(
      Rcpp::NumericVector x,
      boost::math::cubic_b_spline< double > spline_red,
      boost::math::cubic_b_spline< double > spline_green,
      boost::math::cubic_b_spline< double > spline_blue,
      boost::math::cubic_b_spline< double > spline_alpha,
      int& alpha_type,
      std::string na_colour) {

    int n = x.size();

    //resolve_na_colour( na_colour );
    na_colour = na_colour.length() == 9 ? na_colour : na_colour + "FF";

    rcppviridis::scale::rescale(x);
    Rcpp::StringVector hex_strings(n);

    int i, r, g, b, a;
    double this_x;

    for( i = 0; i < n; i++ ) {
      this_x = x[i] * 255;
      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        hex_strings[i] = na_colour;
      } else {
        resolve_item(x, hex_strings, i, r, g, b, a, this_x, spline_red, spline_green, spline_blue, spline_alpha, na_colour);
      }
    }
    return hex_strings;
  }

  inline Rcpp::StringVector colour_values_to_hex(
      Rcpp::NumericVector x,
      boost::math::cubic_b_spline< double > spline_red,
      boost::math::cubic_b_spline< double > spline_green,
      boost::math::cubic_b_spline< double > spline_blue,
      Rcpp::NumericVector alpha,    // alpha must enter here already resovled, including splining?
      int& alpha_type,
      std::string na_colour) {

    int n = x.size();

  //resolve_na_colour( na_colour );
    na_colour = na_colour.length() == 9 ? na_colour : na_colour + "FF";

    rcppviridis::scale::rescale(x);
    Rcpp::StringVector hex_strings(n);

    double this_x;
    int i, r, g, b, a;

    for( i = 0; i < n; i++ ) {
      this_x = x[i] * 255;
      if ( R_IsNA( this_x) || R_IsNaN( this_x ) ) {
        hex_strings[i] = na_colour;
      } else {
        resolve_item(x, hex_strings, i, r, g, b, a, this_x, spline_red, spline_green, spline_blue, alpha, na_colour);
      }
    }
    return hex_strings;
  }

  // in this function the colour vectors will already be scaled [0,1]
  inline Rcpp::StringVector colour_value_hex(
    Rcpp::NumericVector x,
    Rcpp::NumericMatrix palette,
    std::string na_colour ) {

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);
    Rcpp::NumericVector alpha(x.size(), 255.0);

    //int alpha_type = palette.ncol() == 4 ? ALPHA_PALETTE : ALPHA_CONSTANT;       // can't be a palette column in this function

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue, alpha );

    return colour_values_to_hex( x, red, green, blue, alpha, alpha_type, na_colour );
  }

  inline Rcpp::StringVector colour_value_hex(
      Rcpp::NumericVector x,
      std::string palette,
      std::string na_colour,
      Rcpp::NumericVector alpha) {

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }
    //int alpha_type = alpha.size() > 1 ? ALPHA_VECTOR : ALPHA_CONSTANT;

    // if( palette.ncol() == 4 ) {
    //   alpha_type = ALPHA_PALETTE;
    // } else if ( alpha.size() == 1 ) {
    //   alpha_type = ALPHA_CONSTANT;
    // } else {
    //   alpha_type = ALPHA_VECTOR;
    // }

    int x_size = x.size();
    Rcpp::NumericVector alpha_full( x_size );
    rcppviridis::palette_utils::validate_alpha( alpha, alpha_full, x_size );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue );

    return colour_values_to_hex(x, red, green, blue, alpha_full, alpha_type, na_colour);
  }

  Rcpp::StringVector colour_value_hex (
      Rcpp::StringVector x,
      Rcpp::NumericMatrix palette,
      std::string na_colour ) {

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    // need to figure out if the alpha is on the palette or not before anything else.
    // if not on palette,
    //int alpha_type = palette.ncol() == 4 ? ALPHA_PALETTE : ALPHA_CONSTANT;       // can't be avector in this function

    Rcpp::NumericVector alpha(x.size(), 255.0);

    // TODO -
    // if palette.ncol() == 4; the alpha gets interpolated along with the RGB

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue, alpha );
    Rcpp::NumericVector out_nv = rcppviridis::utils::resolve_string_vector( x );

    return colour_values_to_hex( out_nv, red, green, blue, alpha, alpha_type, na_colour );
  }

  inline Rcpp::StringVector colour_value_hex(
      Rcpp::StringVector x,
      std::string palette,
      std::string na_colour,
      Rcpp::NumericVector alpha ) {

    // TODO(this throws an error on Travis)
    // if(!is_hex_colour(na_colour)) {
    //   Rcpp::stop("invalid NA Colour");
    // }

    //int alpha_type = alpha.size() > 1 ? ALPHA_VECTOR : ALPHA_CONSTANT;       // can't be a palette column in this function

    int x_size = x.size();
    Rcpp::NumericVector alpha_full( x_size );
    rcppviridis::palette_utils::validate_alpha( alpha, alpha_full, x_size );

    Rcpp::NumericVector red(256);
    Rcpp::NumericVector green(256);
    Rcpp::NumericVector blue(256);

    rcppviridis::palette_utils::resolve_palette( palette, red, green, blue );
    Rcpp::NumericVector out_nv = rcppviridis::utils::resolve_string_vector( x );

    return colour_values_to_hex( out_nv, red, green, blue, alpha_full, alpha_type, na_colour );
  }

} // namespace colours
} // namespace rcppviridis

#endif

