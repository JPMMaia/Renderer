function(target_add_hlsl_shader target_name relative_directory shader_name)

	set(input_filename "${CMAKE_CURRENT_SOURCE_DIR}/${relative_directory}/${shader_name}.hlsl")	
	set(output_filename "${CMAKE_CFG_INTDIR}/${relative_directory}/${shader_name}.csv")

	find_file(FXC "fxc.exe")
	message("PATH TO FXC: ${FXC}")

	add_custom_command(
		COMMAND ${FXC} ARGS -V "${input_filename}" -o "${output_filename}"
		MAIN_DEPENDENCY "${input_filename}"
		OUTPUT "${output_filename}"
		USES_TERMINAL
	)

	target_sources(${target_name} PRIVATE 
		"${input_filename}" 
		"${CMAKE_CURRENT_BINARY_DIR}/${output_filename}"
	)

	source_group("Resource Files\\${relative_directory}" FILES "${input_filename}")
	source_group("Generated Files\\${relative_directory}" FILES "${CMAKE_CURRENT_BINARY_DIR}/${output_filename}")

endfunction()
