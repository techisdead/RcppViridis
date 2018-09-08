#' Hex to RGB
#'
#' converts hex string colours to RGB
#'
#' @param hex vector of hex colours
#'
#' @examples
#' colour_to_rgb(c("#00FF00","#FF00FF"))
#'
#' @export
hex_to_rgb <- function( hex ) {
  rcpp_convert_hex_to_rgb( hex )
}

#' RGB to Hex
#'
#' converts RGB colours to hex string colours
#'
#' @param x rgb
#'
#' @export
rgb_to_hex <- function( rgb ) {
  UseMethod("rgb_to_hex")
}

#' @export
rgb_to_hex.integer <- function( rgb ) {
  rcpp_convert_rgb_to_hex( rgb[1], rgb[2], rgb[3] )
}

#' @export
rgb_to_hex.numeric <- function( rgb ) {
  rcpp_convert_rgb_to_hex( rgb[1], rgb[2], rgb[3] )
}

#' @export
rgb_to_hex.matrix <- function( rgb ) {
  rcpp_convert_rgb_to_hex( rgb[,1],rgb[,2],rgb[,3] )
}


