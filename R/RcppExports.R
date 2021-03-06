# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

rcpp_encodeSfGeometry <- function(sfc, strip) {
    .Call('_googlePolylines_rcpp_encodeSfGeometry', PACKAGE = 'googlePolylines', sfc, strip)
}

rcpp_encode_polyline <- function(longitude, latitude) {
    .Call('_googlePolylines_rcpp_encode_polyline', PACKAGE = 'googlePolylines', longitude, latitude)
}

polyline_to_wkt <- function(sfencoded) {
    .Call('_googlePolylines_polyline_to_wkt', PACKAGE = 'googlePolylines', sfencoded)
}

wkt_to_polyline <- function(wkt) {
    .Call('_googlePolylines_wkt_to_polyline', PACKAGE = 'googlePolylines', wkt)
}

