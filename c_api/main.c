#include <stdlib.h>
#include <stdio.h>
#include "c_api.h"
#include "../lodepng.h"

int main() {
	basist_etc1_global_selector_codebook* sel_codebook = basist_etc1_global_selector_codebook_new();

	//basist_etc1_global_selector_codebook_init(sel_codebook, basist_g_global_selector_cb_size, basist_g_global_selector_cb);

	basisu_job_pool *jpool = basisu_job_pool_new(1);

	unsigned char *imageData;
	unsigned imageWidth, imageHeight;
	if (lodepng_decode32_file(&imageData, &imageWidth, &imageHeight, "abfeuerumschalter.png"/*"antrieb.png"*/) != 0) {
		fprintf(stderr, "Loading image failed\n");
		return EXIT_FAILURE;
	}
	printf("%ux%u\n", imageWidth, imageHeight);
	basisu_image *image1 = basisu_image_new();
	basisu_image_resize(image1, imageWidth, imageHeight, imageWidth);
	uint8_t *basisuImageData = basisu_image_get_pixels(image1);
	size_t imageSize = imageWidth * imageHeight * 4;
	memcpy(basisuImageData, imageData, imageSize);
	free(imageData);

	if (lodepng_decode32_file(&imageData, &imageWidth, &imageHeight, "RGBA.png") != 0) {
		fprintf(stderr, "Loading image failed\n");
		return EXIT_FAILURE;
	}
	printf("%ux%u\n", imageWidth, imageHeight);
	basisu_image *image2 = basisu_image_new();
	basisu_image_resize(image2, imageWidth, imageHeight, imageWidth);
	basisuImageData = basisu_image_get_pixels(image2);
	imageSize = imageWidth * imageHeight * 4;
	memcpy(basisuImageData, imageData, imageSize);
	free(imageData);

	basisu_basis_compressor_params *params = basisu_basis_compressor_params_new();
	basisu_basis_compressor_params_set_m_pSel_codebook(params, sel_codebook);
	basisu_basis_compressor_params_set_m_pJob_pool(params, jpool);
	basisu_basis_compressor_params_add_m_source_images(params, image1);
	//basisu_basis_compressor_params_add_m_source_images(params, image2);
	basisu_basis_compressor_params_set_m_mip_gen(params, 1);
	basisu_basis_compressor_params_set_m_quality_level(params, 128);
	//basisu_basis_compressor_params_set_m_uastc(params, 1);

	basisu_basis_compressor *compressor = basisu_basis_compressor_new();

	if (basisu_basis_compressor_init(compressor, params) != 0) {
		fprintf(stderr, "Initializing compressor failed\n");
		return EXIT_FAILURE;
	}

	if (basisu_basis_compressor_process(compressor) != 0) {
		fprintf(stderr, "Processing compressor failed\n");
		return EXIT_FAILURE;
	}

	const basisu_basisu_backend_output *backend_output = basisu_basis_compressor_get_backend_output(compressor);
	printf("num_endpoints = 0x%x\n", basisu_basisu_backend_output_get_num_endpoints(backend_output));
	printf("endpoint_palette_size = 0x%x\n", (int)basisu_basisu_backend_output_get_endpoint_palette_size(backend_output));
	printf("num_selectors = 0x%x\n", basisu_basisu_backend_output_get_num_selectors(backend_output));
	printf("selector_palette_size = 0x%x\n", (int)basisu_basisu_backend_output_get_selector_palette_size(backend_output));
	printf("slice_image_tables_size = 0x%x\n", (int)basisu_basisu_backend_output_get_slice_image_tables_size(backend_output));
	uint32_t num_slice_image_data = basisu_basisu_backend_output_get_num_slice_image_data(backend_output);
	printf("num_slice_image_data = 0x%x\n", (int)num_slice_image_data);
	for (uint32_t i = 0; i < num_slice_image_data; ++i) {
		printf("slice %i:\n", i);
		printf("  slice_image_data_size = 0x%x\n", (int)basisu_basisu_backend_output_get_slice_image_data_size(backend_output, i));
	}
	printf("---\n");

	size_t size = basisu_basis_compressor_get_output_basis_file_size(compressor);
	const void *data = basisu_basis_compressor_get_output_basis_file(compressor);
	const uint8_t *header = (const uint8_t*)data;
	printf("m_sig = 0x%x\n", header[0] | (header[1] << 8));
	printf("m_ver = 0x%x\n", header[2] | (header[3] << 8));
	printf("m_header_size = 0x%x\n", header[4] | (header[5] << 8));
	printf("m_header_crc16 = 0x%x\n", header[6] | (header[7] << 8));
	printf("m_data_size = 0x%x\n", header[8] | (header[9] << 8) | (header[10] << 16) | (header[11] << 24));
	printf("m_data_crc16 = 0x%x\n", header[12] | (header[13] << 8));
	uint32_t total_slices = header[14] | (header[15] << 8) | (header[16] << 16);
	printf("m_total_slices = 0x%x\n", total_slices);
	printf("m_total_images = 0x%x\n", header[17] | (header[18] << 8) | (header[19] << 16));
	printf("m_format = 0x%x\n", header[20]);
	printf("m_flags = 0x%x\n", header[21] | (header[22] << 8));
	printf("m_tex_type = 0x%x\n", header[23]);
	printf("m_us_per_frame = 0x%x\n", header[24] | (header[25] << 8) | (header[26] << 16));
	printf("m_reserved = 0x%x\n", header[27] | (header[28] << 8) | (header[29] << 16) | (header[30] << 24));
	printf("m_userdata0 = 0x%x\n", header[31] | (header[32] << 8) | (header[33] << 16) | (header[34] << 24));
	printf("m_userdata1 = 0x%x\n", header[35] | (header[36] << 8) | (header[37] << 16) | (header[38] << 24));
	printf("m_total_endpoints = 0x%x\n", header[39] | (header[40] << 8));
	printf("m_endpoint_cb_file_ofs = 0x%x\n", header[41] | (header[42] << 8) | (header[43] << 16) | (header[44] << 24));
	printf("m_endpoint_cb_file_size = 0x%x\n", header[45] | (header[46] << 8) | (header[47] << 16));
	printf("m_total_selectors = 0x%x\n", header[48] | (header[49] << 8));
	printf("m_selector_cb_file_ofs = 0x%x\n", header[50] | (header[51] << 8) | (header[52] << 16) | (header[53] << 24));
	printf("m_selector_cb_file_size = 0x%x\n", header[54] | (header[55] << 8) | (header[56] << 16));
	printf("m_tables_file_ofs = 0x%x\n", header[57] | (header[58] << 8) | (header[59] << 16) | (header[60] << 24));
	printf("m_tables_file_size = 0x%x\n", header[61] | (header[62] << 8) | (header[63] << 16) | (header[64] << 24));
	uint32_t slice_desc_file_ofs = header[65] | (header[66] << 8) | (header[67] << 16) | (header[68] << 24);
	printf("m_slice_desc_file_ofs = 0x%x\n", slice_desc_file_ofs);
	printf("m_extended_file_ofs = 0x%x\n", header[69] | (header[70] << 8) | (header[71] << 16) | (header[72] << 24));
	printf("m_extended_file_size = 0x%x\n", header[73] | (header[74] << 8) | (header[75] << 16) | (header[76] << 24));
	for (uint32_t i = 0; i < total_slices; ++i) {
		const uint8_t *slice = header + slice_desc_file_ofs + i * 23;
		printf("slice %i:\n", i);
		printf("  m_image_index = 0x%x\n", slice[0] | (slice[1] << 8) | (slice[2] << 16));
		printf("  m_level_index = 0x%x\n", slice[3]);
		printf("  m_flags = 0x%x\n", slice[4]);
		printf("  m_orig_width = 0x%x\n", slice[5] | (slice[6] << 8));
		printf("  m_orig_height = 0x%x\n", slice[7] | (slice[8] << 8));
		printf("  m_num_blocks_x = 0x%x\n", slice[9] | (slice[10] << 8));
		printf("  m_num_blocks_y = 0x%x\n", slice[11] | (slice[12] << 8));
		printf("  m_file_ofs = 0x%x\n", slice[13] | (slice[14] << 8) | (slice[15] << 16) | (slice[16] << 24));
		printf("  m_file_size = 0x%x\n", slice[17] | (slice[18] << 8) | (slice[19] << 16) | (slice[20] << 24));
		printf("  m_slice_data_crc16 = 0x%x\n", slice[21] | (slice[22] << 8));
	}
	FILE *f = fopen("out.basis", "w");
	fwrite(data, size, 1, f);
	fclose(f);

	basisu_basis_compressor_delete(compressor);

	basisu_basis_compressor_params_delete(params);

	basisu_image_delete(image2);
	basisu_image_delete(image1);

	basisu_job_pool_delete(jpool);

	basist_etc1_global_selector_codebook_delete(sel_codebook);

	return EXIT_SUCCESS;
}
