#pragma once

#include <stdint.h>
#include <stddef.h>

#if defined(_WIN32)
#  if defined(basisu_encoder_EXPORTS)
#    define DLLMAPPING __declspec(dllexport)
#  else
#    define DLLMAPPING __declspec(dllimport)
#  endif
#  define CALLCONV __cdecl
#else
#  define DLLMAPPING
#  define CALLCONV __attribute__((cdecl))
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef struct basisu_job_pool_ basisu_job_pool;

DLLMAPPING basisu_job_pool* CALLCONV basisu_job_pool_new(uint32_t num_threads);

DLLMAPPING void CALLCONV basisu_job_pool_delete(basisu_job_pool *job_pool);


typedef struct basisu_image_ basisu_image;

DLLMAPPING void CALLCONV basisu_image_resize(basisu_image *image, uint32_t w, uint32_t h, uint32_t p);

DLLMAPPING uint32_t CALLCONV basisu_image_get_pixels_size(basisu_image *image);

DLLMAPPING uint8_t* CALLCONV basisu_image_get_pixels(basisu_image *image);


typedef struct basisu_basis_compressor_params_ basisu_basis_compressor_params;

DLLMAPPING basisu_basis_compressor_params* CALLCONV basisu_basis_compressor_params_new();

DLLMAPPING void CALLCONV basisu_basis_compressor_params_delete(basisu_basis_compressor_params *params);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_pJob_pool(basisu_basis_compressor_params *params, basisu_job_pool *job_pool);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_resize_m_source_images(basisu_basis_compressor_params *params, size_t count);

DLLMAPPING basisu_image *CALLCONV basisu_basis_compressor_params_get_m_source_images(basisu_basis_compressor_params *params, size_t index);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_mip_gen(basisu_basis_compressor_params *params, int mip_gen);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_etc1s_quality_level(basisu_basis_compressor_params *params, int quality_level);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_uastc(basisu_basis_compressor_params *params, int uastc);


DLLMAPPING void CALLCONV basisu_basisu_encoder_init(int use_opencl, int opencl_force_serialization);

DLLMAPPING void CALLCONV basisu_basisu_encoder_deinit();



typedef struct basisu_basis_compressor_ basisu_basis_compressor;

DLLMAPPING basisu_basis_compressor* CALLCONV basisu_basis_compressor_new();

DLLMAPPING void CALLCONV basisu_basis_compressor_delete(basisu_basis_compressor *compressor);

DLLMAPPING int CALLCONV basisu_basis_compressor_init(basisu_basis_compressor *compressor, const basisu_basis_compressor_params *params);

DLLMAPPING int CALLCONV basisu_basis_compressor_process(basisu_basis_compressor *compressor);

DLLMAPPING uint32_t CALLCONV basisu_basis_compressor_get_output_basis_file_size(basisu_basis_compressor *compressor);

DLLMAPPING const void* CALLCONV basisu_basis_compressor_get_output_basis_file(basisu_basis_compressor *compressor);

typedef struct basisu_basisu_backend_output_ basisu_basisu_backend_output;

DLLMAPPING const basisu_basisu_backend_output* CALLCONV basisu_basis_compressor_get_backend_output(basisu_basis_compressor *compressor);


DLLMAPPING int CALLCONV basisu_basisu_backend_output_get_num_endpoints(const basisu_basisu_backend_output *backend_output);

DLLMAPPING int CALLCONV basisu_basisu_backend_output_get_num_selectors(const basisu_basisu_backend_output *backend_output);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_endpoint_palette_size(const basisu_basisu_backend_output *backend_output);

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_endpoint_palette(const basisu_basisu_backend_output *backend_output);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_selector_palette_size(const basisu_basisu_backend_output *backend_output);

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_selector_palette(const basisu_basisu_backend_output *backend_output);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_slice_image_tables_size(const basisu_basisu_backend_output *backend_output);

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_slice_image_tables(const basisu_basisu_backend_output *backend_output);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_num_slice_image_data(const basisu_basisu_backend_output *backend_output);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_slice_image_data_size(const basisu_basisu_backend_output *backend_output, int i);

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_slice_image_data(const basisu_basisu_backend_output *backend_output, int i);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_num_total_images(const basisu_basisu_backend_output *backend_output);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_num_levels(const basisu_basisu_backend_output *backend_output, uint32_t image_index);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_slice_index(const basisu_basisu_backend_output *backend_output, uint32_t image_index, uint32_t level_index);

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_has_alpha_slices(const basisu_basisu_backend_output *backend_output);


#ifdef __cplusplus
} // extern "C"
#endif
