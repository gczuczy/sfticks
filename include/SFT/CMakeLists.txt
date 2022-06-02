set(SFT_HEADERS
  PRIVATE
  BeltSubsystem.hh
  DCG.hh
  DCGComponent.hh
  DCGEdge.hh
  DCGNode.hh
  Exception.hh
  Loader.hh
  Reader.hh
  Timer.hh
  Trace.hh
  tests.hh
  tick.hh
)

target_sources(sfticks
  PRIVATE
  ${SFT_HEADERS}
)

target_precompile_headers(sfticks
  PRIVATE
  ${SFT_HEADERS}
)
