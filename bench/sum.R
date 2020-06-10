pkgload::load_all()

cases <- expand.grid(
  len = 3e6,
  vector = c("normal", "altrep"),
  method = c("for", "foreach", "accumulate"),
  stringsAsFactors = FALSE
)

# Add special case
cases <- do.call(rbind,
  list(
    list(len = 3e6, vector = "normal", method = "for2"),
    list(len = 3e6, vector = "normal", method = "foreach2"),
    list(len = 3e6, vector = "altrep", method = "foreach2"),
    cases)
  )

bench::press(
  .grid = cases,
  {
    library(cpp11)
    seq_real <- function(x) as.numeric(seq_len(x))
    funs <- c("normal" = rnorm, "altrep" = seq_real)
    x <- funs[[vector]](len)
    fun_name <- sprintf("cpp11_sum_vec_%s_", method)
    bench::mark(
      .Call(fun_name, x)
    )
  }
)
