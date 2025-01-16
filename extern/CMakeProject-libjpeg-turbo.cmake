if(MACOSX)
  set(ARCH_FLAGS "-DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET} -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}")
endif()

include(ExternalProject)
ExternalProject_Add(
  libjpeg_turbo_project

  SOURCE_DIR "${SM_EXTERN_DIR}/libjpeg-turbo"
  INSTALL_DIR "${CMAKE_BINARY_DIR}/libjpeg-turbo-install"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/libjpeg-turbo-install
             -DENABLE_SHARED=OFF
             -DENABLE_STATIC=ON
             ${ARCH_FLAGS}
  BUILD_IN_SOURCE OFF
  BUILD_ALWAYS OFF
)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/include") # This needs to be created immediately, otherwise project generation will fail

add_library(libjpeg-turbo STATIC IMPORTED GLOBAL)
add_dependencies(libjpeg-turbo libjpeg_turbo_project)
target_include_directories(libjpeg-turbo INTERFACE "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/include")

if(WIN32)
  set_property(TARGET libjpeg-turbo PROPERTY IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/lib/turbojpeg-static.lib")
else()
  set_property(TARGET libjpeg-turbo PROPERTY IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/lib/libturbojpeg.a")
endif()
