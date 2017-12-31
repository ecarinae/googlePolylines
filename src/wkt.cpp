#include <Rcpp.h>
#include "wkt.h"
#include "googlePolylines.h"

using namespace Rcpp;

void addLonLatToWKTStream(std::ostringstream& os, float lon, float lat ) {
  os << lon << " " << lat;
}

void geom_type(const char *cls, int *tp = NULL) {
  
  int type = 0;
  if (strcmp(cls, "POINT") == 0)
    type = POINT;
  else if (strcmp(cls, "MULTIPOINT") == 0)
    type = MULTIPOINT;
  else if (strcmp(cls, "LINESTRING") == 0)
    type = LINESTRING;
  else if (strcmp(cls, "POLYGON") == 0)
    type = POLYGON;
  else if (strcmp(cls, "MULTILINESTRING") == 0)
    type = MULTILINESTRING;
  else if (strcmp(cls, "MULTIPOLYGON") == 0)
    type = MULTIPOLYGON;
  else
    type = UNKNOWN;
  if (tp != NULL)
    *tp = type;
}

void beginWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
  
  int tp;
  geom_type(cls[1], &tp);
  
  switch( tp ) {
  case POINT:
    os << "POINT ";
    break;
  case MULTIPOINT:
    os << "MULTIPOINT (";
    break;
  case LINESTRING:
    os << "LINESTRING ";
    break;
  case MULTILINESTRING:
    os << "MULTILINESTRING (";
    break;
  case POLYGON:
    os << "POLYGON (";
    break;
  case MULTIPOLYGON:
    os << "MULTIPOLYGON ((";
    break;
  default: {
      Rcpp::stop("Unknown geometry type");
    }
  }
}

void endWKT(std::ostringstream& os, Rcpp::CharacterVector cls) {
  
  int tp;
  geom_type(cls[1], &tp);
  
  switch( tp ) {
  case POINT:
    os << "";
    break;
  case MULTIPOINT:
    os << ")";
    break;
  case LINESTRING:
    os << "";
    break;
  case MULTILINESTRING:
    os << ")";
    break;
  case POLYGON:
    os << ")";
    break;
  case MULTIPOLYGON:
    os << "))";
    break;
  default: {
      Rcpp::stop("Unknown geometry type");
    }
  }
}

void coordSeparateWKT(std::ostringstream& os) {
  os << ", ";
}

// TODO:
// - user can specify geometry type
// - if not supplied, assume LINESTRING / MULTILINESTRING 
// - if from sfencoded - read the attributes

// - different beginnings based on the geometry -> POLYGON((, LINESTRING(, POINT(, MULTIPOINT((, MULTILINESTRING((, 
// - SPLIT_CHAR -> the beginning of a new polygon (in a MULTIPOLYGON)

// [[Rcpp::export]]
Rcpp::StringVector polyline_to_wkt(Rcpp::List sfencoded) {
  
//  Rcpp::Rcout << "length: " << sfencoded.size() << std::endl;
  int nrow = sfencoded.size();
  Rcpp::StringVector res(nrow);
  
  for (size_t i = 0; i < nrow; i++ ){
    
    std::ostringstream os;
    Rcpp::String wkt;
    std::string stdspl;
    Rcpp::CharacterVector cls;
      
    Rcpp::StringVector pl = sfencoded[i];

    if(!Rf_isNull(pl.attr("sfc"))){
      cls = pl.attr("sfc"); 
    }else{
      Rcpp::stop("No geometry attribute found");
    }

    beginWKT(os, cls);
    int n =  pl.size();
  
    for(size_t j = 0; j < n; j ++ ) {
  
      Rcpp::String spl = pl[j];
      
      if(spl == SPLIT_CHAR){
        os << "),(";
      }else{
        stdspl = spl;
        os << "(";
        polylineToWKT(os, stdspl);
        os << ")";
        if(n > 1 && j < (n - 1)){
          if(pl[j+1] != SPLIT_CHAR){
            os << ",";
          }
        }
      }
      
    }
    endWKT(os, cls);
    res[i] = os.str();
  }
  
  return res;
  
}


void polylineToWKT(std::ostringstream& os, std::string encoded){
  
  int len = encoded.size();
  int index = 0;
  float lat = 0;
  float lng = 0;
  
  while (index < len){
    char b;
    int shift = 0;
    int result = 0;
    do {
      b = encoded.at(index++) - 63;
      result |= (b & 0x1f) << shift;
      shift += 5;
    } while (b >= 0x20);
    float dlat = ((result & 1) ? ~(result >> 1) : (result >> 1));
    lat += dlat;
    
    shift = 0;
    result = 0;
    do {
      b = encoded.at(index++) - 63;
      result |= (b & 0x1f) << shift;
      shift += 5;
    } while (b >= 0x20);
    float dlng = ((result & 1) ? ~(result >> 1) : (result >> 1));
    lng += dlng;

    addLonLatToWKTStream(os, lng* (float)1e-5, lat* (float)1e-5);
    
    if(index < len) {
      coordSeparateWKT(os);
    }
  }
}









