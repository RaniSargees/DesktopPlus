//This is pretty much a straight adaption of Dear ImGui's internal ImRect class

#pragma once

#include "Util.h"
#include "Vectors.h"

// 2D axis aligned bounding-box
class DPRect
{
public:
    Vector2Int      Min;    // Upper-left
    Vector2Int      Max;    // Lower-right

    DPRect()                                             : Min(0.0f, 0.0f), Max(0.0f, 0.0f) {}
    DPRect(const Vector2Int& min, const Vector2Int& max) : Min(min), Max(max)               {}
    DPRect(int x1, int y1, int x2, int y2)               : Min(x1, y1), Max(x2, y2)         {}

    Vector2Int  GetCenter() const                   { return Vector2Int((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f); }
    Vector2Int  GetSize() const                     { return Vector2Int(Max.x - Min.x, Max.y - Min.y); }
    int         GetWidth() const                    { return Max.x - Min.x; }
    int         GetHeight() const                   { return Max.y - Min.y; }
    Vector2Int  GetTL() const                       { return Min; }                      // Top-left
    Vector2Int  GetTR() const                       { return Vector2Int(Max.x, Min.y); } // Top-right
    Vector2Int  GetBL() const                       { return Vector2Int(Min.x, Max.y); } // Bottom-left
    Vector2Int  GetBR() const                       { return Max; }                      // Bottom-right
    bool        Contains(const Vector2Int& p) const { return p.x     >= Min.x && p.y     >= Min.y && p.x     <  Max.x && p.y     <  Max.y; }
    bool        Contains(const DPRect& r) const     { return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x <= Max.x && r.Max.y <= Max.y; }
    bool        Overlaps(const DPRect& r) const     { return r.Min.y <  Max.y && r.Max.y >  Min.y && r.Min.x <  Max.x && r.Max.x >  Min.x; }
    void        Add(const Vector2Int& p)            { if (Min.x > p.x)     Min.x = p.x;     if (Min.y > p.y)     Min.y = p.y;     if (Max.x < p.x)     Max.x = p.x;     if (Max.y < p.y)     Max.y = p.y; }
    void        Add(const DPRect& r)                { if (Min.x > r.Min.x) Min.x = r.Min.x; if (Min.y > r.Min.y) Min.y = r.Min.y; if (Max.x < r.Max.x) Max.x = r.Max.x; if (Max.y < r.Max.y) Max.y = r.Max.y; }
    void        Expand(const int amount)            { Min.x -= amount;   Min.y -= amount;   Max.x += amount;   Max.y += amount; }
    void        Expand(const Vector2Int& amount)    { Min.x -= amount.x; Min.y -= amount.y; Max.x += amount.x; Max.y += amount.y; }
    void        Translate(const Vector2Int& d)      { Min.x += d.x; Min.y += d.y; Max.x += d.x; Max.y += d.y; }
    void        TranslateX(int dx)                  { Min.x += dx; Max.x += dx; }
    void        TranslateY(int dy)                  { Min.y += dy; Max.y += dy; }
    void        ClipWith(const DPRect& r)           { Min = Vector2Int::vec_max(Min, r.Min); Max = Vector2Int::vec_min(Max, r.Max); }         // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.
    void        ClipWithFull(const DPRect& r)       { Min = Vector2Int::vec_clamp(Min, r.Min, r.Max); Max = Vector2Int::vec_clamp(Max, r.Min, r.Max); } // Full version, ensure both points are fully clipped.
    bool        IsInverted() const                  { return Min.x > Max.x || Min.y > Max.y; }

    bool        operator==(const DPRect& r) const   { return r.Min == Min && r.Max == Max; }
};