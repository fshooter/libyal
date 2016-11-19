/* Retrieves a specific sub ${value_description} by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *${python_module_name}_${type_name}_get_sub_${value_name}_by_index(
           PyObject *${python_module_name}_${type_name},
           int sub_${value_name}_index )
{
	PyObject *${value_name}_object                     = NULL;
	PyTypeObject *type_object                          = NULL;
	libcerror_error_t *error                           = NULL;
	${library_name}_${value_type}_t *sub_${value_name} = NULL;
	static char *function                              = "${python_module_name}_${type_name}_get_sub_${value_name}_by_index";
	int result                                         = 0;

	if( ${python_module_name}_${type_name} == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ${type_description}.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = ${library_name}_${type_name}_get_sub_${value_type}(
	          ( (${python_module_name}_${type_name}_t *) ${python_module_name}_${type_name} )->${type_name},
	          sub_${value_name}_index,
	          &sub_${value_name},
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		${python_module_name}_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub ${value_description}: %d.",
		 function,
		 sub_${value_name}_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	type_object = ${python_module_name}_${type_name}_get_${value_type}_type_object(
	               sub_${value_name} );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve ${value_type_description} type object.",
		 function );

		goto on_error;
	}
	${value_name}_object = ${python_module_name}_${value_type}_new(
	                        type_object,
	                        sub_${value_name},
	                        ( (${python_module_name}_${type_name}_t *) ${python_module_name}_${type_name} )->parent_object );

	if( ${value_name}_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sub ${value_type_description} object.",
		 function );

		goto on_error;
	}
	return( ${value_name}_object );

on_error:
	if( sub_${value_name} != NULL )
	{
		${library_name}_${value_type}_free(
		 &sub_${value_name},
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific sub ${value_description}
 * Returns a Python object if successful or NULL on error
 */
PyObject *${python_module_name}_${type_name}_get_sub_${value_name}(
           ${python_module_name}_${type_name}_t *${python_module_name}_${type_name},
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *${value_name}_object = NULL;
	static char *keyword_list[]    = { "sub_${value_name}_index", NULL };
	int sub_${value_name}_index    = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &sub_${value_name}_index ) == 0 )
	{
		return( NULL );
	}
	${value_name}_object = ${python_module_name}_${type_name}_get_sub_${value_type}_by_index(
	                        (PyObject *) ${python_module_name}_${type_name},
	                        sub_${value_name}_index );

	return( ${value_name}_object );
}

/* Retrieves a sequence and iterator object for the sub ${sequence_value_description}
 * Returns a Python object if successful or NULL on error
 */
PyObject *${python_module_name}_${type_name}_get_sub_${sequence_value_name}(
           ${python_module_name}_${type_name}_t *${python_module_name}_${type_name},
           PyObject *arguments ${python_module_name_upper_case}_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object                = NULL;
	libcerror_error_t *error                 = NULL;
	static char *function                    = "${python_module_name}_${type_name}_get_sub_${sequence_value_name}";
	int number_of_sub_${sequence_value_name} = 0;
	int result                               = 0;

	${python_module_name_upper_case}_UNREFERENCED_PARAMETER( arguments )

	if( ${python_module_name}_${type_name} == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ${type_description}.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = ${library_name}_${type_name}_get_number_of_sub_${sequence_value_name}(
	          ${python_module_name}_${type_name}->${type_name},
	          &number_of_sub_${sequence_value_name},
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		${python_module_name}_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sub ${sequence_value_description}.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = ${python_module_name}_${sequence_type_name}_new(
	                   (PyObject *) ${python_module_name}_${type_name},
	                   &${python_module_name}_${type_name}_get_sub_${value_name}_by_index,
	                   number_of_sub_${sequence_value_name} );

	if( sequence_object == NULL )
	{
		${python_module_name}_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}
