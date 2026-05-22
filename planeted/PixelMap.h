#ifndef PLANETED_PIXELMAP_H
#define PLANETED_PIXELMAP_H

#include <functional>
#include <stdexcept>
#include <vector>

#include "Color.h"

namespace Planeted
{
    using ColorFunction = std::function<std::uint8_t(const int x, const int y)>;

    class PixelMap
    {
    public:

        PixelMap(int width, int height)
            : width(width), height(height), pixels(width * height, Colors::Green)
        { }

        void PutPixel(int x, int y, const Color& color)
        {
            if(x < 0 || x >= this->width || y < 0 || y >= this->height)
            {
                throw std::out_of_range("Pixel coordinates out of bounds.");
            }
            this->pixels[y * this->width + x] = color;
        }

        void FillRect(int x, int y, int w, int h, const Color& color)
        {
            int x0 = std::max(x, 0);
            int y0 = std::max(y, 0);
            int x1 = std::min(this->width, x + w);
            int y1 = std::min(this->height, y + h);

            for(int j = y0; j < y1; ++j)
            {
                int start = j * this->width;

                for(int i = x0; i < x1; ++i)
                {
                    this->pixels[start + i] = color;
                }
            }
        }

        void FillRect(int x, int y, int w, int h, ColorFunction colorFun)
        {
            int x0 = std::max(x, 0);
            int y0 = std::max(y, 0);
            int x1 = std::min(this->width, x + w);
            int y1 = std::min(this->height, y + h);

            for(int j = y0; j < y1; ++j)
            {
                int start = j * this->width;

                for(int i = x0; i < x1; ++i)
                {
                    std::uint8_t c = colorFun(i, j);
                    this->pixels[start + i] = {c, c, c};
                }
            }
        }

        const Color& GetPixel(int x, int y) const
        {
            return pixels[y * this->width + x];
        }

        int GetWidth() const
        {
            return this->width;
        }

        int GetHeight() const
        {
            return this->height;
        }

        const std::vector<Color>& GetData() const
        {
            return this->pixels;
        }

    private:
        int width;
        int height;
        std::vector<Color> pixels;
    };
}
#endif // PLANETED_PIXELMAP_H
