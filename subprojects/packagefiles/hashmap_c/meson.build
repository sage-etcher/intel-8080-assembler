
project(
  'hashmap_c', 
  'c',
  version : 'v0.8.1',
  license : 'MIT',
  meson_version : '>=0.59.0',
  default_options : [
    'c_std=none',
    'warning_level=1',
  ],
)

hashmap_c_inc = include_directories('.')
libhashmap_c = library(
  'hashmap_c',
  'hashmap.c',
  version : '0.8.1',
)

hashmap_c_dep = declare_dependency(
  link_with : libhashmap_c,
  include_directories : hashmap_c_inc,
)

# end of file
