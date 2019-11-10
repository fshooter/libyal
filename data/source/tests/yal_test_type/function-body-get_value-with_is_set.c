	/* Test regular cases
	 */
	result = ${library_name}_${type_name}_get_${value_name}(
	          ${type_name},
	          &${value_name},
	          &error );

	${library_name_suffix_upper_case}_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	${library_name_suffix_upper_case}_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	${value_name}_is_set = result;

	/* Test error cases
	 */
	result = ${library_name}_${type_name}_get_${value_name}(
	          NULL,
	          &${value_name},
	          &error );

	${library_name_suffix_upper_case}_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	${library_name_suffix_upper_case}_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( ${value_name}_is_set != 0 )
	{
		result = ${library_name}_${type_name}_get_${value_name}(
		          ${type_name},
		          NULL,
		          &error );

		${library_name_suffix_upper_case}_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		${library_name_suffix_upper_case}_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
