# equivalently templated `cpp11::stop()` and `cpp11::warning()` can coexist (#491)

    Code
      test_template_stop()
    Condition
      Error:
      ! stop

---

    Code
      test_template_warning()
    Condition
      Warning:
      warning

