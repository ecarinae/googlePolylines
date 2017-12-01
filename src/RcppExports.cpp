// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// encodeSfGeometry
Rcpp::List encodeSfGeometry(Rcpp::List sfc, bool strip);
RcppExport SEXP _sfencode_encodeSfGeometry(SEXP sfcSEXP, SEXP stripSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type sfc(sfcSEXP);
    Rcpp::traits::input_parameter< bool >::type strip(stripSEXP);
    rcpp_result_gen = Rcpp::wrap(encodeSfGeometry(sfc, strip));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_decode_polyline
DataFrame rcpp_decode_polyline(std::string encoded);
RcppExport SEXP _sfencode_rcpp_decode_polyline(SEXP encodedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type encoded(encodedSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_decode_polyline(encoded));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_encode_polyline
Rcpp::String rcpp_encode_polyline(Rcpp::NumericVector latitude, Rcpp::NumericVector longitude, int num_coords);
RcppExport SEXP _sfencode_rcpp_encode_polyline(SEXP latitudeSEXP, SEXP longitudeSEXP, SEXP num_coordsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type latitude(latitudeSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type longitude(longitudeSEXP);
    Rcpp::traits::input_parameter< int >::type num_coords(num_coordsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_encode_polyline(latitude, longitude, num_coords));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_sfencode_encodeSfGeometry", (DL_FUNC) &_sfencode_encodeSfGeometry, 2},
    {"_sfencode_rcpp_decode_polyline", (DL_FUNC) &_sfencode_rcpp_decode_polyline, 1},
    {"_sfencode_rcpp_encode_polyline", (DL_FUNC) &_sfencode_rcpp_encode_polyline, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_sfencode(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
