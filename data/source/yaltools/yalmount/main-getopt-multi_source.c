	while( ( option = ${tools_name}_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "${mount_tool_getopt_string}" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

${mount_tool_options_switch}
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source ${mount_tool_source_type}(s).\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	sources           = &( argv[ optind ] );
	number_of_sources = argc - optind - 1;

	if( ( optind + 1 ) == argc )
	{
		fprintf(
		 stderr,
		 "Missing mount point.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	mount_point = argv[ argc - 1 ];

