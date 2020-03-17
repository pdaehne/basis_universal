#pragma once

#include <stdint.h>
#include <stddef.h>

#if defined(_WIN32)
#  if defined(BASISU_DLL_EXPORTS)
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


typedef struct basist_etc1_global_selector_codebook_ basist_etc1_global_selector_codebook;

DLLMAPPING basist_etc1_global_selector_codebook* CALLCONV basist_etc1_global_selector_codebook_new();

DLLMAPPING void CALLCONV basist_etc1_global_selector_codebook_delete(basist_etc1_global_selector_codebook *codebook);

//DLLMAPPING void CALLCONV basist_etc1_global_selector_codebook_init(basist_etc1_global_selector_codebook *codebook, uint32_t N, const uint32_t* pEntries);

//DLLMAPPING extern const uint32_t* basist_g_global_selector_cb;
//DLLMAPPING extern const uint32_t basist_g_global_selector_cb_size;


typedef struct basisu_job_pool_ basisu_job_pool;

DLLMAPPING basisu_job_pool* CALLCONV basisu_job_pool_new(uint32_t num_threads);

DLLMAPPING void CALLCONV basisu_job_pool_delete(basisu_job_pool *job_pool);


typedef struct basisu_image_ basisu_image;

DLLMAPPING basisu_image* CALLCONV basisu_image_new();

DLLMAPPING void CALLCONV basisu_image_delete(basisu_image *image);

DLLMAPPING void CALLCONV basisu_image_resize(basisu_image *image, uint32_t w, uint32_t h, uint32_t p);

DLLMAPPING uint32_t CALLCONV basisu_image_get_pixels_size(basisu_image *image);

DLLMAPPING uint8_t* CALLCONV basisu_image_get_pixels(basisu_image *image);


typedef struct basisu_basis_compressor_params_ basisu_basis_compressor_params;

DLLMAPPING basisu_basis_compressor_params* CALLCONV basisu_basis_compressor_params_new();

DLLMAPPING void CALLCONV basisu_basis_compressor_params_delete(basisu_basis_compressor_params *params);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_pSel_codebook(basisu_basis_compressor_params *params, basist_etc1_global_selector_codebook *codebook);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_pJob_pool(basisu_basis_compressor_params *params, basisu_job_pool *job_pool);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_add_m_source_images(basisu_basis_compressor_params *params, basisu_image *image);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_mip_gen(basisu_basis_compressor_params *params, int mip_gen);

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_quality_level(basisu_basis_compressor_params *params, int quality_level);


typedef struct basisu_basis_compressor_ basisu_basis_compressor;

DLLMAPPING basisu_basis_compressor* CALLCONV basisu_basis_compressor_new();

DLLMAPPING void CALLCONV basisu_basis_compressor_delete(basisu_basis_compressor *compressor);

DLLMAPPING int CALLCONV basisu_basis_compressor_init(basisu_basis_compressor *compressor, const basisu_basis_compressor_params *params);

DLLMAPPING int CALLCONV basisu_basis_compressor_process(basisu_basis_compressor *compressor);

DLLMAPPING uint32_t CALLCONV basisu_basis_compressor_get_output_basis_file_size(basisu_basis_compressor *compressor);

DLLMAPPING const void* CALLCONV basisu_basis_compressor_get_output_basis_file(basisu_basis_compressor *compressor);


#ifdef __cplusplus
}
#endif