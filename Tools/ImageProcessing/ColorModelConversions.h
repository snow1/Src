/**
 * @file ColorModelConversions.h
 *
 * Declaration and implementation of class ColorModelConversions.
 */

#pragma once

#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "Tools/Math/BHMath.h"

/**
 * A class that defines static conversions between color models for single pixels.
 */
namespace ColorModelConversions
{
  /*
   Coefficients for the YUV <-> RGB conversions.
   These are taken from the possible output formats of the NAO's cameras.
   (see http://www.onsemi.com/pub_link/Collateral/MT9M114-D.PDF, page 41)
   */
  constexpr static float yCoeffR = 0.299f; // BT 601-YUV: 0.299f; sRGB-YCbCr: 0.2126f
  constexpr static float yCoeffG = 0.587f; // BT 601-YUV: 0.587f; sRGB-YCbCr: 0.7152f
  constexpr static float yCoeffB = 0.114f; // BT 601-YUV: 0.114f; sRGB-YCbCr: 0.0722f

  constexpr static float uCoeff = 0.564f;  // BT 601-YUV: 0.564f; sRGB-YCbCr: 0.5389f
  constexpr static float vCoeff = 0.713f;  // BT 601-YUV: 0.713f; sRGB-YCbCr: 0.635f

  constexpr static int scaleExponent = 16;

  constexpr static int scaledYCoeffR = static_cast<int>(yCoeffR * static_cast<float>(1 << scaleExponent));
  constexpr static int scaledYCoeffG = static_cast<int>(yCoeffG * static_cast<float>(1 << scaleExponent));
  constexpr static int scaledYCoeffB = static_cast<int>(yCoeffB * static_cast<float>(1 << scaleExponent));

  constexpr static int scaledUCoeff = static_cast<int>(uCoeff * static_cast<float>(1 << scaleExponent));
  constexpr static int scaledVCoeff = static_cast<int>(vCoeff * static_cast<float>(1 << scaleExponent));
  constexpr static int scaledInvUCoeff = static_cast<int>(static_cast<float>(1 << scaleExponent) / uCoeff);
  constexpr static int scaledInvVCoeff = static_cast<int>(static_cast<float>(1 << scaleExponent) / vCoeff);

  constexpr static int scaledGCoeffU = static_cast<int>(yCoeffB / (yCoeffG* uCoeff) * static_cast<float>(1 << scaleExponent));
  constexpr static int scaledGCoeffV = static_cast<int>(yCoeffR / (yCoeffG* vCoeff) * static_cast<float>(1 << scaleExponent));

  /**
   * Converts an YUV pixel into an RGB pixel.
   * @param Y The Y channel of the source pixel.
   * @param U The U channel of the source pixel.
   * @param V The V channel of the source pixel.
   * @param R The R channel of the target pixel.
   * @param G The G channel of the target pixel.
   * @param B The B channel of the target pixel.
   */
  inline void fromYUVToRGB(const unsigned char Y,
                           const unsigned char U,
                           const unsigned char V,
                           unsigned char& R,
                           unsigned char& G,
                           unsigned char& B)
  {
    const int u = U - 128;
    const int v = V - 128;
    const int b = Y + ((u * scaledInvUCoeff) >> scaleExponent);
    const int g = Y - ((u * scaledGCoeffU + v * scaledGCoeffV) >> scaleExponent);
    const int r = Y + ((v * scaledInvVCoeff) >> scaleExponent);

    R = r < 0 ? 0 : (r > 255 ? 255 : static_cast<unsigned char>(r));
    G = g < 0 ? 0 : (g > 255 ? 255 : static_cast<unsigned char>(g));
    B = b < 0 ? 0 : (b > 255 ? 255 : static_cast<unsigned char>(b));
  }

  /**
   * Converts an RGB pixel into an YUV pixel.
   * @param R The R channel of the source pixel.
   * @param G The G channel of the source pixel.
   * @param B The B channel of the source pixel.
   * @param Y The Y channel of the target pixel.
   * @param U The U channel of the target pixel.
   * @param V The V channel of the target pixel.
   */
  inline void fromRGBToYUV(const unsigned char R,
                           const unsigned char G,
                           const unsigned char B,
                           unsigned char& Y,
                           unsigned char& U,
                           unsigned char& V)
  {
    const int y = (scaledYCoeffR * R + scaledYCoeffG * G + scaledYCoeffB * B) >> scaleExponent;
    const int u = 128 + (((B - y) * scaledUCoeff) >> scaleExponent);
    const int v = 128 + (((R - y) * scaledVCoeff) >> scaleExponent);

    Y = y < 0 ? 0 : (y > 255 ? 255 : static_cast<unsigned char>(y));
    U = u < 0 ? 0 : (u > 255 ? 255 : static_cast<unsigned char>(u));
    V = v < 0 ? 0 : (v > 255 ? 255 : static_cast<unsigned char>(v));
  }

  /**
   * Converts an RGB pixel into an HSI pixel.
   * @param R The R channel of the source pixel.
   * @param G The G channel of the source pixel.
   * @param B The B channel of the source pixel.
   * @param H The H channel of the target pixel.
   * @param S The S channel of the target pixel.
   * @param I The I channel of the target pixel.
   */
  inline void fromRGBToHSI(const unsigned char R,
                           const unsigned char G,
                           const unsigned char B,
                           unsigned char& H,
                           unsigned char& S,
                           unsigned char& I)
  {
    int r = static_cast<int>(R);
    int g = static_cast<int>(G);
    int b = static_cast<int>(B);
    int k = 0;

    if(g < b)
    {
      std::swap(g, b);
      k = -256;
    }

    if(r < g)
    {
      std::swap(r, g);
      k = -85 - k;
    }

    const int chroma = r - std::min(g, b);
    const int h = std::abs(k + ((g - b) << 8) / (chroma ? 6 * chroma : 1));
    const int s = (chroma << 8) / (r ? r : 1);

    H = h > 255 ? 255 : static_cast<unsigned char>(h);
    S = s < 0 ? 0 : (s > 255 ? 255 : static_cast<unsigned char>(s));
    I = r < 0 ? 0 : (r > 255 ? 255 : static_cast<unsigned char>(r));
  }

  /**
   * Converts an HSI pixel into an RGB pixel.
   * @param H The H channel of the source pixel.
   * @param S The S channel of the source pixel.
   * @param I The I channel of the source pixel.
   * @param R The R channel of the target pixel.
   * @param G The G channel of the target pixel.
   * @param B The B channel of the target pixel.
   */
  inline void fromHSIToRGB(const unsigned char H,
                           const unsigned char S,
                           const unsigned char I,
                           unsigned char& R,
                           unsigned char& G,
                           unsigned char& B)
  {
    float h = 1.f - H / 255.f;
    const float s = S / 255.f;
    float r, g, b;

    if(h < 1.f / 3.f)
    {
      g = (1 - s) / 3;
      b = (1 + s * std::cos(pi2 * h) / std::cos(pi2 * (1.f / 6.f - h))) / 3.f;
      r = 1 - (g + b);
    }
    else if(h < 2.f / 3.f)
    {
      h -= 1.f / 3.f;
      b = (1 - s) / 3;
      r = (1 + s * std::cos(pi2 * h) / std::cos(pi2 * (1.f / 6.f - h))) / 3.f;
      g = 1 - (b + r);
    }
    else
    {
      h -= 2.f / 3.f;
      r = (1 - s) / 3;
      g = (1 + s * std::cos(pi2 * h) / std::cos(pi2 * (1.f / 6.f - h))) / 3.f;
      b = 1 - (r + g);
    }

    r *= I * 3;
    g *= I * 3;
    b *= I * 3;

    R = r > 255.f ? 255 : static_cast<unsigned char>(r);
    G = g > 255.f ? 255 : static_cast<unsigned char>(g);
    B = b > 255.f ? 255 : static_cast<unsigned char>(b);
  }

  /**
  * Converts an YUV pixel into an HSI pixel.
  * @param Y The Y channel of the source pixel.
  * @param U The U channel of the source pixel.
  * @param V The V channel of the source pixel.
  * @param H The H channel of the target pixel.
  * @param S The S channel of the target pixel.
  * @param I The I channel of the target pixel.
  */
  inline void fromYUVToHSI(const unsigned char Y,
                           const unsigned char U,
                           const unsigned char V,
                           unsigned char& H,
                           unsigned char& S,
                           unsigned char& I)
  {
    unsigned char r, g, b;
    fromYUVToRGB(Y, U, V, r, g, b);
    fromRGBToHSI(r, g, b, H, S, I);
  }

  /**
  * Converts an HSI pixel into an YUV pixel.
  * @param H The H channel of the source pixel.
  * @param S The S channel of the source pixel.
  * @param I The I channel of the source pixel.
  * @param Y The Y channel of the target pixel.
  * @param U The U channel of the target pixel.
  * @param V The V channel of the target pixel.
  */
  inline void fromHSIToYUV(const unsigned char H,
                           const unsigned char S,
                           const unsigned char I,
                           unsigned char& Y,
                           unsigned char& U,
                           unsigned char& V)
  {
    unsigned char r, g, b;
    fromHSIToRGB(H, S, I, r, g, b);
    fromRGBToYUV(r, g, b, Y, U, V);
  }



  /*new add!!!*/

  static void fromYCbCrToRGB(unsigned char Y,
	  unsigned char Cb,
	  unsigned char Cr,
	  unsigned char& R,
	  unsigned char& G,
	  unsigned char& B)
  {
	  int r = Y + ((1436 * (Cr - 128)) >> 10),
		  g = Y - ((354 * (Cb - 128) + 732 * (Cr - 128)) >> 10),
		  b = Y + ((1814 * (Cb - 128)) >> 10);
	  if (r < 0) r = 0;
	  else if (r > 255) r = 255;
	  if (g < 0) g = 0;
	  else if (g > 255) g = 255;
	  if (b < 0) b = 0;
	  else if (b > 255) b = 255;
	  R = static_cast<unsigned char>(r);
	  G = static_cast<unsigned char>(g);
	  B = static_cast<unsigned char>(b);
  }

  /** Converts an RGB pixel into an YCbCr pixel.
  *  @param R The R channel of the source pixel.
  *  @param G The G channel of the source pixel.
  *  @param B The B channel of the source pixel.
  *  @param Y The Y channel of the target pixel.
  *  @param Cb The Cb channel of the target pixel.
  *  @param Cr The Cr channel of the target pixel.
  */
  static void fromRGBToYCbCr(unsigned char R,
	  unsigned char G,
	  unsigned char B,
	  unsigned char& Y,
	  unsigned char& Cb,
	  unsigned char& Cr)
  {
	  int y = (int)(0.2990 * R + 0.5870 * G + 0.1140 * B),
		  cb = 127 + (int)(-0.1687 * R - 0.3313 * G + 0.5000 * B),
		  cr = 127 + (int)(0.5000 * R - 0.4187 * G - 0.0813 * B);
	  if (y < 0) y = 0;
	  else if (y > 255) y = 255;
	  if (cb < 0) cb = 0;
	  else if (cb > 255) cb = 255;
	  if (cr < 0) cr = 0;
	  else if (cr > 255) cr = 255;
	  Y = static_cast<unsigned char>(y);
	  Cb = static_cast<unsigned char>(cb);
	  Cr = static_cast<unsigned char>(cr);
  }

  /** Converts an YCbCr pixel into an HSI pixel.
  *  @param Y The Y channel of the source pixel.
  *  @param Cb The Cb channel of the source pixel.
  *  @param Cr The Cr channel of the source pixel.
  *  @param H The H channel of the target pixel.
  *  @param S The S channel of the target pixel.
  *  @param I The I channel of the target pixel.
  */
  static void fromYCbCrToHSI(unsigned char Y,
	  unsigned char Cb,
	  unsigned char Cr,
	  unsigned char& H,
	  unsigned char& S,
	  unsigned char& I)
  {
	  int r = Y + ((1436 * (Cr - 128)) >> 10);
	  int g = Y - ((354 * (Cb - 128) + 732 * (Cr - 128)) >> 10);
	  int b = Y + ((1814 * (Cb - 128)) >> 10);
	  int k = 0;

	  if (g < b)
	  {
		  std::swap(g, b);
		  k = -256;
	  }

	  if (r < g)
	  {
		  std::swap(r, g);
		  k = -85 - k;
	  }

	  int chroma = r - std::min(g, b);
	  int h = std::abs(k + ((g - b) << 8) / (chroma ? 6 * chroma : 1));
	  int s = (chroma << 8) / (r ? r : 1);

	  // normalize values to their boundaries
	  H = static_cast<unsigned char>(std::min(255, h));
	  S = static_cast<unsigned char>(std::max(0, std::min(255, s)));
	  I = static_cast<unsigned char>(std::max(0, std::min(255, r)));
  }

  /** Converts an HSI pixel into an YCbCr pixel.
  *  @param H The H channel of the source pixel.
  *  @param S The S channel of the source pixel.
  *  @param I The I channel of the source pixel.
  *  @param Y The Y channel of the target pixel.
  *  @param Cb The Cb channel of the target pixel.
  *  @param Cr The Cr channel of the target pixel.
  */
  static void fromHSIToYCbCr(unsigned char H,
	  unsigned char S,
	  unsigned char I,
	  unsigned char& Y,
	  unsigned char& Cb,
	  unsigned char& Cr)
  {
	  float h = 1.0f - H / 255.0f,
		  s = S / 255.0f,
		  r,
		  g,
		  b;

	  if (h < 1.0f / 3.0f)
	  {
		  g = (1 - s) / 3;
		  b = (1 + s * std::cos(pi2 * h) / std::cos(pi2 * (1.0f / 6.0f - h))) / 3.0f;
		  r = 1 - (g + b);
	  }
	  else if (h < 2.0f / 3.0f)
	  {
		  h -= 1.0f / 3.0f;
		  b = (1 - s) / 3;
		  r = (1 + s * std::cos(pi2 * h) / std::cos(pi2 * (1.0f / 6.0f - h))) / 3.0f;
		  g = 1 - (b + r);
	  }
	  else
	  {
		  h -= 2.0f / 3.0f;
		  r = (1 - s) / 3;
		  g = (1 + s * std::cos(pi2 * h) / std::cos(pi2 * (1.0f / 6.0f - h))) / 3.0f;
		  b = 1 - (r + g);
	  }

	  r *= I * 3;
	  g *= I * 3;
	  b *= I * 3;
	  if (r > 255)
		  r = 255;
	  if (g > 255)
		  g = 255;
	  if (b > 255)
		  b = 255;

	  fromRGBToYCbCr(static_cast<unsigned char>(r),
		  static_cast<unsigned char>(g),
		  static_cast<unsigned char>(b),
		  Y, Cb, Cr);
  }
};
