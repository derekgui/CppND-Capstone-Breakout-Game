#ifndef COLORS_H
#define COLORS_H

class Color
{
public:
    unsigned int dword;

public:
    constexpr Color() : dword() {}
    constexpr Color(const Color &col)
        : dword(col.dword)
    {
    }
    constexpr Color(unsigned int dw)
        : dword(dw)
    {
    }
    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char x)
        : dword((x << 24u) | (r << 16u) | (g << 8u) | b)
    {
    }
    constexpr Color(unsigned char r, unsigned char g, unsigned char b)
        : dword((r << 16u) | (g << 8u) | b)
    {
    }
    constexpr Color(Color col, unsigned char x)
        : Color((x << 24u) | col.dword)
    {
    }
    Color &operator=(Color color)
    {
        dword = color.dword;
        return *this;
    }
    bool operator==(const Color &rhs) const
    {
        return dword == rhs.dword;
    }
    bool operator!=(const Color &rhs) const
    {
        return !(*this == rhs);
    }
    constexpr unsigned char GetX() const
    {
        return dword >> 24u;
    }
    constexpr unsigned char GetA() const
    {
        return GetX();
    }
    constexpr unsigned char GetR() const
    {
        return (dword >> 16u) & 0xFFu;
    }
    constexpr unsigned char GetG() const
    {
        return (dword >> 8u) & 0xFFu;
    }
    constexpr unsigned char GetB() const
    {
        return dword & 0xFFu;
    }
    void SetX(unsigned char x)
    {
        dword = (dword & 0xFFFFFFu) | (x << 24u);
    }
    void SetA(unsigned char a)
    {
        SetX(a);
    }
    void SetR(unsigned char r)
    {
        dword = (dword & 0xFF00FFFFu) | (r << 16u);
    }
    void SetG(unsigned char g)
    {
        dword = (dword & 0xFFFF00FFu) | (g << 8u);
    }
    void SetB(unsigned char b)
    {
        dword = (dword & 0xFFFFFF00u) | b;
    }
};

namespace Colors
{
static constexpr Color MakeRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) | (r << 16) | (g << 8) | b;
}
static constexpr Color White = MakeRGB(255u, 255u, 255u, 255u);
static constexpr Color Black = MakeRGB(30u, 30u, 30u, 255u);
static constexpr Color Gray = MakeRGB(0x80u, 0x80u, 0x80u, 255u);
static constexpr Color LightGray = MakeRGB(0xD3u, 0xD3u, 0xD3u, 255u);
static constexpr Color Red = MakeRGB(255u, 0u, 0u, 255u);
static constexpr Color Green = MakeRGB(0u, 255u, 0u, 255u);
static constexpr Color Blue = MakeRGB(0u, 0u, 255u, 255u);
static constexpr Color Yellow = MakeRGB(255u, 255u, 0u, 255u);
static constexpr Color Orange = MakeRGB(255u, 165u, 0u, 255u);
static constexpr Color Magenta = MakeRGB(255u, 0u, 255u, 255u);
} // namespace Colors

#endif