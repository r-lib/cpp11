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
