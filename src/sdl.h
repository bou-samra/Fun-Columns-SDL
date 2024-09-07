#ifndef SDL_H
#define SDL_H

int initSDL(void);
int shutdownSDL(void);
int check_key(void);
int init_gfx(void);

/////////// SDL structures ////////////
extern SDL_Window *window;
extern SDL_Renderer *sr;
extern SDL_Event event;
extern SDL_RWops* rwops_new;
extern SDL_Surface* image;
extern SDL_Texture * texture;

#endif
