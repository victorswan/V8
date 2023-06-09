// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef BASE_GFX_SKIA_UTILS_MAC_H__
#define BASE_GFX_SKIA_UTILS_MAC_H__

#include "SkColor.h"
#include <CoreGraphics/CGColor.h>

struct SkMatrix;
struct SkIRect;
struct SkPoint;
struct SkRect;

namespace gfx {

// Converts a Skia point to a CoreGraphics CGPoint.
// Both use same in-memory format.
inline const CGPoint& SkPointToCGPoint(const SkPoint& point) {
  return reinterpret_cast<const CGPoint&>(point);
}

// Converts a CoreGraphics point to a Skia CGPoint.
// Both use same in-memory format.
inline const SkPoint& CGPointToSkPoint(const CGPoint& point) {
  return reinterpret_cast<const SkPoint&>(point);
}

// Matrix converters.
CGAffineTransform SkMatrixToCGAffineTransform(const SkMatrix& matrix);
  
// Rectangle converters.
SkRect CGRectToSkRect(const CGRect& rect);
SkIRect CGRectToSkIRect(const CGRect& rect);

// Converts a Skia rect to a CoreGraphics CGRect.
CGRect SkIRectToCGRect(const SkIRect& rect);
CGRect SkRectToCGRect(const SkRect& rect);

// Converts CGColorRef to the ARGB layout Skia expects.
SkColor CGColorRefToSkColor(CGColorRef color);

// Converts ARGB to CGColorRef.
CGColorRef SkColorToCGColorRef(SkColor color);

}  // namespace gfx

#endif

