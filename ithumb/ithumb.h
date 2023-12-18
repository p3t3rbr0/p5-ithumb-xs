/* ithumb errors constants */
enum IthumbErrors {
    ITHUMB_WIDTH_ERROR    = 101,
    ITHUMB_HEIGHT_ERROR   = 102,
    ITHUMB_SRC_ERROR      = 103,
    ITHUMB_DST_ERROR      = 104,
    ITHUMB_SCALING_ERROR  = 105,
    ITHUMB_CROPPING_ERROR = 106
};

/* main image structure */
typedef struct image_t {
    int w;
    int h;
    char *src;
    char *dst;
} Image;

/* ithumb error structure */
typedef struct error_t {
    unsigned short int code;
    char *msg;
} IError;

/* resize and crop source image */
int resize_and_crop(Image *image);

/* get error structure by error code */
IError get_error(int err_code);
