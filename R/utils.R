cli_suppress <- function(expr) {
  withCallingHandlers(
    expr,
    cli_message = function(c) {
      invokeRestart("cli_message_handled")
    }
  )
}
