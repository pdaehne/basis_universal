cmake_minimum_required(VERSION 3.5)

project(basisu_encoder_js)

# The encoder always supports generating KTX2 files, but Zstandard support is optional. If it's disabled, KTX2 UASTC files will always be uncompressed.
# If you know you'll never be encoding UASTC+Zstd KTX2 files you can set KTX2_ZSTANDARD to 0 to reduce the size of the compiled encoder.
option(KTX2_ZSTANDARD "KTX2_ZSTANDARD" TRUE)

message("KTX2_ZSTANDARD=${KTX2_ZSTANDARD}")

if (EMSCRIPTEN)
  set(CMAKE_CXX_STANDARD 17)
  
  set(SRC_LIST
    ../transcoder/basis_wrappers.cpp
    ../../transcoder/basisu_transcoder.cpp
	../../encoder/basisu_backend.cpp                         
	../../encoder/basisu_basis_file.cpp                      
	../../encoder/basisu_comp.cpp                            
	../../encoder/basisu_enc.cpp                             
	../../encoder/basisu_etc.cpp                             
	../../encoder/basisu_frontend.cpp                        
	../../encoder/basisu_gpu_texture.cpp                     
	../../encoder/basisu_pvrtc1_4.cpp                        
	../../encoder/basisu_resampler.cpp                       
	../../encoder/basisu_resample_filters.cpp                
	../../encoder/basisu_ssim.cpp                            
	../../encoder/basisu_uastc_enc.cpp                       
	../../encoder/basisu_bc7enc.cpp
	../../encoder/basisu_kernels_sse.cpp
	../../encoder/basisu_opencl.cpp
	../../encoder/pvpngreader.cpp
	../../encoder/jpgd.cpp                                   
	../../encoder/3rdparty/android_astc_decomp.cpp
   ../../encoder/basisu_uastc_hdr_4x4_enc.cpp
   ../../encoder/basisu_astc_hdr_6x6_enc.cpp
   ../../encoder/basisu_astc_hdr_common.cpp
	../../encoder/3rdparty/tinyexr.cpp
  )

  if (KTX2_ZSTANDARD)
  	set(SRC_LIST ${SRC_LIST}
		../../zstd/zstd.c
	)
	set(ZSTD_DEFINITION BASISD_SUPPORT_KTX2_ZSTD=1)
  else()
  	set(ZSTD_DEFINITION BASISD_SUPPORT_KTX2_ZSTD=0)
  endif()
  
  # No threading version
  add_executable(basis_encoder.js ${SRC_LIST})

  #target_compile_definitions(basis_encoder.js PRIVATE NDEBUG BASISD_SUPPORT_UASTC=1 BASISD_SUPPORT_BC7=1 BASISD_SUPPORT_ATC=0 BASISD_SUPPORT_ASTC_HIGHER_OPAQUE_QUALITY=0 BASISD_SUPPORT_PVRTC2=0 BASISD_SUPPORT_FXT1=0 BASISD_SUPPORT_ETC2_EAC_RG11=0 BASISU_SUPPORT_ENCODING=1 BASISU_SUPPORT_SSE=0 ${ZSTD_DEFINITION} )
  #target_compile_options(basis_encoder.js PRIVATE -fno-strict-aliasing -O3)
  
  #target_compile_definitions(basis_encoder.js PRIVATE DEBUG BASISD_SUPPORT_UASTC=1 BASISD_SUPPORT_BC7=1 BASISD_SUPPORT_ATC=0 BASISD_SUPPORT_ASTC_HIGHER_OPAQUE_QUALITY=0 BASISD_SUPPORT_PVRTC2=0 BASISD_SUPPORT_FXT1=0 BASISD_SUPPORT_ETC2_EAC_RG11=0 BASISU_SUPPORT_ENCODING=1 BASISU_SUPPORT_SSE=0 ${ZSTD_DEFINITION} )
  #target_compile_options(basis_encoder.js PRIVATE -fno-strict-aliasing -g -O1 -fsanitize=undefined -fsanitize=address)
  
  # debug options  
  #target_compile_definitions(basis_encoder.js PRIVATE DEBUG BASISD_SUPPORT_UASTC=1 BASISD_SUPPORT_BC7=1 BASISD_SUPPORT_ATC=0 BASISD_SUPPORT_ASTC_HIGHER_OPAQUE_QUALITY=0 BASISD_SUPPORT_PVRTC2=0 BASISD_SUPPORT_FXT1=0 BASISD_SUPPORT_ETC2_EAC_RG11=0 BASISU_SUPPORT_ENCODING=1 BASISU_SUPPORT_SSE=0 ${ZSTD_DEFINITION} )
  #target_compile_options(basis_encoder.js PRIVATE -fno-strict-aliasing -g -O0)
  
  # release options
  target_compile_definitions(basis_encoder.js PRIVATE NDEBUG BASISD_SUPPORT_UASTC=1 BASISD_SUPPORT_BC7=1 BASISD_SUPPORT_ATC=0 BASISD_SUPPORT_ASTC_HIGHER_OPAQUE_QUALITY=0 BASISD_SUPPORT_PVRTC2=0 BASISD_SUPPORT_FXT1=0 BASISD_SUPPORT_ETC2_EAC_RG11=0 BASISU_SUPPORT_ENCODING=1 BASISU_SUPPORT_SSE=0 ${ZSTD_DEFINITION} )
  target_compile_options(basis_encoder.js PRIVATE -fno-strict-aliasing -O3)
  
  target_include_directories(basis_encoder.js PRIVATE ../../transcoder)

  set_target_properties(basis_encoder.js PROPERTIES
      OUTPUT_NAME "basis_encoder"
      SUFFIX ".js"
	  
	#LINK_FLAGS "--bind -s INITIAL_MEMORY=536870912 -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=262144 -s MODULARIZE=1 -s EXPORT_NAME=BASIS  -s EXPORTED_RUNTIME_METHODS=['HEAP8']")
	#LINK_FLAGS "--bind -s INITIAL_MEMORY=536870912 -g -s STACK_SIZE=262144 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -fsanitize=undefined -fsanitize=address  -s EXPORTED_RUNTIME_METHODS=['HEAP8']")
	#LINK_FLAGS "--bind -s INITIAL_MEMORY=536870912 -g -s STACK_SIZE=262144 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -s ASSERTIONS=2  -s EXPORTED_RUNTIME_METHODS=['HEAP8']")
	LINK_FLAGS "--bind -s ALLOW_MEMORY_GROWTH=1 -s INITIAL_MEMORY=536870912 -s STACK_SIZE=262144 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -s ASSERTIONS=0  -s EXPORTED_RUNTIME_METHODS=['HEAP8']")

   add_executable(basis_encoder_threads.js ${SRC_LIST})

   # Threaded version   
   target_compile_definitions(basis_encoder_threads.js PRIVATE NDEBUG BASISD_SUPPORT_UASTC=1 BASISD_SUPPORT_BC7=1 BASISD_SUPPORT_ATC=0 BASISD_SUPPORT_ASTC_HIGHER_OPAQUE_QUALITY=0 BASISD_SUPPORT_PVRTC2=0 BASISD_SUPPORT_FXT1=0 BASISD_SUPPORT_ETC2_EAC_RG11=0 BASISU_SUPPORT_ENCODING=1 BASISU_SUPPORT_SSE=0 ${ZSTD_DEFINITION} WASM_THREADS_ENABLED=1 )
   target_include_directories(basis_encoder_threads.js PRIVATE ../../transcoder)   
   
   target_compile_options(basis_encoder_threads.js PRIVATE -fno-strict-aliasing -O3 -matomics -mbulk-memory)   
   
   set_target_properties(basis_encoder_threads.js PROPERTIES
	OUTPUT_NAME "basis_encoder_threads"
	SUFFIX ".js"
	#LINK_FLAGS "--bind -s INITIAL_MEMORY=536870912 -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=262144 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -s EXPORTED_RUNTIME_METHODS=['HEAP8']")
	#LINK_FLAGS "--bind -s INITIAL_MEMORY=536870912 -g -s STACK_SIZE=262144 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -fsanitize=undefined -fsanitize=address -s EXPORTED_RUNTIME_METHODS=['HEAP8']")
	#LINK_FLAGS "--bind -s INITIAL_MEMORY=536870912 -g -s STACK_SIZE=262144 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -s ASSERTIONS=2 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=18 -s ENVIRONMENT=web,worker -s EXPORTED_RUNTIME_METHODS=['HEAP8']")
	LINK_FLAGS "--bind -s ALLOW_MEMORY_GROWTH=1 -s INITIAL_MEMORY=536870912 -s STACK_SIZE=262144 -s MODULARIZE=1 -s EXPORT_NAME=BASIS -s ASSERTIONS=0 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=18 -s ENVIRONMENT=web,worker -s EXPORTED_RUNTIME_METHODS=['HEAP8']")

endif()
