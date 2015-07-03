/*
    Name:       const.c
    Purpose:    Builtin constants for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* addConst: add numeric constant */
void addConst( char *name, int value )
{
    int     pos;
    Symbol  *s;

    s = createConst( name );
    pos = s->stackPos;
    stack[pos].datatype = DATA_NUMBER;
    stack[pos].value.number = value;
}

/* addStrConst: add string constant */
void addStrConst( char *name, char *value )
{
    int     pos;
    Symbol  *s;

    s = createConst( name );
    pos = s->stackPos;
    stack[pos].datatype = DATA_STRING;
    stack[pos].value.string = eCopyString(value);
}


/* addPtrConst: wrap a constant pointer */
void addConstPtr( char *name, int classIndex, int pointer )
{
    int  handle;

    /* wrap the pointer */
    handle = (int)addObject( classIndex, pointer );

    /* create as a normal constant */
    addConst( name, handle );

}

/* initConsts: initialize the builtin constants */
void initConsts() {

    /* common */

    addStrConst( "dcbasic_version",   RELEASE );
    addStrConst( "dcbasic_date",      DATEOF );

    addConst( "true",  !0 );
    addConst( "false",  0 );
    addConst( "null",   0 );


#ifdef FBSD
    addConst( "isfbsd", !0 );
    addStrConst( "os", "fbsd" );
#else
    addConst( "isfbsd", 0 );
#endif

#ifdef LINUX
    addConst( "islinux", !0 );
    addStrConst( "os", "linux" );
#else
    addConst( "islinux", 0 );
#endif

#ifdef GP2X
    addConst( "isgp2x", !0 );
    addStrConst( "os", "gp2x" );
#else
    addConst( "isgp2x", 0 );
#endif

#ifdef WIN32
    addConst( "iswin32", !0 );
    addStrConst( "os", "win32" );
#else
    addConst( "iswin32", 0 );
#endif

#ifdef __APPLE__
    addConst( "isosx", !0 );
    addStrConst( "os", "osx" );
#else
    addConst( "isosx", 0 );
#endif

#ifdef __MORPHOS__
    addConst( "ismos", !0);
    addStrConst( "os", "morphos" );
#else
    addConst( "ismos", 0 );
#endif

#ifdef OS4
    addConst( "isos4", !0);
    addStrConst( "os", "os4" );
#else
    addConst( "isos4", 0 );
#endif

#ifdef NETBSD
    addConst( "isnetbsd", !0);
    addStrConst( "os", "netbsd" );
#else
    addConst( "isnetbsd", 0);
#endif

#ifdef OPENBSD
    addConst( "isopenbsd", !0);
    addStrConst( "os", "openbsd" );
#else
    addConst( "isopenbsd", 0);
#endif


	addConst("num_screens",NUM_SCREENS);
	addConst("num_images",NUM_IMAGES);

	addConst("num_sprites",NUM_SPRITES);
	addConst("num_bobs",NUM_BOBS);

	addConst("num_waves",NUM_WAVES);

	addConst("num_socks",NUM_SOCKS);

	addConst("num_membank",NUM_MEMBANKS);

	addConst("dual_playfields",1);
	addConst("screen_colorkey",2);

	addConst( "k_backspace", 8 );
	addConst( "k_tab", 9 );
	addConst( "k_clear",12);
	addConst( "k_return",13);
	addConst( "k_pause",19);
	addConst( "k_escape",27);
	addConst( "k_esc",27);
	addConst( "k_space",32);
	addConst( "k_exclaim",33);
	addConst( "k_quotedbl",34);
	addConst( "k_hash",35);
	addConst( "k_dollar",36);
	addConst( "k_ampersand",38);
	addConst( "k_quote",39);
	addConst( "k_leftparen",40);
	addConst( "k_rightparent",41);
	addConst( "k_asterisk",42);
	addConst( "k_plus", 43);
	addConst( "k_comma", 44);
	addConst( "k_minus", 45);
	addConst( "k_period", 46);
	addConst( "k_slash", 47);
	addConst( "k_colon", 58);
	addConst( "k_semicolon", 59);
	addConst( "k_less", 60);
	addConst( "k_equals", 61);
	addConst( "k_greater", 62);
	addConst( "k_question", 63);
	addConst( "k_at", 64);
	addConst( "k_leftbracket", 91);
	addConst( "k_backslash", 92);
	addConst( "k_rightbracket", 93);
	addConst( "k_caret", 94);
	addConst( "k_underscore", 95);
	addConst( "k_backquote", 96);
	addConst( "k_delete", 127);

	addConst( "k_1", 49);
	addConst( "k_2", 50);
	addConst( "k_3", 51);
	addConst( "k_4", 52);
	addConst( "k_5", 53);
	addConst( "k_6", 54);
	addConst( "k_7", 55);
	addConst( "k_8", 56);
	addConst( "k_9", 57);
	addConst( "k_0", 48);

	addConst( "k_kp0",256);
	addConst( "k_kp1",257);
	addConst( "k_kp2",258);
	addConst( "k_kp3",259);
	addConst( "k_kp4",260);
	addConst( "k_kp5",261);
	addConst( "k_kp6",262);
	addConst( "k_kp7",263);
	addConst( "k_kp8",264);
	addConst( "k_kp9",265);
	addConst( "k_kp_period",266);
	addConst( "k_kp_divide",267);
	addConst( "k_kp_multiply",268);
	addConst( "k_kp_minus",269);
	addConst( "k_kp_plus",270);
	addConst( "k_kp_enter",271);
	addConst( "k_kp_equals",272);

	addConst( "k_up", 273);
	addConst( "k_down", 274);
	addConst( "k_right", 275);
	addConst( "k_left", 276);

	addConst( "k_insert", 277);
	addConst( "k_home", 278);
	addConst( "k_end", 279);
	addConst( "k_pageup", 280);
	addConst( "k_pagedown", 281);

	addConst( "k_f1",282);
	addConst( "k_f2",283);
	addConst( "k_f3",284);
	addConst( "k_f4",285);
	addConst( "k_f5",286);
	addConst( "k_f6",287);
	addConst( "k_f7",288);
	addConst( "k_f8",289);
	addConst( "k_f9",290);
	addConst( "k_f10",291);
	addConst( "k_f11",292);
	addConst( "k_f12",293);
	addConst( "k_f13",294);
	addConst( "k_f14",295);
	addConst( "k_f15",296);

	addConst( "k_numlock",300);
	addConst( "k_capslock",301);
	addConst( "k_scrollock",302);
	addConst( "k_rshift",303);
	addConst( "k_lshift",304);
	addConst( "k_rctrl",305);
	addConst( "k_lctrl",306);
	addConst( "k_ralt",307);
	addConst( "k_lalt",308);
	addConst( "k_rmeta",309);
	addConst( "k_lmeta",310);
	addConst( "k_lsuper",311);		/* Left "Windows" key */
	addConst( "k_rsuper",312);		/* Right "Windows" key */
	addConst( "k_mode",313);		/* "Alt Gr" key */
	addConst( "k_compose",314);		/* Multi-key compose key */
	addConst( "k_help",315);
	addConst( "k_print",316);
	addConst( "k_sysreq",317);
	addConst( "k_break",318);
	addConst( "k_menu",319);
	addConst( "k_power",320);		/* Power Macintosh power key */
	addConst( "k_euro",321);		/* Some european keyboards */
	addConst( "k_undo",322);		/* Atari keyboard has Undo */
/************ OPENGL parameter  *******************************************************************/

	/* beginmode */
	addConst("gl_points",0);
	addConst("gl_lines",1);
	addConst("gl_line_loop",2);
	addConst("gl_line_strip",3);
	addConst("gl_triangles",4);
	addConst("gl_triangle_strip",5);
	addConst("gl_triangle_fan",6);
	addConst("gl_quads",7);
	addConst("gl_quad_strip",8);
	addConst("gl_polygon",9);


	/* getpname */
	addConst("gl_current_color",                  0x0b00);
	addConst("gl_current_index",                  0x0b01);
	addConst("gl_current_normal",                 0x0b02);
	addConst("gl_current_texture_coords",         0x0b03);
	addConst("gl_current_raster_color",           0x0b04);
	addConst("gl_current_raster_index",           0x0b05);
	addConst("gl_current_raster_texture_coords",  0x0b06);
	addConst("gl_current_raster_position",        0x0b07);
	addConst("gl_current_raster_position_valid",  0x0b08);
	addConst("gl_current_raster_distance",        0x0b09);
	addConst("gl_point_smooth",                   0x0b10);
	addConst("gl_point_size",                     0x0b11);
	addConst("gl_smooth_point_size_range",        0x0b12);
        addConst("gl_smooth_point_size_granularity",  0x0b13);
        addConst("gl_point_size_range",               0x0000);
        addConst("gl_point_size_granularity",         0x0000);
        addConst("gl_line_smooth",                    0x0b20);
        addConst("gl_line_width",                     0x0b21);
        addConst("gl_smooth_line_width_range",        0x0b22);
        addConst("gl_smooth_line_width_granularity",  0x0b23);
        addConst("gl_line_width_range",               0x0000);
        addConst("gl_line_width_granularity",         0x0000);
        addConst("gl_line_stipple",                   0x0b24);
        addConst("gl_line_stipple_pattern",           0x0b25);
        addConst("gl_line_stipple_repeat",            0x0b26);
        addConst("gl_list_mode",                      0x0b30);
        addConst("gl_max_list_nesting",               0x0b31);
        addConst("gl_list_base",                      0x0b32);
        addConst("gl_list_index",                     0x0b33);
        addConst("gl_polygon_mode",                   0x0b40);
        addConst("gl_polygon_smooth",                 0x0b41);
        addConst("gl_polygon_stipple",                0x0b42);
        addConst("gl_cull_face",                      0x0b44);
        addConst("gl_cull_face_mode",                 0x0b45);
        addConst("gl_front_face",                     0x0b46);
        addConst("gl_lighting",                       0x0b50);
        addConst("gl_light_model_local_viewer",       0x0b51);
        addConst("gl_light_model_two_side",           0x0b52);
        addConst("gl_light_model_ambient",            0x0b53);
        addConst("gl_shade_model",                    0x0b54);
        addConst("gl_color_material_face",            0x0b55);
        addConst("gl_color_material_parameter",       0x0b56);
        addConst("gl_color_material",                 0x0b57);
        addConst("gl_fog",                            0x0b60);
        addConst("gl_fog_index",                      0x0b61);
        addConst("gl_fog_density",                    0x0b62);
        addConst("gl_fog_start",                      0x0b63);
        addConst("gl_fog_end",                        0x0b64);
        addConst("gl_fog_mode",                       0x0b65);
        addConst("gl_fog_color",                      0x0b66);
        addConst("gl_depth_range",                    0x0b70);
        addConst("gl_depth_test",                     0x0b71);
        addConst("gl_depth_writemask",                0x0b72);
        addConst("gl_depth_clear_value",              0x0b73);
        addConst("gl_depth_func",                     0x0b74);
        addConst("gl_accum_clear_value",              0x0b80);
        addConst("gl_stencil_test",                   0x0b90);
        addConst("gl_stencil_clear_value",            0x0b91);
        addConst("gl_stencil_func",                   0x0b92);
        addConst("gl_stencil_value_mask",             0x0b93);
        addConst("gl_stencil_fail",                   0x0b94);
        addConst("gl_stencil_pass_depth_fail",        0x0b95);
        addConst("gl_stencil_pass_depth_pass",        0x0b96);
        addConst("gl_stencil_ref",                    0x0b97);
        addConst("gl_stencil_writemask",              0x0b98);
        addConst("gl_matrix_mode",                    0x0ba0);
        addConst("gl_normalize",                      0x0ba1);
        addConst("gl_viewport",                       0x0ba2);
        addConst("gl_modelview_stack_depth",          0x0ba3);
        addConst("gl_projection_stack_depth",         0x0ba4);
        addConst("gl_texture_stack_depth",            0x0ba5);
        addConst("gl_modelview_matrix",               0x0ba6);
        addConst("gl_projection_matrix",              0x0ba7);
        addConst("gl_texture_matrix",                 0x0ba8);
        addConst("gl_attrib_stack_depth",             0x0bb0);
        addConst("gl_client_attrib_stack_depth",      0x0bb1);
        addConst("gl_alpha_test",                     0x0bc0);
        addConst("gl_alpha_test_func",                0x0bc1);
        addConst("gl_alpha_test_ref",                 0x0bc2);
        addConst("gl_dither",                         0x0bd0);
        addConst("gl_blend_dst",                      0x0be0);
        addConst("gl_blend_src",                      0x0be1);
        addConst("gl_blend",                          0x0be2);
        addConst("gl_logic_op_mode",                  0x0bf0);
        addConst("gl_index_logic_op",                 0x0bf1);
        addConst("gl_logic_op",                       0x0bf1);
        addConst("gl_color_logic_op",                 0x0bf2);
        addConst("gl_aux_buffers",                    0x0c00);
        addConst("gl_draw_buffer",                    0x0c01);
        addConst("gl_read_buffer",                    0x0c02);
        addConst("gl_scissor_box",                    0x0c10);
        addConst("gl_scissor_test",                   0x0c11);
        addConst("gl_index_clear_value",              0x0c20);
        addConst("gl_index_writemask",                0x0c21);
        addConst("gl_color_clear_value",              0x0c22);
        addConst("gl_color_writemask",                0x0c23);
        addConst("gl_index_mode",                     0x0c30);
        addConst("gl_rgba_mode",                      0x0c31);
        addConst("gl_doublebuffer",                   0x0c32);
        addConst("gl_stereo",                         0x0c33);
        addConst("gl_render_mode",                    0x0c40);
        addConst("gl_perspective_correction_hint",    0x0c50);
        addConst("gl_point_smooth_hint",              0x0c51);
        addConst("gl_line_smooth_hint",               0x0c52);
        addConst("gl_polygon_smooth_hint",            0x0c53);
        addConst("gl_fog_hint",                       0x0c54);
        addConst("gl_texture_gen_s",                  0x0c60);
        addConst("gl_texture_gen_t",                  0x0c61);
        addConst("gl_texture_gen_r",                  0x0c62);
        addConst("gl_texture_gen_q",                  0x0c63);
        addConst("gl_pixel_map_i_to_i_size",          0x0cb0);
        addConst("gl_pixel_map_s_to_s_size",          0x0cb1);
        addConst("gl_pixel_map_i_to_r_size",          0x0cb2);
        addConst("gl_pixel_map_i_to_g_size",          0x0cb3);
        addConst("gl_pixel_map_i_to_b_size",          0x0cb4);
        addConst("gl_pixel_map_i_to_a_size",          0x0cb5);
        addConst("gl_pixel_map_r_to_r_size",          0x0cb6);
        addConst("gl_pixel_map_g_to_g_size",          0x0cb7);
        addConst("gl_pixel_map_b_to_b_size",          0x0cb8);
        addConst("gl_pixel_map_a_to_a_size",          0x0cb9);
        addConst("gl_unpack_swap_bytes",              0x0cf0);
        addConst("gl_unpack_lsb_first",               0x0cf1);
        addConst("gl_unpack_row_length",              0x0cf2);
        addConst("gl_unpack_skip_rows",               0x0cf3);
        addConst("gl_unpack_skip_pixels",             0x0cf4);
        addConst("gl_unpack_alignment",               0x0cf5);
        addConst("gl_pack_swap_bytes",                0x0d00);
        addConst("gl_pack_lsb_first",                 0x0d01);
        addConst("gl_pack_row_length",                0x0d02);
        addConst("gl_pack_skip_rows",                 0x0d03);
        addConst("gl_pack_skip_pixels",               0x0d04);
        addConst("gl_pack_alignment",                 0x0d05);
        addConst("gl_map_color",                      0x0d10);
        addConst("gl_map_stencil",                    0x0d11);
        addConst("gl_index_shift",                    0x0d12);
        addConst("gl_index_offset",                   0x0d13);
        addConst("gl_red_scale",                      0x0d14);
        addConst("gl_red_bias",                       0x0d15);
        addConst("gl_zoom_x",                         0x0d16);
        addConst("gl_zoom_y",                         0x0d17);
        addConst("gl_green_scale",                    0x0d18);
        addConst("gl_green_bias",                     0x0d19);
        addConst("gl_blue_scale",                     0x0d1a);
        addConst("gl_blue_bias",                      0x0d1b);
        addConst("gl_alpha_scale",                    0x0d1c);
        addConst("gl_alpha_bias",                     0x0d1d);
        addConst("gl_depth_scale",                    0x0d1e);
        addConst("gl_depth_bias",                     0x0d1f);
        addConst("gl_max_eval_order",                 0x0d30);
        addConst("gl_max_lights",                     0x0d31);
        addConst("gl_max_clip_planes",                0x0d32);
        addConst("gl_max_texture_size",               0x0d33);
        addConst("gl_max_pixel_map_table",            0x0d34);
        addConst("gl_max_attrib_stack_depth",         0x0d35);
        addConst("gl_max_modelview_stack_depth",      0x0d36);
        addConst("gl_max_name_stack_depth",           0x0d37);
        addConst("gl_max_projection_stack_depth",     0x0d38);
        addConst("gl_max_texture_stack_depth",        0x0d39);
        addConst("gl_max_viewport_dims",              0x0d3a);
        addConst("gl_max_client_attrib_stack_depth",  0x0d3b);
        addConst("gl_subpixel_bits",                  0x0d50);
        addConst("gl_index_bits",                     0x0d51);
        addConst("gl_red_bits",                       0x0d52);
        addConst("gl_green_bits",                     0x0d53);
        addConst("gl_blue_bits",                      0x0d54);
        addConst("gl_alpha_bits",                     0x0d55);
        addConst("gl_depth_bits",                     0x0d56);
        addConst("gl_stencil_bits",                   0x0d57);
        addConst("gl_accum_red_bits",                 0x0d58);
        addConst("gl_accum_green_bits",               0x0d59);
        addConst("gl_accum_blue_bits",                0x0d5a);
        addConst("gl_accum_alpha_bits",               0x0d5b);
        addConst("gl_name_stack_depth",               0x0d70);
        addConst("gl_auto_normal",                    0x0d80);
        addConst("gl_map1_color_4",                   0x0d90);
        addConst("gl_map1_index",                     0x0d91);
        addConst("gl_map1_normal",                    0x0d92);
        addConst("gl_map1_texture_coord_1",           0x0d93);
        addConst("gl_map1_texture_coord_2",           0x0d94);
        addConst("gl_map1_texture_coord_3",           0x0d95);
        addConst("gl_map1_texture_coord_4",           0x0d96);
        addConst("gl_map1_vertex_3",                  0x0d97);
        addConst("gl_map1_vertex_4",                  0x0d98);
        addConst("gl_map2_color_4",                   0x0db0);
        addConst("gl_map2_index",                     0x0db1);
        addConst("gl_map2_normal",                    0x0db2);
        addConst("gl_map2_texture_coord_1",           0x0db3);
        addConst("gl_map2_texture_coord_2",           0x0db4);
        addConst("gl_map2_texture_coord_3",           0x0db5);
        addConst("gl_map2_texture_coord_4",           0x0db6);
        addConst("gl_map2_vertex_3",                  0x0db7);
        addConst("gl_map2_vertex_4",                  0x0db8);
        addConst("gl_map1_grid_domain",               0x0dd0);
        addConst("gl_map1_grid_segments",             0x0dd1);
        addConst("gl_map2_grid_domain",               0x0dd2);
        addConst("gl_map2_grid_segments",             0x0dd3);
        addConst("gl_texture_1d",                     0x0de0);
        addConst("gl_texture_2d",                     0x0de1);
        addConst("gl_feedback_buffer_pointer",        0x0df0);
        addConst("gl_feedback_buffer_size",           0x0df1);
        addConst("gl_feedback_buffer_type",           0x0df2);
        addConst("gl_selection_buffer_pointer",       0x0df3);
        addConst("gl_selection_buffer_size",          0x0df4);
        addConst("gl_polygon_offset_units",           0x2a00);
        addConst("gl_polygon_offset_point",           0x2a01);
        addConst("gl_polygon_offset_line",            0x2a02);
        addConst("gl_polygon_offset_fill",            0x8037);
        addConst("gl_polygon_offset_factor",          0x8038);
        addConst("gl_texture_binding_1d",             0x8068);
        addConst("gl_texture_binding_2d",             0x8069);
        addConst("gl_texture_binding_3d",             0x806a);
        addConst("gl_vertex_array",                   0x8074);
        addConst("gl_normal_array",                   0x8075);
        addConst("gl_color_array",                    0x8076);
        addConst("gl_index_array",                    0x8077);
        addConst("gl_texture_coord_array",            0x8078);
        addConst("gl_edge_flag_array",                0x8079);
        addConst("gl_vertex_array_size",              0x807a);
        addConst("gl_vertex_array_type",              0x807b);
        addConst("gl_vertex_array_stride",            0x807c);
        addConst("gl_normal_array_type",              0x807e);
        addConst("gl_normal_array_stride",            0x807f);
        addConst("gl_color_array_size",               0x8081);
        addConst("gl_color_array_type",               0x8082);
        addConst("gl_color_array_stride",             0x8083);
        addConst("gl_index_array_type",               0x8085);
        addConst("gl_index_array_stride",             0x8086);
        addConst("gl_texture_coord_array_size",       0x8088);
        addConst("gl_texture_coord_array_type",       0x8089);
        addConst("gl_texture_coord_array_stride",     0x808a);
        addConst("gl_edge_flag_array_stride",         0x808c);

        addConst("gl_texture_width",                  0x1000);
        addConst("gl_texture_height",                 0x1001);
        addConst("gl_texture_internal_format",        0x1003);
        addConst("gl_texture_components",             0x1003);
        addConst("gl_texture_border_color",           0x1004);
        addConst("gl_texture_border",                 0x1005);
        addConst("gl_texture_red_size",               0x805c);
        addConst("gl_texture_green_size",             0x805d);
        addConst("gl_texture_blue_size",              0x805e);
        addConst("gl_texture_alpha_size",             0x805f);
        addConst("gl_texture_luminance_size",         0x8060);
        addConst("gl_texture_intensity_size",         0x8061);
        addConst("gl_texture_priority",               0x8066);
        addConst("gl_texture_resident",               0x8067);

	/*
    * gp2x joystick buttons
	 */
        addConst("gp2x_north",     0x00001);
        addConst("gp2x_northwest", 0x00002);
        addConst("gp2x_west",      0x00004);
        addConst("gp2x_southwest", 0x00008);
        addConst("gp2x_south",     0x00010);
        addConst("gp2x_southeast", 0x00020);
        addConst("gp2x_east",      0x00040);
        addConst("gp2x_northeast", 0x00080);
        addConst("gp2x_center",    0x40000);

        addConst("gp2x_voldown",   0x20000);
        addConst("gp2x_volup",     0x10000);

        addConst("gp2x_a",         0x01000);
        addConst("gp2x_b",         0x02000);
        addConst("gp2x_x",         0x04000);
        addConst("gp2x_y",         0x08000);

        addConst("gp2x_start",     0x00100);
        addConst("gp2x_select",    0x00200);

        addConst("gp2x_topleft",   0x00400);
        addConst("gp2x_topright",  0x00800);

}
