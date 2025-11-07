
project(
  'intel 8080 assembler', 
  'c',
  default_options : [
    'c_std=c99',
    'warning_level=3',
  ],
)

hashmap_c_proj = subproject('hashmap_c')
hashmap_c_dep = hashmap_c_proj.get_variable('hashmap_c_dep')

subdir('src')

# end of file

