aux_source_directory(. BM_SOURCES)
add_executable(EngineBenchMark ${BM_SOURCES})
target_link_libraries(EngineBenchMark PRIVATE LifeLib benchmark benchmark_main)
