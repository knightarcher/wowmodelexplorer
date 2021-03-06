#pragma once

#include "IFTFont.h"
#include "S3DVertex.h"
#include <vector>
#include <unordered_map>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H

class CFontServices;
class CFTGlyphCache;
struct S2DBlendParam;

class CFTFont : public IFTFont
{
public:
	CFTFont(const char* faceName, int faceIndex, u32 size, int fontStyle, int outlineWidth);
	~CFTFont();

public:
	virtual void drawA(const char* text, SColor color, vector2di position, int nCharCount = -1, recti* pClip = nullptr);
	virtual void drawW(const c16* text, SColor color, vector2di position, int nCharCount = -1, recti* pClip = nullptr);
	virtual void addTextA(const char* text, SColor color, vector2di position, int nCharCount = -1, recti* pClip = nullptr, bool bVertical = false);
	virtual void addTextW(const c16* text, SColor color, vector2di position, int nCharCount = -1, recti* pClip = nullptr, bool bVertical = false);
	virtual void flushText();

	virtual dimension2du getTextExtent(const char* utf8text, int nCharCount = -1, bool vertical = false);	
	virtual dimension2du getWTextExtent(const c16* text, int nCharCount = -1, bool vertical = false) ;	
	virtual dimension2du getWCharExtent(c16 ch, bool vertical = false);
	virtual int GetTextWCount(const char* utf8text) const;

	FT_BitmapGlyph getCharExtent(u32 ch, int& offsetX, int& offsetY, int& chWidth, int& chHeight, int& chBmpW, int& chBmpH);
	const SCharInfo* getCharInfo(c16 ch) const;
	const SCharInfo* addChar(c16 ch);	
	ITexture* getTexture(u32 idx);
	u32 getTextureCount() const { return (u32)FontTextures.size(); }

public:
	bool init();

	int GetUnicodeCMapIndex(FT_Face ftFace);
	My_FaceID GetMyFaceID() { return MyFaceID; }
	FTC_Scaler GetFTCScaler() { return FTCScaler; }
	FT_Face GetFTFace();
	FT_Size GetFTSize();
	FT_Pos GetBoldWidth(){ return BoldWidth; }

private:
	struct SDrawText
	{
		u32		offset;
		u32		length;
		SColor color;
		vector2di position;
		recti		rcClip;
		bool		bClip;
		bool		bVertical;
		//TODO underline
	};

private:
	bool addFontTexture();
	FT_BitmapGlyph RenderChar(u32 ch);
	void drawTextWBatch();

	void drawText(const SDrawText& d, const c16* txt, float fInv, const S2DBlendParam& blendParam);
	void drawTextVertical(const SDrawText& d, const c16* txt, float fInv, const S2DBlendParam& blendParam);

private:
#ifdef USE_QALLOCATOR
	typedef std::map<c16, SCharInfo, std::less<c16>, qzone_allocator<std::pair<c16, SCharInfo>>>	T_CharacterMap;
#else
	typedef std::unordered_map<c16, SCharInfo>	T_CharacterMap;
#endif

	T_CharacterMap		CharacterMap;

private:
	CFontServices*		FontServices;
	CFTGlyphCache*		MyFTGlyphCache;

	My_FaceID	MyFaceID;
	FTC_Scaler	FTCScaler;
	FT_Pos		BoldWidth;
	int		UnicodeCMapIndex;

	int		Ascender;				//overhang
	int		Descender;			//underhang

	std::vector<ITexture*>			FontTextures;

	int	NextX;
	int  NextY;
	int  CurrentX;
	int  CurrentY;
	int  MaxY;

	//
	std::vector<c16>		Texts;
	std::vector<SDrawText>	DrawTexts;
};