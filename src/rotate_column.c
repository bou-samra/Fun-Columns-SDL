int rotate_col (void)
{
	int temp;
	temp = tile_current[0];
	tile_current[0] = tile_current[1];
	tile_current[1] = tile_current[2];
	tile_current[2] = temp;
	return 0;
}
