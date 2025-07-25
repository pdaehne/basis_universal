#include "c_api.h"
#include "../encoder/basisu_enc.h"
#include "../encoder/basisu_comp.h"
#include "../transcoder/basisu_transcoder.h"

extern "C" {


DLLMAPPING basisu_job_pool* CALLCONV basisu_job_pool_new(uint32_t num_threads) {
	return reinterpret_cast<basisu_job_pool*>(new basisu::job_pool(num_threads));
}

DLLMAPPING void CALLCONV basisu_job_pool_delete(basisu_job_pool *job_pool) {
	delete reinterpret_cast<basisu::job_pool*>(job_pool);
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

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_pJob_pool(basisu_basis_compressor_params *params, basisu_job_pool *job_pool) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	auto jp = reinterpret_cast<basisu::job_pool*>(job_pool);
	prms->m_pJob_pool = jp;
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_resize_m_source_images(basisu_basis_compressor_params *params, size_t count) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	prms->m_source_images.resize(count);
}

DLLMAPPING basisu_image *CALLCONV basisu_basis_compressor_params_get_m_source_images(basisu_basis_compressor_params *params, size_t index) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	return reinterpret_cast<basisu_image*>(&(prms->m_source_images[index]));
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_mip_gen(basisu_basis_compressor_params *params, int mip_gen) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	prms->m_mip_gen = mip_gen != 0;
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_etc1s_quality_level(basisu_basis_compressor_params *params, int quality_level) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	prms->m_etc1s_quality_level = quality_level;
}

DLLMAPPING void CALLCONV basisu_basis_compressor_params_set_m_uastc(basisu_basis_compressor_params *params, int uastc) {
	auto prms = reinterpret_cast<basisu::basis_compressor_params*>(params);
	prms->m_uastc = uastc != 0;
}


DLLMAPPING void CALLCONV basisu_basisu_encoder_init(int use_opencl, int opencl_force_serialization) {
	basisu::basisu_encoder_init(use_opencl != 0, opencl_force_serialization != 0);
}

DLLMAPPING void CALLCONV basisu_basisu_encoder_deinit() {
	basisu::basisu_encoder_deinit();
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

DLLMAPPING const basisu_basisu_backend_output* CALLCONV basisu_basis_compressor_get_backend_output(basisu_basis_compressor *compressor) {
	auto cmp = reinterpret_cast<basisu::basis_compressor*>(compressor);
	return reinterpret_cast<const basisu_basisu_backend_output*>(cmp->get_backend_output());
}


DLLMAPPING int CALLCONV basisu_basisu_backend_output_get_num_endpoints(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_num_endpoints;
}

DLLMAPPING int CALLCONV basisu_basisu_backend_output_get_num_selectors(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_num_selectors;
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_endpoint_palette_size(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_endpoint_palette.size();
}

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_endpoint_palette(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_endpoint_palette.data();
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_selector_palette_size(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_selector_palette.size();
}

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_selector_palette(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_selector_palette.data();
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_slice_image_tables_size(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_slice_image_tables.size();
}

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_slice_image_tables(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_slice_image_tables.data();
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_num_slice_image_data(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_slice_image_data.size();
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_slice_image_data_size(const basisu_basisu_backend_output *backend_output, int i) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_slice_image_data[i].size();
}

DLLMAPPING const void* CALLCONV basisu_basisu_backend_output_get_slice_image_data(const basisu_basisu_backend_output *backend_output, int i) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return outp->m_slice_image_data[i].data();
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_num_total_images(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	uint32_t num_total_images = 0;
	for (uint32_t i = 0; i < outp->m_slice_desc.size(); i++)
		num_total_images = basisu::maximum<uint32_t>(num_total_images, outp->m_slice_desc[i].m_source_file_index + 1);
	return num_total_images;
}

int find_first_slice_index(const basisu::basisu_backend_output *outp, uint32_t image_index, uint32_t level_index) {
	for (uint32_t i = 0; i < outp->m_slice_desc.size(); i++) {
		const basisu::basisu_backend_slice_desc& slice_desc = outp->m_slice_desc[i];
		if ((slice_desc.m_source_file_index == image_index) && (slice_desc.m_mip_index == level_index))
			return i;
	}

	return -1;
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_num_levels(const basisu_basisu_backend_output *backend_output, uint32_t image_index) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	int slice_index = find_first_slice_index(outp, image_index, 0);
	if (slice_index < 0) {
		return 0;
	}
	uint32_t total_levels = 1;
	for (uint32_t i = slice_index + 1; i < outp->m_slice_desc.size(); i++) {
		if (outp->m_slice_desc[i].m_source_file_index == image_index)
			total_levels = basisu::maximum<uint32_t>(total_levels, outp->m_slice_desc[i].m_mip_index + 1);
		else
			break;
	}
	return total_levels;
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_get_slice_index(const basisu_basisu_backend_output *backend_output, uint32_t image_index, uint32_t level_index) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	return find_first_slice_index(outp, image_index, level_index);
}

DLLMAPPING uint32_t CALLCONV basisu_basisu_backend_output_has_alpha_slices(const basisu_basisu_backend_output *backend_output) {
	auto outp = reinterpret_cast<const basisu::basisu_backend_output*>(backend_output);
	for (uint32_t slice_index = 0; slice_index < outp->m_slice_desc.size(); ++slice_index) {
		if (outp->m_slice_desc[slice_index].m_alpha) {
			return 1;
		}
	}
	return 0;
}


} // extern "C"
