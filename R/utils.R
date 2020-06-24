cli_suppress <- function(expr) {
  withCallingHandlers(
    expr,
    cli_message = function(c) {
      invokeRestart("cli_message_handled")
    }
  )
}

glue_collapse_data <- function(data, ..., sep = ", ", last = "") {
  res <- glue::glue_collapse(glue::glue_data(data, ...), sep = sep, last = last)
  if (length(res) == 0) {
    return("")
  }
  unclass(res)
}

`%||%` <- function(x, y) if (is.null(x)) y else x

viapply <- function(x, f, ...) vapply(x, f, integer(1), ...)
vcapply <- function(x, f, ...) vapply(x, f, character(1), ...)

stop_unless_installed <- function(pkgs) {
  has_pkg <- logical(length(pkgs))
  for (i in seq_along(pkgs)) {
    has_pkg[[i]] <- requireNamespace(pkgs[[i]], quietly = TRUE)
  }
  if (any(!has_pkg)) {
    msg <- sprintf(
      "The %s package(s) are required for this functionality",
      paste(pkgs[!has_pkg], collapse = ", ")
    )

    if (interactive()) {
      ans <- readline(paste(c(msg, "Would you like to install them? (Y/N) "), collapse = "\n"))
      if (tolower(ans) == "y") {
        install.packages(pkgs[!has_pkg])
        stop_unless_installed(pkgs)
        return()
      }
    }

    stop(msg, call. = FALSE)
  }
}
