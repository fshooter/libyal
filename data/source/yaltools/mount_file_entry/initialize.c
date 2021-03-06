/* Creates a file entry
 * Make sure the value file_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int mount_file_entry_initialize(
     mount_file_entry_t **file_entry,
     mount_file_system_t *file_system,
     const system_character_t *name,
     size_t name_length,
     ${library_name}_${mount_tool_file_entry_type}_t *${mount_tool_file_entry_type_name},
     libcerror_error_t **error )
{
	static char *function = "mount_file_entry_initialize";

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( *file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file entry value already set.",
		 function );

		return( -1 );
	}
	if( file_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file system.",
		 function );

		return( -1 );
	}
	if( name_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	*file_entry = memory_allocate_structure(
	               mount_file_entry_t );

	if( *file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_entry,
	     0,
	     sizeof( mount_file_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file entry.",
		 function );

		memory_free(
		 *file_entry );

		*file_entry = NULL;

		return( -1 );
	}
	( *file_entry )->file_system = file_system;

	if( name != NULL )
	{
		( *file_entry )->name = system_string_allocate(
		                         name_length + 1 );

		if( ( *file_entry )->name == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name string.",
			 function );

			goto on_error;
		}
		if( name_length > 0 )
		{
			if( system_string_copy(
			     ( *file_entry )->name,
			     name,
			     name_length ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy name.",
				 function );

				goto on_error;
			}
		}
		( *file_entry )->name[ name_length ] = 0;

		( *file_entry )->name_size = name_length + 1;
	}
	( *file_entry )->${mount_tool_file_entry_type_name} = ${mount_tool_file_entry_type_name};

	return( 1 );

on_error:
	if( *file_entry != NULL )
	{
		if( ( *file_entry )->name != NULL )
		{
			memory_free(
			 ( *file_entry )->name );
		}
		memory_free(
		 *file_entry );

		*file_entry = NULL;
	}
	return( -1 );
}

