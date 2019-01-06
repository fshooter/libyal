#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "${library_name_suffix}_test_functions.h"
#include "${library_name_suffix}_test_getopt.h"
#include "${library_name_suffix}_test_libbfio.h"
#include "${library_name_suffix}_test_libcerror.h"
#include "${library_name_suffix}_test_${library_name}.h"
#include "${library_name_suffix}_test_macros.h"
#include "${library_name_suffix}_test_memory.h"

