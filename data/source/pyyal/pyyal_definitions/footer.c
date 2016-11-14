	return( 1 );

on_error:
	if( type_object->tp_dict != NULL )
	{
		Py_DecRef(
		 type_object->tp_dict );

		type_object->tp_dict = NULL;
	}
	return( -1 );
}

/* Creates a new ${definitions_description} object
 * Returns a Python object if successful or NULL on error
 */
PyObject *${python_module_name}_${definitions_name}_new(
           void )
{
	${python_module_name}_${definitions_name}_t *${python_module_name}_${definitions_name} = NULL;
	static char *function                                                                  = "${python_module_name}_${definitions_name}_new";

	${python_module_name}_${definitions_name} = PyObject_New(
	                                             struct ${python_module_name}_${definitions_name},
	                                             &${python_module_name}_${definitions_name}_type_object );

	if( ${python_module_name}_${definitions_name} == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize ${definitions_description}.",
		 function );

		goto on_error;
	}
	if( ${python_module_name}_${definitions_name}_init(
	     ${python_module_name}_${definitions_name} ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize ${definitions_description}.",
		 function );

		goto on_error;
	}
	return( (PyObject *) ${python_module_name}_${definitions_name} );

on_error:
	if( ${python_module_name}_${definitions_name} != NULL )
	{
		Py_DecRef(
		 (PyObject *) ${python_module_name}_${definitions_name} );
	}
	return( NULL );
}

/* Intializes a ${definitions_description} object
 * Returns 0 if successful or -1 on error
 */
int ${python_module_name}_${definitions_name}_init(
     ${python_module_name}_${definitions_name}_t *${python_module_name}_${definitions_name} )
{
	static char *function = "${python_module_name}_${definitions_name}_init";

	if( ${python_module_name}_${definitions_name} == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid ${definitions_description}.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Frees a ${definitions_description} object
 */
void ${python_module_name}_${definitions_name}_free(
      ${python_module_name}_${definitions_name}_t *${python_module_name}_${definitions_name} )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "${python_module_name}_${definitions_name}_free";

	if( ${python_module_name}_${definitions_name} == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid ${definitions_description}.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           ${python_module_name}_${definitions_name} );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	ob_type->tp_free(
	 (PyObject*) ${python_module_name}_${definitions_name} );
}

