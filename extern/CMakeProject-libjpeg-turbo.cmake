if(MACOSX)
  set(ARCH_FLAGS "-DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET} -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}")
endif()

include(ExternalProject)
ExternalProject_Add(
  libjpeg_turbo_project

  SOURCE_DIR "${SM_EXTERN_DIR}/libjpeg-turbo"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/libjpeg-turbo-install
             -DENABLE_SHARED=OFF
             -DENABLE_STATIC=ON
             ${ARCH_FLAGS}
  BUILD_IN_SOURCE OFF
  BUILD_ALWAYS OFF
)

add_library(libjpeg-turbo STATIC IMPORTED)
set(LIBJPEG_TURBO_INCLUDE_DIR "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/include" CACHE INTERNAL "libjpeg-turbo include")

if(WIN32)
  set(LIBJPEG_TURBO_LIBRARY "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/lib/turbojpeg-static.lib" CACHE INTERNAL "libjpeg-turbo library")
else()
  set(LIBJPEG_TURBO_LIBRARY "${CMAKE_BINARY_DIR}/libjpeg-turbo-install/lib/libturbojpeg.a" CACHE INTERNAL "libjpeg-turbo library")
endif()
