	if( mount_handle->password != NULL )
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( ${library_name}_file_set_utf16_password(
		     ${mount_tool_source_type},
		     (uint16_t *) mount_handle->password,
		     mount_handle->password_length,
		     error ) != 1 )
#else
		if( ${library_name}_file_set_utf8_password(
		     ${mount_tool_source_type},
		     (uint8_t *) mount_handle->password,
		     mount_handle->password_length,
		     error ) != 1 )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set password.",
			 function );

			goto on_error;
		}
	}
