file(GLOB _all_libdirs libs/*)
foreach(_dir ${_all_libdirs})
  if(EXISTS ${_dir}/src)
    file(GLOB_RECURSE _current_sources ${_dir}/src/*.cpp)
    list(APPEND _sources ${_current_sources})
  endif()
endforeach()

if(WIN32)
  set(_exclude_files "/posix/|/pthread/")
else()
  set(_exclude_files "/windows/|/win32/")
endif()

set(_exclude_files "${_exclude_files}|serialization/src/shared_ptr_helper.cpp")

foreach(_file ${_sources})
  if(${_file} MATCHES ${_exclude_files})
    set_source_files_properties(${_file} PROPERTIES HEADER_FILE_ONLY TRUE)
  endif()
endforeach()

file(GLOB_RECURSE _headers boost/*.hpp boost/*.ipp boost/*.h boost/*.inc)

include_directories(. boost)
add_library(boost_static ${_sources} ${_headers})
