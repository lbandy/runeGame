#ifndef IMAGELOADER_H
#define IMAGELOADER_H

class ImageLoader
{
public:
	SDL_Surface* LoadImage(const std::string &fileName);
};

#endif