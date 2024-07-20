// generate random 3 tile bricks for current and preview
new_brick {
	for (i=0; i<3; i++) {
		tile_current[i] = randombytes_uniform(5)+1;	// current piece
		tile_next[i] = randombytes_uniform(5)+1;	// next piece
	}
	return 0;
}
