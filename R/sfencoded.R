
strSfEncoded <- function(object, ...) {
  n <- length(object)
  cat(paste0(class(object)[1], " of length ", n))
  if (n > 0) {
    cat("; first element: ")
    utils::str(object[1], ...)
  }
}

#' @export
str.encoded_column <- strSfEncoded

#' @export
str.wkt_column <- strSfEncoded


#' @export
`[.sfencoded` <- function(x, i, j, ..., drop = TRUE) {

  geomColumn <- attr(x, "encoded_column")
  wktColumn <- attr(x, "wkt_column")
  attr(x, "sfAttributes") <- NULL

  x <- NextMethod()
  x <- attachEncodedAttribute(x, geomColumn, "encoded_column")
  x <- attachEncodedAttribute(x, wktColumn, "wkt_column")

  if( is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column")) ){
    x <- removeSfencodedClass(x)
  }
  return(x)
}

#' @export
`[.sfencodedLite` <- `[.sfencoded`



attachEncodedAttribute <- function(x, attrCol, attribute) {
  if ( !is.null(attrCol) ) {
    if ( attrCol %in% names(x) ) {
      attr(x, attribute) <- attrCol
    }
  }
  return(x)
}

removeSfencodedClass <- function(x) {
  attr(x, "class") <- setdiff(class(x), c("sfencoded", "sfencodedLite"))
  return(x)
}


#' @export
print.sfencoded <- function(x, ... ){
  
  if(is.null(attr(x, "encoded_column")) && is.null(attr(x, "wkt_column"))) {
    NextMethod()
    return()
  }
  
  printSfEncoded(x, ... )
}

#' @export
print.sfencodedLite <- print.sfencoded

printSfEncoded <- function(x, ...) {
  
  encType <- ifelse(inherits(x, 'sfencoded'), 'sfencoded', 'sfencodedLite')
  
  encoded <- attr(x, "encoded_column")
  wkt <- attr(x, "wkt_column")

  if(!is.null(encoded)) {
    e <- x[[encoded]]
    e <- printSfEncodedPrefix(e, encType)
    e <- stats::setNames(data.frame(e), encoded)
    x[, encoded] <- e
  }

  if(!is.null(wkt)) {
    w <- x[[wkt]]
    w <- paste0(substr(w, 1, pmin(nchar(w), 30)), "...")
    w <- stats::setNames(data.frame(w), wkt)
    x[, wkt] <- w
  }
  
  x <- removeSfencodedClass(x)
  
  print(x)
  invisible(x)
}

printSfEncodedPrefix <- function(e, encType) {
  
  if(encType == "sfencoded") {
    e <- vapply(e, function(z) {
      paste0(
        attr(z, "sfc")[2], ": ",
        substr(z[1], 1, pmin(nchar(z[1]), 20)),
        "..."
      )
    }, "" )
  }else{
    e <- vapply(e, function(z) {
      paste0(
        substr(z[1], 1, pmin(nchar(z[1]), 20)),
        "..."
      )
    }, "" )
  }
  return(e)
  
}

