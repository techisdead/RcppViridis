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
rgb_to_hex <- function( x, ... ) {
  UseMethod("rgb_to_hex")
}

#' @export
rgb_to_hex.integer <- function( x, ... ) {
  rgb_to_hex.default( x[1], x[2], x[3] )
}

#' @export
rgb_to_hex.numeric <- function( x, ... ) {
  rgb_to_hex.default( x[1], x[2], x[3] )
}

#' @export
rgb_to_hex.matrix <- function( x, ... ) {
  rgb_to_hex.default( x[, 1], x[, 2], x[, 3] )
}

#' @export
rgb_to_hex.default <- function( x, y, z, ... ) {
  rcpp_convert_rgb_to_hex( x, y, z )
}
