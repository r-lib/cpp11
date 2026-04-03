# cpp_source fails informatively for nonexistent file

    Code
      cpp_source(i_do_not_exist)
    Condition
      Error:
      ! Can't find `file` at this path:
      {NON_EXISTENT_FILEPATH}

# `cpp11::package` throws expected error on unknown packages

    Code
      test()
    Condition
      Error:
      ! Can't find namespace: 'definitely_not_a_package'.

