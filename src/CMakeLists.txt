include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(magnus
  lanczos.cpp)
target_link_libraries(magnus ${CXXBLAS_LIBRARIES})

# if(CUDA_FOUND)
#   cuda_add_library(cumagnus
#     culanczos.cpp)
#   target_link_libraries(cumagnus ${CUDA_CUBLAS_LIBRARIES})
# endif()
