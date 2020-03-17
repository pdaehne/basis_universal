#include "c_api.h"
#include "../basisu_enc.h"
#include "../basisu_comp.h"
#include "../transcoder/basisu_transcoder.h"

extern "C" {


DLLMAPPING basist_etc1_global_selector_codebook* CALLCONV basist_etc1_global_selector_codebook_new() {
	auto cb = new basist::etc1_global_selector_codebook();
	cb->init(basist::g_global_selector_cb_size, basist::g_global_selector_cb);
	return reinterpret_cast<basist_etc1_global_selector_codebook*>(cb);
}

DLLMAPPING void CALLCONV basist_etc1_global_selector_codebook_delete(basist_etc1_global_selector_codebook *codebook) {
	delete reinterpret_cast<basist::etc1_global_selector_codebook*>(codebook);
}

//DLLMAPPING void CALLCONV basist_etc1_global_selector_codebook_init(basist_etc1_global_selector_codebook *codebook, uint32_t N, const uint32_t* pEntries) {
//	auto cb = reinterpret_cast<basist::etc1_global_selector_codebook*>(codebook);
//	cb->init(N, pEntries);
//}

DLLMAPPING const uint32_t* basist_g_global_selector_cb = basist::g_global_selector_cb;
DLLMAPPING const uint32_t basist_g_global_selector_cb_size = basist::g_global_selector_cb_size;


DLLMAPPING basisu_job_pool* CALLCONV basisu_job_pool_new(uint32_t num_threads) {
	return reinterpret_cast<basisu_job_pool*>(new basisu::job_pool(num_threads));
}

DLLMAPPING void CALLCONV basisu_job_pool_delete(basisu_job_pool *job_pool) {
	delete reinterpret_cast<basisu::job_pool*>(job_pool);
}


DLLMAPPING basisu_image* CALLCONV basisu_image_new() {
	return reinterpret_cast<basisu_image*>(new basisu::image());
}

DLLMAPPING void CALLCONV basisu_image_delete(basisu_image *image) {
	delete reinterpret_cast<basisu::image*>(image);
}

DLLMAPPING void CALLCONV basisu_image_resize(basisu_image *image, uint32_t w, uint32_t h, uint32_t p) {
	auto img = reinterpret_cast<basisu::image*>(image);
	img->resize(w, h, p);
}

DLLMAPPING uint32_t CALLCONV basisu_image_get_pixels_size(basisu_image *image) {
	auto img = reinterpret_cast<basisu::image*>(image);
	return static_cast<uint32_t>(img->get_pixels().size());
}

DLLMAPPING uint8_t* CALLCONV basisu_image_get_pixels(basisu_image *image) {
	auto img = reinterpret_cast<basisu::image*>(image);
	return &(img->get_ptr()->r);
}


DLLMAPPING basisu_basis_compressor_params* CALLCONV basisu_basis_compressor_params_new() {
	return reinterpret_cast<basisu_basis_compressor_params*>(new basisu::basis_compressor_params());
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_delete(basisu_basis_compressor_params *params) {
	delete reinterpret_cast<basisu::basis_compressor_params*>(params);
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_pSel_codebook(basisu_basis_compressor_params *params, basist_etc1_global_selector_codebook *codebook) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	auto cb = reinterpret_cast<basist::etc1_global_selector_codebook*>(codebook);
	prms->m_pSel_codebook = cb;
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_pJob_pool(basisu_basis_compressor_params *params, basisu_job_pool *job_pool) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	auto jp = reinterpret_cast<basisu::job_pool*>(job_pool);
	prms->m_pJob_pool = jp;
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_add_m_source_images(basisu_basis_compressor_params *params, basisu_image *image) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	auto img = reinterpret_cast<basisu::image*>(image);
	prms->m_source_images.push_back(*img);
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_mip_gen(basisu_basis_compressor_params *params, int mip_gen) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	prms->m_mip_gen = mip_gen != 0;
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_quality_level(basisu_basis_compressor_params *params, int quality_level) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	prms->m_quality_level = quality_level;
}


DLLMAPPING basisu_basis_compressor* CALLCONV basisu_basis_compressor_new() {
	return reinterpret_cast<basisu_basis_compressor*>(new basisu::basis_compressor());
}

DLLMAPPING void CALLCONV basisu_basis_compressor_delete(basisu_basis_compressor *compressor) {
	delete reinterpret_cast<basisu::basis_compressor*>(compressor);
}

DLLMAPPING int CALLCONV basisu_basis_compressor_init(basisu_basis_compressor *compressor, const basisu_basis_compressor_params *params) {
	auto cmp = reinterpret_cast<basisu::basis_compressor*>(compressor);
	auto prms = reinterpret_cast<const basisu::basis_compressor_params*>(params);
	return cmp->init(*prms) ? 0 : 1;
}

DLLMAPPING int CALLCONV basisu_basis_compressor_process(basisu_basis_compressor *compressor) {
	auto cmp = reinterpret_cast<basisu::basis_compressor*>(compressor);
	return cmp->process();
}

DLLMAPPING uint32_t CALLCONV basisu_basis_compressor_get_output_basis_file_size(basisu_basis_compressor *compressor) {
	auto cmp = reinterpret_cast<basisu::basis_compressor*>(compressor);
	return static_cast<uint32_t>(cmp->get_output_basis_file().size());
}

DLLMAPPING const void* CALLCONV basisu_basis_compressor_get_output_basis_file(basisu_basis_compressor *compressor) {
	auto cmp = reinterpret_cast<basisu::basis_compressor*>(compressor);
	return cmp->get_output_basis_file().data();
}


}
