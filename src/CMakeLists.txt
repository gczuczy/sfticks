
add_subdirectory(SFT)
add_subdirectory(FG)

target_sources(sfticks
  PRIVATE main.cc misc.cc
)
