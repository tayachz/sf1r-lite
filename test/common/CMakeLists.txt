INCLUDE_DIRECTORIES(
  ${Boost_INCLUDE_DIRS}
  )

SET(libs
  sf1r_common

  ${izenelib_LIBRARIES}

  #external
  ${Boost_LIBRARIES}
  ${Glog_LIBRARIES}
  ${TokyoCabinet_LIBRARIES}
  ${SYS_LIBS}
  )

SET(Boost_USE_STATIC_LIBS OFF)
FIND_PACKAGE(Boost ${Boost_FIND_VERSION}
  COMPONENTS unit_test_framework serialization)

IF(Boost_FOUND AND Boost_UNIT_TEST_FRAMEWORK_FOUND AND Boost_SERIALIZATION_FOUND)

  ADD_EXECUTABLE(t_ScdParser
    Runner.cpp
    t_ScdParser.cpp
    )
  TARGET_LINK_LIBRARIES(t_ScdParser ${libs})

  ADD_EXECUTABLE(t_ScdIndex
    Runner.cpp
    t_ScdIndex.cpp
  )
  TARGET_LINK_LIBRARIES(t_ScdIndex ${libs})

  ADD_EXECUTABLE(t_ScdIndexLeveldb
    Runner.cpp
    t_ScdIndexLeveldb.cpp
  )
  TARGET_LINK_LIBRARIES(t_ScdIndexLeveldb ${libs})

  ADD_EXECUTABLE(t_ClickCounterDB
    Runner.cpp
    t_ClickCounterDB.cpp
    ClickCounterDBTestFixture.cpp
    )
  TARGET_LINK_LIBRARIES(t_ClickCounterDB ${libs})

  ADD_EXECUTABLE(t_SDBWrapper
    Runner.cpp
    t_SDBWrapper.cpp
    )
  TARGET_LINK_LIBRARIES(t_SDBWrapper ${libs})

  ADD_EXECUTABLE(t_Utilities
    Runner.cpp
    t_Utilities.cpp
    )
  TARGET_LINK_LIBRARIES(t_Utilities ${libs})

  ADD_EXECUTABLE(t_scd_type_writer
    Runner.cpp
    t_scd_type_writer.cpp
    )
  TARGET_LINK_LIBRARIES(t_scd_type_writer ${libs})


  ADD_EXECUTABLE(t_pairwise_scd_meger
    Runner.cpp
    t_pairwise_scd_meger.cpp
    )
  TARGET_LINK_LIBRARIES(t_pairwise_scd_meger ${libs})

  ADD_EXECUTABLE(t_QueryNormalizer
    Runner.cpp
    t_QueryNormalizer.cpp
    )
  TARGET_LINK_LIBRARIES(t_QueryNormalizer ${libs})

  ADD_EXECUTABLE(t_FileMonitor
    Runner.cpp
    t_FileMonitor.cpp
    FileMonitorTestFixture.cpp
    )
  TARGET_LINK_LIBRARIES(t_FileMonitor ${libs})

  ADD_EXECUTABLE(t_ByteSizeParser
    Runner.cpp
    t_ByteSizeParser.cpp
    )
  TARGET_LINK_LIBRARIES(t_ByteSizeParser ${libs})

ENDIF()

ADD_EXECUTABLE(ScdMerger
    ScdMerger.cpp
    )
TARGET_LINK_LIBRARIES(ScdMerger ${libs})
SET_TARGET_PROPERTIES(ScdMerger PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${SF1RENGINE_ROOT}/scripts
)

ADD_EXECUTABLE(ScdMergeTool
    ScdMergeTool.cpp
    )
TARGET_LINK_LIBRARIES(ScdMergeTool ${libs})
SET_TARGET_PROPERTIES(ScdMergeTool PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${SF1RENGINE_ROOT}/tool
)

ADD_EXECUTABLE(ScdParserPerformance
    ScdParserPerformance.cpp
    )
TARGET_LINK_LIBRARIES(ScdParserPerformance ${libs} )
SET_TARGET_PROPERTIES(ScdParserPerformance PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${SF1RENGINE_ROOT}/tool
)
