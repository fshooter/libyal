/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc ${library_name_suffix_upper_case}_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] ${library_name_suffix_upper_case}_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc ${library_name_suffix_upper_case}_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] ${library_name_suffix_upper_case}_TEST_ATTRIBUTE_UNUSED )
#endif
{
	${library_name_suffix_upper_case}_TEST_UNREFERENCED_PARAMETER( argc )
	${library_name_suffix_upper_case}_TEST_UNREFERENCED_PARAMETER( argv )

	${test_to_run}

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

