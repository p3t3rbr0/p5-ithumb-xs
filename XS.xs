#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ithumb/ithumb.c"


MODULE = Ithumb::XS		PACKAGE = Ithumb::XS
PROTOTYPES: DISABLE

int
create_thumbnail(SV *params)
	CODE:
        SV **svp;
        HV *h_params = (HV*) SvRV(params);

        if (!hv_exists(h_params, "width", 5))
            Perl_croak(aTHX_ "'width' parameter is required");

        if (!hv_exists(h_params, "height", 6))
            Perl_croak(aTHX_ "'height' parameter is required");

        if (!hv_exists(h_params, "src", 3))
            Perl_croak(aTHX_ "'src' (source file path) parameter is required");

        if (!hv_exists(h_params, "dst", 3))
            Perl_croak(aTHX_ "'dst' (destionation file path) parameter is required");

        long width, height;
        char *src_path, *dst_path;

        svp = hv_fetch(h_params, "width", 5, 0);
        width = SvIV(*svp);

        svp = hv_fetch(h_params, "height", 6, 0);
        height = SvIV(*svp);

        svp = hv_fetch(h_params, "src", 3, 0);
        src_path = SvPV_nolen(*svp);

        svp = hv_fetch(h_params, "dst", 3, 0);
        dst_path = SvPV_nolen(*svp);

        Image image = { (int)width, (int)height, src_path, dst_path };

        int result = resize_and_crop(&image);

        if (result != 0) {
            IError error = get_error(result);
            Perl_croak(aTHX_ "%s", error.msg);
        }

        RETVAL = 1;
    OUTPUT:
        RETVAL
