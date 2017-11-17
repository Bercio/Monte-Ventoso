file(REMOVE_RECURSE
  "testEvol.pdb"
  "testEvol"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/testEvol.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
