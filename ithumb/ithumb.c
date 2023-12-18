/*
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2018-2020 Peter P. Neuromantic <p.brovchenko@protonmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <string.h>
#include <Imlib2.h>

#include "ithumb.h"


IError get_error(int err_code) {
    IError error;

    switch(err_code) {
    case IMLIB_LOAD_ERROR_NONE:
        break;
    case IMLIB_LOAD_ERROR_FILE_DOES_NOT_EXIST:
        error.msg = "[Ithumb::XS] imlib error: File does not exist";
        break;
    case IMLIB_LOAD_ERROR_FILE_IS_DIRECTORY:
        error.msg = "[Ithumb::XS] imlib error: File is directory";
        break;
    case IMLIB_LOAD_ERROR_PERMISSION_DENIED_TO_READ:
        error.msg = "[Ithumb::XS] imlib error: Permission denied";
        break;
    case IMLIB_LOAD_ERROR_NO_LOADER_FOR_FILE_FORMAT:
        error.msg = "[Ithumb::XS] imlib error: No loader for file format";
        break;
    case IMLIB_LOAD_ERROR_PATH_TOO_LONG:
        error.msg = "[Ithumb::XS] imlib error: Path too long";
        break;
    case IMLIB_LOAD_ERROR_PATH_COMPONENT_NON_EXISTANT:
        error.msg = "[Ithumb::XS] imlib error: Path component non existant";
        break;
    case IMLIB_LOAD_ERROR_PATH_COMPONENT_NOT_DIRECTORY:
        error.msg = "[Ithumb::XS] imlib error: Path component not directory";
        break;
    case IMLIB_LOAD_ERROR_PATH_POINTS_OUTSIDE_ADDRESS_SPACE:
        error.msg = "[Ithumb::XS] imlib error: Path points outside address space";
        break;
    case IMLIB_LOAD_ERROR_TOO_MANY_SYMBOLIC_LINKS:
        error.msg = "[Ithumb::XS] imlib error: Too many symbolic links";
        break;
    case IMLIB_LOAD_ERROR_OUT_OF_MEMORY:
        error.msg = "[Ithumb::XS] imlib error: Out of memory";
        break;
    case IMLIB_LOAD_ERROR_OUT_OF_FILE_DESCRIPTORS:
        error.msg = "[Ithumb::XS] imlib error: Out of file descriptors";
        break;
    case IMLIB_LOAD_ERROR_PERMISSION_DENIED_TO_WRITE:
        error.msg = "[Ithumb::XS] imlib error: Permission denied to write";
        break;
    case IMLIB_LOAD_ERROR_OUT_OF_DISK_SPACE:
        error.msg = "[Ithumb::XS] imlib error: Out of disk space";
        break;
    case IMLIB_LOAD_ERROR_UNKNOWN:
        error.msg = "[Ithumb::XS] imlib error: Unknown";
        break;
    case ITHUMB_WIDTH_ERROR:
        error.msg = "[Ithumb::XS] error: invalid value of width (width must be a positive integer)";
        break;
    case ITHUMB_HEIGHT_ERROR:
        error.msg = "[Ithumb::XS] error: invalid value of height (height must be a positive integer)";
        break;
    case ITHUMB_SRC_ERROR:
        error.msg = "[Ithumb::XS] error: invalid value of source file path";
        break;
    case ITHUMB_DST_ERROR:
        error.msg = "[Ithumb::XS] error: invalid value of destination file path";
        break;
    case ITHUMB_SCALING_ERROR:
        error.msg = "[Ithumb::XS] error: image can't be a scaled";
        break;
    case ITHUMB_CROPPING_ERROR:
        error.msg = "[Ithumb::XS] error: image can't be croped";
        break;
    default:
        break;
    }

    error.code = err_code;

    return error;
}

int resize_and_crop(Image *image) {
    float aspect_ration_orig, aspect_ratio_new;

    int width = 0, height = 0;

    Imlib_Image src_img, scaled_img, croped_img;
    Imlib_Load_Error imlib_error = IMLIB_LOAD_ERROR_NONE;

    if (image->w <= 0)
        return ITHUMB_WIDTH_ERROR;

    if (image->h <= 0)
        return ITHUMB_HEIGHT_ERROR;

    if (!strlen(image->src))
        return ITHUMB_SRC_ERROR;

    if (!strlen(image->dst))
        return ITHUMB_DST_ERROR;

    src_img = imlib_load_image_with_error_return(image->src, &imlib_error);

    if (imlib_error)
        return imlib_error;

    imlib_context_set_image(src_img);

    width  = imlib_image_get_width();
    height = imlib_image_get_height();
    aspect_ration_orig = (float)width / (float)height;
    aspect_ratio_new = (float)image->w / (float)image->h;

    if ( aspect_ratio_new > 1 ) {
        scaled_img = imlib_create_cropped_scaled_image(
            0, 0, width, height, (int)(image->h * aspect_ration_orig), image->h);
    } else {
        scaled_img = imlib_create_cropped_scaled_image(
            0, 0, width, height, (int)(image->h * aspect_ration_orig), image->h);
    }

    scaled_img = imlib_create_cropped_scaled_image(
        0, 0, width, height, 640, 360);

    if (!scaled_img)
        return ITHUMB_SCALING_ERROR;

    imlib_context_set_image(scaled_img);

    croped_img = imlib_create_cropped_image(0, 0, image->w, 200);

    if (!croped_img)
        return ITHUMB_CROPPING_ERROR;

    imlib_context_set_image(croped_img);
    imlib_save_image_with_error_return(image->dst, &imlib_error);

    if (imlib_error)
        return imlib_error;

    return 0;
}
